/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:07:39 by saberton          #+#    #+#             */
/*   Updated: 2024/05/29 14:41:27 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(long nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		count++;
	}
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	int			count;
	long		nb;
	char		*s;

	nb = n;
	count = ft_count(nb);
	if (!count)
		return (NULL);
	s = (char *)malloc(sizeof(char) * (count + 1));
	if (!s)
		return (NULL);
	s[count] = '\0';
	if (nb < 0)
	{
		nb = -nb;
		s[0] = '-';
	}
	else if (nb == 0)
		s[0] = '0';
	while (nb != 0)
	{
		s[--count] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (s);
}

/*#include <stdio.h>

int	main(void)
{
	char	*s;
	int	n = INT_MIN;

	printf("int d'origine : %d\n", n);
	s = ft_itoa(n);
	printf("chaine : %s\n", s);
	free(s);
	return (0);
}*/
