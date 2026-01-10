/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:58:51 by carmegon          #+#    #+#             */
/*   Updated: 2025/12/01 21:39:55 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cast_c;
	char	*aux;
	int		i;

	cast_c = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == cast_c)
		{
			aux = (char *)&s[i];
			return (aux);
		}
		i++;
	}
	if (cast_c == '\0')
	{
		aux = (char *)&s[i];
		return (aux);
	}
	else
		return (NULL);
}
