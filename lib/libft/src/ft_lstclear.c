/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:34:47 by chaejkim          #+#    #+#             */
/*   Updated: 2022/04/30 18:07:28 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*cur;

	tmp = *lst;
	while (tmp)
	{
		cur = tmp;
		tmp = tmp->next;
		if (del == 0)
		{
			if (cur->content)
				ft_lstdelone(cur, ft_del_ptr);
			else
				ft_lstdelone(cur, free);
		}
		ft_lstdelone(cur, del);
	}
	*lst = NULL;
}
