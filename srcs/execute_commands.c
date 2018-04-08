/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 19:21:18 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/02 19:21:19 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	display_error_msg(const char *cmd_path, const char *cmd)
{
	if (cmd_path == CMD_NOT_FOUND)
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	else if (cmd_path == CMD_NOPERM)
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static int	execute_one_command(struct s_msh_cmd *cur_node, char ***env)
{
	int		ret_value;
	int		builtin_index;
	char	*cmd_path;

	cmd_path = NULL;
	ret_value = 1;
	if ((builtin_index = is_cmd_builtin(cur_node->cmd)) != NOT_BUILTIN)
	{
		ret_value = execute_builtin(cur_node, builtin_index, env);
		return (ret_value);
	}
	cmd_path = search_cmd_path(cur_node->cmd, *env);
	if (cmd_path == CMD_NOT_FOUND || cmd_path == CMD_NOPERM)
		display_error_msg(cmd_path, cur_node->cmd);
	else
		ret_value = execute_program(cur_node, cmd_path, *env);
	if (cmd_path != CMD_NOT_FOUND && cmd_path != CMD_NOPERM)
		free(cmd_path);
	return (ret_value);
}

int			execute_commands(struct s_msh_cmd *ll_cmd, char ***env)
{
	int					last_ret_value;
	struct s_msh_cmd	*del;

	last_ret_value = 0;
	while (ll_cmd != NULL)
	{
		if (ll_cmd->connection == MSH_CON_NONE
		|| ll_cmd->connection == MSH_CON_SEMICOLON
		|| (ll_cmd->connection == MSH_CON_AND && last_ret_value == 0)
		|| (ll_cmd->connection == MSH_CON_OR && last_ret_value != 0))
			last_ret_value = execute_one_command(ll_cmd, env);
		del = ll_cmd;
		ll_cmd = ll_cmd->next;
		free(del->cmd);
		if (del->args_cmd != NULL)
			ft_del_2d_char_array(&(del->args_cmd));
		free(del);
	}
	return (last_ret_value);
}
