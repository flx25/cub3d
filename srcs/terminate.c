/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:36 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/16 12:39:34 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_list	*ft_lstcut(t_list **lst, void *cnt)
{
	t_list	*buf;
	t_list	*buf2;

	buf = *lst;
	if (buf->content == cnt)
	{
		*lst = (*lst)->next;
		free(buf->content);
		free(buf);
		buf = 0;
		return (*lst);
	}
	while (buf && buf->next && buf->next->content != cnt)
		buf = buf->next;
	if (buf && buf->next && buf->next->content == cnt)
	{
		buf2 = buf->next->next;
		free(buf->next->content);
		free(buf->next);
		buf->next = 0;
		buf->next = buf2;
	}
	return (buf->next);
}

void	free_anim(t_cub3d *cub3d, t_anim *anim)
{
	t_list	*buf;
	t_list	*iter;
	t_img	*frame;

	iter = anim->frames;
	while (iter)
	{
		buf = iter;
		iter = iter->next;
		frame = (t_img *)buf->content;
		mlx_destroy_image(cub3d->mlx.mlx, frame->img);
		free(buf->content);
		free(buf);
	}
}

void	free_map(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	while (cub3d->map[++i])
		free(cub3d->map[i]);
	free(cub3d->map);
}

void	free_data(t_cub3d *cub3d)
{
	free_map(cub3d);
	free_parse_error(cub3d);
	if (cub3d->mlx.n_tex.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.n_tex.img);
	if (cub3d->mlx.s_tex.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.s_tex.img);
	if (cub3d->mlx.e_tex.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.e_tex.img);
	if (cub3d->mlx.w_tex.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.w_tex.img);
	if (cub3d->mlx.maze.img)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->mlx.maze.img);
	free_anim(cub3d, &cub3d->mlx.door_a);
	free_anim(cub3d, &cub3d->mlx.fire_a);
	free_anim(cub3d, &cub3d->mlx.pl_a);
	free_anim(cub3d, &cub3d->mlx.win_a);
	free_anim(cub3d, &cub3d->mlx.lose_a);
	ft_lstclear(&cub3d->mlx.sp, &free);
	if (cub3d->mlx.win)
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
}

int	ft_close(void *cub3d_ptr)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)cub3d_ptr;
	free_data(cub3d);
	exit(0);
	return (0);
}
