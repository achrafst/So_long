/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 05:12:35 by asettar           #+#    #+#             */
/*   Updated: 2023/03/28 13:08:58 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_images(t_vr *vr, t_map *map)
{
	int	wt;
	int	ht;

	vr->img_b = mlx_xpm_file_to_image(vr->mlx, "textures/Backg.xpm", &wt, &ht);
	vr->img_pr = mlx_xpm_file_to_image(vr->mlx, "textures/Prt.xpm", &wt, &ht);
	vr->img_pl = mlx_xpm_file_to_image(vr->mlx, "textures/Plt.xpm", &wt, &ht);
	vr->img_c = mlx_xpm_file_to_image(vr->mlx, "textures/Coll.xpm", &wt, &ht);
	vr->img_e = mlx_xpm_file_to_image(vr->mlx, "textures/Exit.xpm", &wt, &ht);
	vr->img_w = mlx_xpm_file_to_image(vr->mlx, "textures/Wall.xpm", &wt, &ht);
	vr->win = mlx_new_window(vr->mlx, map->cols * wt, map->rows * ht, "game");
	if (!vr->img_b || !vr->img_c || !vr->img_e || !vr->img_pl
		|| !vr->img_pr || !vr->img_w || !vr->win)
		clean_all(vr, EXIT_FAILURE);
}

int	is_valid(int nr, int nc, t_map *map)
{
	if (nc < 0 || nr < 0 || nc >= map->cols || nr >= map->rows
		|| map->game[nr][nc] == '1')
		return (0);
	if (map->game[nr][nc] == 'E' && map->cnt_c != 0)
		return (0);
	if (map->game[nr][nc] == 'E')
		return (2);
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
	{
		if (key == UP_KEY || key == DOWN_KEY
			|| key == LEFT_KEY || key == RIGHT_KEY)
			ft_printf("%d\n", ++moves);
		mlx_clear_window(vr->mlx, vr->win);
		if (key == EXIT_KEY || valid == 2)
		{
			if (valid == 2)
				ft_putstr_fd("Congrats, You won\n", 2);
			clean_all(vr, EXIT_SUCCESS);
		}
		put_images_to_window(vr, vr->map);
	}
	return (0);
}

int	handle2(t_vr *vr)
{
	mlx_clear_window(vr->mlx, vr->win);
	clean_all(vr, EXIT_SUCCESS);
	return (0);
}
