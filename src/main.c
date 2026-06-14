/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsouza-s <hsouza-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:45:55 by hsouza-s          #+#    #+#             */
/*   Updated: 2026/06/14 00:00:00 by hsouza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	cleanup(t_canvas *canvas)
{
	if (canvas->m_img.img_ptr)
		mlx_delete_image(canvas->mlx, canvas->m_img.img_ptr);
	if (canvas->mlx)
		mlx_terminate(canvas->mlx);
	free_map(canvas);
}

void	on_scroll(double xdelta, double ydelta, void *param)
{
	t_canvas	*canvas;

	(void)xdelta;
	canvas = (t_canvas *)param;
	if (ydelta > 0)
		zoom(0.5, &canvas->m_cam);
	else if (ydelta < 0)
		zoom(-0.5, &canvas->m_cam);
	render(canvas);
}

void	on_mouse(mouse_key_t button, action_t action, modifier_key_t mods,
	void *param)
{
	t_canvas	*canvas;
	int32_t		x;
	int32_t		y;
	int			x_rel;
	int			y_rel;

	(void)mods;
	canvas = (t_canvas *)param;
	mlx_get_mouse_pos(canvas->mlx, &x, &y);
	if (action == MLX_PRESS)
	{
		canvas->m_pos_down.m_x = x;
		canvas->m_pos_down.m_y = y;
	}
	else if (action == MLX_RELEASE)
	{
		x_rel = canvas->m_pos_down.m_x - x;
		y_rel = canvas->m_pos_down.m_y - y;
		if (button == MLX_MOUSE_BUTTON_LEFT)
		{
			if (abs(x_rel) > abs(y_rel))
				rotate_y(x_rel / 10, &canvas->m_cam);
			else
				rotate_x(y_rel / 10, &canvas->m_cam);
		}
		else if (button == MLX_MOUSE_BUTTON_RIGHT)
			translate(x_rel / 15, y_rel / 15, &canvas->m_cam);
		render(canvas);
	}
}

void	on_key(mlx_key_data_t keydata, void *param)
{
	t_canvas	*canvas;
	float		radius;

	canvas = (t_canvas *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	radius = 1.5 * fmax(canvas->m_map.m_rows, canvas->m_map.m_cols) + 5;
	if (keydata.key == MLX_KEY_R)
	{
		init_cam(&canvas->m_cam, radius);
		render(canvas);
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(canvas->mlx);
}

int	main(int argc, char **argv)
{
	t_canvas	canvas_handle;

	ft_bzero(&canvas_handle, sizeof(t_canvas));
	if (argc == 2)
		read_args(argv[1], &canvas_handle.m_map);
	else
		msg_error("The argument should be only a regular grid\n");
	canvas_handle.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "fdf", false);
	if (!canvas_handle.mlx)
		msg_error("MLX42 initialization failed\n");
	canvas_handle.m_img.img_ptr = mlx_new_image(canvas_handle.mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!canvas_handle.m_img.img_ptr
		|| mlx_image_to_window(canvas_handle.mlx,
			canvas_handle.m_img.img_ptr, 0, 0) < 0)
		msg_error("MLX42 image initialization failed\n");
	init_cam(&canvas_handle.m_cam, 1.5
		* fmax(canvas_handle.m_map.m_rows, canvas_handle.m_map.m_cols) + 5);
	render(&canvas_handle);
	mlx_mouse_hook(canvas_handle.mlx, &on_mouse, &canvas_handle);
	mlx_scroll_hook(canvas_handle.mlx, &on_scroll, &canvas_handle);
	mlx_key_hook(canvas_handle.mlx, &on_key, &canvas_handle);
	mlx_loop(canvas_handle.mlx);
	cleanup(&canvas_handle);
	return (0);
}
