/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:19:06 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/14 14:19:08 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_door_anim(t_cub3d *cub3d)
{
	if (add_frame(cub3d, &cub3d->mlx.door_a, "textures/door/door_0.xpm")
		|| add_frame(cub3d, &cub3d->mlx.door_a, "textures/door/door_1.xpm")
		|| add_frame(cub3d, &cub3d->mlx.door_a, "textures/door/door_2.xpm"))
		return (1);
	cub3d->mlx.door_a.curr_frame = cub3d->mlx.door_a.frames;
	return (0);
}

void	manage_doors(t_cub3d *cub3d)
{
	if (cub3d->door_raycast.open && cub3d->mlx.door_a.curr_frame->next)
		cub3d->mlx.door_a.curr_frame = cub3d->mlx.door_a.curr_frame->next;
	else if (!cub3d->door_raycast.open
		&& cub3d->mlx.door_a.curr_frame != cub3d->mlx.door_a.frames)
	{
		if (cub3d->mlx.door_a.curr_frame != cub3d->mlx.door_a.frames->next)
			cub3d->mlx.door_a.curr_frame = cub3d->mlx.door_a.frames->next;
		else
			cub3d->mlx.door_a.curr_frame = cub3d->mlx.door_a.frames;
	}
}
