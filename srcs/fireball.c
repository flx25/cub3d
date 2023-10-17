/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fireball.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:19:13 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/16 12:02:54 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_fireball(t_cub3d *cub3d)
{
	t_pl	*pl;
	t_list	*new;

	pl = (t_pl *)malloc(sizeof(t_pl));
	pl->anim = cub3d->mlx.fire_a;
	pl->pos[0] = cub3d->pos[0];
	pl->pos[1] = cub3d->pos[1];
	pl->dir[0] = cub3d->dir[0];
	pl->dir[1] = cub3d->dir[1];
	pl->v_move = 300;
	pl->scale = 1;
	pl->dead = false;
	pl->type = FIRE;
	new = ft_lstnew(pl);
	if (!cub3d->mlx.sp)
		cub3d->mlx.sp = new;
	else
		ft_lstadd_back(&cub3d->mlx.sp, new);
}

int	load_fireball_anim(t_cub3d *cub3d)
{
	if (add_frame(cub3d, &cub3d->mlx.fire_a, "textures/fire/0.xpm")
		|| add_frame(cub3d, &cub3d->mlx.fire_a, "textures/fire/1.xpm")
		|| add_frame(cub3d, &cub3d->mlx.fire_a, "textures/fire/2.xpm")
		|| add_frame(cub3d, &cub3d->mlx.fire_a, "textures/fire/3.xpm")
		|| add_frame(cub3d, &cub3d->mlx.fire_a, "textures/fire/4.xpm")
		|| add_frame(cub3d, &cub3d->mlx.fire_a, "textures/fire/5.xpm")
		|| add_frame(cub3d, &cub3d->mlx.fire_a, "textures/fire/6.xpm")
		|| add_frame(cub3d, &cub3d->mlx.fire_a, "textures/fire/7.xpm"))
		return (1);
	cub3d->mlx.fire_a.curr_frame = cub3d->mlx.fire_a.frames;
	return (0);
}

bool	check_dist(double pos1[2], double pos2[2], double dist)
{
	double	dxy[2];

	dxy[0] = fabs(pos1[0] - pos2[0]);
	dxy[1] = fabs(pos1[1] - pos2[1]);
	if (dxy[0] + dxy[1] < dist)
		return (true);
	return (false);
}

int	should_kill(t_cub3d *cub3d, t_pl *pl)
{
	t_list	*buf;
	t_pl	*npc;

	buf = cub3d->mlx.sp;
	while (buf)
	{
		npc = (t_pl *)buf->content;
		if (npc->type == NPC && check_dist(npc->pos, pl->pos, 0.5))
		{
			npc->dead = true;
			return (1);
		}
		buf = buf->next;
	}
	return (0);
}

void	manage_fire(t_cub3d *cub3d, t_pl *pl)
{
	double	d;

	d = 0.5;
	if (should_kill(cub3d, pl))
		pl->dead = true;
	else if (!move_available(cub3d, pl, 0.005, d))
		pl->dead = true;
	else
	{
		play_anim(&pl->anim);
		pl->pos[0] += d * pl->dir[0];
		pl->pos[1] += d * pl->dir[1];
	}
}
