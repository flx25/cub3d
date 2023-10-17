/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:37:14 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/26 17:09:06 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_contains(char c, char const *set)
{
	int	i;

	if (!set)
		return (0);
	i = -1;
	while (set[++i])
	{
		if (set[i] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		beg;
	int		end;
	int		i;
	char	*res;

	if (!s1)
		return (0);
	beg = 0;
	while (s1[beg] && set_contains(s1[beg], set))
		beg++;
	end = ft_strlen(s1) - 1;
	while (end > beg && set_contains(s1[end], set))
		end--;
	end++;
	res = (char *)ft_calloc(end - beg + 1, sizeof(char));
	if (!res)
		return (0);
	i = -1;
	while (beg + ++i < end)
		res[i] = s1[beg + i];
	return (res);
}
