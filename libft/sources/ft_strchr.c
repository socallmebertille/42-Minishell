/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:42:23 by saberton          #+#    #+#             */
/*   Updated: 2024/05/30 17:05:07 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *) s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)0);
}

/*#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	*str = "teste";

	printf("%s\n", ft_strchr(str, '\0'));
	printf("%s\n", strchr(str, '\0'));
	return (0);
}*/
