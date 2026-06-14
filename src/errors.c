/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsouza-s <hsouza-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:41:51 by hsouza-s          #+#    #+#             */
/*   Updated: 2023/06/02 18:17:17 by hsouza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_valid_map(char *filename, const t_map *map)
{
	int		fd;
	int		col_check;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		i = 0;
		col_check = 0;
		while (line[i])
		{
			if ((line[i] != ' ' && line[i] != '\n') && (line[i + 1] == ' '
					|| line[i + 1] == '\0' || line[i + 1] == '\n'))
				col_check++;
			i++;
		}
		free(line);
		if (col_check != map->m_cols)
			return (0);
	}
	return (1);
}

int	out(const t_pixel *pixel)
{
	if (pixel->m_x == INVALID_PIX || pixel->m_y == INVALID_PIX)
		return (1);
	return (0);
}

void	msg_error(const char *msg)
{
	ft_printf(msg);
	exit(EXIT_FAILURE);
}

void	free_map(t_canvas *canvas)
{
	int	i;

	i = 0;
	while (i < canvas->m_map.m_rows)
	{
		free(canvas->m_map.m_pts[i]);
		i++;
	}
	free(canvas->m_map.m_pts);
}

void	alloc_vec(t_map *map, int i)
{
	(map->m_pts)[i] = (t_vector4 *) malloc
		(map->m_cols * sizeof(t_vector4));
	if (!(map->m_pts[i]))
		msg_error("Malloc error \n");
}
