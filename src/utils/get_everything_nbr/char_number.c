/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:08:58 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/06 13:16:38 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../inc/minishell.h"

int	get_chars_number(char *str, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i += skip_argument(&str[i]);
		if (str[i] && str[i] == c)
			res++;
		i++;
	}
	return (res);
}
