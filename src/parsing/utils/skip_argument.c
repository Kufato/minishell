/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:18:14 by arforgea          #+#    #+#             */
/*   Updated: 2023/06/13 13:18:26 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	skip_argument(char *c)
{
	int		index;
	char	temple;

	index = 1;
	temple = *c;
	while (c)
	{
		if (c[index] && temple == c[index])
			return (index);
		index++;
	}
	return (-1);
}
