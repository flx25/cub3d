/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:51:44 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/10/17 13:17:37 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strlen_space(char *s)
{
	int	res;

	if (!s || !*s)
		return (0);
	res = 0;
	while (*s)
	{
		if (*s != ' ')
			res++;
		s++;
	}
	return (res);
}

char	*searchforparam(char *param, char *file)
{
	char	*out;
	int		len1;
	int		len2;
	char	*pointer;

	pointer = ft_strnstr(file, param, ft_strlen(file));
	if (!pointer)
		return (NULL);
	len1 = lengtonl(pointer + ft_strlen(param) - 1) + 1;
	len2 = lengtonl(pointer + ft_strlen(param) - 1);
	out = ft_calloc(sizeof(char), len1);
	ft_strlcpy(out, pointer + ft_strlen(param), len2);
	if (ft_strnstr(pointer +1, param, ft_strlen(file)))
		return (free(out), NULL);
	out = copywithoutspaces(out);
	return (out);
}

int	getparameters(char *argv1, t_cub3d *cub3d)
{
	char	*file;

	file = readmap(argv1);
	cub3d->no_path = searchforparam("NO ", file);
	if (!cub3d->no_path)
		return (free(file), 1);
	cub3d->so_path = searchforparam("SO ", file);
	if (!cub3d->so_path)
		return (free(file), 1);
	cub3d->we_path = searchforparam("WE ", file);
	if (!cub3d->we_path)
		return (free(file), 1);
	cub3d->ea_path = searchforparam("EA ", file);
	if (!cub3d->ea_path)
		return (free(file), 1);
	cub3d->floor_color_str = searchforparam("F ", file);
	if (!cub3d->floor_color_str)
		return (free(file), 1);
	cub3d->ceiling_color_str = searchforparam("C", file);
	if (!cub3d->ceiling_color_str)
		return (free(file), 1);
	free(file);
	return (0);
}

int	parser(char *argv1, t_cub3d *cub3d)
{
	char	*map;
	int		len;

	len = ft_strlen(argv1);
	if (len - 4 <= 0 || (ft_strncmp(argv1 + len - 4, ".cub", 5)))
		return (1);
	if (checkunknowntokens(argv1) || getparameters(argv1, cub3d)
		|| check_cf(cub3d->ceiling_color_str)
		|| check_cf(cub3d->floor_color_str) || convertcolors(cub3d))
		return (1);
	map = get_cut_map(argv1);
	if (checkmap(map, cub3d))
		return (free(map), 1);
	cub3d->map = makemapmatrix(map, ft_strlen_longestline(map));
	getstartpoint(cub3d);
	free(map);
	return (0);
}
