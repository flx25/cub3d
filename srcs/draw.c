/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:45:54 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/16 13:52:23 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	drw_pnt(t_img *img, int x, int y, int clr)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT
		&& (clr & 0x00ffffff))
	{
		*(unsigned int *)(img->data + y * img->line_size
				+ x * img->bpp / 8) = img->mask | clr;
	}
}

unsigned int	get_img_color(t_img img, int x, int y)
{
	if (x >= 0 && y >= 0 && x < img.width && y < img.height)
		return (*(unsigned int *)(img.data + y * img.line_size
			+ x * img.bpp / 8));
	return (0);
}

void	draw_fullscreen(t_cub3d *cub3d, t_img *img, int fill_clr)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
			drw_pnt(&cub3d->mlx.maze, x, y, fill_clr);
	}
	start_x = (WIN_WIDTH - img->width) / 2;
	start_y = (WIN_HEIGHT - img->height) / 2;
	x = -1;
	while (++x < img->width)
	{
		y = -1;
		while (++y < img->width)
			drw_pnt(&cub3d->mlx.maze, start_x + x, start_y + y,
				get_img_color(*img, x, y));
	}
}

void	draw_all(t_cub3d *cub3d)
{
	if (!cub3d->win_lose)
	{
		raycasting(cub3d);
		drawminimap(cub3d);
		exec_anims(cub3d);
	}
	else if (cub3d->win_lose == 1)
		draw_win(cub3d);
	else if (cub3d->win_lose == 2)
		draw_lose(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win,
		cub3d->mlx.maze.img, 0, 0);
}
