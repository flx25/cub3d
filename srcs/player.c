/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:17:00 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/16 13:55:48 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_lose_anim(t_cub3d *cub3d)
{
	if (add_frame(cub3d, &cub3d->mlx.lose_a, "textures/lose/0.XPM")
		|| add_frame(cub3d, &cub3d->mlx.lose_a, "textures/lose/1.XPM")
		|| add_frame(cub3d, &cub3d->mlx.lose_a, "textures/lose/2.XPM")
		|| add_frame(cub3d, &cub3d->mlx.lose_a, "textures/lose/3.XPM")
		|| add_frame(cub3d, &cub3d->mlx.lose_a, "textures/lose/4.XPM")
		|| add_frame(cub3d, &cub3d->mlx.lose_a, "textures/lose/5.XPM"))
		return (1);
	cub3d->mlx.lose_a.curr_frame = cub3d->mlx.lose_a.frames;
	return (0);
}

int	load_win_anim(t_cub3d *cub3d)
{
	if (add_frame(cub3d, &cub3d->mlx.win_a, "textures/win/0.XPM")
		|| add_frame(cub3d, &cub3d->mlx.win_a, "textures/win/1.XPM")
		|| add_frame(cub3d, &cub3d->mlx.win_a, "textures/win/2.XPM")
		|| add_frame(cub3d, &cub3d->mlx.win_a, "textures/win/3.XPM")
		|| add_frame(cub3d, &cub3d->mlx.win_a, "textures/win/4.XPM")
		|| add_frame(cub3d, &cub3d->mlx.win_a, "textures/win/5.XPM")
		|| add_frame(cub3d, &cub3d->mlx.win_a, "textures/win/6.XPM"))
		return (1);
	cub3d->mlx.win_a.curr_frame = cub3d->mlx.win_a.frames;
	return (0);
}

void	draw_lose(t_cub3d *cub3d)
{
	cub3d->mlx.maze.mask = 0;
	play_anim(&cub3d->mlx.lose_a);
	draw_fullscreen(cub3d, cub3d->mlx.lose_a.curr_frame->content, 0x000000);
}

void	draw_win(t_cub3d *cub3d)
{
	cub3d->mlx.maze.mask = 0;
	play_anim(&cub3d->mlx.win_a);
	draw_fullscreen(cub3d, cub3d->mlx.win_a.curr_frame->content, 0x000000);
}

void	check_win_lose(t_cub3d *cub3d)
{
	if (NPC_COUNT && !cub3d->mlx.sp)
		cub3d->win_lose = 1;
	else if (cub3d->health <= 0)
		cub3d->win_lose = 2;
	if (cub3d->c > 300)
		cub3d->mlx.maze.mask = 0;
}
