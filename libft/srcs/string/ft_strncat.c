/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:03:53 by saberton          #+#    #+#             */
/*   Updated: 2024/12/03 18:09:39 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (siz == 0 && (!dst || !src))
		return (NULL);
	len = ft_strlen(dst);
	if (siz <= len)
		return (NULL);
	i = len;
	j = 0;
	while (src[j] && i + 1 < siz)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst);
}
