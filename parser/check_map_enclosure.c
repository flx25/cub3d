/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_enclosure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:53:07 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/10/17 11:35:58 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mapsizeheight(char *map)
{
	int	height;
	int	i;

	i = 0;
	height = -1;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
			height++;
		i++;
	}
	if (checkadditionalnl(map) == 0)
		height++;
	return (height);
}

int	checkmapenclosure_depth(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (cub3d->map[i])
	{
		j = 0;
		while (cub3d->map[i][j] != '\0')
		{
			if (cub3d->map[i][j] == '0' || cub3d->map[i][j] == '2' ||
				cub3d->map[i][j] == 'N' || cub3d->map[i][j] == 'S' ||
				cub3d->map[i][j] == 'W' || cub3d->map[i][j] == 'E')
			{
				if (!cub3d->map[i][j + 1] || !cub3d->map[i][j - 1]
					|| !cub3d->map[i + 1][j] || !cub3d->map[i - 1][j]
					|| cub3d->map[i][j + 1] == ' ' || cub3d->map[i][j -1] == ' '
					|| cub3d->map[i +1][j] == ' ' || cub3d->map[i -1][j] == ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	checkfirstandlastline(t_cub3d *cub3d, int height)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cub3d->map[i][j] != '\0')
	{
		if (cub3d->map[i][j] != '1' && cub3d->map[i][j] != ' '
			&& cub3d->map[i][j] != '\0')
			return (1);
		j++;
	}
	j = 0;
	while (cub3d->map[height][j] != '\0')
	{
		if (cub3d->map[height][j] != '1' &&
			cub3d->map[height][j] != ' ' && cub3d->map[i][j] != '\0')
			return (1);
		j++;
	}
	return (0);
}

void	freematrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	checkmapenclosure(char *map, t_cub3d *cub3d)
{
	cub3d->map = makemapmatrix(map, ft_strlen_longestline(map));
	if (checkfirstandlastline(cub3d, mapsizeheight(map)))
	{
		freematrix(cub3d->map);
		return (1);
	}
	if (checkmapenclosure_depth(cub3d))
	{
		freematrix(cub3d->map);
		return (1);
	}
	freematrix(cub3d->map);
	return (0);
}
