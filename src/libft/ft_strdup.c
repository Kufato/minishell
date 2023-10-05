/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:38:26 by axcallet          #+#    #+#             */
/*   Updated: 2023/05/24 14:52:37 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		size;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	size = ft_strlen(s);
	dest = ft_calloc(sizeof(char), size + 1);
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
