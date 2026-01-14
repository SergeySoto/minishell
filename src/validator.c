/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:08:15 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/14 20:28:04 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_mid_double_pipes(char *str)
{
	int		i;
	char	quotes;

	quotes = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quotes == 0)
			quotes = str[i];
		else if (str[i] == quotes)
			quotes = 0;
		if (quotes == 0)
		{
			if (str[i] == '|' && str[i + 1] == '|')
			{
				printf("Error: Syntax error near unexpected token `||'\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static int	check_mid_double_ampersand(char *str)
{
	int		i;
	char	quotes;

	quotes = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quotes == 0)
			quotes = str[i];
		else if (str[i] == quotes)
			quotes = 0;
		if (quotes == 0)
		{
			if (str[i] == '&' && str[i + 1] == '&')
			{
				printf("Error: Syntax error near unexpected token `&&'\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	validator(char *input)
{
	if (!input)
		return (0);
	if (!check_pipe(input))
		return (0);
	if (!check_quotes(input))
		return (0);
	if (!check_pending_pipe(input))
		return (0);
	if (!check_mid_double_pipes(input))
		return (0);
	if (!check_mid_double_ampersand(input))
		return (0);
	if (!check_forbidden(input))
		return (0);
	return (1);
	//pensaba en hacer la funcion de checkear los caracteres de redireccion,
	//pero la ia me recomendo dejar esa parte para cuando ya tengamos los tokens
	// que es mucho mas facil hacer eso en ese punto.
	//tratar los "echo || caca" y el "&&"
}
