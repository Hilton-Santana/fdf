/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsouza-s <hsouza-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:49:50 by hsouza-s          #+#    #+#             */
/*   Updated: 2023/06/02 18:26:11 by hsouza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_frame_buffer(t_canvas *canvas)
{
	int	i;

	i = 0;
	while (i < canvas->m_map.m_rows)
	{
		free(canvas->m_frame_bf[i]);
		i++;
	}
	free(canvas->m_frame_bf);
}

void	transform_vec(int i, int j, float look_at[4][4], t_canvas *cv_handle)
{
	float	vertex[4];
	t_cam	*cam;
	int		x;
	int		y;

	cam = &cv_handle->m_cam;
	ft_mat4_vec(look_at, cv_handle->m_map.m_pts[i][j].m_vec, vertex);
	vertex[0] = vertex[0] * cam->m_f / vertex[2];
	vertex[1] = vertex[1] * cam->m_f / vertex[2];
	x = (int)((cam->m_w / cam->m_w_wld) * (vertex[0] + cam->m_w_wld / 2));
	y = (int)(-(cam->m_h / cam->m_h_wld) * (vertex[1] - cam->m_h_wld / 2));
	if (x < 0 || y < 0 || x > WINDOW_WIDTH || y > WINDOW_HEIGHT)
	{
		x = INVALID_PIX;
		y = INVALID_PIX;
	}
	cv_handle->m_frame_bf[i][j].m_x = x;
	cv_handle->m_frame_bf[i][j].m_y = y;
	cv_handle->m_frame_bf[i][j].m_color = color_lerp
		(YELLOW, PURPLE, cv_handle->m_map.m_pts[i][j].m_vec[2] / MAX_HEIGHT);
}

void	transform(t_canvas	*cv_handle)
{
	float	look_at[4][4];
	int		i;
	int		j;

	create_look_at(look_at, &cv_handle->m_cam);
	cv_handle->m_frame_bf = (t_pixel **) malloc
		(cv_handle->m_map.m_rows * sizeof(t_pixel *));
	if (!cv_handle->m_frame_bf)
		msg_error("Malloc error");
	i = 0;
	while (i < cv_handle->m_map.m_rows)
	{
		(cv_handle->m_frame_bf)[i] = (t_pixel *) malloc
			(cv_handle->m_map.m_cols * sizeof(t_pixel));
		if (!(cv_handle->m_frame_bf)[i])
			msg_error("Malloc error");
		j = 0;
		while (j < cv_handle->m_map.m_cols)
		{
			transform_vec(i, j, look_at, cv_handle);
			j++;
		}
		i++;
	}
}

void	render(t_canvas *canvas)
{
	canvas->m_img.img_ptr = mlx_new_image
		(canvas->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	canvas->m_img.m_data = mlx_get_data_addr(canvas->m_img.img_ptr,
			&canvas->m_img.bpp, &canvas->m_img.line_len, &canvas->m_img.endian);
	transform(canvas);
	raster(canvas);
	mlx_clear_window(canvas->mlx, canvas->win);
	mlx_put_image_to_window(canvas->mlx, canvas->win,
		canvas->m_img.img_ptr, 0, 0);
	mlx_destroy_image(canvas->mlx, canvas->m_img.img_ptr);
	free_frame_buffer(canvas);
}
