/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:05:37 by saberton          #+#    #+#             */
/*   Updated: 2024/05/26 01:06:29 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*#include <stdio.h>

void	ft_change(unsigned int i, char *s)
{
	if (s[i] >= 'a' && s[i] <= 'z')
		s[i] -= 32;
	else if (s[i] >= 'A' && s[i] <= 'Z')
		s[i] += 32;
}

int	main(void)
{
	char	s[] = "LoReM iPsUm";

	printf("Chaine originale :\n%s\n", s);
	printf("Chaine apres ft_change :\n");
	ft_striteri(s, ft_change);
	printf("%s\n", s);
	return (0);
}*/
