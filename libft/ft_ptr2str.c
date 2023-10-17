/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr2str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:15:28 by psimonen          #+#    #+#             */
/*   Updated: 2023/06/07 11:13:58 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ptr2str(void *ptr)
{
	char				*res;
	char				*buf_1;
	char				buf_2[2];
	unsigned long long	n;

	n = (unsigned long long)ptr;
	if (n / 16)
		buf_1 = ft_ptr2str((void *)(n / 16));
	else
		buf_1 = ft_strcnct("", 0);
	if (!buf_1)
		return (0);
	buf_2[0] = "0123456789abcdef"[n % 16];
	buf_2[1] = 0;
	res = ft_strcnct(buf_1, buf_2);
	free(buf_1);
	return (res);
}
