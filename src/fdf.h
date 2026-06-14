/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsouza-s <hsouza-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:53:13 by hsouza-s          #+#    #+#             */
/*   Updated: 2026/06/14 16:26:27 by hsouza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <libft/libft.h>
# include <MLX42/MLX42.h>

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 632
# define YELLOW 0xfdfd96
# define PURPLE 0xb19cd9
# define MAX_HEIGHT 3
# define INVALID_PIX -1 
# define KEY_R 114 // 15 on MAC
# define ESCAPE 53
# define BUTTONPRESS 4
# define BUTTONPRESSMASK 4
# define BUTTONRELEASEMASK 8
# define BUTTONSRELEASE 5
# define DESTROYNOTIFY 17
# define KEYPRESS 2
# define KEYPRESSMASK 1

typedef struct s_img
{
	void	*img_ptr;
	char	*m_data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_vector4
{
	float	m_vec[4];
}	t_vector4;

typedef struct s_map
{
	t_vector4	**m_pts;
	int			m_rows;
	int			m_cols;
	int			m_max_height;
	int			m_min_height;
}	t_map;

typedef struct s_pixel
{
	int	m_x;
	int	m_y;
	int	m_color;
}	t_pixel;

typedef struct s_camera
{
	int		m_w;
	int		m_h;
	float	m_w_wld;
	float	m_h_wld;
	int		m_f;
	float	m_fov;
	float	m_eye[3];
	float	m_up[3];
	float	m_x[3];
	float	m_y[3];
	float	m_z[3];
	float	m_at[3];
}	t_cam;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	t_cam		m_cam;
	t_pixel		**m_frame_bf;
	t_map		m_map;
	t_img		m_img;
	t_pixel		m_pos_down;
}	t_canvas;

int		main(int argc, char **argv);
int		on_mouse_down(int press_code,
			int x, int y, t_canvas *canvas_handle);
int		on_mouse_up(int press_code, int x, int y, t_canvas *canvas_handle);
void	line_of_sight(float az, float el, float radius, float m_eye[3]);
void	init_cam(t_cam *cam, float radius);
void	init_cam_basis(t_cam *cam);
void	create_look_at(float look_at[4][4], t_cam *cam);
int		rgb2hex(int r, int g, int b);
void	hex2rgb(int hex, int *r, int *g, int *b);
int		color_lerp(int color_0, int color_1, float t);
int		is_valid_map(char *filename, const t_map *map);
int		out(const t_pixel *pixel);
void	read_args(char *filename, t_map	*map);
void	raster(t_canvas	*cv);
void	draw_line(t_pixel A, t_pixel B, t_canvas *screen_handle);
void	bresenham_line_yx(t_pixel A, t_pixel B,
			t_canvas *screen_handle, int dx);
void	bresenham_line_xy(t_pixel A, t_pixel B,
			t_canvas *screen_handle, int dx);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	initMatrix(int **matrix, int rows, int cols, t_list *map);
void	transform(t_canvas *canvas);
void	render(t_canvas *canvas_handle);
void	transform(t_canvas	*cv_handle);
void	transform_vec(int i, int j,
			float look_at[4][4], t_canvas *cv_handle);
void	rotate_x(float angle, t_cam *cam);
void	rotate_y(float angle, t_cam *cam);
void	translate(float x, float y, t_cam *cam);
void	zoom(float fac, t_cam *cam);
void	scale_t(float *h, const t_map *map);
void	msg_error(const char *msg);
void	free_frame_buffer(t_canvas *canvas);
void	msg_error(const char *msg);
void	free_map(t_canvas *canvas);
void	alloc_vec(t_map *map, int i);
#endif
