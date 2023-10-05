/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:27:11 by axcallet          #+#    #+#             */
/*   Updated: 2023/03/14 13:13:37 by arforgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	t_list	*temp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new_lst;
		else
		{
			temp = ft_lstlast(*lst);
			temp->next = new_lst;
		}
	}
}
