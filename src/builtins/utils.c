/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:05:20 by arforgea          #+#    #+#             */
/*   Updated: 2023/06/13 13:19:49 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_var_size(char *str)
{
	int	index;
	int	size;

	size = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == '"' || str[index] == '\'')
		{
			index++;
			continue ;
		}
		index++;
		size++;
	}
	return (size);
}

int	get_name_var_size(char *var)
{
	int	index;
	int	size;

	size = 0;
	index = 0;
	while (var[index] && var[index] != '=')
	{
		if (var[index] == '"' || var[index] == '\'')
		{
			index++;
			continue ;
		}
		index++;
		size++;
	}
	return (size);
}

int	is_var(char **envp, char *var)
{
	int	i;
	int	var_size;

	i = 0;
	var_size = get_name_var_size(var);
	while (envp[i])
	{
		if (!ft_strncmp(var, envp[i], var_size))
			return (1);
		i++;
	}
	return (0);
}

int	get_env_size(char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
		index++;
	return (index);
}
