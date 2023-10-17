/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:46:39 by psimonen          #+#    #+#             */
/*   Updated: 2023/10/13 11:46:45 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_path(char *path)
{
	int	len;

	if (!path || !*path)
		return (ft_putstr_fd("Error\nWrong texture path\n", 2));
	len = ft_strlen(path);
	if (len - 4 <= 0 || (ft_strncmp(path + len - 4, ".xpm", 5)
			&& ft_strncmp(path + len - 4, ".XPM", 5)))
		return (ft_putstr_fd("Error\nWrong texture file extension for ", 2),
			ft_putstr_fd(path, 2), ft_putstr_fd("\n", 2));
	return (0);
}

int	load_texture(t_cub3d *cub3d, t_img *img, char *path)
{
	int	err;

	err = check_path(path);
	if (err)
		return (err);
	img->img = mlx_xpm_file_to_image(cub3d->mlx.mlx, path,
			&(img->width), &(img->height));
	if (!img->img)
		return (ft_putstr_fd("Error\nCannot load ", 2),
			ft_putstr_fd(path, 2), ft_putstr_fd("\n", 2));
	img->data = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_size, &img->endian);
	if (!img->data)
		return (ft_putstr_fd("Error\nCannot load ", 2),
			ft_putstr_fd(path, 2), ft_putstr_fd("\n", 2));
	return (err);
}
