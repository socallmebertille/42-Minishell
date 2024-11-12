/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:29:02 by saberton          #+#    #+#             */
/*   Updated: 2024/05/27 19:22:39 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
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
	elem1->content = "Que";
	elem1->next = elem2;
	elem2->content = " tal ?";
	elem2->next = NULL;
	
	printf("Ma liste chainee avant ft_lstadd_front :\n");
	aff_list(lst);
	
	t_list	*new = malloc(sizeof(t_list));

	if (!new)
		return (1);
	new->content = "Hola ";
	ft_lstadd_front(&lst, new);

	printf("\nMa liste chaine apresft_lstadd_front :\n");
	aff_list(lst);

	free(new);
	free(elem1);
	free(elem2);
	return (0);
}*/
