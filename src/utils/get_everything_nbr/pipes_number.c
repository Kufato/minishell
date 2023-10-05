/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:00:01 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/06 13:17:33 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../inc/minishell.h"

int	get_pipes_number(char *cmd)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (cmd[i])
	{
		if (cmd[i] && (cmd[i] == '\"' || cmd[i] == '\''))
		{
			if (skip_argument(&cmd[i]))
				i += skip_argument(&cmd[i]);
		}
		if (cmd[i] && cmd[i] == '|')
			res++;
		i++;
	}
	return (res + 1);
}
