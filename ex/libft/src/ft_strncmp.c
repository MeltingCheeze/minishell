/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:35:54 by chaejkim          #+#    #+#             */
/*   Updated: 2022/01/07 11:45:10 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	while (n-- > 0)
	{
		c1 = *(unsigned char *)s1++;
		c2 = *(unsigned char *)s2++;
		if (c1 != c2)
			return (c1 - c2);
		if (!c1)
			return (0);
	}
	return (0);
}
