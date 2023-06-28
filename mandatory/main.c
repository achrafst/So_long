/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:31:59 by asettar           #+#    #+#             */
/*   Updated: 2023/03/28 21:34:58 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	clean_exit(t_map *map, int n, int type)
{
	if (n == INVALID_MAP)
		ft_putstr_fd("ERROR\nINVALID MAP\n", 2);
	else if (n == ALLOCATION_FAILURE)
		ft_putstr_fd("ERROR\nMEMORY ALLOCATION FAILURE\n", 2);
	if (map->first_line)
		free(map->first_line);
	if (map->last_line)
		free(map->last_line);
	if (map->total)
		free(map->total);
	if (map->game)
		ft_arr_clear(map->game);
	if (map->visited)
		ft_arr_clear(map->visited);
	free(map);
	if (type == EXIT_FAILURE || type == EXIT_SUCCESS)
		exit(type);
}

void	check_args_errors(int ac, char **argv)
{
	if (ac != 2)
	{
		ft_putstr_fd("ERROR\nINVALID NUMBER OF ARGUMENTS", 2);
		exit(1);
	}
	else if (ft_strlen(argv[1]) < 4
		|| ft_strncmp(".ber", argv[1] + ft_strlen(argv[1]) - 4, 4) != 0)
	{
		ft_putstr_fd("ERROR\nTHE FILE FORMAT SHOULD BE .ber", 2);
		exit(1);
	}
}

int	main(int ac, char **argv)
{
	t_map	*map;
	int		fd;

	check_args_errors(ac, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("ERROR\n");
		exit(1);
	}
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
	{
		perror("ERROR\n");
		exit(1);
	}
	parse_file(map, fd);
	close(fd);
	graphic_handle(map);
}
