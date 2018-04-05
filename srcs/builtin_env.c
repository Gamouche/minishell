/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:17:29 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 18:17:53 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/minishell.h"

int		builtin_env(char **args, char ***env)
{
	size_t	i;

	(void)args;
	i = 0;
	if (env != NULL)
		while ((*env)[i] != NULL)
		{
			write(STDOUT_FILENO, (*env)[i], ft_strlen((*env)[i]));
			write(STDOUT_FILENO, "\n", 1);
			++i;
		}
	return (BUILTIN_SUCCESS);
}
