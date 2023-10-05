/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:39:12 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/13 13:20:34 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*get_str(char *str, int *index, int *j, char c)
{
	char	*f_tab;

	f_tab = NULL;
	while (str && index && str[*index])
	{
		if (str[*index + *j] == '\"' || str[*index + *j] == '\'')
			*j += skip_argument(&str[*index + *j]);
		if (str[*index + *j] == c || str[*index + *j] == '\0')
		{
			f_tab = malloc(sizeof(char) * (*j + 1));
			if (!f_tab)
				return (NULL);
			ft_memcpy(f_tab, &str[*index], *j);
			f_tab[*j] = '\0';
			*index += *j + 1;
			break ;
		}
		(*j)++;
	}
	return (f_tab);
}

char	**turbo_split(char *str, char c)
{
	int		i;
	int		j;
	int		index;
	char	**f_tab;

	i = 0;
	j = 0;
	index = 0;
	f_tab = malloc(sizeof(char *) * (get_chars_number(str, c) + 2));
	if (!f_tab)
		return (NULL);
	while (i <= get_chars_number(str, c))
	{
		f_tab[i] = get_str(str, &index, &j, c);
		i++;
		j = 0;
	}
	f_tab[i] = NULL;
	return (f_tab);
}
