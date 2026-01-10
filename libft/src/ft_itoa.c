/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:57:26 by carmegon          #+#    #+#             */
/*   Updated: 2025/12/01 21:32:01 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_numbers(long int num)
{
	int	result;

	result = 0;
	if (num <= 0)
		result++;
	while (num)
	{
		num /= 10;
		result++;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	long int	num;
	int			len_num;

	num = n;
	len_num = ft_count_numbers(num);
	result = (char *)malloc((len_num + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len_num] = '\0';
	if (num == 0)
		result[0] = '0';
	if (num < 0)
	{
		num = -num;
		result[0] = '-';
	}
	while (num != 0)
	{
		result[len_num - 1] = (num % 10) + '0';
		num /= 10;
		len_num--;
	}
	return (result);
}
