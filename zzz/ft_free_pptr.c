/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_pptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 06:22:37 by chaejkim          #+#    #+#             */
/*   Updated: 2022/08/24 17:06:33 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pptr(char **pptr)
{
	int	i;

	i = 0;
	while (pptr[i])
	{
		free(pptr[i]);
		pptr[i] = 0;
		i++;
	}
	free(pptr);
	pptr = 0;
	return ;
}
