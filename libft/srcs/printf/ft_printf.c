/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saberton <saberton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:01:31 by saberton          #+#    #+#             */
/*   Updated: 2024/06/25 17:37:41 by saberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_var(char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_print_ptr(HEX_BASE_MIN, va_arg(args, void *), 16));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putnbr_base(DEC_BASE, va_arg(args, int), 10));
	else if (format == 'x')
		return (ft_putnbr_base(HEX_BASE_MIN, va_arg(args, int), 16));
	else if (format == 'X')
		return (ft_putnbr_base(HEX_BASE_MAJ, va_arg(args, int), 16));
	else if (format == '%')
		return (ft_putchar('%'));
	else
		return (0);
}

int	ft_check_percent(const char *format)
{
	int	i;

	i = 0;
	while (format[i] == ' ')
		i++;
	if (format[i] != 'c' || format[i] != 's' || format[i] != 'p'
		|| format[i] != 'd' || format[i] != 'i' || format[i] != 'u'
		|| format[i] != 'x' || format[i] != 'X')
		i++;
	if (!format[i])
		return (-1);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	if (!format)
		return (0);
	i = 0;
	if (ft_check_percent(format) == -1)
		return (-1);
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			while (ft_check_percent(format + i) == -1)
				len += ft_check_var(format[i], args);
			len += ft_check_var(format[++i], args);
		}
		else
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}

// #include <stdio.h>
// #include <limits.h>

// int	main(void)
// {
// 	char	*ptr = "Hola que tal";
// 	unsigned long	nb = LONG_MIN;
// 	unsigned long	*p = &nb;

// 	printf(" %d : \n", printf("%c", '0' - 256));
// 	ft_printf(" %d\n", ft_printf("%c", '0' - 256));
// 	ft_printf("------------------------------\n");
// 	printf(" %d : \n", printf("%s", ptr));
// 	ft_printf(" %d\n", ft_printf("%s", ptr));
// 	ft_printf("------------------------------\n");
// 	printf(" %d : \n", printf("%d", 10));
// 	ft_printf(" %d\n", ft_printf("%d", 10));
// 	ft_printf("------------------------------\n");
// 	printf(" %d : \n", printf("%i", -101));
// 	ft_printf(" %d\n", ft_printf("%i", -101));
// 	ft_printf("------------------------------\n");
// 	printf(" %d : \n", printf("%u", -99));
// 	ft_printf(" %d\n", ft_printf("%u", -99));
// 	ft_printf("------------------------------\n");
// 	printf(" %d : \n", printf("%x", -26647485));
// 	ft_printf(" %d\n", ft_printf("%x", -26647485));
// 	ft_printf("------------------------------\n");
// 	printf(" %d : \n", printf("%X", 42));
// 	ft_printf(" %d\n", ft_printf("%X", 42));
// 	ft_printf("------------------------------\n");
// 	printf(" %d : \n", printf("%p", p));
// 	ft_printf(" %d \n", ft_printf("%p", p));
// 	ft_printf("------------------------------\n");
// 	printf(" %d : \n", printf("%%"));
// 	ft_printf(" %d \n", ft_printf("%%"));
// 	ft_printf("-----------test 1-------------------\n");
// 	int i = printf("printf : dgwwyt%weh\n");
// 	int j = ft_printf("ft_printf : dgwwyt%weh\n");
// 	printf("p %d : f %d\n", i, j);
// 	ft_printf("-------------test 2-----------------\n");
// 	ft_printf("ft_printf : %p%p%p%p\n");
// 	printf("printf : %p%p%p%p\n");
// 	ft_printf("-------------test 3-----------------\n");
// 	printf("printf : '%i'", 11);
// 	ft_printf("\n");
// 	ft_printf("ft_printf : '%i'", 11);
// 	ft_printf("\n");
// 	ft_printf("-------------test 4-----------------\n");
// 	printf("printf : gdlfkjgfd%%gjdflkgj");
// 	ft_printf("\n");
// 	ft_printf("ft_printf : gdlfkjgfd%%gjdflkgj\n");
// 	return (0);
// }
