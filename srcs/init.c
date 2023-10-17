/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:45:58 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/17 09:31:20 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx.mlx = mlx_init();
	cub3d->mlx.win = mlx_new_window(cub3d->mlx.mlx,
			WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	cub3d->mlx.maze.img = mlx_new_image(cub3d->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	cub3d->mlx.maze.width = WIN_WIDTH;
	cub3d->mlx.maze.height = WIN_HEIGHT;
	cub3d->mlx.maze.mask = 0;
	cub3d->mlx.maze.data = mlx_get_data_addr(cub3d->mlx.maze.img,
			&cub3d->mlx.maze.bpp, &cub3d->mlx.maze.line_size,
			&cub3d->mlx.maze.endian);
	cub3d->m.mouse_pressed = false;
	cub3d->m.ch = false;
	cub3d->m.lock = false;
	cub3d->door_raycast.open = 0;
	cub3d->k.fb = 0;
	cub3d->k.rl = 0;
	cub3d->k.rr = 0;
	cub3d->c = 0;
	cub3d->health = HEALTH;
	cub3d->win_lose = 0;
	cub3d->speed = 1;
	if (init_anim(cub3d))
		ft_close(cub3d);
	create_npcs(cub3d);
}

void	init_coord(double coord[2], double x, double y)
{
	coord[0] = x;
	coord[1] = y;
}

int	init_dir_plane(t_cub3d *cub3d)
{
	if (cub3d->player_dir == 'E')
	{
		init_coord(cub3d->dir, 1.0, 0.0);
		init_coord(cub3d->plane, 0.0, 1.0);
	}
	else if (cub3d->player_dir == 'W')
	{
		init_coord(cub3d->dir, -1.0, 0.0);
		init_coord(cub3d->plane, 0.0, -1.0);
	}
	else if (cub3d->player_dir == 'S')
	{
		init_coord(cub3d->dir, 0.0, 1.0);
		init_coord(cub3d->plane, -1.0, 0.0);
	}
	else if (cub3d->player_dir == 'N')
	{
		init_coord(cub3d->dir, 0.0, -1.0);
		init_coord(cub3d->plane, 1.0, 0.0);
	}
	else
		return (ft_putstr_fd("Error\nWrong player direction.\n", 2));
	return (0);
}

int	init_pos(t_cub3d *cub3d)
{
	if (init_dir_plane(cub3d))
		return (1);
	cub3d->pos[0] = (double)cub3d->player_pos[1] + 0.5;
	cub3d->pos[1] = (double)cub3d->player_pos[0] + 0.5;
	if (load_texture(cub3d, &(cub3d->mlx.n_tex), cub3d->no_path)
		|| load_texture(cub3d, &(cub3d->mlx.s_tex), cub3d->so_path)
		|| load_texture(cub3d, &(cub3d->mlx.e_tex), cub3d->ea_path)
		|| load_texture(cub3d, &(cub3d->mlx.w_tex), cub3d->we_path))
		return (1);
	return (0);
}

void	init_hooks(t_cub3d *cub3d)
{
	mlx_hook(cub3d->mlx.win, 2, 1L << 0, &key_press, cub3d);
	mlx_hook(cub3d->mlx.win, 3, 1L << 1, &key_release, cub3d);
	mlx_hook(cub3d->mlx.win, 4, 1L << 2, &mouse_press, cub3d);
	mlx_hook(cub3d->mlx.win, 5, 1L << 3, &mouse_release, cub3d);
	mlx_hook(cub3d->mlx.win, 6, 1L << 6, &mouse_move, cub3d);
	mlx_hook(cub3d->mlx.win, 17, 0, &ft_close, cub3d);
	mouse_move_center(cub3d);
	mlx_loop_hook(cub3d->mlx.mlx, &loop_hook, cub3d);
}
