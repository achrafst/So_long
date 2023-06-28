/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:25:00 by asettar           #+#    #+#             */
/*   Updated: 2023/03/28 12:03:47 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	valid(t_map *map, int r, int c)
{
	if (r < 0 || r >= map->rows || c < 0 || c >= map->cols
		|| map->game[r][c] == '1' || map->visited[r][c] == '1'
		|| map->game[r][c] == 'N')
		return (0);
	return (1);
}

void	dfs_c(t_map *map, int r, int c, int *collec_num)
{
	int	i;
	int	j;
	int	ans;

	if (*collec_num == 0)
		return ;
	map->visited[r][c] = '1';
	ans = 0;
	*collec_num -= (map->game[r][c] == 'C');
	i = -2;
	while (++i <= 1)
	{
		j = -2;
		while (++j <= 1)
		{
			if (ft_abs(i) != ft_abs(j))
			{
				if (valid(map, r + i, c + j) && map->game[r][c] != 'E' )
					dfs_c(map, r + i, c + j, collec_num);
			}
		}
	}
}

int	dfs_e(t_map *map, int r, int c)
{
	int	i;
	int	j;
	int	ans;

	if (map->game[r][c] == 'E')
		return (1);
	map->visited[r][c] = '1';
	ans = 0;
	i = -2;
	while (++i <= 1)
	{
		j = -2;
		while (++j <= 1)
		{
			if (abs(i) != abs(j))
			{
				if (valid(map, r + i, c + j))
					ans = (ans || dfs_e(map, r + i, c + j));
			}
		}
	}
	return (ans);
}

void	check_path(t_map *map)
{
	int		i;
	int		possible_exit;
	int		collec_num;

	i = -1;
	map->visited = ft_split(map->total, '\n');
	if (!map->visited)
		clean_exit(map, ALLOCATION_FAILURE, EXIT_FAILURE);
	while (++i < map->rows)
		ft_memset(map->visited[i], '0', map->cols);
	collec_num = map->cnt_c;
	dfs_c(map, map->pr_start, map->pc_start, &collec_num);
	if (collec_num != 0)
		clean_exit(map, INVALID_MAP, EXIT_FAILURE);
	i = -1;
	while (++i < map->rows)
		ft_memset(map->visited[i], '0', map->cols);
	possible_exit = dfs_e(map, map->pr_start, map->pc_start);
	if (possible_exit == 0)
		clean_exit(map, INVALID_MAP, EXIT_FAILURE);
}

void	check_valid_path(t_map *map)
{
	int	i;
	int	j;
	int	flg;

	i = -1;
	flg = 1;
	while (map->game[++i] && flg)
	{
		j = -1;
		while (map->game[i][++j])
		{
			if (map->game[i][j] == 'P')
			{
				map->pr_start = i;
				map->pc_start = j;
				flg = 0;
				break ;
			}
		}
	}
	check_path(map);
}
