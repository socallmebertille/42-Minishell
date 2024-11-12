/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:06:02 by saberton          #+#    #+#             */
/*   Updated: 2024/05/25 20:01:41 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	unsigned int	i;

	i = 0;
	if (siz == 0)
		return (ft_strlen(src));
	while (src[i] && i < siz - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	src[15] = "Hola que tal ?";
	char	dest[13];

	printf("La chaine src : %s ", src);
	printf("est composee de %zu caractere.\n",ft_strlcpy(dest, src, 13));
	printf("Voici a quoi ressemble maintenant dest : %s", dest);
	return (0);
}*/
