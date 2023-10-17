/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:47:52 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/10/17 11:36:04 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	multicommas(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (1);
		i++;
	}
	return (0);
}

char	*return_pointer(char *file)
{
	char	*pointer[3];

	pointer[1] = ft_strnstr(file, "\n ", ft_strlen(file));
	pointer[2] = ft_strnstr(file, "\n1", ft_strlen(file));
	if (pointer[1] && pointer[2])
	{
		if (pointer[1] < pointer[2])
			pointer[0] = pointer[1];
		else
			pointer[0] = pointer[2];
	}
	else if (pointer[1])
		pointer[0] = pointer[1];
	else if (pointer[2])
		pointer[0] = pointer[2];
	else
		pointer[0] = NULL;
	return (pointer[0]);
}

int	checkadditionalnl(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		i++;
	}
	if (map[i - 1] == '\n')
		return (1);
	else
		return (0);
}
