/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:53:15 by saberton          #+#    #+#             */
/*   Updated: 2024/05/26 00:13:21 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!big && len == 0)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		if (little[j] == big[i])
		{
			while (little[j] == big[i + j] && i + j < len)
			{
				j++;
				if (!little[j])
					return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>

int	main(void)
{
	char	little[] = "";
	char	big[19] = "Hola que tal ?";

        printf("Little : %s\n", little);
        printf("Big : %s\n", big);
	printf("Resultat obtenu : %s", ft_strnstr(big, little, 6));
        return (0);
}*/
