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

/*
**	builtins.c
*/
int		is_cmd_builtin(const char *cmd);
int		execute_builtin(char **args, int index, char **env);

/*
**	builtin_echo.c
*/
int		builtin_echo(char **args, char **env);

/*
**	builtin_cd.c
*/
int		builtin_cd(char **args, char **env);

/*
**	builtin_setenv.c
*/
int		builtin_setenv(char **args, char **env);

/*
**	builtin_unsetenv.c
*/
int		builtin_unsetenv(char **args, char **env);

/*
**	builtin_env.c
*/
int		builtin_env(char **args, char **env);

/*
**	builtin_exit.c
*/
int		builtin_exit(char **args, char **env);

#endif
