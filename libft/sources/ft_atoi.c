/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:45:07 by saberton          #+#    #+#             */
/*   Updated: 2024/05/21 20:22:25 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
		sign *= -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb *= 10;
		nb += *nptr - '0';
		nptr++;
	}
	return (sign * nb);
}

/*#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char	*np = "    -2147483648bcef";

	printf("Le nombre sous forme de chaine : %s.\n", np);
	printf("Le nombre sous forme d'entier : %d.\n", ft_atoi(np));
	printf("Le nombre sous forme d'entier : %d.\n", atoi(np));
	return (0);
}*/
