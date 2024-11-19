/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:45:10 by saberton          #+#    #+#             */
/*   Updated: 2024/05/25 17:10:52 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	if (!s)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*#include <stdio.h>

char	ft_change(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	else if (c >= 'A' && c <= 'Z')
		c += 32;
	else if (c >= '0' && c <= '9')
		c = i + '0';
	return (c);
}

int	main(void)
{
	char	*s = "ERROR 404";
	char	*new;

	printf("Chaine originale :\n%s\n", s);
	printf("Chaine apres ft_change :\n");
	new = ft_strmapi(s, ft_change);
	printf("%s\n", new);
	free(new);
	return (0);
}*/
