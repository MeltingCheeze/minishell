/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:29:57 by chaejkim          #+#    #+#             */
/*   Updated: 2022/01/07 12:38:15 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	while (n-- > 0)
	{
		c1 = *(unsigned char *)s1++;
		c2 = *(unsigned char *)s2++;
		if (c1 != c2)
			return (c1 - c2);
	}
	return (0);
}
