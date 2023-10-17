/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:07 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/17 09:30:52 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_clrs(t_cub3d *cub3d)
{
	if (!cub3d->floor_color)
		cub3d->floor_color++;
	if (!cub3d->ceiling_color)
		cub3d->ceiling_color++;
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	ft_memset(&cub3d, 0, sizeof(t_cub3d));
	if (argc != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 2);
		return (1);
	}
	if (parser(argv[1], &cub3d))
	{
		ft_putstr_fd("Error\nWrong map\n", 2);
		free_parse_error(&cub3d);
		return (1);
	}
	init_clrs(&cub3d);
	init_mlx(&cub3d);
	if (init_pos(&cub3d))
	{
		free_data(&cub3d);
		return (1);
	}
	draw_all(&cub3d);
	init_hooks(&cub3d);
	mlx_loop(cub3d.mlx.mlx);
}
