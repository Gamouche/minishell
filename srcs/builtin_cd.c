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

#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "../includes/minishell.h"

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

int				go_to_dir(const char *path, char **env)
{
	int			ret_value;
	int			ret_chdir;
	size_t		i;
	struct stat	s_stat;

	if ((!(ret_value = BUILTIN_SUCCESS)) && path != NULL)
		ret_chdir = chdir(path);
	else
	{
		i = 0;
		while (ft_strncmp(env[i], "HOME", 4) != 0)
			++i;
		ret_chdir = chdir(env[i] + 5);
	}
	if (ret_chdir != 0)
	{
		if ((stat(path, &s_stat) == 0) && (!(S_ISDIR(s_stat.st_mode)))
		&& ft_write_n_strings_fd(STDERR_FILENO, 3, "cd: not a directory: ",
		path, "\n"))
			return (BUILTIN_ERROR);
		ft_write_n_strings_fd(STDERR_FILENO, 3,
		"cd: No such file or directory or permission denied: ", path, "\n");
		ret_value = BUILTIN_ERROR;
	}
	return (ret_value);
}

static	void	builtin_cd_2_norme_lol(char **args, char last_dir[],
									int *ret_value, char ***env)
{
	if (ft_strcmp(args[0], "-") == 0)
	{
		if (last_dir[0] == '\0')
			*ret_value = BUILTIN_SUCCESS;
		else
			*ret_value = go_to_dir(last_dir, *env);
	}
	else
		*ret_value = go_to_dir(args[0], *env);
}

int				builtin_cd(char **args, char ***env)
{
	static char	last_dir[1024] = {0};
	char		*cwd;
	int			ret_value;

	if (ft_get_nb_entities_2d_array(args) > 1)
	{
		write(STDERR_FILENO, "cd: Too many arguments\n", 23);
		return (BUILTIN_ERROR);
	}
	cwd = getcwd(NULL, 0);
	if (args == NULL)
	{
		if (home_is_valid(*env) == true)
			ret_value = go_to_dir(NULL, *env);
		else
			ret_value = BUILTIN_SUCCESS;
	}
	else
		builtin_cd_2_norme_lol(args, last_dir, &ret_value, env);
	if (ret_value == BUILTIN_SUCCESS && cwd != NULL)
		ft_strcpy(last_dir, cwd);
	free(cwd);
	return (ret_value);
}
