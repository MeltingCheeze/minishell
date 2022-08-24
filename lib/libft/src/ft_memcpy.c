/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:42:38 by chaejkim          #+#    #+#             */
/*   Updated: 2022/01/10 18:55:33 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_tmp;
	const unsigned char	*src_tmp;

	dst_tmp = dst;
	src_tmp = src;
	if (dst_tmp == src_tmp)
		return (dst);
	while (n-- > 0)
		*dst_tmp++ = *src_tmp++;
	return (dst);
}
