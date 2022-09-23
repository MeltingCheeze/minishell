/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcmdline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:27:00 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:43:30 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*readcmdline(void)
{
	char	*line;

	signal(SIGINT, &signal_readline);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minishell$ ");
	if (line == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (*line)
		add_history(line);
	return (line);
}
