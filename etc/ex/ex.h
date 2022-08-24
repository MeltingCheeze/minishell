/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 22:24:01 by chaejkim          #+#    #+#             */
/*   Updated: 2022/08/20 22:48:11 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EX_H
# define EX_H

typedef enum e_type
{
	Word,
	ParameterExpansion,
}			t_type;

typedef struct s_table
{
	void			*head;
	struct s_table	*next;
}				t_table;

typedef struct s_cmd_line
{
	t_table	token_table;
	int		fd_in;
	int		fd_out;
}				t_cmd_line;

typedef struct s_cmd
{
	t_table		cmd_line;
	
}				t_cmd;

typedef struct s_env
{
	char 			*key;
	char 			**value;
	struct s_env	*next;
}				t_env;

typedef struct s_sh
{
	t_cmd	*cmd;
	t_env	*env;
}				t_sh;

#endif EX_H
