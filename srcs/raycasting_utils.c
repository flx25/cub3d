/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:21 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/17 09:31:00 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_floor_ceil(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = 0;
		while (++x < WIN_WIDTH)
		{
			drw_pnt(&(cub3d->mlx.maze), x, y, cub3d->floor_color);
			drw_pnt(&(cub3d->mlx.maze), x, WIN_HEIGHT - y - 1,
				cub3d->ceiling_color);
		}
	}
}

void	choose_texture(t_cub3d *cub3d, int door)
{
	t_img	*frame;

	if (door == 1)
	{
		frame = (t_img *)cub3d->mlx.door_a.curr_frame->content;
		cub3d->door_raycast.tex = *frame;
	}
	else if (cub3d->raycst.side == 1 && cub3d->raycst.ray_dir_y >= 0)
		cub3d->raycst.tex = cub3d->mlx.s_tex;
	else if (cub3d->raycst.side == 1 && cub3d->raycst.ray_dir_y < 0)
		cub3d->raycst.tex = cub3d->mlx.n_tex;
	else if (cub3d->raycst.side != 1 && cub3d->raycst.ray_dir_x >= 0)
		cub3d->raycst.tex = cub3d->mlx.e_tex;
	else
		cub3d->raycst.tex = cub3d->mlx.w_tex;
}

int	calc_text_x(t_cub3d *cub3d, double perp_wall_d, int door)
{
	double			wall_x;
	int				tex_x;
	t_raycast		*raycst;

	raycst = &cub3d->raycst;
	if (door)
		raycst = &cub3d->door_raycast;
	if (raycst->side == 0)
		wall_x = cub3d->pos[1] + perp_wall_d * raycst->ray_dir_y;
	else
		wall_x = cub3d->pos[0] + perp_wall_d * raycst->ray_dir_x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)raycst->tex.width);
	if (raycst->side == 0 && raycst->ray_dir_x > 0)
		tex_x = raycst->tex.width - tex_x - 1;
	if (raycst->side == 1 && raycst->ray_dir_y < 0)
		tex_x = raycst->tex.width - tex_x - 1;
	return (tex_x);
}

void	draw_x(t_cub3d *cub3d, int x, int door)
{
	int			sel[5];
	double		st[2];
	t_raycast	*raycst;

	raycst = &cub3d->raycst;
	if (door == 1)
		raycst = &cub3d->door_raycast;
	sel[2] = (int)(WIN_HEIGHT / raycst->perp_d);
	sel[0] = -sel[2] / 2 + WIN_HEIGHT / 2;
	if (sel[0] < 0)
		sel[0] = 0;
	sel[1] = sel[2] / 2 + WIN_HEIGHT / 2;
	if (sel[1] >= WIN_HEIGHT)
		sel[1] = WIN_HEIGHT - 1;
	choose_texture(cub3d, door);
	sel[3] = calc_text_x(cub3d, raycst->perp_d, door);
	st[0] = (double)raycst->tex.height / (double)sel[2];
	st[1] = (sel[0] - WIN_HEIGHT / 2 + sel[2] / 2) * st[0];
	sel[4] = sel[0] - 1;
	while (++sel[4] < sel[1])
	{
		drw_pnt(&(cub3d->mlx.maze), x, sel[4], get_img_color(raycst->tex,
				sel[3], (int)st[1] % (raycst->tex.height - 1)));
		st[1] += st[0];
	}
}

void	copy_raycast(t_cub3d *cub3d)
{
	t_raycast	*raycst;

	if (cub3d->raycst.wall == '2' && !cub3d->door_raycast.used)
		raycst = &cub3d->door_raycast;
	else
		return ;
	raycst->d_dst_x = cub3d->raycst.d_dst_x;
	raycst->d_dst_y = cub3d->raycst.d_dst_y;
	raycst->s_dst_x = cub3d->raycst.s_dst_x;
	raycst->s_dst_y = cub3d->raycst.s_dst_y;
	raycst->side = cub3d->raycst.side;
	raycst->ray_dir_x = cub3d->raycst.ray_dir_x;
	raycst->ray_dir_y = cub3d->raycst.ray_dir_y;
	raycst->wall = cub3d->raycst.wall;
	raycst->used = 1;
}
