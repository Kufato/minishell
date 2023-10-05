/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:05:00 by arforgea          #+#    #+#             */
/*   Updated: 2023/06/13 18:33:40 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_format_var(char *var)
{
	char	*new_var;
	int		i;
	int		j;

	new_var = malloc(sizeof(char) * get_var_size(var) + 1);
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '\'' || var[i] == '"')
		{
			i++;
			continue ;
		}
		new_var[j] = var[i];
		j++;
		i++;
	}
	new_var[j] = '\0';
	return (new_var);
}

static char	**change_var(char **envp, char *var)
{
	char	**new_envp;
	int		var_size;
	int		envp_size;
	int		i;

	envp_size = get_env_size(envp);
	var_size = get_name_var_size(var);
	if (!ft_strchr(var, '='))
		return (ft_tab_dup(envp));
	new_envp = malloc(sizeof(char *) * (envp_size + 1));
	i = 0;
	while (i < envp_size)
	{
		if (!ft_strncmp(var, envp[i], var_size))
			new_envp[i] = get_format_var(var);
		else
			new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

static char	**add_var(char **envp, char *var)
{
	char	**new_envp;
	int		var_size;
	int		envp_size;
	int		i;

	envp_size = get_env_size(envp);
	var_size = get_name_var_size(var);
	new_envp = malloc(sizeof(char *) * (envp_size + 2));
	i = 0;
	while (i < envp_size)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = get_format_var(var);
	new_envp[i + 1] = NULL;
	return (new_envp);
}

static int	check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		g_status = 2;
		printf("bash: export: %s: invalid option\n", str);
		return (1);
	}
	while (str[i])
	{
		if (i > 0 && str[i] == '=')
			break ;
		if (str[0] == '=' || (str[i] && (!ft_isalpha(str[i]) && str[i] != '_')))
		{
			g_status = 1;
			printf("bash: export: `%s': not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(char ***envp, char **tab_cmd)
{
	int		index;
	char	**new_envp;

	index = 1;
	if (!tab_cmd[1])
	{
		print_tab_sort(*envp);
		return (0);
	}
	while (tab_cmd[index])
	{
		tab_cmd[index] = str_without_quotes(tab_cmd[index]);
		if (!check(tab_cmd[index]))
		{
			if (is_var(*envp, tab_cmd[index]))
				new_envp = change_var(*envp, tab_cmd[index]);
			else
				new_envp = add_var(*envp, tab_cmd[index]);
			free_tab(*envp);
			*envp = new_envp;
		}
		index++;
	}
	return (0);
}
