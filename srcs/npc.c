/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:19:56 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/16 14:18:11 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_npc(t_cub3d *cub3d, double dir[2])
{
	t_pl	*pl;
	t_list	*new;

	pl = (t_pl *)malloc(sizeof(t_pl));
	pl->anim = cub3d->mlx.pl_a;
	rand_pos(cub3d, pl);
	pl->dir[0] = dir[0];
	pl->dir[1] = dir[1];
	pl->v_move = 100;
	pl->scale = 1;
	pl->type = NPC;
	pl->dead = false;
	new = ft_lstnew(pl);
	if (!cub3d->mlx.sp)
		cub3d->mlx.sp = new;
	else
		ft_lstadd_back(&cub3d->mlx.sp, new);
}

/*
int	load_npc_anim(t_cub3d *cub3d)
{
	if (add_frame(cub3d, &cub3d->mlx.pl_a, "textures/sprite/anim_1.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/sprite/anim_2.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/sprite/anim_3.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/sprite/anim_4.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/sprite/anim_5.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/sprite/anim_6.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/sprite/anim_7.XPM"))
		return (1);
	cub3d->mlx.pl_a.curr_frame = cub3d->mlx.pl_a.frames;
	return (0);
}
*/

int	load_npc_anim(t_cub3d *cub3d)
{
	if (add_frame(cub3d, &cub3d->mlx.pl_a, "textures/din/1.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/din/2.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/din/3.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/din/4.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/din/5.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/din/6.XPM")
		|| add_frame(cub3d, &cub3d->mlx.pl_a, "textures/din/7.XPM"))
		return (1);
	cub3d->mlx.pl_a.curr_frame = cub3d->mlx.pl_a.frames;
	return (0);
}

void	check_player(t_cub3d *cub3d, t_pl *pl)
{
	double	dx;
	double	dy;
	double	m;

	if (check_dist(pl->pos, cub3d->pos, 0.5))
	{
		cub3d->health -= DAMAGE;
		cub3d->mlx.maze.mask = 0xFF0000;
	}
	else if (check_dist(pl->pos, cub3d->pos, 6))
	{
		dx = cub3d->pos[0] - pl->pos[0];
		dy = cub3d->pos[1] - pl->pos[1];
		m = sqrt(dx * dx + dy * dy);
		pl->dir[0] = dx / m;
		pl->dir[1] = dy / m;
	}
}

void	manage_npc(t_cub3d *cub3d, t_pl *pl)
{
	double	ax[2];
	double	d;

	d = (double)NPC_SPEED / 100.0;
	check_player(cub3d, pl);
	if (!move_available(cub3d, pl, 0.45, d))
	{
		ax[0] = (double)((rand() % (471 - 157 + 1)) + 157) / 100.0;
		ax[1] = pl->dir[0];
		pl->dir[0] = pl->dir[0] * cos(ax[0]) - pl->dir[1] * sin(ax[0]);
		pl->dir[1] = ax[1] * sin(ax[0]) + pl->dir[1] * cos(ax[0]);
	}
	if (move_available(cub3d, pl, 0.45, d))
	{
		play_anim(&pl->anim);
		pl->pos[0] += d * pl->dir[0];
		pl->pos[1] += d * pl->dir[1];
	}
}

void	create_npcs(t_cub3d *cub3d)
{
	int		i;
	double	dir[2];

	dir[0] = 1.0;
	dir[1] = 0.0;
	i = -1;
	while (++i < NPC_COUNT)
	{
		dir[0] = -dir[0];
		init_npc(cub3d, dir);
	}
}
