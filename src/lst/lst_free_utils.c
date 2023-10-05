/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_free_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 11:37:47 by arforgea          #+#    #+#             */
/*   Updated: 2023/06/16 15:38:30 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	cmd_link_value_free(t_exec *ptr)
{
	if (!ptr)
		return ;
	if (ptr->cmd)
		free(ptr->cmd);
	if (ptr->abs_path)
		free(ptr->abs_path);
	if (ptr->full_cmd)
		free_tab(ptr->full_cmd);
	if (ptr->fd_in > 2)
		close(ptr->fd_in);
	if (ptr->fd_out > 2)
		close(ptr->fd_out);
	return ;
}

void	exec_lst_free(t_exec *ptr)
{
	t_exec	*next;
	t_exec	*current;

	current = ptr;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	return ;
}

void	lst_destroy(t_exec *ptr)
{
	t_exec	*next;
	t_exec	*current;

	current = ptr;
	while (current)
	{
		next = current->next;
		if (current->cmd)
			cmd_link_value_free(current);
		free(current);
		current = next;
	}
	return ;
}
