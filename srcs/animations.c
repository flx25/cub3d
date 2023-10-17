/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:45:50 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/16 12:39:40 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	add_frame(t_cub3d *cub3d, t_anim *anim, char *path)
{
	t_img	*frame;
	t_list	*last;
	t_list	*new;

	frame = (t_img *)malloc(sizeof(t_img));
	if (!frame || load_texture(cub3d, frame, path))
		return (1);
	new = ft_lstnew(frame);
	if (!new)
		return (1);
	if (!anim->frames)
		anim->frames = new;
	else
	{
		last = ft_lstlast(anim->frames);
		last->next = new;
	}
	return (0);
}

int	init_anim(t_cub3d *cub3d)
{
	if (load_door_anim(cub3d)
		|| load_npc_anim(cub3d)
		|| load_fireball_anim(cub3d)
		|| load_lose_anim(cub3d)
		|| load_win_anim(cub3d))
		return (1);
	return (0);
}

void	play_anim(t_anim *anim)
{
	if (anim->curr_frame->next)
		anim->curr_frame = anim->curr_frame->next;
	else
		anim->curr_frame = anim->frames;
}

t_list	*choose_anim(t_cub3d *cub3d, t_pl *pl, int *deleted)
{
	*deleted = 0;
	if (pl->dead)
	{
		*deleted = 1;
		return (ft_lstcut(&cub3d->mlx.sp, pl));
	}
	else if (pl->type == FIRE)
		manage_fire(cub3d, pl);
	else if (pl->type == NPC)
		manage_npc(cub3d, pl);
	return (0);
}

void	exec_anims(t_cub3d *cub3d)
{
	t_list	*buf;
	t_list	*next;
	int		deleted;

	if (cub3d->c % 3)
		return ;
	manage_doors(cub3d);
	buf = cub3d->mlx.sp;
	while (buf)
	{
		next = choose_anim(cub3d, buf->content, &deleted);
		if (next)
			buf = next;
		else if (!deleted)
			buf = buf->next;
		else if (deleted)
			return ;
	}
}
