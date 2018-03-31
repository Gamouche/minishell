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

# include <stdlib.h>
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
	MSH_CON_AND,
	MSH_CON_OR
};

struct s_msh_cmd
{
	char					*cmd;
	char					**args_cmd;
	enum e_msh_connection 	connection;
	struct s_msh_cmd		*next;
};

# include <stdbool.h> // cette structure va aller dans un autre .h 
struct s_get_cmd_list_var_norme_lol
{
	char					*keep;
	bool					need_new_node;
	enum e_msh_connection	connec;
	struct s_msh_cmd		*cur_ll;
};

struct 	s_msh_cmd	*get_cmd(void);
//struct s_msh_cmd	*get_cmd_list(char *cmd_input);
void				func_destroy_list(struct s_msh_cmd *ll);


#endif