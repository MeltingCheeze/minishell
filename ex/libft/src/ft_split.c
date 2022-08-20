/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:12:55 by chaejkim          #+#    #+#             */
/*   Updated: 2022/01/09 15:52:21 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcnt(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			cnt++;
		s++;
	}
	return (cnt);
}

static char	*get_word(char const *s, char c)
{
	char	*word;
	size_t	len;
	size_t	i;

	len = 0;
	while (*(s + len) && *(s + len) != c)
		len++;
	word = (char *)ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
		word[i++] = *s++;
	return (word);
}

static void	free_all(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
	return ;
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word_cnt;
	size_t	i;

	if (!s)
		return (NULL);
	word_cnt = wordcnt(s, c);
	result = (char **)ft_calloc(word_cnt + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_cnt)
	{
		while (*s == c)
			s++;
		result[i] = get_word(s, c);
		if (!result[i++])
		{
			free_all(result);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
	}
	return (result);
}
