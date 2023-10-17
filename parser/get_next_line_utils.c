/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:50:40 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/10/15 12:46:08 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_gnl_strchr(char *c, int i)
{
	int	j;

	j = 0;
	if (!c)
		return (NULL);
	if (i == '\0')
		return ((char *)&c[ft_strlen(c)]);
	while (c[j] != '\0')
	{
		if (c[j] == (char) i)
			return ((char *)&c[j]);
		j++;
	}
	return (NULL);
}

int	ft_gnl_strjoin_helper(char **str, char *buff)
{
	if (!*str)
	{
		*str = (char *)malloc(1 * sizeof(char));
		(*str)[0] = '\0';
	}
	if (!buff && *str)
		free(*str);
	if (!*str || !buff)
		return (0);
	return (1);
}

char	*ft_gnl_strjoin(char *str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*nstr;

	if (!ft_gnl_strjoin_helper(&str, buff))
		return (0);
	nstr = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(buff)) + 1));
	if (nstr == NULL)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	j = 0;
	if (str)
		while (str[++i] != '\0')
			nstr[i] = str[i];
	while (buff[j] != '\0')
		nstr[i++] = buff[j++];
	nstr[ft_strlen(str) + ft_strlen(buff)] = '\0';
	free(str);
	return (nstr);
}
