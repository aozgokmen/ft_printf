/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozgokme <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:56:10 by aozgokme          #+#    #+#             */
/*   Updated: 2022/07/07 15:08:25 by aozgokme         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_allputvalue(unsigned long num, char *base, int check, int base_len)
{
	int	len;
	int	i;

	i = -1;
	len = 0;
	if (check == 3)
	{
		if (!base)
			return (write(1, "(null)", 6));
		else
			while (base[++i])
				len += write(1, &base[i], 1);
		return (len);
	}
	if (check == 1)
		len += write(1, "0x", 2);
	if ((int)num < 0 && check == 2)
	{
		len += write(1, "-", 1);
		num = num * -1;
	}
	if (num / base_len != 0)
		len += ft_allputvalue(num / base_len, base, 0, base_len);
	len += write(1, &base[num % base_len], 1);
	return (len);
}

int	ft_control(char c, va_list a)
{
	int	ch;

	if (c == 'c')
	{
		ch = va_arg(a, int);
		return (write(1, &ch, 1));
	}
	else if (c == 's')
		return (ft_allputvalue(0, va_arg(a, char *), 3, 0));
	else if (c == 'p')
		return (ft_allputvalue(va_arg(a, unsigned long), \
					"0123456789abcdef", 1, 16));
	else if (c == 'd' || c == 'i')
		return (ft_allputvalue(va_arg(a, int), "0123456789", 2, 10));
	else if (c == 'u')
		return (ft_allputvalue(va_arg(a, unsigned), "0123456789", 0, 10));
	else if (c == 'x')
		return (ft_allputvalue(va_arg(a, unsigned), "0123456789abcdef", 0, 16));
	else if (c == 'X')
		return (ft_allputvalue(va_arg(a, unsigned), "0123456789ABCDEF", 0, 16));
	else if (c == '%')
		return (write(1, &c, 1));
	else
		return (write(1, &c, 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	a;

	va_start(a, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			while (str[i] == ' ')
				i++;
			len += ft_control(str[i], a);
		}
		else
			len += write(1, &str[i], 1);
		i++;
	}
	va_end(a);
	return (len);
}
/*
#include <stdio.h>
int main()
{
	ft_printf("%d",ft_printf("%      Penguen", 42));
	printf("%d",printf("%    Penguen", 42));
	ft_printf("%d\n%s\n%x", -12345, "alalade insanların alalde", 54);
	ft_printf("%p %p", 0, 0);
	printf("%p %p", 0, 0);

}
*/
