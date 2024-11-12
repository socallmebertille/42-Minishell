/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:44:12 by saberton          #+#    #+#             */
/*   Updated: 2024/05/23 20:32:09 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd > -1)
		write(fd, &c, 1);
}

/*#include <fcntl.h>

int	main(void)
{
	int	fd;
       
	fd = open("test.txt", O_TRUNC | O_CREAT | O_WRONLY, 0640);
	ft_putchar_fd('a', fd);
	close(fd);
	return (0);
}*/
