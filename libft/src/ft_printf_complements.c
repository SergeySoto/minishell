/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_complements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:51:53 by marvin            #+#    #+#             */
/*   Updated: 2025/12/01 21:34:25 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_nbr(int num)
{
	char	d;
	int		printed_bytes;

	printed_bytes = 0;
	d = num;
	if (num == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (num < 0)
	{
		printed_bytes += write(1, "-", 1);
		num *= -1;
	}
	if (num >= 10)
	{
		printed_bytes += ft_print_nbr(num / 10);
	}
	d = num % 10 + '0';
	printed_bytes += write(1, &d, 1);
	return (printed_bytes);
}

int	ft_print_ptr(void *ptr)
{
	unsigned long long int	cst;
	int						printed_bytes;

	printed_bytes = 0;
	cst = (unsigned long long int)ptr;
	if (!cst)
		printed_bytes += write(1, "(nil)", 5);
	else
	{
		printed_bytes += write(1, "0x", 2);
		printed_bytes += ft_print_hex_bottom(cst);
	}
	return (printed_bytes);
}

int	ft_print_str(char *str)
{
	int	i;

	if (str == NULL)
	{
		(write(1, "(null)", 6));
		return (6);
	}
	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_uns(unsigned int num)
{
	int					printed_bytes;
	char				d;
	unsigned long int	n;

	n = num;
	printed_bytes = 0;
	if (n >= 10)
	{
		printed_bytes += ft_print_nbr(n / 10);
	}
	d = n % 10 + '0';
	printed_bytes += write(1, &d, 1);
	return (printed_bytes);
}
