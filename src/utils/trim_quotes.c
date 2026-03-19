#include "../../includes/minishell.h"

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
