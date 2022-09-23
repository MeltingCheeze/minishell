/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_file_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:44:39 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:44:40 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <sys/stat.h>

t_bool	is_file_exists(char *file_name)
{
	struct stat	buf;

	return (stat(file_name, &buf) == 0);
}
