/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 09:40:28 by axcallet          #+#    #+#             */
/*   Updated: 2023/03/14 13:14:21 by arforgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_lst)
{
	t_list	*temp;

	if (new_lst == NULL)
		return ;
	if (!*lst)
		*lst = new_lst;
	else
	{
		temp = *lst;
		*lst = new_lst;
		new_lst->next = temp;
	}
}
