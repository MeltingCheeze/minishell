/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:44:42 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:44:43 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	set_quote(char old_quote, char new_quote)
{
	if (!old_quote)
		return (new_quote);
	if (old_quote && (old_quote == new_quote))
		return (0);
	return (old_quote);
}
