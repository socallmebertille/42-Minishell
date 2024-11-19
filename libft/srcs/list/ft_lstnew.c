/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 04:51:00 by saberton          #+#    #+#             */
/*   Updated: 2024/11/13 19:57:00 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/*#include <stdio.h>

int	main(void)
{
	char	*content = "Hola";
	t_list	*node = ft_lstnew(&content);

	if (!node)
		return(1);
	printf("%s\n", *(char **)(node->content));
	free(node);
	return (0);
}*/
