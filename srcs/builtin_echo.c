/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:17:03 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 18:17:11 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "../includes/minishell.h"

static bool	n_option(char **args)
{
	if (args == NULL)
		return (false);
	if (ft_strcmp(args[0], "-n") == 0)
		return (true);
	return (false);
}

int			builtin_echo(char **args, char ***env)
{
	bool	newline;
	size_t	index;

	(void)env;
	newline = n_option(args);
	index = (newline == true) ? (1) : (0);

	if (args != NULL)
		while (args[index] != NULL)
		{
			write(STDOUT_FILENO, args[index], ft_strlen(args[index]));
			write(STDOUT_FILENO, " ", 1);
			++index;
		}
	if (newline == false)
		write(STDOUT_FILENO, "\n", 1);
	return (BUILTIN_SUCCESS);
}
