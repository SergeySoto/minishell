
#include "../../includes/minishell.h"

int	is_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	count_ops(char *str, int *i, int *count, char *in_word)
{
	*in_word = 0;
	(*count)++;
	if ((str[*i] == '>' || str[*i] == '<') && str[*i + 1] == str[*i])
		(*i)++;
}

static void	count_regular(char c, int *count, char *in_w, char *in_q)
{
	update_quote_status(c, in_q);
	if (is_space(c) && *in_q == 0)
		*in_w = 0;
	else if (*in_w == 0)
	{
		(*count)++;
		*in_w = 1;
	}
}

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
			count_ops(str, &i, &count, &in_word);
		else
			count_regular(str[i], &count, &in_word, &in_quotes);
		i++;
	}
	return (count);
}
