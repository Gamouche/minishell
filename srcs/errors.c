/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:02:20 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/23 18:02:22 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/minishell.h"

void	my_exit(int exit_value, const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(exit_value);
}