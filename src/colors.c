/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsouza-s <hsouza-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:40:34 by hsouza-s          #+#    #+#             */
/*   Updated: 2023/05/27 17:01:30 by hsouza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rgb2hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	hex2rgb(int hex, int *r, int *g, int *b)
{
	*r = hex >> 16;
	*g = (hex >> 8) & 0xFF;
	*b = hex & 0xFF;
}

int	color_lerp(int color_0, int color_1, float t)
{
	int	rgb_0[3];
	int	rgb_1[3];
	int	new_color;

	hex2rgb(color_0, (int *)rgb_0, (int *)rgb_0 + 1, (int *)rgb_0 + 2);
	hex2rgb(color_1, (int *)rgb_1, (int *)rgb_1 + 1, (int *)rgb_1 + 2);
	new_color = rgb2hex((float)rgb_0[0] + t * (float)(rgb_1[0] - rgb_0[0]),
			(float)rgb_0[1] + t * (float)(rgb_1[1] - rgb_0[1]),
			(float)rgb_0[2] + t * (float)(rgb_1[2] - rgb_0[2]));
	return (new_color);
}
