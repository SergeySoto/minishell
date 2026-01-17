
#include "../minishell.h"

static int	word_count(char *str)
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
		update_quote_status(str[i], &in_quotes);
		if (is_space(str[i]) && in_quotes == 0)
			in_word = 0;
		else if (in_word == 0)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}
static char	**c_mem(int n_words)
{
	char	**words;

	words = malloc((n_words + 1) * sizeof(char *));
	if (!words)
	{
		free(words);
		return (NULL);
	}
	return (words);
}

static void	fill_mem(char **str, char *input)
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
		if (is_space(input[i]))
			i++;
		else
		{
			start = i;
			while (input[i] && (!is_space(input[i]) || quote != 0))
			{
				update_quote_status(input[i], &quote);
				i++;
			}
			str[word++] = ft_substr(input, start, i - start);
		}
	}
	str[word] = NULL;
}

char	**smart_split(char *input)
{
	char	**words;

	if (!input)
		return (NULL);
	words = c_mem(word_count(input));
	if (!words)
		return (NULL);
	fill_mem(words, input);
	return (words);
}
