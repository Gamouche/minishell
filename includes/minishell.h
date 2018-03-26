/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:15:28 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/23 17:15:29 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/includes/libft.h"

					#include <stdio.h> // debuggggggg

# define FATAL_ERROR (2)
# define MSH_CMD_SEPARATORS (char[4]){0x20, 0x09, 0x0a, 0x00}
# define CMD_EMPTY ((struct s_msh_cmd *)(-1))
# define PARSE_ERROR ((struct s_msh_cmd *)(-2))

enum e_msh_connection
{
	MSH_CON_NONE,
	MSH_CON_SEMICOLON,
	MSH_CON_AND
};

struct s_msh_cmd
{
	char					*cmd;
	char					**args_cmd;
	enum e_msh_connection 	connection;
	struct s_msh_cmd		*next;
};

struct 	s_msh_cmd	*get_cmd(void);
char				*read_user_input(void);
struct s_msh_cmd	*get_cmd_list(const char *cmd_input);


#endif