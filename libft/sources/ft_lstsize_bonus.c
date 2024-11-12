/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 06:12:32 by saberton          #+#    #+#             */
/*   Updated: 2024/05/27 19:35:56 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

/*#include <stdio.h>

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

	if (!elem1 || !elem2 || !elem3)
	{
		if (elem1)
			free(elem1);
		if (elem2)
			free(elem2);
		if (elem3)
			free(elem3);
		return (1);
	}

	lst = elem1;
	elem1->content = "Hola";
	elem1->next = elem2;
	elem2->content = " que";
	elem2->next = elem3;
	elem3->content = " tal ?";
	elem3->next = NULL;

	printf("Ma liste chainee de taille %d :\n", ft_lstsize(lst));
	aff_list(lst);
	
	free(elem1);
	free(elem2);
	free(elem3);
	return (0);
}*/
