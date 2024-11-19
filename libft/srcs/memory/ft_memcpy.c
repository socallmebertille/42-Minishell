/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:26:49 by saberton          #+#    #+#             */
/*   Updated: 2024/05/26 02:50:38 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	if (d == (void *)0 && s == (void *)0)
		return (NULL);
	while (n-- > 0)
		*d++ = *s++;
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

void print_memory(const void *ptr, size_t size)
{
    const unsigned char *p = (const unsigned char *)ptr;
    for (size_t i = 0; i < size; i++) {
        printf("%02x ", p[i]);
    }
    printf("\n");
}

int main(void)
{
    char d[15] = "Hola que tal ?";
    char s[42] = "Sarah ne sait pas utiliser les pointers !";

    printf("Test avec une chaine de caractere :\n");
    printf("Chaine src : %s\n", s);
    printf("Chaine dest : %s\n", d);
    printf("Etat de la memoire de dest au depart :\n");
    print_memory(d, sizeof(d));   
    // Utilisation de memcpy
    memcpy(d, s, 4);
    printf("Resultat attendu : %s\n", d);


    // Etat de la memoire après memcpy
    printf("Etat de la memoire de dest apres memcpy :\n");
    print_memory(d, sizeof(d));

    // Utilisation de ft_memcpy
    ft_memcpy(d, s, 4);
    printf("Resultat trouve: %s\n", d);

    // Etat de la memoire après ft_memcpy
    printf("Etat de la memoire de dest apres ft_memcpy :\n");
    print_memory(d, sizeof(d));
    
    int tab[4] = {0, 1, 2, 3};
    printf("\nTest avec une tableau d'entiers :\n");
    printf("Tableau de int initial :\n");
    for (int i = 0; i < 4; i++)
        printf("%d ", tab[i]);
    printf("\n");
    
    memcpy(tab + 2, tab, 2 * sizeof(int));
    printf("Resultat attendu :\n");
    for (int i = 0; i < 4; i++)
        printf("%d ", tab[i]);
    printf("\n");
    
    ft_memcpy(tab + 2, tab, 2 * sizeof(int));
    printf("Resultat trouve :\n");
    for (int i = 0; i < 4; i++)
        printf("%d ", tab[i]);
    printf("\n");

    return 0;
}*/
