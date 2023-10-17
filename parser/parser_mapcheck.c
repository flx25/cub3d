/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mapcheck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:51:05 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/10/17 10:22:35 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	checkmapchars(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != '0' && map[i] != '1' && map[i] != '\n'
			&& map[i] != 'N' && map[i] != 'S' && map[i] != 'W'
			&& map[i] != 'E' && map[i] != ' ' && map[i] != '2')
			return (1);
		i++;
	}
	return (0);
}

int	checksingleentrance(char *map)
{
	int	i;
	int	entrance;

	i = 0;
	entrance = 0;
	while (map[i])
	{
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W' || map[i] == 'E')
			entrance++;
		i++;
	}
	if (entrance != 1)
		return (1);
	return (0);
}

int	checkmap(char *map, t_cub3d *cub3d)
{
	if (checkmapchars(map))
		return (1);
	if (checksingleentrance(map))
		return (1);
	if (checkmapenclosure(map, cub3d))
		return (1);
	return (0);
}

int	checkforvalidtoken(char *line)
{
	if (ft_strnstr(line, "NO ", lengtonl(line)))
		return (0);
	if (ft_strnstr(line, "SO ", lengtonl(line)))
		return (0);
	if (ft_strnstr(line, "WE ", lengtonl(line)))
		return (0);
	if (ft_strnstr(line, "EA ", lengtonl(line)))
		return (0);
	if (ft_strnstr(line, "F ", lengtonl(line)))
		return (0);
	if (ft_strnstr(line, "C ", lengtonl(line)))
		return (0);
	if (line[0] == '\n')
		return (0);
	return (1);
}

int	checkunknowntokens(char *argv1)
{
	char	*file;
	int		i;
	char	*pointer;

	file = readmap(argv1);
	i = 0;
	pointer = return_pointer(file);
	if (!pointer)
		return (free(file), 1);
	while (file + i < pointer)
	{
		if (checkforvalidtoken(file + i))
			return (free(file), 1);
		i = i + lengtonl(file + i) + 1;
	}
	free(file);
	return (0);
}
