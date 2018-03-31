/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 19:16:30 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 19:16:31 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_CMD_H

# define GET_CMD_H

# include <stdbool.h>
# include "../includes/minishell.h"

# define MSH_CMD_SEPARATORS (char[4]){0x20, 0x09, 0x0a, 0x00}
# define CMD_EMPTY ((struct s_msh_cmd *)(-1))
# define PARSE_ERROR ((struct s_msh_cmd *)(-2))

struct				s_get_cmd_list_var_norme_lol
{
	char					*keep;
	bool					need_new_node;
	enum e_msh_connection	connec;
	struct s_msh_cmd		*cur_ll;
};

/*
**	get_cmd.c
*/
struct s_msh_cmd	*get_cmd(void);

/*
**	check_input.c
*/
void				special_case_management(char *input);
bool				check_if_input_is_full_blank(const char *input);
bool				input_is_valid(const char *input);

/*
**	is_sep_or_not.c
*/
int					is_sep(int c);
int					is_not_sep(int c);

/*
**	manage_connections.c
*/
struct s_msh_cmd	*manage_connections(char **cmd_input,
		struct s_get_cmd_list_var_norme_lol *variables,
		struct s_msh_cmd *ll_cmd);

/*
**	reinput.c
*/
struct s_msh_cmd	*manage_arg_and_reinput(char **cmd_input,
			struct s_get_cmd_list_var_norme_lol *variables,
			const char *tmp, struct s_msh_cmd *ll_cmd);
struct s_msh_cmd	*complete_input_command(char **cmd_input, char **keep,
												struct s_msh_cmd *ll_cmd);

/*
**	manage_llist.c
*/
struct s_msh_cmd	*init_first_node(struct s_msh_cmd **cur_ll);
void				create_new_node(struct s_msh_cmd **cur_ll,
								enum e_msh_connection connec);
void				func_destroy_list(struct s_msh_cmd *ll);

/*
**	manage_argument.c
*/
void				store_argument(struct s_msh_cmd *ll, const char *arg);
void				isolate_command_or_argument(char **cmd_input,
												char tmp[1024]);

/*
**	input_cmd_special_case_management.c
*/
void				special_case_management(char *input);

#endif
