/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:41:07 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/16 16:23:37 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_after_fork(t_data *data, t_exec *dtt)
{
	if (!ft_strncmp(dtt->cmd, "echo", 5))
		ft_echo(dtt->full_cmd);
	else if (!ft_strncmp(dtt->cmd, "exit", 5))
		ft_exit(data, dtt);
	else if (!ft_strncmp(dtt->cmd, "pwd", 4))
		ft_pwd(dtt);
	else if (!ft_strncmp(dtt->cmd, "env", 4))
		ft_env(dtt, data->envp);
	else if (!ft_strncmp(dtt->cmd, "cd", 3))
		ft_cd(data, dtt);
	else if (!ft_strncmp(dtt->cmd, "export", 7))
		ft_export(&data->envp, dtt->full_cmd);
	else if (!ft_strncmp(dtt->cmd, "unset", 6))
		ft_unset(&data->envp, dtt->full_cmd);
	else
		return (0);
	return (1);
}

int	check_before_fork(t_data *data, t_exec *dtt)
{
	if (dtt->next)
		return (0);
	if (!ft_strncmp(dtt->cmd, "cd", 3))
		ft_cd(data, dtt);
	else if (!ft_strncmp(dtt->cmd, "export", 7))
		ft_export(&data->envp, dtt->full_cmd);
	else if (!ft_strncmp(dtt->cmd, "unset", 6))
		ft_unset(&data->envp, dtt->full_cmd);
	else
		return (0);
	return (1);
}

int	check_builtins(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}
