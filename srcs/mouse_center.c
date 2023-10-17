/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_center.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:10:46 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/16 10:11:21 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifdef __APPLE__

void	mouse_move_center(t_cub3d *cub3d)
{
	mlx_mouse_move(cub3d->mlx.win, (WIN_WIDTH / 2), WIN_HEIGHT / 2);
}
#else

void	mouse_move_center(t_cub3d *cub3d)
{
	mlx_mouse_move(cub3d->mlx.mlx, cub3d->mlx.win,
		(WIN_WIDTH / 2), WIN_HEIGHT / 2);
}
#endif