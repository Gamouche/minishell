/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_n_strings_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 20:48:40 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/07 20:48:41 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "../includes/libft.h"

ssize_t		ft_write_n_strings_fd(int fd, size_t n, ...)
{
	va_list		ap;
	const char	*str;
	ssize_t		ret;
	ssize_t		tmp_ret;

	va_start(ap, n);
	ret = 0;
	while (n > 0)
	{
		str = va_arg(ap, const char *);
		if ((tmp_ret = write(fd, str, ft_strlen(str))) == -1)
			return (-1);
		ret += tmp_ret;
		--n;
	}
	va_end(ap);
	return (ret);
}
