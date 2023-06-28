/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:01:07 by asettar           #+#    #+#             */
/*   Updated: 2023/03/27 15:33:22 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_len(char *str, t_map *map)
{
	int	i;

	if (!str)
		clean_exit(map, INVALID_MAP, EXIT_FAILURE);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int	check_ones(char *first, char *last)
{
	int	i;

	if (!first || !last)
		return (1);
	i = 0;
	while (first[i] != '\n' && first[i])
	{
		if (first[i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (last[i] != '\n' && last[i])
	{
		if (last[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strrjoin(char *line, char *dst)
{
	char	*ret;
	int		i;
	int		d;

	if (!dst)
		d = 0;
	else
		d = ft_strlen(dst);
	ret = (char *)malloc(ft_strlen(line) + d + 1);
	if (!ret)
		return (NULL);
	i = -1;
	if (!dst)
		ft_memcpy(ret, line, ft_strlen(line) + 1);
	else
	{
		ft_memcpy(ret, dst, ft_strlen(dst));
		ft_memcpy(ret + ft_strlen(dst), line, ft_strlen(line) + 1);
	}
	free(dst);
	return (ret);
}
