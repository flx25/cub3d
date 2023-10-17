/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:09:43 by psimonen          #+#    #+#             */
/*   Updated: 2023/06/08 19:33:36 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned int n, char *base)
{
	int		ijl[3];
	char	buf[12];
	char	*res;

	ijl[0] = 0;
	ijl[2] = ft_strlen(base);
	if (!n && ++ijl[0])
		buf[0] = base[0];
	while (n)
	{
		buf[ijl[0]] = base[n % ijl[2]];
		n /= ijl[2];
		ijl[0]++;
	}
	res = (char *)malloc(sizeof(char) * (ijl[0] + 1));
	if (!res)
		return (0);
	ijl[1] = 0;
	while (--ijl[0] >= 0)
		res[ijl[1]++] = buf[ijl[0]];
	res[ijl[1]] = 0;
	return (res);
}

/*
char	*ft_itoa_base(unsigned int n, char *base)
{
	int		base_len;
	char	*res;
	char	*buf_1;
	char	buf_2[2];

	base_len = ft_strlen(base);
	buf_1 = 0;
	if (n / base_len)
	{
		buf_1 = ft_itoa_base(n / base_len, base);
		if (!buf_1)
			return (0);
	}
	buf_2[0] = base[n % base_len];
	buf_2[1] = 0;
	res = ft_strcnct(buf_1, buf_2);
	free(buf_1);
	return (res);
}
*/