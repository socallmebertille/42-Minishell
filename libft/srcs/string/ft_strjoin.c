/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:34:30 by saberton          #+#    #+#             */
/*   Updated: 2024/05/26 00:21:00 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (*s1 && i < len)
		join[i++] = *s1++;
	while (*s2 && i < len)
		join[i++] = *s2++;
	join[i] = '\0';
	return (join);
}

/*#include <stdio.h>

int	main(void)
{
	char	*s1 = "Hola";
	char	*s2 = " !";
	char	*strj;

	printf("s1 : %s & s2 : %s\n", s1, s2);
	strj = ft_strjoin(s1, s2);
	printf("new string : %s\n", strj);
	free(strj);
	return (0);
}*/
