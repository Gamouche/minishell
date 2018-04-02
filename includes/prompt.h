/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 21:34:46 by cyfermie          #+#    #+#             */
/*   Updated: 2018/03/31 21:34:47 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H

# define PROMPT_H

# define GREEN  "\x1B[32m"
# define RED    "\x1B[31m"
# define BOLD   "\e[1m"
# define EOC	"\x1B[0m"

void	msh_prompt(int last_ret_value);
void	msh_prompt_complete_cmd(void);

#endif
