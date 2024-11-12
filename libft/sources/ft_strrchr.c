/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:29:22 by saberton          #+#    #+#             */
/*   Updated: 2024/05/30 17:05:56 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			str = (char *)s;
		}
		s++;
		if (*s == '\0' && str != (void *)0)
			return (str);
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)0);
}

/*#include <string.h>
#include <stdio.h>

int     main(void)
{
        char    *str = "";

        printf("%s\n", ft_strrchr(str, 97));
        printf("%s\n", strrchr(str, 97));
        return (0);
}*/
