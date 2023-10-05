/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtt_refile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:56:54 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/13 13:20:08 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_data	*dtt_refile(t_data *data)
{
	int		i;
	char	**tab;
	t_exec	*tmp;

	i = 0;
	tab = input_to_tab(data->input);
	tmp = data->dtt;
	while (tab[i])
	{
		tmp = refile_exec(data, tmp, tab, &tab[i]);
		if (!tmp)
		{
			free_tab(tab);
			write(2, "Error: dtt_refile.", 18);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	free_tab(tab);
	return (data);
}
