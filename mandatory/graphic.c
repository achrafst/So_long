/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 04:46:52 by asettar           #+#    #+#             */
/*   Updated: 2023/03/28 21:38:30 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	clean_all(t_vr *vr, int type)
{
	clean_exit(vr->map, 0, 3);
	if (vr->img_b)
		mlx_destroy_image(vr->mlx, vr->img_b);
	if (vr->img_pr)
		mlx_destroy_image(vr->mlx, vr->img_pr);
	if (vr->img_pl)
		mlx_destroy_image(vr->mlx, vr->img_pl);
	if (vr->img_c)
		mlx_destroy_image(vr->mlx, vr->img_c);
	if (vr->img_e)
		mlx_destroy_image(vr->mlx, vr->img_e);
	if (vr->img_w)
		mlx_destroy_image(vr->mlx, vr->img_w);
	if (vr->win)
		mlx_destroy_window(vr->mlx, vr->win);
	if (vr->mlx)
		free(vr->mlx);
	free(vr);
	if (type == EXIT_FAILURE)
		ft_putstr_fd("ERROR\nMEMORY ALLOCATION FAILURE\n", 2);
	exit(type);
}

void	put_to_window(t_vr *vr, t_map *map, int i, int j)
{
	int	x;
	int	y;

	x = j * WT;
	y = i * HT;
	if (map->game[i][j] == '1')
		mlx_put_image_to_window(vr->mlx, vr->win, vr->img_w, x, y);
	if (map->game[i][j] == '0')
		mlx_put_image_to_window(vr->mlx, vr->win, vr->img_b, x, y);
	if (map->game[i][j] == 'C')
		mlx_put_image_to_window(vr->mlx, vr->win, vr->img_c, x, y);
	if (map->game[i][j] == 'E')
		mlx_put_image_to_window(vr->mlx, vr->win, vr->img_e, x, y);
	if (map->game[i][j] == 'P')
	{
		if (map->moving_left)
			mlx_put_image_to_window(vr->mlx, vr->win, vr->img_pl, x, y);
		else
			mlx_put_image_to_window(vr->mlx, vr->win, vr->img_pr, x, y);
	}
}

void	put_images_to_window(t_vr *vr, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
			put_to_window(vr, map, i, j);
	}
}

void	graphic_handle(t_map *map)
{
	t_vr	*vr;

	vr = (t_vr *)malloc(sizeof(t_vr));
	if (!vr)
		clean_exit(map, ALLOCATION_FAILURE, EXIT_FAILURE);
	ft_memset(vr, 0, sizeof(t_vr));
	vr->map = map;
	vr->mlx = mlx_init();
	if (!vr->mlx)
		clean_all(vr, EXIT_FAILURE);
	get_images(vr, map);
	put_images_to_window(vr, map);
	mlx_hook(vr->win, 02, 1L << 0, handle, vr);
	mlx_hook(vr->win, 17, 1L << 17, handle2, vr);
	mlx_loop(vr->mlx);
}
