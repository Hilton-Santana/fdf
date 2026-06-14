/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsouza-s <hsouza-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:45:24 by hsouza-s          #+#    #+#             */
/*   Updated: 2023/05/27 18:47:41 by hsouza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line_of_sight(float az, float el, float radius, float m_eye[3])
{
	m_eye[0] = radius * cos(az) * sin(el);
	m_eye[1] = radius * sin(az) * sin(el);
	m_eye[2] = radius * cos(el);
}

void	init_cam(t_cam *cam, float radius)
{
	cam->m_w = WINDOW_WIDTH;
	cam->m_h = WINDOW_HEIGHT;
	cam->m_f = 1.0f;
	cam->m_fov = M_PI / 2;
	cam->m_w_wld = 2 * cam->m_f * tan(cam->m_fov / 2);
	cam->m_h_wld = cam->m_w_wld * cam->m_h / cam->m_w;
	line_of_sight(M_PI / 6, M_PI / 6, radius, cam->m_eye);
	cam->m_up[0] = 0.0f;
	cam->m_up[1] = 0.0f;
	cam->m_up[2] = 1.0f;
	cam->m_at[0] = 0.0f;
	cam->m_at[1] = 0.0f;
	cam->m_at[2] = 0.0f;
}

void	init_cam_basis(t_cam	*cam)
{
	float	n[3];
	float	at_eye[3];

	at_eye[0] = cam->m_at[0] - cam->m_eye[0];
	at_eye[1] = cam->m_at[1] - cam->m_eye[1];
	at_eye[2] = cam->m_at[2] - cam->m_eye[2];
	ft_normalized(at_eye, cam->m_z);
	ft_cross(cam->m_z, cam->m_up, n);
	ft_normalized(n, cam->m_x);
	ft_cross(cam->m_x, cam->m_z, cam->m_y);
}

void	create_look_at(float look_at[4][4], t_cam *cam)
{
	float	rotation[4][4];
	float	translation[4][4];
	float	neg_eye[3];

	neg_eye[0] = -cam->m_eye[0];
	neg_eye[1] = -cam->m_eye[1];
	neg_eye[2] = -cam->m_eye[2];
	init_cam_basis(cam);
	ft_rot_axes(rotation, cam->m_x, cam->m_y, cam->m_z);
	ft_translation4(translation, neg_eye);
	ft_mat4_mul(rotation, translation, look_at);
}
