/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:22:00 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/03 20:22:01 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../includes/minishell.h"

static char	**set_real_args(struct s_msh_cmd *cur_node)
{
	char	**real_args;
	size_t	nb_args;
	size_t	i;

	if ((!(i = 0)) && cur_node->args_cmd == NULL)
	{
		real_args = ft_malloc(sizeof(char *) * 2, FATAL_ERROR);
		real_args[0] = cur_node->cmd;
		real_args[1] = NULL;
	}
	else
	{
		nb_args = 0;
		while (cur_node->args_cmd[nb_args] != NULL)
			++nb_args;
		real_args = ft_malloc(sizeof(char *) * (nb_args + 2), FATAL_ERROR);
		real_args[0] = cur_node->cmd;
		real_args[nb_args + 1] = NULL;
		while (cur_node->args_cmd[i] != NULL)
		{
			real_args[i + 1] = cur_node->args_cmd[i];
			++i;
		}
	}
	return (real_args);
}

static char	*get_full_path(const char *cmd_path, const char *cmd)
{
	char	*full_path;

	if (ft_strcmp(cmd_path, cmd) == 0)
	{
		if ((full_path = ft_strdup(cmd)) == NULL)
			ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
		return (full_path);
	}
	full_path = ft_malloc(ft_strlen(cmd_path) + ft_strlen(cmd) + 2,
	FATAL_ERROR);
	ft_strcpy(full_path, cmd_path);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	return (full_path);
}

static int	get_program_ret_value(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}

static void	son_execute_prog(char *full_path, char **real_args, char **env,
												struct s_msh_cmd *cur_node)
{
	execve(full_path, real_args, env);
	ft_putstr_fd("minishell: exec format error: ", STDERR_FILENO);
	ft_putstr_fd(cur_node->cmd, STDERR_FILENO);
	ft_putchar('\n');
	exit(1);
}

int			execute_program(struct s_msh_cmd *cur_node, const char *cmd_path,
																char **env)
{
	char		*full_path;
	pid_t		fork_ret;
	int			status;
	char		**real_args;

	real_args = NULL;
	status = 1;
	full_path = get_full_path(cmd_path, cur_node->cmd);
	real_args = set_real_args(cur_node);
	if ((fork_ret = fork()) == -1)
		ft_exit(FATAL_ERROR, "Call to fork() failed\n");
	if (fork_ret == 0)
		son_execute_prog(full_path, real_args, env, cur_node);
	else
	{
		g_cmd_status.cmd_running = true;
		g_cmd_status.pid = fork_ret;
		wait(&status);
		g_cmd_status.cmd_running = false;
	}
	status = get_program_ret_value(status);
	free(real_args);
	free(full_path);
	return (status);
}
