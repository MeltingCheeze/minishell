/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:38:54 by chaejkim          #+#    #+#             */
/*   Updated: 2022/01/09 15:45:51 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		len;
	int		i;

	if (!s || !f)
		return (0);
	len = (int)ft_strlen(s);
	i = -1;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (len == 0)
	{
		result[len] = '\0';
		return (result);
	}
	if (!result)
		return (NULL);
	while (++i < len)
		result[i] = f(i, s[i]);
	result[len] = '\0';
	return (result);
}
