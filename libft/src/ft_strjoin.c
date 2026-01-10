/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:37:48 by carmegon          #+#    #+#             */
/*   Updated: 2025/12/01 21:40:31 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	len_new;

	len_new = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_s = (char *)malloc(len_new * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s1, len_new);
	ft_strlcat(new_s, s2, len_new);
	return (new_s);
}
