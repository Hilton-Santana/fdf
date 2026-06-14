/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsouza-s <hsouza-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:42:52 by hsouza-s          #+#    #+#             */
/*   Updated: 2023/06/02 18:23:56 by hsouza-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	ft_get_cols(char	*filename)
{
	int		fd;
	char	*line;
	int		cols;
	int		i;

	cols = 0;
	i = 0;
	fd = open(filename, O_RDONLY);
	get_next_line(fd, &line);
	if (!line)
		return (0);
	while (line[i])
	{
		if ((line[i] != ' ' && line[i] != '\n') && (line[i + 1] == ' '
				|| line[i + 1] == '\0' || line[i + 1] == '\n'))
			cols++;
		i++;
	}
	free(line);
	while (get_next_line(fd, &line))
		free(line);
	free(line);
	if (close(fd) == -1)
		msg_error("Cannot close file\n");
	return (cols);
}

static	int	ft_get_rows(char	*filename)
{
	int		fd;
	char	*line;
	int		rows;

	fd = open(filename, O_RDONLY);
	rows = 0;
	while (get_next_line(fd, &line))
	{
		if (!line)
			break ;
		rows++;
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		msg_error("Cannot close file\n");
	return (rows);
}

static void	init_min_max_height(int fd, t_map *map)
{
	int		i;
	int		h;
	char	*line;

	while (get_next_line(fd, &line))
	{
		i = 0;
		while (line[i])
		{
			if (line[i] != ' ')
			{
				h = ft_atoi(&line[i]);
				if (h > map->m_max_height)
					map->m_max_height = h;
				if (h < map->m_min_height)
					map->m_min_height = h;
				while (line[i] && line[i] != ' ' && line[i] != '\n')
					i++;
			}
			i++;
		}
		free(line);
	}
	free(line);
}

void	init_map(int fd, t_map *map)
{
	int		i;
	int		j;
	char	**fields;
	char	*line;

	i = -1;
	while (++i < map->m_rows)
	{
		get_next_line(fd, &line);
		fields = ft_split(line, ' ');
		free (line);
		j = -1;
		alloc_vec(map, i);
		while (++j < map->m_cols)
		{
			map->m_pts[i][j].m_vec[2] = ft_atoi(&fields[j][0]);
			map->m_pts[i][j].m_vec[0] = i - (float) map->m_rows * 0.5;
			map->m_pts[i][j].m_vec[1] = j - (float) map->m_cols * 0.5;
			scale_t(&map->m_pts[i][j].m_vec[2], map);
			map->m_pts[i][j].m_vec[3] = 1.0f;
			free(&fields[j][0]);
		}
		free(fields);
	}
}

void	read_args(char *filename, t_map	*map)
{
	int		fd;

	map->m_max_height = 0;
	map->m_min_height = 0;
	map->m_rows = ft_get_rows(filename);
	map->m_cols = ft_get_cols(filename);
	if (map->m_rows == -1 || map->m_cols == -1)
		msg_error("Non existent map\n");
	if (!is_valid_map(filename, map))
		msg_error("Irregular map\n");
	fd = open(filename, O_RDONLY);
	init_min_max_height(fd, map);
	if (close(fd) == -1)
		msg_error("Cannot close file\n");
	fd = open(filename, O_RDONLY);
	map->m_pts = (t_vector4 **) malloc (map->m_rows * sizeof(t_vector4 *));
	if (!map->m_pts)
		msg_error("Malloc error\n");
	init_map(fd, map);
	if (close(fd) == -1)
		msg_error("Cannot close file\n");
}
