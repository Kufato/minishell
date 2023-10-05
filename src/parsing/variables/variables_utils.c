/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:49:28 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/08 16:10:57 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	char_is_valid(char c)
{
	int		i;
	char	*tab;

	i = 0;
	tab = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
	while (tab[i])
	{
		if (tab[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	check_flag(int flag, char c)
{
	if (c == '\'' && flag == 0)
		flag = 1;
	else if (c == '\'' && flag == 1)
		flag = 0;
	else if (c == '\"' && flag == 0)
		flag = 2;
	else if (c == '\"' && flag == 2)
		flag = 0;
	return (flag);
}

int	check_just_dollar(char *str)
{
	int	i;

	i = 1;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '\'' || str[i] == '\"'
		|| str[i] == '|' || str[i] == '\0'
		|| str[i] == '<' || str[i] == '>')
		return (1);
	return (0);
}

int	check_var_heredoc(char *str, int i)
{
	while (i != 0 || str[i] == '|')
	{
		if (str[i] == '<' && str[i - 1] == '<')
			return (1);
		i--;
	}
	return (0);
}
