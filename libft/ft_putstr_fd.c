/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:38:26 by psimonen          #+#    #+#             */
/*   Updated: 2023/06/05 20:07:35 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	res;
	int	buf;

	if (!s)
		return (0);
	res = ft_strlen(s);
	buf = write(fd, s, res);
	if (buf < 0)
		return (buf);
	return (res);
}
