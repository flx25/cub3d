/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:26 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/16 12:39:31 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_dist(t_cub3d *cub3d)
{
	int		map_x;
	int		map_y;

	map_x = (int)cub3d->pos[0];
	map_y = (int)cub3d->pos[1];
	if (cub3d->raycst.ray_dir_x == 0)
		cub3d->raycst.d_dst_x = 1e30;
	else
		cub3d->raycst.d_dst_x = fabs(1 / cub3d->raycst.ray_dir_x);
	if (cub3d->raycst.ray_dir_y == 0)
		cub3d->raycst.d_dst_y = 1e30;
	else
		cub3d->raycst.d_dst_y = fabs(1 / cub3d->raycst.ray_dir_y);
	if (cub3d->raycst.ray_dir_x < 0)
		cub3d->raycst.s_dst_x = (cub3d->pos[0] - map_x) * cub3d->raycst.d_dst_x;
	else
		cub3d->raycst.s_dst_x = (map_x + 1.0 - cub3d->pos[0])
			* cub3d->raycst.d_dst_x;
	if (cub3d->raycst.ray_dir_y < 0)
		cub3d->raycst.s_dst_y = (cub3d->pos[1] - map_y) * cub3d->raycst.d_dst_y;
	else
		cub3d->raycst.s_dst_y = (map_y + 1.0 - cub3d->pos[1])
			* cub3d->raycst.d_dst_y;
}

void	calc_perp_d(t_cub3d *cub3d)
{
	if (cub3d->raycst.side == 0)
		cub3d->raycst.perp_d = (cub3d->raycst.s_dst_x - cub3d->raycst.d_dst_x);
	else
		cub3d->raycst.perp_d = (cub3d->raycst.s_dst_y - cub3d->raycst.d_dst_y);
	if (cub3d->door_raycast.used && cub3d->door_raycast.side == 0)
		cub3d->door_raycast.perp_d = (cub3d->door_raycast.s_dst_x
				- cub3d->door_raycast.d_dst_x);
	else if (cub3d->door_raycast.used)
		cub3d->door_raycast.perp_d = (cub3d->door_raycast.s_dst_y
				- cub3d->door_raycast.d_dst_y);
}

void	calc_side(t_cub3d *cub3d)
{
	int	step_x;
	int	step_y;

	calc_dist(cub3d);
	if (cub3d->raycst.ray_dir_x < 0)
		step_x = -1;
	else
		step_x = 1;
	if (cub3d->raycst.ray_dir_y < 0)
		step_y = -1;
	else
		step_y = 1;
	calc_side_helper(cub3d, step_x, step_y);
	calc_perp_d(cub3d);
}

void	calc_ray_dir(t_cub3d *cub3d, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	cub3d->raycst.ray_dir_x = cub3d->dir[0] + cub3d->plane[0] * camera_x;
	cub3d->raycst.ray_dir_y = cub3d->dir[1] + cub3d->plane[1] * camera_x;
}

void	raycasting(t_cub3d *cub3d)
{
	int		x;
	t_list	*buf;

	x = -1;
	draw_floor_ceil(cub3d);
	while (++x < WIN_WIDTH)
	{
		calc_ray_dir(cub3d, x);
		calc_side(cub3d);
		draw_x(cub3d, x, 0);
		cub3d->mlx.z_buf[x] = cub3d->raycst.perp_d;
		if (cub3d->door_raycast.used)
		{
			draw_x(cub3d, x, 1);
			if (!cub3d->door_raycast.open)
				cub3d->mlx.z_buf[x] = cub3d->door_raycast.perp_d;
		}
	}
	buf = cub3d->mlx.sp;
	while (buf)
	{
		draw_sprite(cub3d, buf->content);
		buf = buf->next;
	}
}
