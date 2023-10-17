/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:51:20 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/10/17 10:18:29 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_cut_map(char *argv1)
{
	char	*file;
	char	*map;
	char	*pointer[3];

	file = readmap(argv1);
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
		return (free(file), NULL);
	map = ft_calloc(ft_strlen(file), sizeof(char));
	ft_strlcpy(map, pointer[0], ft_strlen(file));
	free(file);
	return (map);
}

int	check_cf(char *str)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (str[i])
	{
		if (str[i] == ',')
			comma++;
		if (comma > 2)
			return (1);
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != ' ')
			return (1);
		i++;
	}
	if (str[ft_strlen(str) -1] == ',' || comma != 2
		|| multicommas(str))
		return (1);
	return (0);
}

int	check_and_fill(int rgb[3], char **src)
{
	rgb[0] = ft_atoi(src[0]);
	rgb[1] = ft_atoi(src[1]);
	rgb[2] = ft_atoi(src[2]);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (1);
	return (0);
}

int	convertcolors(t_cub3d *cub3d)
{
	char	**floor;
	char	**ceiling;
	int		rgb[3];

	floor = ft_split(cub3d->floor_color_str, ',');
	if (check_and_fill(rgb, floor))
	{
		freesplit(floor);
		return (1);
	}
	cub3d->floor_color = pack_rgb(rgb[0], rgb[1], rgb[2]);
	ceiling = ft_split(cub3d->ceiling_color_str, ',');
	if (check_and_fill(rgb, ceiling))
	{
		freesplit(floor);
		freesplit(ceiling);
		return (1);
	}
	cub3d->ceiling_color = pack_rgb(rgb[0], rgb[1], rgb[2]);
	freesplit(floor);
	freesplit(ceiling);
	return (0);
}

void	getstartpoint(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub3d->map[i])
	{
		while (cub3d->map[i][j])
		{
			if (cub3d->map[i][j] == 'N' || cub3d->map[i][j] == 'S'
				|| cub3d->map[i][j] == 'W' || cub3d->map[i][j] == 'E')
			{
				cub3d->player_dir = cub3d->map[i][j];
				cub3d->player_pos[0] = i;
				cub3d->player_pos[1] = j;
				cub3d->map[i][j] = '0';
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}
