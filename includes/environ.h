/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 21:55:43 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/02 21:55:44 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H

# define ENVIRON_H

/*
**	environ.c
*/
char	**init_my_env(char **environ);
size_t	get_nb_env_var(char **environ);
void	copy_environ(char **my_env, char **environ);

#endif
