/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:19:37 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/13 18:08:57 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*final_variable(char *var, t_data *data, int j, int i)
{
	free(var);
	return (ft_substr(data->envp[j], i + 1, ft_strlen(data->envp[j]) - i));
}

static char	*get_variable(t_data *data, int index)
{
	int		i;
	int		j;
	char	*var;

	i = -1;
	j = -1;
	if (data->input[index + 1] == '?')
		return (ft_itoa(g_status));
	while (data->input[index + ++i])
	{
		if (data->input[index + i] && char_is_valid(data->input[index + i + 1]))
		{
			var = ft_substr(data->input, index + 1, i);
			while (data->envp[++j])
			{
				if (ft_strnstr(data->envp[j], var, i))
					return (final_variable(var, data, j, i));
			}
			if (data->envp[j] == NULL)
				break ;
		}
	}
	free(var);
	return (NULL);
}

static void	change_variables(t_data *data, char **new, int *i, int *j)
{
	*new = ft_secur_cat(*new, ft_substr(data->input, (*j), ((*i) - (*j))));
	*new = ft_secur_cat(*new, get_variable(data, (*i)));
	(*i)++;
	if (!data->input[(*i) + 1])
		(*i)++;
	if (data->input[(*i)] == '?')
		(*i)++;
	else if (data->input[(*i)])
	{
		while (!is_separator(data->input[(*i)]) && data->input[*i] != '$')
			(*i)++;
	}
	(*j) = (*i);
}

static void	skip_flag_replace(t_data *data, char **new, int *i, int *j)
{
	data->flag = check_flag(data->flag, data->input[*i]);
	if (data->input[*i] == '\'' && data->flag == 1)
		(*i) += (skip_argument(&data->input[*i]));
	else if (data->input[*i] == '$' && !check_var_heredoc(data->input, *i)
		&& !check_just_dollar(&data->input[*i]))
		change_variables(data, new, i, j);
}

char	*replace_variables(t_data *data)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = NULL;
	data->flag = 0;
	while (data->input[i])
	{
		skip_flag_replace(data, &new, &i, &j);
		if (data->input[i] == '\0' || data->input[i + 1] == '\0')
		{
			new = ft_secur_cat(new, ft_substr(data->input, j, (i - j) + 1));
			free(data->input);
			return (new);
		}
		else if (data->input[i] == '$' && !check_var_heredoc(data->input, i))
			continue ;
		i++;
	}
	free(data->input);
	return (new);
}
