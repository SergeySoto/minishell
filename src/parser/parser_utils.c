/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:28:18 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/20 18:44:33 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (ft_strncmp(&str[i], "||", 2) == 0)
	{
		printf("Error: Syntax error near unexpected token '||'\n");
		return (0);
	}
	else if (str[i] == '|')
	{
		printf("Error: Syntax error near unexpected token '|'\n");
		return (0);
	}
	return (1);
}

int	check_pending_pipe(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (i > 0 && is_space(str[i - 1]))
		i--;
	if (str[i - 1] == '|')
	{
		if (str[i - 2] == '|')
		{
			printf("Error: Syntax error near unexpected token '||'\n");
			return (0);
		}
		printf("Error: Syntax error near unexpected token '|'\n");
		return (0);
	}
	return (1);
}

int	check_quotes(char *str)
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
		i++;
	}
	if (quotes != 0)
	{
		printf("Error: Unclosed quotes\n");
		return (0);
	}
	return (1);
}

int	check_forbidden(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quotes == 0)
			quotes = str[i];
		else if (str[i] == quotes)
			quotes = 0;
		if (quotes == 0)
		{
			if (str[i] == '\\' || str[i] == ';')
			{
				printf("Error: Forbidden character found\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}
