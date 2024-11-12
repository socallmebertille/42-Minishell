/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 06:16:37 by saberton          #+#    #+#             */
/*   Updated: 2024/05/29 12:31:42 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next_node;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next_node = current->next;
		if (del)
			del(current->content);
		free(current);
		current = next_node;
	}
	*lst = NULL;
}

/*#include <stdio.h>

void	del_node(void *node)
{
	free(node);
}

void	aff_list(t_list **lst)
{
	t_list	*current;
	
	current = *lst;
	while (current)
	{
		printf("%s", (char *)current->content);
		current = current->next;
	}
}

int	main(void)
{
	t_list	**lst;
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

	lst = &elem1;
	elem1->content = ft_strdup("Hola ");
	elem1->next = elem2;
	elem2->content = ft_strdup("hola, ");
	elem2->next = elem3;
	elem3->content = ft_strdup("que ");
	elem3->next = elem4;
	elem4->content = ft_strdup("tal ?");
	elem4->next = NULL;
	
	printf("Ma liste chainee avant ft_lstclear :\n");
	aff_list(lst);

	ft_lstclear(&elem2, del_node);
	elem1->next = NULL;
	
	printf("\nMa liste chainee apres fr_lstclear :\n");
	aff_list(lst);

	ft_lstclear(lst, del_node);
	return (0);
}*/
