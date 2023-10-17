/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:33:24 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/26 16:52:30 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!len || src == dst)
		return (dst);
	if (dst >= src)
	{
		i = len;
		while (--i >= 0)
			((char *)dst)[i] = ((char *)src)[i];
	}
	else
	{
		i = -1;
		while ((size_t)++i < len)
			((char *)dst)[i] = ((char *)src)[i];
	}
	return (dst);
}
