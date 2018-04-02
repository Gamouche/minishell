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

extern char	**environ;

static size_t	get_nb_env_var(void)
{
	size_t	i;

	i = 0;
	while (environ[i] != NULL)
		++i;
	return (i);
}

char			**init_my_env(void)
{
	char	**my_env;
	size_t	nb_env_var;

	nb_env_var = get_nb_env_var();
	my_env = ft_malloc(sizeof(char *) * (nb_env_var + 1), FATAL_ERROR);

	return (my_env);
}