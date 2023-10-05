/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtt_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:49:35 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/16 10:34:27 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	set_values(t_exec *dtt)
{
	dtt->abs_path = NULL;
	dtt->cmd = NULL;
	dtt->full_cmd = NULL;
}

t_data	*dtt_init(t_data *data)
{
	t_exec	*dtt;
	t_exec	*tmp;
	int		cmp;

	dtt = NULL;
	dtt = malloc(sizeof(t_exec));
	if (!dtt)
		return (NULL);
	dtt->back = NULL;
	tmp = dtt;
	set_values(tmp);
	cmp = 0;
	while (++cmp < get_pipes_number(data->input))
	{
		tmp->next = malloc(sizeof(t_exec));
		set_values(tmp->next);
		if (!tmp->next)
			return (NULL);
		tmp->next->back = tmp;
		tmp = tmp->next;
	}
	tmp->next = NULL;
	data->dtt = dtt;
	data->nb_cmd = 0;
	return (data);
}
