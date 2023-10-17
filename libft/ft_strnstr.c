/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:35:24 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/27 10:02:58 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!len && *needle)
		return (0);
	if (!*needle)
		return ((char *)haystack);
	j = 0;
	while (haystack[j] && j < len)
	{
		if (haystack[j] == *needle)
		{
			i = 0;
			while (haystack[j + i] && needle[i] && j + i < len)
			{
				if (haystack[j + i] != needle[i])
					break ;
				i++;
			}
			if (needle[i] == 0)
				return ((char *)haystack + j);
		}
		j++;
	}
	return (0);
}
