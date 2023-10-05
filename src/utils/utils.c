/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:53:43 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/16 13:49:58 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_separator(char c)
{
	return (is_space(c) || c == '|' || c == '\''
		|| c == '\"' || c == '\0');
}

int	strlen_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*get_next_word(char *str)
{
	int		i;
	int		j;
	int		len_word;
	char	*next_word;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			i++;
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
		{
			len_word = strlen_word(&str[i]);
			next_word = malloc(sizeof(char) * (len_word + 1));
			while (j <= len_word)
				next_word[j++] = str[i++];
			next_word[j - 1] = '\0';
			return (next_word);
		}
	}
	return (NULL);
}

char	*str_without_quotes(char *str)
{
	int		i;
	int		j;
	char	tmp;
	char	*res;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] && (str[i] == '\"' || str[i] == '\''))
		{
			tmp = str[i++];
			while (str[i] && str[i] != tmp)
				res[j++] = str[i++];
		}
		else if (str[i])
			res[j++] = str[i++];
	}
	res[j] = '\0';
	free(str);
	return (res);
}
