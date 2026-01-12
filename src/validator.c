/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:08:15 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/12 21:10:14 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Iterar en la lista y verificar todas las condiciones posible para
// que se pueda tokenizar. 
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
		//añadir un is space
		if (input[i] == 32 || (input[i] >= 9 && input[i] <= 13))
			i++;
		if (input[0] == '|')
			status = '|';
		else if (input[0] == '"' && status)
			status = '"';
		else if (input[0] == '\'')
			status = '\'';
		else if (input[0] == '<')
			status = '<';
	}
}
