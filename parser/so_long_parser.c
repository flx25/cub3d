/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:51:53 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/10/17 12:53:21 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strlen_longestline(char *str)
{
	int	i;
	int	count;
	int	longest;
	int	current;

	i = 0;
	count = 0;
	longest = 0;
	while (str[i])
	{
		if (str[i] != '\n')
			count++;
		i++;
		if (str[i] == '\n' || str[i] == '\0')
		{
			current = count;
			if (current > longest)
				longest = current;
			count = 0;
		}
	}
	return (longest);
}

char	**makemapmatrix(char *map, int msize)
{
	int		i;
	int		j;
	int		k;
	char	**matrix;

	i = 0;
	j = 0;
	k = 0;
	matrix = malloc(sizeof(char *) * (ft_strlen(map) + 1));
	while (map[i])
	{
		matrix[j] = malloc(sizeof(char) * (msize + 1));
		while (map[i] != '\n' && map[i] != '\0')
		{
			matrix[j][k] = map[i];
			i++;
			k++;
		}
		matrix[j][k] = '\0';
		k = 0;
		j++;
		i++;
	}
	matrix[j] = NULL;
	return (matrix);
}

char	*readmap(char *map)
{
	int		fd;
	char	*temp;
	char	*out;

	temp = ft_calloc(1, sizeof(char));
	out = ft_calloc(1, sizeof(char));
	fd = open(map, O_RDONLY);
	while (temp)
	{
		free(temp);
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		out = ft_gnl_strjoin(out, temp);
	}
	close(fd);
	return (out);
}
