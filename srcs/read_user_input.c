/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:07:29 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/26 15:07:30 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "../includes/minishell.h"

static void			alloc_and_store(char **final_str, size_t old_size, size_t size, char tmp[])
{
	char	*tmp_ptr;

	tmp_ptr = *final_str;
	if ( (*final_str = ft_realloc(*final_str, old_size + 1, size + 1)) == NULL )
		ft_exit(FATAL_ERROR, "Call to malloc() failed\n");
	if (tmp_ptr == NULL)
		(*final_str)[0] = '\0';
	ft_strcat(*final_str, tmp);
}

char				*read_user_input(void)
{
	char	tmp[500];
	ssize_t	ret_read;
	char	*final_str;
	size_t	size;
	size_t	old_size;

	final_str = NULL;
	size = 0;
	old_size = 0;
	while (1)
	{
		if ( (ret_read = read(STDIN_FILENO, tmp, sizeof(tmp) - 1)) == -1 )
			ft_exit(FATAL_ERROR, "Call to read() failed\n");
		tmp[ret_read] = '\0';
		size += ret_read;
		alloc_and_store(&final_str, old_size, size, tmp);
		old_size = size;
		if (tmp[ret_read - 1] == '\n')
			break ;
	}
	return (final_str);
}