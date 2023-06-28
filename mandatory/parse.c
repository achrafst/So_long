/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:54:56 by asettar           #+#    #+#             */
/*   Updated: 2023/03/28 21:37:27 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	allocate_memory(t_map *map, char *line)
{
	map->cols = ft_len(line, map);
	map->first_line = (char *)malloc(map->cols + 1);
	if (!map->first_line)
		clean_exit(map, ALLOCATION_FAILURE, EXIT_FAILURE);
	map->last_line = (char *)malloc(map->cols + 1);
	if (!map->last_line)
		clean_exit(map, ALLOCATION_FAILURE, EXIT_FAILURE);
	map->first_line[map->cols] = 0;
	map->last_line[map->cols] = 0;
	ft_memcpy(map->first_line, line, map->cols);
}

void	check_line_errors(char *line, t_map *map)
{
	int			i;

	if (!line)
	{
		if (map->cnt_e != 1 || map->cnt_p != 1 || map->cnt_c < 1)
			clean_exit(map, INVALID_MAP, EXIT_FAILURE);
		return ;
	}
	if (ft_len(line, map) != map->cols || map->cnt_e > 1 || map->cnt_p > 1)
		clean_exit(map, INVALID_MAP, EXIT_FAILURE);
	i = -1;
	while (++i < map->cols)
	{
		if (i == 0 || i == map->cols - 1)
		{
			if (line[i] != '1')
				clean_exit(map, INVALID_MAP, EXIT_FAILURE);
		}
		if (line[i] != '1' && line[i] != 'E' && line[i] != 'C'
			&& line[i] != '0' && line[i] != 'P')
			clean_exit(map, INVALID_MAP, EXIT_FAILURE);
		map->cnt_e += (line[i] == 'E');
		map->cnt_p += (line[i] == 'P');
		map->cnt_c += (line[i] == 'C');
	}
}

void	parse_file(t_map *map, int fd)
{
	char	*line;

	ft_memset(map, 0, sizeof(t_map));
	line = get_next_line(fd);
	if (!line)
		clean_exit(map, ALLOCATION_FAILURE, EXIT_FAILURE);
	allocate_memory(map, line);
	while (line != NULL)
	{
		check_line_errors(line, map);
		map->total = ft_strrjoin(line, map->total);
		if (!map->total)
			clean_exit(map, ALLOCATION_FAILURE, EXIT_FAILURE);
		ft_memcpy(map->last_line, line, map->cols);
		map->rows++;
		free(line);
		line = get_next_line(fd);
	}
	check_line_errors(line, map);
	if (map->rows <= 2 || check_ones(map->first_line, map->last_line))
		clean_exit(map, ALLOCATION_FAILURE, EXIT_FAILURE);
	map->game = ft_split(map->total, '\n');
	if (!map->game)
		clean_exit(map, ALLOCATION_FAILURE, EXIT_FAILURE);
	check_valid_path(map);
}
