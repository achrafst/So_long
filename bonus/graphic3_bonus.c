/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic3_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 02:31:36 by asettar           #+#    #+#             */
/*   Updated: 2023/03/28 13:04:14 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	valid_enemy_pos(t_vr *vr, int r, int c)
{
	if (r < 0 || r >= vr->map->rows || c < 0
		|| c >= vr->map->cols || vr->map->visited[r][c] == '1')
		return (0);
	if (vr->map->game[r][c] == 'P')
	{
		mlx_clear_window(vr->mlx, vr->win);
		ft_putstr_fd("You Lost, Good Luck Next Time !", 1);
		clean_all(vr, EXIT_SUCCESS);
	}
	else if (vr->map->game[r][c] != '0')
		return (0);
	vr->map->game[r][c] = 'N';
	vr->map->visited[r][c] = '1';
	return (1);
}

void	check_valid_pos(t_vr *vr, int i, int j)
{
	if (valid_enemy_pos(vr, i, j + 1) || valid_enemy_pos(vr, i, j - 1)
		|| valid_enemy_pos(vr, i + 1, j) || valid_enemy_pos(vr, i - 1, j))
	{
		vr->map->game[i][j] = '0';
		mlx_clear_window(vr->mlx, vr->win);
		put_images_to_window(vr, vr->map);
	}
}

int	make_animation(t_vr *vr)
{
	static int	n = 0;
	int			i;
	int			j;
	int			k;

	if (n == 20000)
	{
		n = 0;
		i = -1;
		k = -1;
		while (++k < vr->map->rows)
			ft_memset(vr->map->visited[k], '0', vr->map->cols);
		while (++i < vr->map->rows)
		{
			j = -1;
			while (++j < vr->map->cols)
			{
				if (vr->map->game[i][j] == 'N' && vr->map->visited[i][j] == '0')
					check_valid_pos(vr, i, j);
			}
		}
	}
	n++;
	return (0);
}
