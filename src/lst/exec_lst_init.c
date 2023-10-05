/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 10:11:33 by arforgea          #+#    #+#             */
/*   Updated: 2023/06/13 13:20:13 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	t_exec	*exec_link_create(void)
{
	t_exec	*current;

	current = malloc(sizeof(t_exec) * 1);
	if (!current)
	{
		write(2, "Error: exec_link_create.\n", 25);
		return (NULL);
	}
	current->next = NULL;
	current->back = NULL;
	current->cmd = NULL;
	return (current);
}

static	t_exec	*exec_lst_add(t_exec *current)
{
	t_exec	*tmp;

	if (!current)
	{
		write(2, "Error: exec_lst_add.\n", 21);
		return (NULL);
	}
	tmp = exec_link_create();
	if (!tmp)
		return (NULL);
	tmp->back = current;
	current->next = tmp;
	return (tmp);
}

t_exec	*exec_lst_init(int nbr)
{
	t_exec	*lst;
	t_exec	*tmp;

	if (nbr <= 0)
	{
		write(2, "Error: exec_lst_init.\n", 22);
		return (NULL);
	}
	lst = exec_link_create();
	tmp = lst;
	nbr--;
	while (nbr)
	{
		tmp = exec_lst_add(tmp);
		if (!tmp)
		{
			exec_lst_free(lst);
			return (NULL);
		}
		nbr--;
	}
	return (lst);
}
