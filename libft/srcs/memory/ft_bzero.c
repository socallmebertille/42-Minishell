/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:58:05 by saberton          #+#    #+#             */
/*   Updated: 2024/10/04 15:02:59 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*z;

	z = (char *)s;
	while (n-- > 0)
		*z++ = 0;
}

/*
OU
void    ft_bzero(void *s, size_t n)
{
        char    *z;

        z = (char *)s;
        ft_memset(s, 0, n);
}

#include <stdio.h>
#include <strings.h>

int	main(void)
{
	char	s[14] = "Hola que tal ?";
	int	tab[4] = {0, 1, 2, 3};

	printf("Test ave une chaine de caractere :\n");
	printf("Chaine : %s\n", s);
	bzero(s + 4, 4);
        printf("Resultat attendu : %s\n", s);
	ft_bzero(s + 4, 4);
	printf("Resultat : %s\n", s);

	printf("\nTest ave une chaine de caractere :\n");
        for (int i = 0; i < 4; i++)
		printf("Tableau de int : %d\n", tab[i]);
        bzero(tab + 2, 1);
	for (int i = 0; i < 4; i++)
		printf("Resultat attendu : %d\n", tab[i]);
        ft_bzero(tab + 2, 1);
	for (int i = 0; i < 4; i++)
		printf("Resultat : %d\n", tab[i]);
	return (0);
}*/
