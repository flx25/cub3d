/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcnct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:42:55 by psimonen          #+#    #+#             */
/*   Updated: 2023/06/05 15:21:49 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcnct(char *s1, char *s2)
{
	char	*res;
	int		i;

	res = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (s1 && *s1)
	{
		res[i] = *s1;
		i++;
		s1++;
	}
	while (s2 && *s2)
	{
		res[i] = *s2;
		i++;
		s2++;
	}
	return (res);
}
