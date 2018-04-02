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

static int	execute_one_command(struct s_msh_cmd *cur_node, char **env)
{
	int		ret_value; // la valeur retournee par la commande lancee (le status de wait() quoi)
	int		builtin_index;


	// si la cmd courrante est un builtin, alors on l'execute
		if ( (builtin_index = is_cmd_builtin(cur_node->cmd)) != NOT_BUILTIN ) printf("index %d\n", builtin_index);
		// l'index est celui d'un tableau de ptr sur func gere dans execute_builtin()
		//	execute_builtin(builtin_index, env)

		// sinon si cest pas un builtin, on cherche l'access dans PATH et on verifie que cest bien executable
			// si cest bon on execute
			// sinon command not found je suppose (d'autres cas a gerer ?)

			ret_value = 0; // pour les warnings
		return (ret_value);
}

int			execute_commands(struct s_msh_cmd *ll_cmd)
{
	int		last_ret_value;
	char	**my_env;

	last_ret_value = 0;
	my_env = init_my_env();

	while (ll_cmd != NULL)
	{

		if (ll_cmd->connection == MSH_CON_NONE
		|| ll_cmd->connection == MSH_CON_SEMICOLON
		|| (ll_cmd->connection == MSH_CON_AND && last_ret_value == 0)
		|| (ll_cmd->connection == MSH_CON_OR && last_ret_value != 0))
			last_ret_value = execute_one_command(ll_cmd, my_env);

	

		ll_cmd = ll_cmd->next;
	}

	return (last_ret_value);
}
