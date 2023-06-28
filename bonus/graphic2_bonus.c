/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 05:12:35 by asettar           #+#    #+#             */
/*   Updated: 2023/03/28 13:03:58 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	is_valid(int nr, int nc, t_map *map)
{
	if (nc < 0 || nr < 0 || nc >= map->cols || nr >= map->rows
		|| map->game[nr][nc] == '1')
		return (0);
	if (map->game[nr][nc] == 'E' && map->cnt_c != 0)
		return (0);
	if (map->game[nr][nc] == 'E')
		return (2);
	if (map->game[nr][nc] == 'N')
		return (3);
	if (map->game[nr][nc] == 'C')
		map->cnt_c -= 1;
	map->game[map->pr_start][map->pc_start] = '0';
	map->game[nr][nc] = 'P';
	if (map->pc_start > nc)
		map->moving_left = 1;
	else
		map->moving_left = 0;
	map->pr_start = nr;
	map->pc_start = nc;
	return (1);
}

void	handle_helper(int key, t_vr *vr, int valid, int *moves)
{
	char	*moves_cnt;

	mlx_clear_window(vr->mlx, vr->win);
	if (key == EXIT_KEY || valid == 2 || valid == 3)
	{
		if (valid == 2)
			ft_putstr_fd("Congrats, You Won!\n", 2);
		else
			ft_putstr_fd("You Lost, Good Luck Next Time.\n", 2);
		clean_all(vr, EXIT_SUCCESS);
	}
	put_images_to_window(vr, vr->map);
	if (key == UP_KEY || key == DOWN_KEY
		|| key == LEFT_KEY || key == RIGHT_KEY)
			*moves += 1;
	moves_cnt = ft_itoa(*moves);
	mlx_string_put(vr->mlx, vr->win, 20, HT * vr->map->rows, L_BLUE, moves_cnt);
	free(moves_cnt);
}

int	handle(int key, t_vr *vr)
{
	int			nr;
	int			nc;
	int			valid;
	static int	moves = 0;

	nr = vr->map->pr_start - (key == UP_KEY) + (key == DOWN_KEY);
	nc = vr->map->pc_start - (key == LEFT_KEY) + (key == RIGHT_KEY);
	valid = is_valid(nr, nc, vr->map);
	if (valid)
		handle_helper(key, vr, valid, &moves);
	return (0);
}

int	handle2(t_vr *vr)
{
	mlx_clear_window(vr->mlx, vr->win);
	clean_all(vr, EXIT_SUCCESS);
	return (0);
}
