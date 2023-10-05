/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:17:37 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/08 15:02:07 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	signals_disabled(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_heredoc(void)
{
	signal(SIGINT, mini_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, mini_sigint_fork);
	signal(SIGQUIT, mini_sigquit_fork);
}
