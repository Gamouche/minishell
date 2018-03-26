/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:00:37 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/26 15:00:43 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/libft.h"

void	ft_exit(int exit_value, const char *msg)
{
	if (msg != NULL)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(exit_value);
}
