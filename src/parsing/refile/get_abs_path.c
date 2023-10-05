/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abs_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:24:03 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/16 14:34:48 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*get_good_path(char *cmd, char **envp_path)
{
	char	*path_bin;
	char	*path_tmp;
	int		index;

	index = -1;
	while (envp_path && envp_path[++index])
	{
		if (envp_path[index][ft_strlen(envp_path[index]) - 1] == '/')
			path_bin = ft_strjoin(envp_path[index], cmd);
		else
		{
			path_tmp = ft_strjoin(envp_path[index], "/");
			path_bin = ft_strjoin(path_tmp, cmd);
			free(path_tmp);
		}
		if (!access(path_bin, X_OK))
		{
			free_tab(envp_path);
			return (path_bin);
		}
		free(path_bin);
	}
	free_tab(envp_path);
	return (NULL);
}

static char	*r_place(char *str)
{
	char	*tmp;

	if (!ft_strncmp(str, "PATH=", 5))
	{
		tmp = ft_substr(str, 5, (ft_strlen(str) - 5));
		free(str);
		return (tmp);
	}
	else
		return (str);
}

char	*get_abs_path(char *cmd, char **envp)
{
	int		i;
	int		fd;
	char	*path_bin;
	char	**envp_path;

	if (!cmd || !envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	envp_path = ft_split(envp[i], ':');
	envp_path[0] = r_place(envp_path[0]);
	fd = open(cmd, O_DIRECTORY);
	if (!access(cmd, X_OK) && fd == -1)
	{
		free_tab(envp_path);
		path_bin = ft_strdup(cmd);
	}
	else
		path_bin = get_good_path(cmd, envp_path);
	if (fd > 2)
		close(fd);
	return (path_bin);
}
