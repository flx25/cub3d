/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:06:57 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/17 10:47:37 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	move_available(t_cub3d *cub3d, t_pl *pl, double pl_w, double d)
{
	int		dxy[2];

	if ((pl->dir[0] < 0 && pl_w > 0) || (pl->dir[0] >= 0 && pl_w < 0))
		pl_w = -pl_w;
	dxy[0] = (int)(pl->pos[0] + pl_w + d * pl->dir[0]);
	if ((pl->dir[1] >= 0 && pl_w < 0) || (pl->dir[1] < 0 && pl_w > 0))
		pl_w = -pl_w;
	dxy[1] = (int)(pl->pos[1] + pl_w + d * pl->dir[1]);
	return (
		dxy[0] > 0 && dxy[1] > 0 && cub3d->map[dxy[1]]
		&& cub3d->map[dxy[1]][dxy[0]] && cub3d->map[dxy[1]][dxy[0]] != '1'
		&& !(cub3d->map[dxy[1]][dxy[0]] == '2' && !cub3d->door_raycast.open)
	);
}

int	rand_pos_helper(t_cub3d *cub3d, t_pl *pl, int w, int h)
{
	if (cub3d->map[h][w] == '0' || cub3d->map[h][w] == 'N'
		|| cub3d->map[h][w] == 'S' || cub3d->map[h][w] == 'W'
		|| cub3d->map[h][w] == 'E')
	{
		pl->pos[0] = (double)w;
		pl->pos[1] = (double)h;
		return (1);
	}
	return (0);
}

void	rand_pos(t_cub3d *cub3d, t_pl *pl)
{
	int	h;
	int	w;
	int	max_h;

	max_h = 0;
	h = 0;
	while (cub3d->map[max_h])
		max_h++;
	while (1)
	{
		h = (rand() % (max_h - 1)) + 1;
		w = 0;
		while (cub3d->map[h][w])
			w++;
		if (w < 3)
			continue ;
		w = (rand() % (w - 1)) + 1;
		if (rand_pos_helper(cub3d, pl, w, h))
			return ;
	}
}
