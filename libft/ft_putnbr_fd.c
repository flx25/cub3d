/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:38:47 by psimonen          #+#    #+#             */
/*   Updated: 2023/05/22 16:28:11 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	buf;
	int		flag;

	flag = 0;
	if (n >= 10 || n <= -10)
	{
		ft_putnbr_fd(n / 10, fd);
		flag = 1;
	}
	if (!flag && n < 0)
		write(fd, "-", 1);
	flag = n % 10;
	if (flag < 0)
		flag *= -1;
	buf = flag + '0';
	write(fd, &buf, 1);
}
