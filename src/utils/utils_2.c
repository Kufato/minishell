/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:29:59 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/13 17:43:12 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_tab_dup(char **tab)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * (get_env_size(tab) + 1));
	if (!new)
	{
		free(new);
		return (NULL);
	}
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
		{
			free_tab(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	*ft_secur_cat(char *s1, char *s2)
{
	int		s_s1;
	int		s_s2;
	char	*f_str;

	s_s1 = 0;
	s_s2 = 0;
	if (!s1 && !s2)
		return (NULL);
	s_s1 = ft_strlen(s1);
	s_s2 = ft_strlen(s2);
	f_str = malloc(sizeof(char) * (s_s1 + s_s2) + 1);
	if (s1)
	{
		ft_strlcpy(f_str, s1, s_s1 + 1);
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		ft_strlcpy(f_str + s_s1, s2, s_s2 + 1);
		free(s2);
		s2 = NULL;
	}
	return (f_str);
}

int	string_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && (str[i] != '\0' || str[i] != '\n'))
			return (1);
		i++;
	}
	return (0);
}

int	str_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && !is_space(str[i]))
			return (1);
		i++;
	}
	return (0);
}
