/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:17 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/13 11:46:19 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_side_helper(t_cub3d *cub3d, int step_x, int step_y)
{
	int		a[3];

	a[0] = (int)cub3d->pos[0];
	a[1] = (int)cub3d->pos[1];
	a[2] = 0;
	cub3d->door_raycast.used = 0;
	while (a[2] == 0)
	{
		if (cub3d->raycst.s_dst_x < cub3d->raycst.s_dst_y)
		{
			a[0] += step_x;
			cub3d->raycst.s_dst_x += cub3d->raycst.d_dst_x;
			cub3d->raycst.side = 0;
		}
		else
		{
			cub3d->raycst.s_dst_y += cub3d->raycst.d_dst_y;
			a[1] += step_y;
			cub3d->raycst.side = 1;
		}
		cub3d->raycst.wall = cub3d->map[a[1]][a[0]];
		copy_raycast(cub3d);
		if (cub3d->raycst.wall != '0' && cub3d->raycst.wall != '2')
			a[2] = 1;
	}
}
