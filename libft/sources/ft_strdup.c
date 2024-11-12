/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:24:31 by saberton          #+#    #+#             */
/*   Updated: 2024/05/21 20:38:47 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	while (s[i])
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s = "Hola que tal ?";
	char	*dup;

	printf("La chaine source : %s.\n", s);
	dup = strdup(s);
	printf("La chaine dupliquee attendue : %s.\n", dup);
	free(dup);
	dup = ft_strdup(s);
	printf("La chaine dupliquee obtenue : %s.\n", dup);
	free(dup);
	return (0);
}*/
