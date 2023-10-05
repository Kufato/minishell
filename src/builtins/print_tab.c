/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:05:10 by arforgea          #+#    #+#             */
/*   Updated: 2023/06/13 21:09:43 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tab(char **array)
{
	int	i;
	int	j;

	i = -1;
	while (array[++i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (array[i][j])
		{
			if (array[i][j] == '=')
			{
				ft_putchar_fd(array[i][j], 1);
				ft_putchar_fd('\"', 1);
				j++;
				while (array[i][j])
					ft_putchar_fd(array[i][j++], 1);
				ft_putchar_fd('\"', 1);
			}
			if (array[i][j])
				ft_putchar_fd(array[i][j++], 1);
		}
		ft_putchar_fd('\n', 1);
	}
	return ;
}

void	print_tab_sort(char **tab)
{
	char	**tab_tmp;
	int		index;
	char	*tmp;

	index = 0;
	tab_tmp = ft_tab_dup(tab);
	while (tab_tmp[index] && tab_tmp[index + 1])
	{
		if (ft_strncmp(tab_tmp[index], tab_tmp[index + 1], 10) > 0)
		{
			tmp = tab_tmp[index];
			tab_tmp[index] = tab_tmp[index + 1];
			tab_tmp[index + 1] = tmp;
			index = 0;
			continue ;
		}
		index++;
	}
	print_tab(tab_tmp);
	free_tab(tab_tmp);
	return ;
}
