/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:03 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/15 16:44:57 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press_helper(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_SPACE)
		cub3d->door_raycast.open = !cub3d->door_raycast.open;
	else if (keycode == KEY_E)
		cub3d->speed = 2;
	return (0);
}

int	key_press(int keycode, void *cub3d_ptr)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)cub3d_ptr;
	if (keycode == KEY_ESC)
		ft_close(cub3d_ptr);
	else if (keycode == KEY_LEFT)
		cub3d->k.rr = 2;
	else if (keycode == KEY_RIGHT)
		cub3d->k.rr = 1;
	else if (keycode == KEY_W)
		cub3d->k.fb = 1;
	else if (keycode == KEY_S)
		cub3d->k.fb = 2;
	else if (keycode == KEY_A)
		cub3d->k.rl = 2;
	else if (keycode == KEY_D)
		cub3d->k.rl = 1;
	else if (keycode == KEY_F)
		cub3d->k.f = !cub3d->k.f;
	else if (keycode == KEY_ENTER)
		init_fireball(cub3d);
	else
		return (key_press_helper(keycode, cub3d));
	return (0);
}

int	key_release(int keycode, void *cub3d_ptr)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)cub3d_ptr;
	if (keycode == KEY_LEFT)
		cub3d->k.rr = 0;
	else if (keycode == KEY_RIGHT)
		cub3d->k.rr = 0;
	else if (keycode == KEY_W)
		cub3d->k.fb = 0;
	else if (keycode == KEY_S)
		cub3d->k.fb = 0;
	else if (keycode == KEY_A)
		cub3d->k.rl = 0;
	else if (keycode == KEY_D)
		cub3d->k.rl = 0;
	else if (keycode == KEY_E)
		cub3d->speed = 1;
	return (0);
}
