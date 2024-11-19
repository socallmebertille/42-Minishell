/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:14:46 by saberton          #+#    #+#             */
/*   Updated: 2024/05/26 01:41:23 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*p == (unsigned char)c)
			return (p);
		p++;
	}
	return (NULL);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	s[15] = "Hola que tal ?";
	int	c = 116;
	char	*p;

	printf("Resultat attendu :\n");
        printf("Le premier %c de %s est :\n", c, s);
	p = memchr(s, c, 15);
	printf("%s\n", p);

	printf("Resultat obtenu :\n");
	printf("Le premier %c de %s est :\n", c, s);
	p = ft_memchr(s, c, 15);
	printf("%s\n", p);
	return (0);
}*/
