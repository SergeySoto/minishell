
#include "../../includes/minishell.h"

static int	is_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
static int	count_ops(char *str, int *i, int *count, char *in_word)
{
	in_word = 0;
	count++;
	if (str[(*i)] == '>' || str[(*i)] == '<' && str[(*i) + 1] == str[(*i)])
		(*i)++;
}
*/

int	word_count(char *str)
{
	int		i;
	char	in_quotes;
	char	in_word;
	int		count;

	count = 0;
	in_word = 0;
	in_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (in_quotes == 0 && is_op(str[i]))
		{
			in_word = 0;
			count++;
			if ((str[i] == '>' || str[i] == '<') && str[i + 1] == str[i])
				i++;
			i++;
		}
		else
		{
			update_quote_status(str[i], &in_quotes);
			if (is_space(str[i]) && in_quotes == 0)
				in_word = 0;
			else if (in_word == 0)
			{
				count++;
				in_word = 1;
			}
		}
		i++;
	}
	return (count);
}

void	fill_mem(char **str, char *input)
{
	int		i;
	char	quote;
	int		word;
	int		start;

	start = 0;
	word = 0;
	quote = 0;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]) && quote == 0)
			i++;
		else if (quote == 0 && is_op(input[i]))
		{
			start = i;
			if ((input[i] == '>' || input[i] == '<')
					&& input[i + 1] == input[i])
				i += 2;
			else
				i++;
			str[word++] = ft_substr(input, start, i - start);
		}
		else
		{
			start = i;
			while (input[i] && (quote != 0
					|| (!is_space(input[i]) && !is_op(input[i]))))
			{
				update_quote_status(input[i], &quote);
				i++;
			}
			str[word++] = ft_substr(input, start, i - start);
		}
	}
	str[word] = NULL;
}
