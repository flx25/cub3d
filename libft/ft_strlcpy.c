/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:33:35 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/28 10:36:30 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	size;
	size_t	res;

	res = ft_strlen(src);
	if (!dstsize)
		return (res);
	size = dstsize;
	if (dstsize > res)
		size = res + 1;
	dst = ft_memmove(dst, src, size);
	dst[size - 1] = 0;
	return (res);
}
