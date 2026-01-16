/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:08:15 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/16 19:01:42 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Idea: create a function that looks for the right heredoc and if there is
something after de dobule << return 0 else return 1. Check that logic*/

void	update_quote_status(char c, char *quotes)
{
	if ((c == '"' || c == '\'') && *quotes == 0)
		*quotes = c;
	else if (c == *quotes)
		*quotes = 0;
}

static int	invalid_neighbor(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\0')
		return (1);
	return (0);
}

static int	check_redirect(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		update_quote_status(str[i], &quote);
		if ((str[i] == '<' || str[i] == '>') && quote == 0)
		{
			j = i + 1;
			if (str[i + 1] == str[i])
				j++;
			while (str[j] && is_space(str[j]))
				j++;
			if (invalid_neighbor(str[j]))
			{
				printf("Error: Syntax error near unexpected token\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static int	check_invalid_double(char *str)
{
	int		i;
	char	quotes;

	quotes = 0;
	i = 0;
	while (str[i])
	{
		update_quote_status(str[i], &quotes);
		if (quotes == 0)
		{
			if (str[i] == '|' && str[i + 1] == '|')
			{
				printf("Error: Syntax error near unexpected token `||'\n");
				return (0);
			}
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
	if (!check_quotes(input))
		return (0);
	if (!check_pipe(input))
		return (0);
	if (!check_pending_pipe(input))
		return (0);
	if (!check_redirect(input))
		return (0);
	if (!check_invalid_double(input))
		return (0);
	if (!check_forbidden(input))
		return (0);
	return (1);
}
