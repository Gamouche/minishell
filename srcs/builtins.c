/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:50:47 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 16:50:48 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_builtins_name_array(char *builtins_array[NB_BUILTINS])
{
	builtins_array[0] = "echo";
	builtins_array[1] = "cd";
	builtins_array[2] = "setenv";
	builtins_array[3] = "unsetenv";
	builtins_array[4] = "env";
}

int			is_cmd_builtin(const char *cmd)
{
	char	*builtins_name_array[NB_BUILTINS];
	int		builtin_index;

	init_builtins_name_array(builtins_name_array);
	builtin_index = 0;
	while (builtin_index < NB_BUILTINS - 1)
	{
		if (ft_strcmp(cmd, "exit") == 0)
			return (BUILTIN_EXIT);
		if (ft_strcmp(cmd, builtins_name_array[builtin_index]) == 0)
			return (builtin_index);
		++builtin_index;
	}
	return (NOT_BUILTIN);
}

static void	init_builtins_array(int (*builtins_array[])(char **, char ***))
{
	builtins_array[0] = &builtin_echo;
	builtins_array[1] = &builtin_cd;
	builtins_array[2] = &builtin_setenv;
	builtins_array[3] = &builtin_unsetenv;
	builtins_array[4] = &builtin_env;
}

int			execute_builtin(struct s_msh_cmd *cur_node, int index, char ***env)
{
	int	ret_value;
	int (*builtins_array[NB_BUILTINS - 1])(char **args, char ***env);

	init_builtins_array(builtins_array);
	if (index == BUILTIN_EXIT)
		ret_value = builtin_exit(cur_node, *env);
	else
		ret_value = (*builtins_array[index])(cur_node->args_cmd, env);
	return (ret_value);
}
