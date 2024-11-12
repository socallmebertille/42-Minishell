/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:36:44 by saberton          #+#    #+#             */
/*   Updated: 2024/05/26 04:26:38 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	len;

	len = nmemb * size;
	if (nmemb != 0 && len / nmemb != size)
		return (NULL);
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}

/*#include <stdio.h>
#define HEX_BASE "0123456789abcdef"

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_puthex(unsigned char octet)
{
    ft_putchar(HEX_BASE[octet / 16]);
    ft_putchar(HEX_BASE[octet % 16]);
}

void    ft_putaddr(void *addr)
{
    int    i;

    i = 64;
    while (i > 0)
    {
        i -= 8;
        ft_puthex(((unsigned long int)(addr) >> i) & 0xff);
    }
}

void    ft_putdata(char *str, unsigned int size)
{
    unsigned int    i;

    i = 0;
    while (i < 16)
    {
        if (!(i % 2))
            ft_putchar(32);
        if (i < size)
            ft_puthex(str[i]);
        else
            write(1, "  ", 2);
        i++;
    }
    ft_putchar(32);
    i = 0;
    while (i < 16 && i < size)
    {
        if (str[i] >= 32 && str[i] < 127)
            ft_putchar(str[i]);
        else
            ft_putchar('.');
        i++;
    }
}

void    *print_memory(void *addr, unsigned int size)
{
    unsigned int    i;

    i = 0;
    while (i < size)
    {
        ft_putaddr((addr + i));
        ft_putchar(':');
        ft_putdata((char *)(addr + i), (size - i));
        ft_putchar('\n');
        i += 16;
    }
    return (addr);
}

int	main(void)
{
	size_t	count = 4;
	size_t	size = sizeof(char);
	size_t	count1 = 4;
	size_t	size1 = sizeof(int);
	int	*arr;
	char	*tab = "Hey";

	printf("Tableau de int :\n");
	arr = (int *)calloc(count1, size1);
	printf("Resultat attendu :\n");
	for (size_t i = 0; i < count1; i++)
		printf("%d ", arr[i]);
	free(arr);
	arr = (int *)ft_calloc(count1, size1);
	printf("\nResultat obtenu :\n");
	for (size_t i = 0; i < count1; i++)
		printf("%d ", arr[i]);
	free(arr);

	printf("\n\nTableau de char :\n");
	printf("Etat de la memoire de tab au debut : ");
        print_memory(tab, count*size);
	tab = (char *)calloc(count, size);
        printf("\nResultat attendu :\n");
        printf("%s\n", tab);
	printf("Etat de la memoire de tab apres calloc : ");
	print_memory(tab, count*size);
	free(tab);
        tab = (char *)ft_calloc(count, size);
        printf("\nResultat obtenu :\n");
        printf("%s\n", tab);
	printf("Etat de la memoire de tab apres ft_calloc : ");
        print_memory(tab, count*size);
	free(tab);
	return (0);
}*/
