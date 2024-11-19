/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:09:29 by saberton          #+#    #+#             */
/*   Updated: 2024/05/31 14:43:24 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (siz == 0 && (!dst || !src))
		return (ft_strlen(src));
	len = ft_strlen(dst);
	if (siz <= len)
		return (siz + ft_strlen(src));
	i = len;
	j = 0;
	while (src[j] && i + 1 < siz)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (len + ft_strlen(src));
}

/*#include <stdio.h>
#include <string.h>

int     main(void)
{
	char    dest[6] = "Hello";
        char    *src = " Wolrd";
	size_t	dstsiz = sizeof(dest);

	printf("Chaine dest : %s\n", dest);
        printf("Chaine src : %s\n", src);
        printf("Taille ideale de dest : %zu\n",ft_strlcat(dest, src, dstsiz));
        printf("Chaine dest apres ft_strlcat: %s\n", dest);
        return (0);
}*/
