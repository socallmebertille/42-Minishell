/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:31:11 by saberton          #+#    #+#             */
/*   Updated: 2024/05/26 04:18:43 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = (char *)dest;
	s = (const char *)src;
	i = 0;
	if (d == (void *)0 && s == (void *)0)
		return (NULL);
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	src[] = "1234567890";

	printf("%s\n", src);
	ft_memmove(src + 5, src + 3, 4);
	//mouvement de memoire de n octets a la position pointee par dest dans src
	printf("%s\n", src);
	return (0);
}*/
