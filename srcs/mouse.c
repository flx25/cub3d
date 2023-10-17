/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:12 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/16 10:22:41 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_press(int keycode, int x, int y, void *cub3d_ptr)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)cub3d_ptr;
	if (keycode == M_LEFT && x > 0 && y > 0
		&& x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		cub3d->m.mouse_pressed = true;
		if (cub3d->k.f)
			init_fireball(cub3d);
	}
	else if (keycode == M_RIGHT && x > 0 && y > 0
		&& x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		cub3d->m.lock = !cub3d->m.lock;
		if (cub3d->m.lock)
			mlx_mouse_hide(cub3d->mlx.mlx, cub3d->mlx.win);
		else
			mlx_mouse_show(cub3d->mlx.mlx, cub3d->mlx.win);
	}
	return (0);
}

int	mouse_release(int keycode, int x, int y, void *cub3d_ptr)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)cub3d_ptr;
	if (keycode == M_LEFT && x > 0 && y > 0)
		cub3d->m.mouse_pressed = false;
	return (0);
}

int	mouse_move(int x, int y, void *cub3d_ptr)
{
	t_cub3d	*cub3d;
	double	dx;

	cub3d = (t_cub3d *)cub3d_ptr;
	if (!cub3d->m.lock || y < 0)
		return (0);
	dx = WIN_WIDTH / 2 - x;
	y = 0;
	rotate(cub3d, -((double)MOUSE_SPEED / 100.0) * (dx / 400));
	cub3d->m.ch = true;
	return (0);
}
