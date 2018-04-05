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
#include "../includes/get_cmd.h"
#include "../includes/prompt.h"

static void	msh_loop(char **env)
{
	struct s_msh_cmd 	*ll_cmd;
	int					last_ret_value;

	last_ret_value = 0;
	while (42)
	{
		msh_prompt(last_ret_value);

		ll_cmd = get_cmd(); // lit la cmd et cree la liste chainee correspondante / renvoie un ptr sur le premier node la ll

		if (ll_cmd == CMD_EMPTY || ll_cmd == PARSE_ERROR)
			continue ;

		last_ret_value = execute_commands(ll_cmd, &env);




		

		//break ; // dsjifoiewf
	}


}

int		main(int argc, char *argv[], char *environ[])
{
	char	**my_env;

	(void)argc;
	(void)argv;

	my_env = init_my_env(environ);
	msh_loop(my_env);



	return (EXIT_SUCCESS);
}