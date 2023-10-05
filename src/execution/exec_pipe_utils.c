/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:56:28 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/16 14:15:15 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_directory(char *str)
{
	int	fd;

	fd = open(str, O_DIRECTORY);
	if (fd != -1)
	{
		printf("minishell: %s: Is a directory\n", str);
		g_status = 126;
		close(fd);
		return (1);
	}
	return (0);
}

int	check_exec(char *str)
{
	int	i;
	int	fd;

	i = 0;
	if (str && !ft_strncmp(str, "./", 2))
	{
		fd = open(str, O_RDONLY);
		if (fd == -1)
		{
			perror(str);
			if (access(str, F_OK) == -1)
				g_status = 127;
			else
				g_status = 126;
			return (1);
		}
		close(fd);
		if (check_directory(str))
			return (1);
	}
	return (0);
}

void	close_all(int *fds, int fd_in)
{
	close(fd_in);
	close(fds[0]);
	close(fds[1]);
}

void	free_fork(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->tab_pid)
		free(data->tab_pid);
	if (data->envp)
		free_tab(data->envp);
	lst_destroy(data->dtt);
	if (data)
		free(data);
}

void	wait_all_pid(t_data *data, int *tab_pid)
{
	int	i;
	int	status;

	i = 0;
	if (tab_pid)
	{
		while (i != data->nb_cmd)
		{
			if (tab_pid[i] != 0)
				waitpid(tab_pid[i], &status, 0);
			if (g_status == 131)
				ft_putstr_fd("Quit core dumped\n", 2);
			if (tab_pid[i] && WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			i++;
		}
	}
	signal(SIGINT, mini_sigint);
}
