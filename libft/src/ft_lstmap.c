/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:30:21 by chaejkim          #+#    #+#             */
/*   Updated: 2022/01/09 16:02:18 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*next_new;

	if (lst == NULL)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (!new_lst)
	{
		ft_lstclear(&new_lst, del);
		return (NULL);
	}
	next_new = new_lst;
	lst = lst->next;
	while (lst)
	{
		next_new->next = ft_lstnew(f(lst->content));
		if (!next_new->next)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		next_new = next_new->next;
		lst = lst->next;
	}
	return (new_lst);
}
