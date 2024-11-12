/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 06:14:59 by saberton          #+#    #+#             */
/*   Updated: 2024/05/27 19:50:04 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else if (lst && new)
	{
		current = ft_lstlast(*lst);
		current->next = new;
	}
}

/*#include <stdio.h>

void	aff_list(t_list *lst)
{
	while(lst)
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

	if (!elem1 || !elem2)
	{
		if (elem1)
			free(elem1);
		if (elem2)
			free(elem2);
		return (1);
	}

	lst = elem1;
	elem1->content = "Hola";
	elem1->next = elem2;
	elem2->content = " que";
	elem2->next = NULL;

	printf("Ma liste chainee avant ft_lstadd_back :\n");
	aff_list(lst);

	t_list	*begin = lst;
	t_list	*new = malloc(sizeof(t_list));

	if (!new)
		return (1);
	new->content = " tal ?";
	new->next = NULL;

	ft_lstadd_back(&begin, new);

	printf("\nMa liste chainee apres ft_lstadd_back :\n");
	aff_list(begin);

	free(elem1);
	free(elem2);
	free(new);
	return (0);
}*/
