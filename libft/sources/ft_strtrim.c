/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:55:49 by saberton          #+#    #+#             */
/*   Updated: 2024/05/24 14:25:12 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1);
	while (s1[j - 1] && ft_strchr(set, s1[j - 1]))
		j--;
	trim = ft_substr(s1, i, j - i);
	return (trim);
}

/*#include <stdio.h>

int	main(void)
{
	char	*s1 = "***H*o*la***";
	char	*set = "*";
	char	*trim;

	printf("Chaine s1 : %s & Chaine set : %s\n", s1, set);
        trim = ft_strtrim(s1, set);
        printf("Chaine s1 coupee : %s\n", trim);
        free(trim);
	return (0);
}*/
