/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:36:07 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/22 18:59:57 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;

	res = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!res)
		return (0);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	return (res);
}
