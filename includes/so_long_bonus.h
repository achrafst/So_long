/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 05:13:39 by asettar           #+#    #+#             */
/*   Updated: 2023/03/28 02:44:58 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft.h"
# include "mlx.h"
# define WT 50
# define HT 50
# define ALLOCATION_FAILURE 2
# define INVALID_MAP 1
# define L_BLUE 65535

typedef struct s_map
{
	char	*first_line;
	char	*last_line;
	char	*total;
	char	**game;
	int		cols;
	int		rows;
	int		pr_start;
	int		pc_start;
	int		cnt_c;
	int		cnt_e;
	int		cnt_p;
	int		cnt_n;
	int		moving_left;
	char	**visited;
}t_map;

typedef struct s_vr
{
	void	*mlx;
	void	*win;
	void	*img_b;
	void	*img_c;
	void	*img_pl;
	void	*img_pr;
	void	*img_w;
	void	*img_e;
	void	*img_n;
	t_map	*map;
}t_vr;

enum e_moves
{
	UP_KEY = 126,
	DOWN_KEY = 125,
	RIGHT_KEY = 124,
	LEFT_KEY = 123,
	EXIT_KEY = 53,
};

void	check_args_errors(int ac, char **argv);
void	clean_exit(t_map *map, int n, int type);
void	ft_initialize(t_map *map);
void	check_line_errors(char *line, t_map *map);
void	parse_file(t_map *map, int fd);
int		ft_len(char *str, t_map *map);
int		check_ones(char *first, char *last);
char	*ft_strrjoin(char *line, char *dst);

void	check_valid_path(t_map *map);
void	check_path(t_map *map);
int		dfs_e(t_map *map, int r, int c);
void	dfs_c(t_map *map, int r, int c, int *collec_num);
int		valid(t_map *map, int r, int c);

void	graphic_handle(t_map *map);
void	put_images_to_window(t_vr *vr, t_map *map);
void	clean_all(t_vr *vr, int type);
void	get_images(t_vr *vr);
void	ft_initialize_vars(t_vr *vr);
int		handle(int key, t_vr *vr);
int		handle2(t_vr *vr);
int		is_valid(int nr, int nc, t_map *map);
int		make_animation(t_vr *vr);
void	check_valid_pos(t_vr *vr, int i, int j);
int		valid_enemy_pos(t_vr *vr, int r, int c);

#endif
