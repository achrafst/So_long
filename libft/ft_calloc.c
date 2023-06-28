/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:21:30 by asettar           #+#    #+#             */
/*   Updated: 2023/03/26 20:45:44 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	cnt;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	cnt = count * size;
	ptr = malloc(cnt);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, cnt);
	return (ptr);
}
