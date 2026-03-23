#include "../../includes/minishell.h"

/**
 * @brief Allocates a NULL-terminated char** array of n_words + 1 pointers.
 * @param n_words Number of words to allocate space for.
 * @return Heap-allocated char** array, or NULL on malloc failure.
 */
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

/**
 * @brief Extracts an operator token (<, >, <<, >>) from input at position *i
 *		into str[*word] and advances both counters.
 * @param str Destination array of strings.
 * @param input The raw input string.
 * @param i Pointer to the current position in input (advanced in place).
 * @param word Pointer to the current word index (incremented in place).
 * @return void
 */
static void	extract_op(char **str, char *input, int *i, int *word)
{
	int	start;

	start = *i;
	if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i])
		(*i) += 2;
	else
		(*i)++;
	str[(*word)] = ft_substr(input, start, *i - start);
	(*word)++;
}

/**
 * @brief Extracts a word token (respecting quotes) from input at position *i
 *		into str[*word] and advances both counters.
 * @param str Destination array of strings.
 * @param input The raw input string.
 * @param i Pointer to the current position in input (advanced in place).
 * @param word Pointer to the current word index (incremented in place).
 * @return void
 */
static void	extract_word(char **str, char *input, int *i, int *word)
{
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	while (input[*i] && (quote != 0
			|| (!is_space(input[*i]) && !is_op(input[*i]))))
	{
		update_quote_status(input[*i], &quote);
		(*i)++;
	}
	str[(*word)] = ft_substr(input, start, *i - start);
	(*word)++;
}

void	fill_mem(char **str, char *input)
{
	int		i;
	int		word;

	word = 0;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (is_op(input[i]))
			extract_op(str, input, &i, &word);
		else
			extract_word(str, input, &i, &word);
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
