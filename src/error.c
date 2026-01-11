/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:36:34 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/11 11:41:15 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_token(char *str, char **env)
{
	int	i;

	if (env)
	{
		i = 0;
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
	if (str)
		free(str);
	return (NULL);
}
