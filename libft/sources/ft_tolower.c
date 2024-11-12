/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:49:56 by saberton          #+#    #+#             */
/*   Updated: 2024/05/31 12:51:56 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

/*#include <ctype.h>
#include <stdio.h>

int	main()
{
	int	c;

	c = 5;
	printf("%d\n", tolower(c));
	printf("%d\n", ft_tolower(c));	
}*/
