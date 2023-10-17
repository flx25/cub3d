/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:37:42 by psimonen          #+#    #+#             */
/*   Updated: 2023/06/05 18:17:20 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_num_len(int n)
{
	int	str_len;

	str_len = 1;
	while (n >= 10)
	{
		str_len++;
		n /= 10;
	}
	return (str_len);
}

static char	*convert(int n, int dig)
{
	int		str_len;
	char	*res;

	str_len = calc_num_len(n);
	res = (char *)ft_calloc(str_len + dig + 1, sizeof(char));
	if (!res)
		return (0);
	while (--str_len >= 0)
	{
		res[str_len + dig] = '0' + n % 10;
		n /= 10;
	}
	if (dig)
		res[0] = '-';
	if (dig == 2)
		res[1] = '2';
	return (res);
}

char	*ft_itoa(int n)
{
	int	dig;

	dig = 0;
	if (n == -2147483648)
	{
		n = 147483648;
		dig = 2;
	}
	else if (n < 0)
	{
		n *= -1;
		dig = 1;
	}
	return (convert(n, dig));
}
