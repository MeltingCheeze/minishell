/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:36:39 by chaejkim          #+#    #+#             */
/*   Updated: 2022/01/09 15:45:10 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src == dst || len == 0)
		return (dst);
	if (dst > src)
	{
		while (len--)
			((char *)dst)[len] = ((char *)src)[len];
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
