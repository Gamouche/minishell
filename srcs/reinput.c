/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reinput.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 19:56:25 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 19:56:26 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool			need_reinput(char *input)
{
	char c;

	c = *input;
	++input;
	if (*input == 0)
		return (false);
	while (is_sep(*input))
	{
		if (*input == 0)
			break ;
		++input;
	}
	if (*input == 0 && c != ';')
		return (true);
	return (false);
}

static void			get_new_input(char **cmd_input, char **keep)
{
	char	*suite_cmd;
	char	*tmp;

	msh_prompt_complete_cmd();
	suite_cmd = read_user_input();
	tmp = *cmd_input;
	*cmd_input = ft_malloc(ft_strlen(tmp) + ft_strlen(suite_cmd) + 1,
	FATAL_ERROR);
	(*cmd_input)[0] = 0;
	ft_strcat(*cmd_input, suite_cmd);
	free(suite_cmd);
	free(*keep);
	*keep = *cmd_input;
}

struct s_msh_cmd	*complete_input_command(char **cmd_input, char **keep,
												struct s_msh_cmd *ll_cmd)
{
	get_new_input(cmd_input, keep);
	if ((*cmd_input)[ft_strlen(*cmd_input) - 1] == '\n')
		(*cmd_input)[ft_strlen(*cmd_input) - 1] = '\0';
	if (input_is_valid(*cmd_input) == false)
	{
		func_destroy_list(ll_cmd);
		free(*keep);
		return (PARSE_ERROR);
	}
	special_case_management(*cmd_input);
	while (**cmd_input != 0)
	{
		while (**cmd_input == 0x20 || **cmd_input == 0x09
		|| **cmd_input == 0x0a)
			++(*cmd_input);
		if (**cmd_input == 0)
			break ;
		if (**cmd_input == ';')
			++(*cmd_input);
		if (is_not_sep(**cmd_input))
			break ;
	}
	return (NULL);
}

struct s_msh_cmd	*manage_arg_and_reinput(char **cmd_input,
	struct s_get_cmd_list_var_norme_lol *variables, const char *tmp,
	struct s_msh_cmd *ll_cmd)
{
	if (variables->cur_ll->cmd == NULL && tmp[0] != '\0')
	{
		if ((variables->cur_ll->cmd = ft_strdup(tmp)) == NULL)
			ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
	}
	else if (tmp[0] != '\0')
		store_argument(variables->cur_ll, tmp);
	else if (need_reinput(*cmd_input) == true)
	{
		if (complete_input_command(cmd_input, &(variables->keep), ll_cmd)
		== PARSE_ERROR)
			return (PARSE_ERROR);
	}
	return (NULL);
}
