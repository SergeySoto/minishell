/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:08:15 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/13 19:06:53 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '|')
	{
		printf("Error: Syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

static int	check_quotes(char *str)
{
	int		i;
	char	quotes;

	quotes = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == "\'") && quotes == 0)
			quotes = str[i];
		else if (str[i] == quotes)
			quotes = 0;
		i++;
	}
	if (quotes != 0)
	{
		printf("Error: Unclosed quotes\n");
		return (0);
	}
	return (1);
}

static int	check_forbidden(char *str)
{
	int	i;
	int	quotes; //0 = nada, 1 = simple quotes ('), 2 = double quotes (")

	while (str[i])
	{
		if (str[i] == "'" && quotes != 2)
			quotes = !quotes;
		else if (str[i] == '\"' && quotes != 1)
			quotes = !quotes;
		if (!quotes && (str[i] == '\\' || str[i] == ';'))
		{
			printf("Error: Forbidden character found\n");
			return (0);
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
	if (!check_forbidden(input))
		return (0);
	//pensaba en hacer la funcion de checkear los caracteres de redireccion,
	//pero la ia me recomendo dejar esa parte para cuando ya tengamos los tokens
	// que es mucho mas facil hacer eso en ese punto.
}
