/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:04:56 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/13 13:19:25 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_char_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_env(t_exec *dtt, char **envp)
{
	int	i;

	i = 0;
	if (dtt->full_cmd[1])
	{
		perror(dtt->full_cmd[1]);
		if (dtt->full_cmd[1][0] == '-')
			g_status = 125;
		else
			g_status = 127;
		return (1);
	}
	while (envp[i])
	{
		if (check_char_equal(envp[i]))
			printf("%s\n", envp[i]);
		i++;
	}
	return (1);
}
