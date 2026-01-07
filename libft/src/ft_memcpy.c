/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:45:46 by carmegon          #+#    #+#             */
/*   Updated: 2025/12/01 21:33:27 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	size_t		j;
	const char	*aux;
	char		*cpy;

	aux = (const char *)src;
	cpy = (char *)dest;
	i = 0;
	j = 0;
	if (!cpy && !aux)
		return (NULL);
	while (i < n)
	{
		cpy[j] = aux[i];
		i++;
		j++;
	}
	src = (const void *)aux;
	dest = (void *)cpy;
	return (dest);
}
