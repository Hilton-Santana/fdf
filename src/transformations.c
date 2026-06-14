/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsouza-s <hsouza-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:44:06 by hsouza-s          #+#    #+#             */
/*   Updated: 2023/05/27 19:27:38 by hsouza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(const float angle, t_cam *cam)
{
	float	rotate_x[3][3];
	float	rotate_about_fixed_point[4][4];
	float	temp[4];

	ft_normalize(cam->m_x);
	ft_rot_ax_angle(cam->m_x, angle, rotate_x);
	ft_transform_vec3(rotate_x, cam->m_up);
	ft_rotate_about_fixed_point(cam->m_x, angle,
		cam->m_at, rotate_about_fixed_point);
	temp[0] = cam->m_eye[0];
	temp[1] = cam->m_eye[1];
	temp[2] = cam->m_eye[2];
	temp[3] = 1.0f;
	ft_transform_vec4(rotate_about_fixed_point, temp);
	cam->m_eye[0] = temp[0];
	cam->m_eye[1] = temp[1];
	cam->m_eye[2] = temp[2];
}

void	rotate_y(const float angle, t_cam *cam)
{
	float	rotate_y[3][3];
	float	rotate_about_fixed_point[4][4];
	float	temp[4];

	ft_normalize(cam->m_y);
	ft_rot_ax_angle(cam->m_y, angle, rotate_y);
	ft_transform_vec3(rotate_y, cam->m_up);
	ft_rotate_about_fixed_point(cam->m_y, angle,
		cam->m_at, rotate_about_fixed_point);
	temp[0] = cam->m_eye[0];
	temp[1] = cam->m_eye[1];
	temp[2] = cam->m_eye[2];
	temp[3] = 1.0f;
	ft_transform_vec4(rotate_about_fixed_point, temp);
	cam->m_eye[0] = temp[0];
	cam->m_eye[1] = temp[1];
	cam->m_eye[2] = temp[2];
}

void	translate(float x, float y, t_cam *cam)
{
	cam->m_eye[0] += x * cam->m_x[0] - y * cam->m_y[0];
	cam->m_eye[1] += x * cam->m_x[1] - y * cam->m_y[1];
	cam->m_eye[2] += x * cam->m_x[2] - y * cam->m_y[2];
	cam->m_at[0] += x * cam->m_x[0] - y * cam->m_y[0];
	cam->m_at[1] += x * cam->m_x[1] - y * cam->m_y[1];
	cam->m_at[2] += x * cam->m_x[2] - y * cam->m_y[2];
}

void	zoom(float fac, t_cam *cam)
{
	cam->m_eye[0] += fac * cam->m_z[0];
	cam->m_eye[1] += fac * cam->m_z[1];
	cam->m_eye[2] += fac * cam->m_z[2];
}

void	scale_t(float *h, const t_map *map)
{
	if (map->m_max_height == 0 && map->m_min_height == 0)
	{
		*h = 0.0;
		return ;
	}
	*h = MAX_HEIGHT * (*h - map->m_min_height)
		/ (map->m_max_height - map->m_min_height);
}
