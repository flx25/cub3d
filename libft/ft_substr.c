/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:36:51 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/26 14:24:05 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	res_len;
	size_t	i;
	char	*res;

	if (!s)
		return (0);
	res_len = ft_strlen(s);
	if (start >= res_len || len <= 0)
		res_len = 0;
	else if (res_len - start > len)
		res_len = len;
	else
		res_len -= start;
	res = (char *)ft_calloc(res_len + 1, sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < res_len)
	{
		res[i] = s[start + i];
		i++;
	}
	return (res);
}
