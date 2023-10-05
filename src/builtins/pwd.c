/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:23:52 by axcallet          #+#    #+#             */
/*   Updated: 2023/06/16 16:25:26 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_exec *dtt)
{
	char	pwd[PATH_MAX];

	if (dtt->full_cmd[1] && dtt->full_cmd[1][0] == '-')
	{
		ft_putstr_fd("bash: pwd: invalid option\n", 2);
		g_status = 2;
	}
	else
	{
		getcwd(pwd, sizeof(pwd));
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		g_status = 0;
	}
	return (1);
}
