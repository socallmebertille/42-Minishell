/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:29:37 by saberton          #+#    #+#             */
/*   Updated: 2024/05/26 04:22:56 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*d1;
	char	*d2;

	d1 = (char *)s1;
	d2 = (char *)s2;
	if (d1 == (void *)0 && d2 == (void *)0)
		return (0);
	while (n-- > 0)
	{
		if (*d1 != *d2)
			return ((unsigned char)*d1 - (unsigned char)*d2);
		d1++;
		d2++;
	}
	return (0);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	s1[15] = "Hola hue tal ?";
	char	s2[12] = "Hola hola !";
	int	n = 7;
	
	printf("Resultat attendu :\n");
        printf("La difference de taille de memoire sur %d bytes entre \n", n);
	printf("%s\n et \n%s\n est : ", s1, s2);
	printf("%d\n", memcmp(s1, s2, n));

	printf("\nResultat obtenu :\n");
	printf("La difference de taille de memoire sur %d bytes entre \n", n);
	printf("%s\n et \n%s\n est : ", s1, s2);
	printf("%d\n", ft_memcmp(s1, s2, n));
	return (0);
}*/
