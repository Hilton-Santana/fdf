/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsouza-s <hsouza-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:45:55 by hsouza-s          #+#    #+#             */
/*   Updated: 2024/07/17 14:35:01 by hsouza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_mouse_up(int press_code, int x, int y, t_canvas *canvas_handle)
{
	int	x_rel;
	int	y_rel;

	x_rel = canvas_handle->m_pos_down.m_x - x;
	y_rel = canvas_handle->m_pos_down.m_y - y;
	if (press_code == 1)
	{
		if (abs(x_rel) > abs(y_rel))
			rotate_y(x_rel / 10, &canvas_handle->m_cam);
		else
			rotate_x(y_rel / 10, &canvas_handle->m_cam);
	}
	else if (press_code == 3)
		translate(x_rel / 15, y_rel / 15, &canvas_handle->m_cam);
	render(canvas_handle);
	return (1);
}

int	on_mouse_down(int press_code, int x, int y, t_canvas *canvas_handle)
{
	canvas_handle->m_pos_down.m_x = x;
	canvas_handle->m_pos_down.m_y = y;
	if (press_code == 4)
	{
		zoom(0.5, &canvas_handle->m_cam);
		render(canvas_handle);
	}
	else if (press_code == 5)
	{
		zoom(-0.5, &canvas_handle->m_cam);
		render(canvas_handle);
	}
	return (1);
}

int	on_destroy(t_canvas *canvas_handle)
{
	mlx_destroy_window(canvas_handle->mlx, canvas_handle->win);
	free(canvas_handle->mlx);
	free_map(canvas_handle);
	exit(EXIT_FAILURE);
	return (1);
}

int	on_key_press(int key, t_canvas *canvas_handle)
{
	float	radius;

	radius = 1.5 * fmax(canvas_handle->m_map.m_rows,
			canvas_handle->m_map.m_cols) + 5;
	if (key == KEY_R)
	{
		init_cam(&canvas_handle->m_cam, radius);
		render(canvas_handle);
	}
	else if (key == ESCAPE)
		on_destroy(canvas_handle);
	return (1);
}

int	main(int argc, char **argv)
{
	t_canvas	canvas_handle;

	if (argc == 2)
		read_args(argv[1], &canvas_handle.m_map);
	else
		msg_error("The argument should be only a regular grid\n");
	canvas_handle.mlx = mlx_init();
	canvas_handle.win = mlx_new_window(canvas_handle.mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "first windown");
	init_cam(&canvas_handle.m_cam, 1.5
		* fmax(canvas_handle.m_map.m_rows, canvas_handle.m_map.m_cols) + 5);
	render(&canvas_handle);
	mlx_hook(canvas_handle.win, BUTTONPRESS,
		BUTTONPRESSMASK, &on_mouse_down, &canvas_handle);
	mlx_hook(canvas_handle.win, BUTTONSRELEASE,
		BUTTONRELEASEMASK, &on_mouse_up, &canvas_handle);
	mlx_hook(canvas_handle.win, DESTROYNOTIFY, 0, &on_destroy, &canvas_handle);
	mlx_hook(canvas_handle.win, KEYPRESS,
		KEYPRESSMASK, &on_key_press, &canvas_handle);
	mlx_loop(canvas_handle.mlx);
	free(canvas_handle.mlx);
	return (1);
}
