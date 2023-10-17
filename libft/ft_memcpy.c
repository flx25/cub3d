/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:33:10 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/26 17:14:02 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_c;
	char	*src_c;

	src_c = (char *)src;
	dst_c = (char *)dst;
	if (n == 0 || src_c == dst_c)
		return (dst);
	while (n--)
		*dst_c++ = *src_c++;
	return (dst);
}
