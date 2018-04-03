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
// ------------- a mettre dans un autre .c
static void	init_builtins_array(char *builtins_array[NB_BUILTINS])
{
	builtins_array[0] = "echo";
	builtins_array[1] = "cd";
	builtins_array[2] = "setenv";
	builtins_array[3] = "unsetenv";
	builtins_array[4] = "env";
	builtins_array[5] = "exit";
}

int			is_cmd_builtin(const char *cmd)
{
	char	*builtins_array[NB_BUILTINS];
	int		builtin_index;

	init_builtins_array(builtins_array);

	builtin_index = 0;
	while (builtin_index < NB_BUILTINS)
	{
		if (ft_strcmp(cmd, builtins_array[builtin_index]) == 0)
			return (builtin_index);
		++builtin_index;
	}

	return (NOT_BUILTIN);
}


// -------------

static void	display_error_msg(const char *cmd_path, const char *cmd)
{
	if (cmd_path == CMD_NOT_FOUND)
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	else if (cmd_path == CMD_NOPERM)
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putchar('\n');
}

static int	execute_one_command(struct s_msh_cmd *cur_node, char **env)
{
	int		ret_value; // la valeur retournee par la commande lancee (le status de wait() quoi)
	int		builtin_index;
	char	*cmd_path;
												//	printf("\t\t\t\tEXECUTE %s\n", cur_node->cmd);

	ret_value = 1;
	cmd_path = NULL;

// si la cmd courrante est un builtin, alors on l'execute
	if ( (builtin_index = is_cmd_builtin(cur_node->cmd)) != NOT_BUILTIN ) {}  // exit doit free l'env aussi
	// l'index est celui d'un tableau de ptr sur func gere dans execute_builtin()
	//	ret_value = execute_builtin(builtin_index, env)

	// sinon si cest pas un builtin, on cherche l'access dans PATH et on verifie que cest bien executable
	cmd_path = search_cmd_path(cur_node->cmd, env); // renvoie NULL si aucun PATH nest trouve, ou si le binaire trouve nest en fait pas executable
	if (cmd_path == CMD_NOT_FOUND || cmd_path == CMD_NOPERM)
		display_error_msg(cmd_path, cur_node->cmd);
	else
		ret_value = execute_program(cur_node, cmd_path, env);

	if (cmd_path != CMD_NOT_FOUND && cmd_path != CMD_NOPERM)
		free(cmd_path);

		
	return (ret_value);
}

int			execute_commands(struct s_msh_cmd *ll_cmd, char **env)
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

		// faire une fonction pour ca ...
		free(del->cmd);
		if (del->args_cmd != NULL)
		{
			for (int i = 0 ; del->args_cmd[i] != NULL ; ++i)
				free(del->args_cmd[i]);
			free(del->args_cmd);
		}
		free(del);

	}

	return (last_ret_value);
}
