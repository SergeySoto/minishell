#include "../../includes/minishell.h"

/**
 * @brief Returns 1 if the character at position i should be skipped when
 *		trimming quotes: opening/closing quote chars and bare $ before a quote.
 * @param content The token content string.
 * @param i Index of the character to evaluate.
 * @param quote Current quote state (0 = none, '\'' or '"' = inside quotes).
 * @return 1 if the character must be skipped, 0 otherwise.
 */
static int	should_skip_char(char *content, int i, char quote)
{
	if (quote == 0 && content[i] == '$' && (
			content[i + 1] == '"' || content[i + 1] == '\''))
		return (1);
	if (quote == 0 && (content[i] == '"' || content[i] == '\''))
		return (1);
	if (content[i] == quote && quote != 0)
		return (1);
	return (0);
}

/**
 * @brief Copies the token content into result, skipping all quote characters,
 *		then frees the old content and assigns result to lst->content.
 * @param lst Pointer to the token whose content is being trimmed.
 * @param result Pre-allocated buffer to write the trimmed string into.
 * @return void
 */
static void	trim_loop(t_token *lst, char *result)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (lst->content[i])
	{
		update_quote_status(lst->content[i], &quote);
		if (should_skip_char(lst->content, i, quote))
		{
			i++;
			continue ;
		}
		result[j] = lst->content[i];
		j++;
		i++;
	}
	result[j] = '\0';
	free(lst->content);
	lst->content = result;
}

void	trim_quotes(t_token *lst)
{
	char	*result;

	if (!lst || !lst->content)
		return ;
	result = malloc(ft_strlen(lst->content) + 1);
	if (!result)
		return ;
	trim_loop(lst, result);
}
