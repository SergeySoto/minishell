
#include "../minishell.h"

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
char	**c_mem(int n_words)
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
