/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:51:29 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/10/13 15:04:41 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_parse_error(t_cub3d *cub3d)
{
	if (cub3d->no_path != NULL)
		free(cub3d->no_path);
	if (cub3d->so_path != NULL)
		free(cub3d->so_path);
	if (cub3d->we_path != NULL)
		free(cub3d->we_path);
	if (cub3d->ea_path != NULL)
		free(cub3d->ea_path);
	if (cub3d->floor_color_str != NULL)
		free(cub3d->floor_color_str);
	if (cub3d->ceiling_color_str != NULL)
		free(cub3d->ceiling_color_str);
}

int	lengtonl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*copywithoutspaces(char *str)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	j = 0;
	out = ft_calloc(sizeof(char), ft_strlen_space(str) + 1);
	while (str[i])
	{
		if (str[i] != ' ')
		{
			out[j] = str[i];
			j++;
		}
		i++;
	}
	free(str);
	return (out);
}

uint32_t	pack_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16 | g << 8 | b);
}

void	freesplit(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
