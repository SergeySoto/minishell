#include "../../includes/minishell.h"

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

/**
 * @brief Checks that every redirection operator (<, >, <<, >>) is followed
 *		by a valid filename token (not another operator, pipe or NUL).
 * @param str The raw input string.
 * @return 1 if all redirections are valid, 0 if a syntax error is found
 *		(also prints an error message to stderr).
 */
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
				ft_fprintf(2, ERR_SYNTERR_1D, str[i]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

/**
 * @brief Checks for invalid double operators: || and &&.
 * @param str The raw input string.
 * @return 1 if no invalid doubles are found, 0 otherwise
 *		(also prints an error message to stderr).
 */
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
			if (str[i] == '|')
			{
				if (!check_double_pipes(str, i))
					return (0);
			}
			if (str[i] == '&' && str[i + 1] == '&')
			{
				ft_fprintf(2, ERR_SYNTERR_REDIR, "&&");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	pre_pars(char *input)
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
	if (!check_forbidden(input))
		return (0);
	if (!check_invalid_double(input))
		return (0);
	return (1);
}
