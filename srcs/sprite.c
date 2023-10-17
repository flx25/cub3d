/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:30 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/15 10:39:37 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calc_transform(t_cub3d *cub3d, t_pl *pl)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = pl->pos[0] - cub3d->pos[0];
	sprite_y = pl->pos[1] - cub3d->pos[1];
	inv_det = 1.0 / (cub3d->plane[0] * cub3d->dir[1]
			- cub3d->dir[0] * cub3d->plane[1]);
	cub3d->sp.tr_x = inv_det * (cub3d->dir[1] * sprite_x
			- cub3d->dir[0] * sprite_y);
	cub3d->sp.tr_y = inv_det * (-cub3d->plane[1] * sprite_x
			+ cub3d->plane[0] * sprite_y);
	cub3d->sp.v_move = (int)((double)pl->v_move / cub3d->sp.tr_y);
	cub3d->sp.sp_s_x = ((int)(WIN_WIDTH / 2)*(1
				+ cub3d->sp.tr_x / cub3d->sp.tr_y));
	cub3d->sp.sp_hei = abs((int)(WIN_HEIGHT / (pl->scale * cub3d->sp.tr_y)));
}

void	calc_ends(t_cub3d *cub3d, t_pl *pl)
{
	cub3d->sp.st_y = -cub3d->sp.sp_hei / 2 + WIN_HEIGHT / 2 + cub3d->sp.v_move;
	if (cub3d->sp.st_y < 0)
		cub3d->sp.st_y = 0;
	cub3d->sp.en_y = cub3d->sp.sp_hei / 2 + WIN_HEIGHT / 2 + cub3d->sp.v_move;
	if (cub3d->sp.en_y >= WIN_HEIGHT)
		cub3d->sp.en_y = WIN_HEIGHT - 1;
	cub3d->sp.sp_wid = abs((int)(WIN_HEIGHT / (pl->scale * cub3d->sp.tr_y)));
	cub3d->sp.st_x = -cub3d->sp.sp_wid / 2 + cub3d->sp.sp_s_x;
	if (cub3d->sp.st_x < 0)
		cub3d->sp.st_x = 0;
	cub3d->sp.en_x = cub3d->sp.sp_wid / 2 + cub3d->sp.sp_s_x;
	if (cub3d->sp.en_x >= WIN_WIDTH)
		cub3d->sp.en_x = WIN_WIDTH - 1;
}

void	draw_sprite(t_cub3d *cub3d, t_pl *pl)
{
	t_img	*tex;
	int		x[2];
	int		txy[2];
	int		d;

	tex = (t_img *)pl->anim.curr_frame->content;
	calc_transform(cub3d, pl);
	calc_ends(cub3d, pl);
	x[0] = cub3d->sp.st_x - 1;
	while (++x[0] < cub3d->sp.en_x)
	{
		txy[0] = (int)(256 * (x[0] - (-cub3d->sp.sp_wid / 2 + cub3d->sp.sp_s_x))
				* tex->width / cub3d->sp.sp_wid) / 256;
		if (cub3d->sp.tr_y > 0 && x[0] > 0 && x[0] < WIN_WIDTH
			&& cub3d->sp.tr_y < cub3d->mlx.z_buf[x[0]])
			x[1] = cub3d->sp.st_y - 1;
		while (++x[1] < cub3d->sp.en_y)
		{
			d = (x[1] - cub3d->sp.v_move) * 256 - WIN_HEIGHT * 128
				+ cub3d->sp.sp_hei * 128;
			txy[1] = ((d * tex->height) / cub3d->sp.sp_hei) / 256;
			drw_pnt(&cub3d->mlx.maze, x[0], x[1],
				get_img_color(*tex, txy[0], txy[1]));
		}
	}
}
