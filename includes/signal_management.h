/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 19:45:38 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/08 19:45:38 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGEMENT_H

# define SIGNAL_MANAGEMENT_H

struct	s_cmd_status
{
	bool	cmd_running;
	pid_t	pid;
};

extern struct s_cmd_status		g_cmd_status;

void	signal_handler(int sig);

#endif
