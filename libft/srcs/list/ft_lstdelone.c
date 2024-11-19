/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 06:15:47 by saberton          #+#    #+#             */
/*   Updated: 2024/05/29 18:49:50 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

/*#include <stdio.h>

void	del_node(void *node)
{
	free(node);
}

void	aff_list(t_list *lst)
{
	while (lst)
	{
		printf("%s", (char *)lst->content);
		lst = lst->next;
	}
}

int	main(void)
{
	t_list	*lst;
	t_list	*elem1 = malloc(sizeof(t_list));
	t_list	*elem2 = malloc(sizeof(t_list));
	t_list	*elem3 = malloc(sizeof(t_list));
	t_list	*elem4 = malloc(sizeof(t_list));

	if (!elem1 || !elem2 || !elem3 || !elem4)
	{
		if (elem1)
			free(elem1);
		if (elem2)
			free(elem2);
		if (elem3)
			free(elem3);
		if (elem4)
			free(elem4);
		return (1);
	}

	lst = elem1;
	elem1->content = ft_strdup("Hola");
	elem1->next = elem2;
	elem2->content = ft_strdup(" hola,");
	elem2->next = elem3;
	elem3->content = ft_strdup(" que");
	elem3->next = elem4;
	elem4->content = ft_strdup(" tal ?");
	elem4->next = NULL;

	printf("Ma liste chainee avant ft_lstdelone :\n");
	aff_list(lst);
	ft_lstdelone(elem2, del_node);
	elem1->next = elem3;
	printf("\nMa liste chainee apres ft_lstdelone :\n");
	aff_list(lst);
	
	t_list	*lst_original;
	while (lst)
	{
		lst_original = lst->next;
		ft_lstdelone(lst, del_node);
		lst = lst_original;
	}
	return (0);
}*/
