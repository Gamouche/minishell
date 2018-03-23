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

void	msh_loop(void)
{
	struct s_msh_cmd *ll_cmd;

	while (42)
	{
		ll_cmd = get_cmd(); // lit la cmd et cree la liste chainee correspondante / renvoie un ptr sur le premier node la ll

		// func_exec()   execute les cmd de la liste chainee

		// func_destroy_list   detruit correctement la liste chainee pour laisser place a une nouvelle



		

		break ; // dsjifoiewf
	}


}

int		main(void)
{
	msh_loop();



	return (EXIT_SUCCESS);
}