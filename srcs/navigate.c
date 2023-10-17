/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:15 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/16 13:55:41 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate(t_cub3d *cub3d, double angle_delta)
{
	double	old_x;

	old_x = cub3d->dir[0];
	cub3d->dir[0] = cub3d->dir[0] * cos(angle_delta)
		- cub3d->dir[1] * sin(angle_delta);
	cub3d->dir[1] = old_x * sin(angle_delta)
		+ cub3d->dir[1] * cos(angle_delta);
	old_x = cub3d->plane[0];
	cub3d->plane[0] = cub3d->plane[0] * cos(angle_delta)
		- cub3d->plane[1] * sin(angle_delta);
	cub3d->plane[1] = old_x * sin(angle_delta)
		+ cub3d->plane[1] * cos(angle_delta);
}

int	chck_pl(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = (int)cub3d->pos[0];
	y = (int)cub3d->pos[1];
	if (cub3d->map[y][x] == '2')
		return (0);
	return (1);
}

void	check_wall_and_move(t_cub3d *cub3d, double delta_x, double delta_y)
{
	int		x;
	int		y;
	double	d;

	x = (int)(cub3d->pos[0] + delta_x);
	y = (int)(cub3d->pos[1] + delta_y);
	d = 1.0;
	if (chck_pl(cub3d) && cub3d->map[y][x] == '2'
		&& !cub3d->door_raycast.open)
		return ;
	while (cub3d->map[y][x] != '0' && cub3d->map[y][x] != '2'
		&& cub3d->map[y][x] != '3')
	{
		x = (int)(cub3d->pos[0] + delta_x / d);
		y = (int)(cub3d->pos[1] + delta_y / d);
		d *= 2.0;
		if (d > 16.0)
			return ;
	}
	cub3d->pos[0] += delta_x / d;
	cub3d->pos[1] += delta_y / d;
}

void	move(t_cub3d *cub3d, char direction, double delta)
{
	if (direction == 'F')
		check_wall_and_move(cub3d,
			delta * cub3d->dir[0], delta * cub3d->dir[1]);
	else if (direction == 'B')
		check_wall_and_move(cub3d,
			-delta * cub3d->dir[0], -delta * cub3d->dir[1]);
	else if (direction == 'R')
		check_wall_and_move(cub3d,
			-delta * cub3d->dir[1], delta * cub3d->dir[0]);
	else if (direction == 'L')
		check_wall_and_move(cub3d,
			delta * cub3d->dir[1], -delta * cub3d->dir[0]);
}

int	loop_hook(void *cub3d_ptr)
{
	t_cub3d		*cub3d;

	cub3d = (t_cub3d *)cub3d_ptr;
	cub3d->c = (cub3d->c + 1) % 1000;
	if (cub3d->k.fb == 1)
		move(cub3d, 'F', (double)(MOVE_SPEED * cub3d->speed) / 10000);
	else if (cub3d->k.fb == 2)
		move(cub3d, 'B', (double)(MOVE_SPEED * cub3d->speed) / 10000);
	if (cub3d->k.rl == 1)
		move(cub3d, 'R', (double)(MOVE_SPEED * cub3d->speed) / 10000);
	else if (cub3d->k.rl == 2)
		move(cub3d, 'L', (double)(MOVE_SPEED * cub3d->speed) / 10000);
	if (cub3d->k.rr == 1)
		rotate(cub3d, (double)(ROTATE_SPEED) / 10000);
	else if (cub3d->k.rr == 2)
		rotate(cub3d, -(double)(ROTATE_SPEED) / 10000);
	if (cub3d->k.fb || cub3d->k.rl || cub3d->k.rr || cub3d->m.ch || !cub3d->c)
	{
		check_win_lose(cub3d);
		draw_all(cub3d);
		cub3d->m.ch = false;
		if (cub3d->m.lock)
			mouse_move_center(cub3d);
	}
	return (0);
}
