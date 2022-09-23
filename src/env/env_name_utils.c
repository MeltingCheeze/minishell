/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_name_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:32:41 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/23 13:32:42 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

int	is_valid_env_first_name(char c)
{
	return (ft_isalpha(c) || (c == '_'));
}

int	is_valid_env_name(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || (c == '_'));
}
