/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:37:29 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/27 16:45:59 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	add_word(const char *s, char **dest, char c)
{
	int	len;
	int	i;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	*dest = (char *)ft_calloc(len + 1, sizeof(char));
	if (!(*dest))
		return (-1);
	i = -1;
	while (++i < len)
		(*dest)[i] = s[i];
	return (1);
}

static int	count_words(const char *s, char c, char **res)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			if (res && add_word(s + i, res + len, c) == -1)
				return (-1);
			len++;
			while (s[i] && s[i] != c)
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**res;

	if (!s)
		return (0);
	count = count_words(s, c, 0);
	res = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (0);
	if (count_words(s, c, res) == -1)
	{
		count = -1;
		while (res[++count])
			free(res[count]);
		free(res);
		return (0);
	}
	return (res);
}
