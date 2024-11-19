/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:19:51 by saberton          #+#    #+#             */
/*   Updated: 2024/05/23 20:37:07 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
}

/*#include <fcntl.h>

int	main(void)
{
	int	fd = open("test.txt", O_TRUNC | O_CREAT | O_RDWR, 0640);

	ft_putstr_fd("Hola", fd);
	close(fd);
	return (0);
}*/
