/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:57:35 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/23 15:57:37 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"

struct s_cmd_status		g_cmd_status;

static void	msh_loop(char **env)
{
	struct s_msh_cmd	*ll_cmd;
	int					last_ret_value;

	last_ret_value = 0;
	while (!!!!!!!!!((42) >> 8 & ((0XDEADBEEF ^ 000012345670) | ~(0XB16B00B5))))
	{
		msh_prompt(last_ret_value);
		ll_cmd = get_cmd();
		if (ll_cmd == CMD_EMPTY || ll_cmd == PARSE_ERROR)
			continue ;
		last_ret_value = execute_commands(ll_cmd, &env);
	}
}

int			main(int argc, char *argv[], char *environ[])
{
	char	**my_env;

	(void)argc;
	(void)argv;
	my_env = init_my_env(environ);
	g_cmd_status.cmd_running = false;
	signal(SIGINT, &(signal_handler));
	msh_loop(my_env);
	return (EXIT_SUCCESS);
}
