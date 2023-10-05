/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:30:42 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/14 16:28:02 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cd_errors(t_exec *ptr)
{
	if (!ptr->full_cmd[1])
	{
		ft_putstr_fd("cd: wrong number of arguments\n", 2);
		g_status = 1;
		return (1);
	}
	if (ptr->full_cmd && ptr->full_cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_status = 1;
		return (1);
	}
	return (0);
}

static void	change_vars(char ***envp, char *var)
{
	char	pwd[PATH_MAX];
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	tmp[0] = ft_strdup("export");
	getcwd(pwd, sizeof(pwd));
	tmp[1] = ft_strjoin(var, pwd);
	tmp[2] = NULL;
	ft_export(envp, tmp);
	free_tab(tmp);
}

static char	*for_the_tild(char *str)
{
	char	*tmp;

	if (str[1])
	{
		tmp = ft_substr(str, 1, ft_strlen(str));
		free(str);
		str = ft_strjoin(getenv("HOME"), tmp);
		free(tmp);
	}
	else
	{
		free(str);
		str = ft_strdup(getenv("HOME"));
	}
	return (str);
}

int	ft_cd(t_data *data, t_exec *dtt)
{
	t_exec	*ptr;

	ptr = dtt;
	if (!cd_errors(ptr))
	{
		if (ptr->full_cmd[1][0] == '~')
			ptr->full_cmd[1] = for_the_tild(ptr->full_cmd[1]);
		change_vars(&data->envp, "OLDPWD=");
		if (chdir(ptr->full_cmd[1]))
		{
			perror(ptr->full_cmd[1]);
			g_status = 1;
			return (1);
		}
		change_vars(&data->envp, "PWD=");
		return (0);
	}
	return (1);
}
