/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:17:26 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 18:17:51 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cpy_env(char ***env, char **new_env, size_t new_size, size_t index)
{
	size_t	i_env;
	size_t	i_new_env;

	i_env = 0;
	i_new_env = 0;
	while (i_env < new_size + 1)
	{
		if (i_env != index)
		{
			if ((new_env[i_new_env] = ft_strdup((*env)[i_env])) == NULL)
				ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
			++i_new_env;
		}
		free((*env)[i_env]);
		++i_env;
	}
	free(*env);
	*env = new_env;
}

static void	delete_entry(char ***env, int index)
{
	char	**new_env;
	size_t	new_size;

	new_size = ft_get_nb_entities_2d_array(*env) - 1;
	if (new_size == 0)
	{
		free((*env)[0]);
		(*env)[0] = NULL;
		return ;
	}
	new_env = ft_malloc(sizeof(char *) * (new_size + 1), FATAL_ERROR);
	new_env[new_size] = NULL;
	cpy_env(env, new_env, new_size, index);
}

int			builtin_unsetenv(char **args, char ***env)
{
	int		index;
	size_t	nb_entry;

	if ((nb_entry = ft_get_nb_entities_2d_array(args)) == 0)
	{
		ft_putstr_fd("unsetenv: not enough arguments\n", STDERR_FILENO);
		return (BUILTIN_ERROR);
	}
	while (nb_entry > 0)
	{
		if ((index = entry_already_exist(*env, args[nb_entry - 1])) != NO_ENTRY)
		{
			delete_entry(env, index);
		}

		--nb_entry;
	}

	return (BUILTIN_SUCCESS);
}
