/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manages_connections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 19:49:21 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 19:49:24 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void				manage_semicolon_connection(char **cmd_input,
			bool *need_new_node, enum e_msh_connection *connec)
{
	*connec = MSH_CON_SEMICOLON;
	*need_new_node = true;
	while (is_sep(**cmd_input) || **cmd_input == ';')
	{
		if (**cmd_input == '\0')
			break ;
		++(*cmd_input);
	}
}

static struct s_msh_cmd	*manage_and_connection(
	struct s_get_cmd_list_var_norme_lol *variables, char **cmd_input,
	struct s_msh_cmd *ll_cmd)
{
	variables->connec = MSH_CON_AND;
	variables->need_new_node = true;
	(*cmd_input) += 2;
	while (is_sep(**cmd_input))
	{
		if (**cmd_input == '\0')
		{
			if (complete_input_command(cmd_input, &(variables->keep), ll_cmd)
			== PARSE_ERROR)
				return (PARSE_ERROR);
			break ;
		}
		++(*cmd_input);
	}
	return (NULL);
}

static struct s_msh_cmd	*manage_or_connection(
	struct s_get_cmd_list_var_norme_lol *variables, char **cmd_input,
	struct s_msh_cmd *ll_cmd)
{
	variables->connec = MSH_CON_OR;
	variables->need_new_node = true;
	(*cmd_input) += 2;
	while (is_sep(**cmd_input))
	{
		if (**cmd_input == '\0')
		{
			if (complete_input_command(cmd_input, &(variables->keep), ll_cmd)
			== PARSE_ERROR)
				return (PARSE_ERROR);
			break ;
		}
		++(*cmd_input);
	}
	return (NULL);
}

static void				manage_separators(
	struct s_get_cmd_list_var_norme_lol *variables, char **cmd_input)
{
	variables->need_new_node = false;
	while (is_sep(**cmd_input))
	{
		if (**cmd_input == '\0')
			break ;
		++(*cmd_input);
	}
}

struct s_msh_cmd		*manage_connections(char **cmd_input,
	struct s_get_cmd_list_var_norme_lol *variables, struct s_msh_cmd *ll_cmd)
{
	if (**cmd_input == ';')
		manage_semicolon_connection(cmd_input, &(variables->need_new_node),
		&(variables->connec));
	else if (**cmd_input == '&')
	{
		if (manage_and_connection(variables, cmd_input, ll_cmd) == PARSE_ERROR)
			return (PARSE_ERROR);
	}
	else if (**cmd_input == '|')
	{
		if (manage_or_connection(variables, cmd_input, ll_cmd) == PARSE_ERROR)
			return (PARSE_ERROR);
	}
	else if (is_sep(**cmd_input))
		manage_separators(variables, cmd_input);
	return (NULL);
}
