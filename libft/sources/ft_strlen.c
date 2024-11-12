/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:33:54 by saberton          #+#    #+#             */
/*   Updated: 2024/09/30 16:27:48 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

/*#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	*str = "Hola que tal ?";

	printf("%lu\n", ft_strlen(str));
	printf("%lu\n", strlen(str));
	return (0);
}*/
