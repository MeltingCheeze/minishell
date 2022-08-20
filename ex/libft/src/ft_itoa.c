/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:06:06 by chaejkim          #+#    #+#             */
/*   Updated: 2022/02/02 04:01:23 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(long long_n)
{
	size_t	len;

	len = 1;
	while (long_n > 9)
	{
		len++;
		long_n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		minus;
	size_t	len;
	long	long_n;

	long_n = (long)n;
	minus = 0;
	if (long_n < 0)
	{
		minus = 1;
		long_n *= -1;
	}
	len = get_len(long_n);
	result = (char *)ft_calloc(len + minus + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (long_n > 9)
	{
		result[--len + minus] = (long_n % 10) + 48;
		long_n /= 10;
	}
	result[minus] = (long_n % 10) + 48;
	if (minus)
		result[0] = '-';
	return (result);
}
