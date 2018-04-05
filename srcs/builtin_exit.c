/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:17:32 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 18:17:54 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"

int		builtin_exit(struct s_msh_cmd *cur_node, char **env)
{
	size_t	i;

	func_destroy_list(cur_node);
	if (env != NULL)
	{
		i = 0;
		while (env[i] != NULL)
		{
			free(env[i]);
			++i;
		}
		free(env);
	}
	exit(EXIT_SUCCESS);
}
