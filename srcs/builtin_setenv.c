/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:17:23 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 18:17:47 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../includes/minishell.h"

int				entry_already_exist(char **env, const char *entry)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], entry, ft_strlen(entry)) == 0)
			return (i);
		++i;
	}
	return (NO_ENTRY);
}

static void		add_entry(char ***env, const char *entry, const char *value)
{
	char	**new_env;
	size_t	nb_entry;
	size_t	i;

	nb_entry = ft_get_nb_entities_2d_array(*env);
	new_env = ft_malloc(sizeof(char *) * (nb_entry + 2), FATAL_ERROR);
	new_env[nb_entry + 1] = NULL;
	i = 0;
	while (i < nb_entry)
	{
		if ((new_env[i] = ft_strdup((*env)[i])) == NULL)
			ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
		free((*env)[i]);
		++i;
	}
	new_env[i] = ft_malloc(ft_strlen(entry) + ft_strlen(value) + 2,
	FATAL_ERROR);
	ft_strcpy(new_env[i], entry);
	ft_strcat(new_env[i], "=");
	ft_strcat(new_env[i], value);
	free(*env);
	*env = new_env;
}

static void		replace_entry(char **env, const char *entry, const char *value,
																	int index)
{
	free(env[index]);
	env[index] = ft_malloc(ft_strlen(entry) + ft_strlen(value) + 2,
	FATAL_ERROR);
	ft_strcpy(env[index], entry);
	ft_strcat(env[index], "=");
	ft_strcat(env[index], value);
}

int				builtin_setenv(char **args, char ***env)
{
	int		index;

	if (ft_get_nb_entities_2d_array(args) != 2)
	{
		write(STDERR_FILENO, "usage: setenv [KEY] [VALUE]\n", 28);
		return (BUILTIN_ERROR);
	}
	if ((index = entry_already_exist(*env, args[0])) != NO_ENTRY)
		replace_entry(*env, args[0], args[1], index);
	else
		add_entry(env, args[0], args[1]);
	return (BUILTIN_SUCCESS);
}
