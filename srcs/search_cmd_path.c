/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:10:23 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/03 18:10:24 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "../includes/minishell.h"

static char	*get_path_entry(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			break ;
		++i;
	}

	return (env[i]);
}

static bool	is_ok_for_perm(const char *path, const char *cmd)
{
	char		*full_path;
	struct stat	s_stat;

	full_path = ft_malloc(ft_strlen(path) + ft_strlen(cmd) + 2 ,FATAL_ERROR);
	ft_strcpy(full_path, path);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);

	//printf("perms test on = |%s|\n", full_path);

	stat(full_path, &s_stat);
	if (s_stat.st_mode & S_IXOTH)
	{
		free(full_path);
		return (true);
	}
	free(full_path);
	return (false);
}

static bool	is_good_path(const char *path, const char *cmd)
{
	DIR				*dir;
	struct dirent	*dirent;

	if ((dir = opendir(path)) == NULL)
		return (false);
	while ((dirent = readdir(dir)) != NULL)
	{
		if (ft_strcmp(dirent->d_name, cmd) == 0)
		{
			closedir(dir);
			return (true);
		}
	}
	closedir(dir);
	return (false);
}

static char	*test_paths(char **paths, const char *cmd)
{
	char	*cmd_path;
	size_t	i;

	i = 0;
	while (paths[i] != NULL)
	{
		if ( is_good_path(paths[i], cmd) == true )
		{											//printf("cmd = %s et path = %s\n", cmd, paths[i]);
			if ( is_ok_for_perm(paths[i], cmd) == true )
			{
				if ((cmd_path = ft_strdup(paths[i])) == NULL)
					ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
				return (cmd_path);
			}
			return (CMD_NOPERM);
		}

		++i;
	}

	return (CMD_NOT_FOUND);
}

char		*search_cmd_path(const char *cmd, char **env)
{
	char	*cmd_path;
	char	*path_entry;
	char	**cut_paths;
	size_t	i;

	if ((path_entry = get_path_entry(env)) == NULL)
		return (CMD_NOT_FOUND);
	if ((cut_paths = ft_strsplit(path_entry, ':')) == NULL)
		ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
	ft_memmove(&(cut_paths[0][0]), &(cut_paths[0][5]),  ft_strlen(cut_paths[0]) - 4);
	
	cmd_path = test_paths(cut_paths, cmd); // cherche le binaire dans les paths, et si il toruve il egarde quon a bien les droits exec
	if (cmd_path == CMD_NOT_FOUND)
		cmd_path = test_savage_cmd(cmd); // par exemple "../exec.out" je vais aller opendir le bon dossier et chercher exec.out et tester ses droits
	// test_savage_cmd() renvoie CMD_NOT_FOUND ou CMD_NOPERM ou un pointeur valide

	i = 0;
	while (cut_paths[i] != NULL)
	{
		free(cut_paths[i]);
		++i;
	}
	free(cut_paths);
	return (cmd_path);
}

