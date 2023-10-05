/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevrons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:35:54 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/16 16:48:43 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*get_file(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*res;

	i = 0;
	j = 0;
	count = 0;
	res = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i] && (str[i] == '<' || str[i] == '>') && count++ < 2)
		i++;
	if (str[i] && str[i] == ' ')
		i++;
	while (str[i] && (!is_space(str[i]) && str[i] != ' '
			&& str[i] != '\0' && str[i] != '|'))
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i++;
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

int	check_chevrons(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i += skip_argument(&str[i]);
		if (str[i] && (str[i] == '>' || str[i] == '<'))
			return (1);
		i++;
	}
	return (0);
}

int	is_rdir(char c)
{
	return (c == '<' || c == '>');
}

t_exec	*left_chevrons(t_exec *dtt, char *cmd)
{
	int		i;
	int		fd_tmp;
	char	*file;
	t_exec	*tmp;

	i = 0;
	tmp = dtt;
	file = get_file(&cmd[i]);
	if (cmd[i + 1] != '<')
	{
		if (tmp->fd_in > 2)
			close (tmp->fd_in);
		fd_tmp = open(file, O_RDONLY);
		if (fd_tmp == -1)
		{
			printf("minishell: %s: No such file or directory\n", file);
			g_status = 1;
		}
		tmp->fd_in = fd_tmp;
	}
	free(file);
	return (tmp);
}

t_exec	*right_chevrons(t_exec *dtt, char *cmd)
{
	int		i;
	int		fd_tmp;
	char	*file;
	t_exec	*tmp;

	i = 0;
	tmp = dtt;
	if (tmp->fd_out > 2)
		close (tmp->fd_out);
	file = get_file(&cmd[i]);
	if (cmd[i] && cmd[i + 1] == '>')
		fd_tmp = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd_tmp = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(file);
	tmp->fd_out = fd_tmp;
	return (tmp);
}
