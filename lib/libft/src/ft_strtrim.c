/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:43:30 by chaejkim          #+#    #+#             */
/*   Updated: 2022/01/09 15:45:28 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	s1_len;

	result = 0;
	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	s1_len = ft_strlen(s1);
	while (s1_len && s1[s1_len - 1] && ft_strchr(set, s1[s1_len - 1]))
		s1_len--;
	result = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, s1_len);
	result[s1_len] = '\0';
	return (result);
}
