/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:51:44 by saberton          #+#    #+#             */
/*   Updated: 2024/05/20 19:28:57 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*p;

	p = s;
	i = 0;
	while (i < n)
	{
		*p = (char)c;
	i++;
	p++;
	}
	return (s);
}

/*
#include <string.h>
#include <stdio.h>
#include <limits.h>

int main()
{
    int intArray[5];
    char charArray[10];
    char    str[] = "Hola que tal ?";
    
    printf("%s\n", str);
    ft_memset(str + 12, '!', 2); 
    printf("%s\n", str);


    // memset
    memset(intArray, INT_MAX, sizeof(intArray));

    memset(charArray, 'A', sizeof(charArray));

    printf("MEMSET\n");
    printf("tableau de int :\n");
    for (int i = 0; i < 5; i++)
        printf("%d ", intArray[i]);
    printf("\n");

    printf("tableau de char :\n");
    for (int i = 0; i < 10; i++)
        printf("%c ", charArray[i]);
    printf("\n \n");

    // ft_memset
    ft_memset(intArray, INT_MAX, sizeof(intArray));

    ft_memset(charArray, 33, sizeof(charArray));

    printf("FT_MEMSET\n");
    printf("tableau de int :\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", intArray[i]);
    }
    printf("\n");

    printf("tableau de char :\n");
    for (int i = 0; i < 10; i++) {
        printf("%c ", charArray[i]);
    }
    printf("\n");
}*/
