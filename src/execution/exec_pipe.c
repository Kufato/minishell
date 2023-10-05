/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:28:36 by arforgea          #+#    #+#             */
/*   Updated: 2023/06/16 16:00:54 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	all_dup2(t_exec *dtt, int *fds, int fd_in)
{
	if (dtt->fd_in > 2)
	{
		dup2(dtt->fd_in, 0);
		close(dtt->fd_in);
	}
	else if (dtt->back && dtt->fd_in <= 2)
	{
		dup2(fd_in, 0);
		if (fd_in != -1)
			close(fd_in);
	}
	if (dtt->fd_out > 2)
	{
		dup2(dtt->fd_out, 1);
		close (dtt->fd_out);
	}
	else if (dtt->next && dtt->fd_out <= 2)
	{
		dup2(fds[1], 1);
		close(fds[1]);
		close(fds[0]);
	}
}

static int	fork_exec(t_data *data, t_exec *dtt, int *fds, int fd_in)
{
	pid_t	pid;

	signal_exec();
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (!pid)
	{
		all_dup2(dtt, fds, fd_in);
		close_all(fds, fd_in);
		if (!dtt->abs_path && dtt->cmd)
		{
			ft_putstr_fd("Command not found\n", 2);
			g_status = 127;
		}
		else if (!check_after_fork(data, dtt) && dtt->cmd)
		{
			g_status = 0;
			execve(dtt->abs_path, dtt->full_cmd, data->envp);
		}
		free_fork(data);
		exit (g_status);
	}
	return (pid);
}

static int	ft_pipe(t_data *data, t_exec *dtt, int *pid, int fd_in)
{
	int		fds[2];
	t_exec	*ptr;

	ptr = dtt;
	if (pipe(fds))
	{
		perror("pipe");
		return (1);
	}
	if (fd_in == -1)
		fd_in = fds[0];
	*pid = fork_exec(data, ptr, fds, fd_in);
	close(fds[1]);
	if (fd_in > 0)
		close(fd_in);
	return (fds[0]);
}

static void	exec_core(t_data *data, t_exec *ptr, int *fd_in, int i)
{
	if (!ft_strncmp(ptr->cmd, "exit", 4) && !ptr->next)
	{
		close(*fd_in);
		ft_exit(data, data->dtt);
		data->tab_pid[i] = 0;
	}
	else if (check_exec(ptr->cmd))
		data->tab_pid[i] = 0;
	else if (!check_before_fork(data, ptr) && ptr->fd_in != -1)
	{
		*fd_in = ft_pipe(data, ptr, &data->tab_pid[i], *fd_in);
		if (g_status != 130)
			g_status = 0;
	}
	else
		data->tab_pid[i] = 0;
}

int	exec_pipeline(t_data *data)
{
	int		i;
	int		fd_in;
	t_exec	*ptr;

	i = 0;
	ptr = data->dtt;
	fd_in = dup(0);
	if (data->nb_cmd > 0)
	{
		data->tab_pid = malloc(sizeof(pid_t) * data->nb_cmd);
		while (ptr)
		{
			if (ptr->cmd)
				exec_core(data, ptr, &fd_in, i);
			ptr = ptr->next;
			i++;
		}
		wait_all_pid(data, data->tab_pid);
		signal(SIGQUIT, SIG_IGN);
		free(data->tab_pid);
	}
	if (fd_in > 0)
		close(fd_in);
	return (0);
}
