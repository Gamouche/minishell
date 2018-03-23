/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 13:56:08 by cyfermie          #+#    #+#             */
/*   Updated: 2018/01/13 13:56:25 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned	ft_abs(int nb)
{
	return ((nb < 0) ? -(unsigned int)nb : (unsigned int)nb);
}
