/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:45:43 by saberton          #+#    #+#             */
/*   Updated: 2024/12/15 19:49:55 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_nb(int nb, int len)
{
	int	i;

	i = 1;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb >= len)
	{
		nb /= len;
		i++;
	}
	return (i);
}

int	ft_putnbr(int nbr)
{
	long	nb;
	int		len_ret;

	nb = nbr;
	len_ret = 0;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
		len_ret++;
	}
	if (nb >= 10)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
	return (ft_len_nb(nb, 10) + len_ret);
}

int	ft_putnbr_base(char *base, int nbr, int len)
{
	long	nb;
	size_t	len_ret;

	nb = nbr;
	if (nbr < 0)
	{
		nb = U_MAX + nbr + 1;
		len_ret = ft_len_nb(nb, len);
	}
	else
	{
		nb = nbr;
		len_ret = ft_len_nb(nb, len);
	}
	if (nb >= len)
		ft_putnbr_base(base, nb / len, len);
	ft_putchar(base[nb % len]);
	return (len_ret);
}

void	ft_putptr(char *base, size_t p, size_t len)
{
	if (p >= len)
		ft_putptr(base, p / len, len);
	ft_putchar(base[p % len]);
}

int	ft_print_ptr(char *base, void *ptr, size_t len)
{
	size_t		len_ret;

	len_ret = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	len_ret += ft_putstr("0x");
	len_ret += ft_len_nb((size_t)ptr, len);
	ft_putptr(base, (size_t)ptr, len);
	return (len_ret);
}
