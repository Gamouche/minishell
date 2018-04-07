/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_nb_entities_2d_array.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 21:45:06 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/07 21:45:11 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_get_nb_entities_2d_array(char **array)
{
	size_t	i;

	if (array == NULL)
		return (0);
	i = 0;
	while (array[i] != NULL)
		++i;
	return (i);
}
