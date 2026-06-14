/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsouza-s <hsouza-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:47:14 by hsouza-s          #+#    #+#             */
/*   Updated: 2023/05/27 18:50:12 by hsouza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->m_data + (y * img->line_len + x * (img->bpp / 8));
	*(int *) pixel = color;
}

void	bresenham_line_xy(t_pixel A, t_pixel B, t_canvas *screen_handle, int dx)
{
	int		x;
	int		y;
	int		error;
	int		inclination;

	inclination = abs(B.m_y - A.m_y) * 2;
	error = 0;
	x = A.m_x;
	y = A.m_y;
	while (x <= B.m_x)
	{
		img_pixel_put(&screen_handle->m_img, x, y,
			color_lerp(A.m_color, B.m_color, (float)(x - A.m_x) / (float)dx));
		error += inclination;
		if (error > dx)
		{
			if (B.m_y > A.m_y)
				y++;
			else
				y--;
			error -= 2 * dx;
		}
		x++;
	}
}

void	bresenham_line_yx(t_pixel A, t_pixel B, t_canvas *screen_handle, int dx)
{
	int		x;
	int		y;
	int		error;
	int		inclination;

	inclination = abs(B.m_y - A.m_y) * 2;
	error = 0;
	x = A.m_x;
	y = A.m_y;
	while (x <= B.m_x)
	{
		img_pixel_put(&screen_handle->m_img, y, x,
			color_lerp(A.m_color, B.m_color, (float)(x - A.m_x) / (float)dx));
		error += inclination;
		if (error > dx)
		{
			if (B.m_y > A.m_y)
				y++;
			else
				y--;
			error -= 2 * dx;
		}
		x++;
	}
}

void	draw_line(t_pixel A, t_pixel B, t_canvas *canvas)
{
	int		is_yx;
	int		dx;

	is_yx = 0;
	if ((abs(B.m_y - A.m_y) > abs(B.m_x - A.m_x)))
	{
		swap_int(&A.m_y, &A.m_x);
		swap_int(&B.m_y, &B.m_x);
		is_yx = 1;
	}
	if (A.m_x > B.m_x)
	{
		swap_int(&A.m_x, &B.m_x);
		swap_int(&A.m_y, &B.m_y);
	}
	dx = B.m_x - A.m_x;
	if (is_yx)
		bresenham_line_yx(A, B, canvas, dx);
	else
		bresenham_line_xy(A, B, canvas, dx);
}

void	raster(t_canvas	*cv)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cv->m_map.m_rows)
	{
		j = -1;
		while (++j < cv->m_map.m_cols - 1)
		{
			if (out(&cv->m_frame_bf[i][j]) || out(&cv->m_frame_bf[i][j + 1]))
				continue ;
			draw_line(cv->m_frame_bf[i][j], cv->m_frame_bf[i][j + 1], cv);
		}
	}
	i = -1;
	while (++i < cv->m_map.m_rows - 1)
	{
		j = -1;
		while (++j < cv->m_map.m_cols)
		{
			if (out(&cv->m_frame_bf[i][j]) || out(&cv->m_frame_bf[i + 1][j]))
				continue ;
			draw_line(cv->m_frame_bf[i][j], cv->m_frame_bf[i + 1][j], cv);
		}
	}
}
