/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:17:20 by cyfermie          #+#    #+#             */
/*   Updated: 2018/04/04 18:17:42 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/minishell.h"

int		builtin_cd(char **args, char **env)
{
	static char	last_dir[1024];



}



/*

0 - gerer les arguments (trop d'arg par exemple ou option invalide)
{
	penser a --
	exemple : cd -- --   => le second -- c'est un dossier
			  cd -- -- -- -? trop d'arg
}

1 - si ya pas d'argument (args == NULL), ET si HOME n'existe pas ou est vide, alors il ne se passe rien

2 - si ya pas d'argument ET si HOME existe et n'est pas vide, ben on va la-bas

3 - si l'argument commence par slash, go step 7

4 - algo simple : concatener pwd+ slash + argument, puis go dedans







*/