/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:44:39 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 15:28:04 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_struct.h"
#include <sys/stat.h>

t_bool	is_file_exists(char *file_name)
{
	struct stat	statbuf;

	return (stat(file_name, &statbuf) == 0);
}

t_bool	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}