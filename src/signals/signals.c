/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:47:39 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/13 21:14:49 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	mini_sigint(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_status = 130;
	}
	return ;
}

void	mini_sigint_fork(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	g_status = 130;
}

void	mini_sigquit_fork(int signal)
{
	(void)signal;
	g_status = 131;
}

void	mini_sigint_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		close(0);
		ft_putchar_fd('\n', 1);
		g_status = 3;
	}
}
