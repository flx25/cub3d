/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:56:38 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/10/16 13:55:34 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	drawsquare(t_cub3d *cub3d, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			drw_pnt(&cub3d->mlx.maze, x + j + 5, y + i, color);
			j++;
		}
		i++;
	}
}

void	drawminimap_2(t_cub3d *cub3d, t_minimap m)
{
	while (cub3d->map[m.i])
	{
		m.j = 0;
		m.x = 0;
		while (cub3d->map[m.i][m.j] != '\0')
		{
			if (cub3d->map[m.i][m.j] == '1')
				drawsquare(cub3d, m.x, m.y, 0xFF00FF00);
			m.j++;
			m.x += 5;
		}
		m.i++;
		m.y += 5;
	}
}

void	draw_health(t_cub3d *cub3d)
{
	int	health_len;
	int	x;
	int	start;
	int	clr;

	health_len = (int)(((double)(HEALTH_BAR_LEN - 10)
				/ (double)HEALTH) * (double)cub3d->health);
	start = (WIN_WIDTH - HEALTH_BAR_LEN) / 2;
	if (cub3d->health > HEALTH / 2)
		clr = 0x00FF00;
	else
		clr = 0xFF0000;
	x = 0;
	while (x <= HEALTH_BAR_LEN)
	{
		drawsquare(cub3d, start + x, 5, 0xFF00FF00);
		if (x && x <= health_len + 5)
			drawsquare(cub3d, start + x, 10, clr);
		else if (!x)
			drawsquare(cub3d, start + x, 10, 0xFF00FF00);
		else if (x > HEALTH_BAR_LEN - 5)
			drawsquare(cub3d, start + x, 10, 0xFF00FF00);
		drawsquare(cub3d, start + x, 15, 0xFF00FF00);
		x += 5;
	}
}

void	drawminimap(t_cub3d *cub3d)
{
	t_minimap	m;
	t_list		*buf;
	t_pl		*pl;

	buf = cub3d->mlx.sp;
	while (buf)
	{
		pl = (t_pl *)buf->content;
		if (pl->type == NPC)
			drawsquare(cub3d, pl->pos[0] * 5, pl->pos[1] * 5, 0xFF0000);
		buf = buf->next;
	}
	drawsquare(cub3d, cub3d->pos[0] * 5, cub3d->pos[1] * 5, 0x1111FF);
	ft_memset(&m, 0, sizeof(t_minimap));
	drawminimap_2(cub3d, m);
	draw_health(cub3d);
	if (cub3d->k.f)
	{
		drawsquare(cub3d, WIN_WIDTH / 2, WIN_HEIGHT / 2, 0xFF0000);
		drawsquare(cub3d, WIN_WIDTH / 2 - 5, WIN_HEIGHT / 2, 0xAA0000);
		drawsquare(cub3d, WIN_WIDTH / 2 + 5, WIN_HEIGHT / 2, 0xAA0000);
		drawsquare(cub3d, WIN_WIDTH / 2, WIN_HEIGHT / 2 - 5, 0xAA0000);
		drawsquare(cub3d, WIN_WIDTH / 2, WIN_HEIGHT / 2 + 5, 0xAA0000);
	}
}
