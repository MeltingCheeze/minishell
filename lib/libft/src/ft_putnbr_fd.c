/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:57:23 by chaejkim          #+#    #+#             */
/*   Updated: 2022/01/09 16:08:11 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_nb(int fd, long nb)
{
	char	c;

	if (nb < 0)
		return ;
	if (nb > 9)
		write_nb(fd, nb / 10);
	c = nb % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	long_n;

	long_n = (long)n;
	if (fd < 0)
		return ;
	if (long_n < 0)
	{
		write(fd, "-", 1);
		long_n = -long_n;
	}
	write_nb(fd, long_n);
}
