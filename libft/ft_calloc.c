/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:35:57 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/24 19:39:55 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	i;

	res = (void *)malloc(count * size);
	if (!res)
		return (0);
	i = 0;
	while (i < count * size)
	{
		((char *)res)[i] = 0;
		i++;
	}
	return (res);
}
