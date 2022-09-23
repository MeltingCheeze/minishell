/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:55:08 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:55:09 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* utils */
void	ft_error(char *msg);
// t_bool	is_file_exists(char *file_name);
//void	ft_free_pptr(char *msg);
char	set_quote(char old_quote, char new_quote);
t_bool	is_file_exists(char *file_name);

#endif
