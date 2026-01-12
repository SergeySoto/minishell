/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 00:36:14 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/12 19:40:15 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_type(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
			return (1);
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
				return (4);
			else
				return (2);
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
				return (5);
			else
				return (3);
		}
		else
			return (0);
	}
	return (0);
}
