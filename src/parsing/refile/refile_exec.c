/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refile_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:02:37 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/16 16:10:21 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	**cmd_core(char **t_cmd)
{
	int		i;
	int		j;
	char	**new_tab;

	i = 0;
	j = 0;
	new_tab = malloc(sizeof(char *) * (get_good_nb_word(t_cmd) + 1));
	if (!new_tab)
		return (NULL);
	while (t_cmd[i])
	{
		if (t_cmd[i + 1] && (t_cmd[i][0] == '<' || t_cmd[i][0] == '>'))
			i += 2;
		else if (!t_cmd[i + 1] && (t_cmd[i][0] == '<' || t_cmd[i][0] == '>'))
			i++;
		else
		{
			new_tab[j] = str_without_quotes(ft_strdup(t_cmd[i]));
			j++;
			i++;
		}
	}
	new_tab[j] = NULL;
	return (new_tab);
}

static t_exec	*get_cmd(t_data *data, t_exec *exec, char **cmd, char **envp)
{
	char	**new_tab;
	char	**tab_cmd;
	t_exec	*tmp;

	*cmd = add_spaces_rdir(*cmd);
	tab_cmd = turbo_split(*cmd, ' ');
	tmp = exec;
	new_tab = cmd_core(tab_cmd);
	if (!new_tab)
		return (NULL);
	tmp->full_cmd = ft_tab_dup(new_tab);
	tmp->cmd = str_without_quotes(ft_strdup(new_tab[0]));
	if (tmp->cmd)
		data->nb_cmd++;
	else
		free_tab(tmp->full_cmd);
	if (!check_builtins(tmp->cmd))
		tmp->abs_path = get_abs_path(tmp->cmd, envp);
	else if (check_builtins(tmp->cmd))
		tmp->abs_path = ft_strdup(tmp->cmd);
	free_tab(tab_cmd);
	free_tab(new_tab);
	return (tmp);
}

static t_exec	*change_fds(t_exec *dtt, char *cmd)
{
	int		i;
	t_exec	*tmp;

	i = 0;
	tmp = dtt;
	while (cmd && cmd[i])
	{
		if (cmd[i] && cmd[i] == '<')
		{
			tmp = left_chevrons(tmp, &cmd[i]);
			if (tmp->fd_in == -1)
				return (tmp);
			while (cmd[i] && cmd[i] == '<')
				i++;
		}
		else if (cmd[i] && cmd[i] == '>')
		{
			tmp = right_chevrons(tmp, &cmd[i]);
			if (cmd[i] && cmd[i + 1] == '>')
				i++;
		}
		if (cmd[i])
			i++;
	}
	return (tmp);
}

t_exec	*refile_exec(t_data *data, t_exec *dtt, char **tab, char **cmd)
{
	t_exec	*tmp;

	tmp = dtt;
	tmp->fd_in = 0;
	tmp->fd_out = 1;
	if (!check_heredoc(*cmd))
		tmp = heredoc_call(data, tmp, tab, *cmd);
	if (check_chevrons(*cmd) && g_status != 130)
		tmp = change_fds(tmp, *cmd);
	tmp = get_cmd(data, tmp, cmd, data->envp);
	return (tmp);
}
