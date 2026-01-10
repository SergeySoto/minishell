/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:39:18 by marvin            #+#    #+#             */
/*   Updated: 2025/12/01 21:41:53 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cast_c;
	char	*aux;
	int		len_s;

	cast_c = c;
	len_s = ft_strlen(s);
	if (cast_c == '\0')
	{
		aux = (char *)&s[len_s];
		return (aux);
	}
	while (len_s >= 0)
	{
		if (s[len_s] == cast_c)
		{
			aux = (char *)&s[len_s];
			return (aux);
		}
		len_s--;
	}
	return (NULL);
}
