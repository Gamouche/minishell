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
#include "../includes/minishell.h"

static size_t	get_nb_args(char **args)
{
	size_t	nb;

	nb = 0;
	if (args != NULL)
	{
		while (args[nb] != NULL)
			++nb;
	}
	return (nb);
}

static int		entry_already_exist(char **env, const char *entry) // renvoie l'index de l'entry ou alors -1 si elle n'existe pas
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

static size_t	get_actual_nb_entry(char **env)
{
	size_t	nb;

	nb = 0;
	while (env[nb] != NULL)
		++nb;
	return (nb);
}

static void		add_entry(char ***env, const char *entry, const char *value)
{
	char	**new_env;
	size_t	nb_entry;
	size_t	i;
	
	nb_entry = get_actual_nb_entry(*env);
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

	new_env[i] = ft_malloc(ft_strlen(entry) + ft_strlen(value) + 2, FATAL_ERROR);
	ft_strcpy(new_env[i], entry);
	ft_strcat(new_env[i], "=");
	ft_strcat(new_env[i], value);

	free(*env);
	*env = new_env;
	// go la creer
	// compter le nb d'entry, puis malloc(nb_entry + 2) (plus 2 pour NULL et la nouvelle)
	// on copie les entry actuelles, et on ajoute la nouvelle

}

int				builtin_setenv(char **args, char ***env)
{
	// je prends 2 argument, sinon warning et on fait rien
	// supprimer l'entree si elle existe deja
	// creer (ou recreer) l'entree

	if (get_nb_args(args) != 2)
	{
		write(STDERR_FILENO, "usage: setenv [KEY] [VALUE]\n", 28);
		return (BUILTIN_ERROR);
	}

	if (entry_already_exist(*env, args[0]) != NO_ENTRY)
	{
		//replace_entry();
		// go la supprimer et la remplacer
		// trouver le ptr sur char qui pointe sur l'entry, le free et le re;placer par une nouvelle entry
	}

	else
		add_entry(env, args[0], args[1]);


	return (BUILTIN_SUCCESS);
}
