/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:08:15 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/12 20:04:05 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validator(char *input)
{
	int		i;
	char	status;

	status = '\0';
	if (input[0] == '\0')
		return (0);

	i = 0;
	while (input[i])
	{
		if (input[0] == '"' && status)
			status = '"';
		else if (input[0] == '\'')
			status = '\'';
		else if (input[0] == '<')
			status = '<';
	}
}
