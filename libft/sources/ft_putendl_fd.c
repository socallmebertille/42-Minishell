/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:27:46 by saberton          #+#    #+#             */
/*   Updated: 2024/05/24 10:24:19 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*s++, fd);
	ft_putchar_fd('\n', fd);
}

/*#include <fcntl.h>

int     main(void)
{
        int     fd;
       
	fd = open("test.txt", O_TRUNC | O_CREAT | O_RDWR, 0640);
        ft_putendl_fd("Hola", fd);
        close(fd);
        return (0);
}*/
