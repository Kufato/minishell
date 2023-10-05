/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:05:25 by arforgea          #+#    #+#             */
/*   Updated: 2023/06/13 13:19:41 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] != '=' && s2[i] == s1[i])
		i++;
	if (s2[i] == '=')
		return (1);
	return (0);
}

static int	remove_string(char ***arr, char *str)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = malloc(sizeof(char *) * (get_env_size((*arr))));
	if (!new_envp)
		return (1);
	i = 0;
	j = 0;
	while ((*arr)[i] != NULL)
	{
		if (compare(str, (*arr)[i]))
		{
			i++;
			continue ;
		}
		new_envp[j] = ft_strdup((*arr)[i]);
		j++;
		i++;
	}
	new_envp[get_env_size(*arr) - 1] = NULL;
	free_tab((*arr));
	*arr = new_envp;
	return (0);
}

static int	check(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '-')
		{
			printf("bash: `%c%c' invalid option\n", str[i], str[i + 1]);
			g_status = 2;
			return (1);
		}
		i++;
	}
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		printf("bash: unset: `%s': not a valid identifier\n", str);
		g_status = 1;
		return (1);
	}
	return (0);
}

int	ft_unset(char ***envp, char **tab_cmd)
{
	int		i;
	int		index;

	index = 0;
	if (!tab_cmd[1])
	{
		printf("unset: not enough arguments");
		return (1);
	}
	while (tab_cmd[++index])
	{
		if (!check(tab_cmd[index]))
		{
			i = -1;
			while ((*envp)[++i])
			{
				if (compare(tab_cmd[index], (*envp)[i]))
				{
					remove_string(envp, tab_cmd[index]);
					break ;
				}
			}
		}
	}
	return (0);
}
