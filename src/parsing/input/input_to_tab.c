/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:13:28 by arforgea          #+#    #+#             */
/*   Updated: 2023/06/08 15:21:10 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*refactor_str(char *str)
{
	int		i;
	int		j;
	char	tmp;
	char	*res;

	i = 0;
	j = 0 ;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] && (str[i] == '\"' || str[i] == '\''))
		{
			tmp = str[i];
			res[j++] = str[i++];
			while (str[i] && str[i] != tmp)
				res[j++] = str[i++];
			res[j++] = str[i++];
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

char	**input_to_tab(char *input)
{
	char				**f_tab;
	char				*str_tmp;
	unsigned int		index;

	index = 0;
	f_tab = turbo_split(input, '|');
	while (f_tab[index])
	{
		str_tmp = refactor_str(f_tab[index]);
		free(f_tab[index]);
		f_tab[index] = str_tmp;
		index++;
	}
	return (f_tab);
}
