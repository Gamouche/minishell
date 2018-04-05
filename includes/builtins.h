/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 16:49:59 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 16:50:27 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H

# define BUILTINS_H

# define NOT_BUILTIN (-1)
# define NB_BUILTINS (6)
# define BUILTIN_SUCCESS (0)
# define BUILTIN_ERROR (1)
# define BUILTIN_EXIT (NB_BUILTINS + 1)
# define NO_ENTRY (-1)

/*
**	builtins.c
*/
int		is_cmd_builtin(const char *cmd);
int		execute_builtin(struct s_msh_cmd *cur_node, int index, char ***env);


/*
**	builtin_echo.c
*/
int		builtin_echo(char **args, char ***env);

/*
**	builtin_cd.c
*/
int		builtin_cd(char **args, char ***env);

/*
**	builtin_setenv.c
*/
int		builtin_setenv(char **args, char ***env);

/*
**	builtin_unsetenv.c
*/
int		builtin_unsetenv(char **args, char ***env);

/*
**	builtin_env.c
*/
int		builtin_env(char **args, char ***env);

/*
**	builtin_exit.c
*/
int		builtin_exit(struct s_msh_cmd *cur_node, char **env);

#endif
