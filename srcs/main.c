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

void	func_destroy_list(struct s_msh_cmd *ll)
{
	struct s_msh_cmd *del;
	while (ll != NULL)
	{
		del = ll;
		ll = ll->next;
		free(del->cmd);
		if (del->args_cmd)
			for (int i = 0 ; (del->args_cmd)[i] != NULL ; ++i)
				free((del->args_cmd)[i]);
		free(del->args_cmd);
		free(del);
	}

}

void	msh_prompt(void)
{
	const char *prompt = "\e[1m\x1B[32mSERGE $> \x1B[0m";
	ft_putstr(prompt);
}

void	msh_loop(void)
{
	struct s_msh_cmd *ll_cmd;

	while (42)
	{
		msh_prompt();

		ll_cmd = get_cmd(); // lit la cmd et cree la liste chainee correspondante / renvoie un ptr sur le premier node la ll

		if (ll_cmd == CMD_EMPTY)
			continue ;

		// func_exec()   execute les cmd de la liste chainee

		func_destroy_list(ll_cmd); //   detruit correctement la liste chainee pour laisser place a une nouvelle



		

		//break ; // dsjifoiewf
	}


}

int		main(void)
{
	msh_loop();



	return (EXIT_SUCCESS);
}