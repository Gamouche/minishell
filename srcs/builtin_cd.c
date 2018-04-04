/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:17:20 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 18:17:42 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "../includes/minishell.h"

static size_t	get_nb_args(char **args)
{
	size_t	nb;

	if (args == NULL)
		return (0);
	nb = 0;
	while (args[nb] != NULL)
		++nb;
	return (nb);
}

static bool		home_is_valid(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "HOME", 4) == 0)
		{
			if (ft_strlen(env[i] + 6) > 0)
				return (true);
			return (false);
		}
		++i;
	}
	return (false);
}

// cette fonction se rend au chemin du premier param. Si le premier param est NULL, alors la fonction va dans le chemin de HOME.
int		go_to_dir(const char *path, char **env)
{
	int		ret_value;

	if (path != NULL)
	{
		if (chdir(path) != 0)
		{
			write(STDERR_FILENO, "cd: No such file or directory: ", 31);
			write(STDERR_FILENO, path, ft_strlen(path));
			write(STDERR_FILENO, "\n", 1);
			return (BUILTIN_ERROR);
		}

	}
	else
	{
		//ret_value = go_to_home(env);
	}
	return (BUILTIN_SUCCESS);
}

int				builtin_cd(char **args, char **env)
{
	static char	last_dir[1024] = {0};
	char		*cwd;
	int			ret_value;

	if (get_nb_args(args) > 1)
	{
		write(STDERR_FILENO, "cd: Too many arguments\n", 23);
		return (BUILTIN_ERROR);
	}
	if ((cwd = getcwd(NULL, 0)) == NULL)
		ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
	if (args == NULL)
	{
		if (home_is_valid(env) == true)
			ret_value = go_to_dir(NULL, env);
		else
			ret_value = BUILTIN_SUCCESS;
	}
	else
	{
		if (ft_strcmp(args[0], "-") == 0)
		{
			if (last_dir[0] == '\0')
				ret_value = BUILTIN_SUCCESS;
			else
				ret_value = go_to_dir(last_dir, env);
		}
		else
			ret_value = go_to_dir(args[0], env);
	}

	if (ret_value == BUILTIN_SUCCESS)
		ft_strcpy(last_dir, cwd);
	free(cwd);
	return (ret_value);
}



/*

- algo simple : concatener pwd+ slash + argument, puis go dedans



*/