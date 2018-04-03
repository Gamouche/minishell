/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 21:59:00 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/02 21:59:01 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	get_nb_env_var(char **environ)
{
	size_t	i;

	i = 0;
	while (environ[i] != NULL)
		++i;
	return (i);
}

void		copy_environ(char **my_env, char **environ)
{
	size_t	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if ((my_env[i] = ft_strdup(environ[i])) == NULL)
			ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
		++i;
	}
}

char			**init_my_env(char **environ)
{
	char		**my_env;
	size_t		nb_env_var;

	nb_env_var = get_nb_env_var(environ);
	my_env = ft_malloc(sizeof(char *) * (nb_env_var + 1), FATAL_ERROR);
	my_env[nb_env_var] = NULL;
	copy_environ(my_env, environ);

	return (my_env);
}