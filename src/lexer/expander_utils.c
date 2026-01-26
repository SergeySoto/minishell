
#include "../../includes/minishell.h"

void	heredoc_bf_dollar(t_token *lst)
{
	if (!lst || !lst->content)
		return ;
	if (lst->type == 4 && lst->next && lst->next->expand == 1)
		lst->next->expand = 0;
}

void	expand_checker(t_token *lst)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (lst->content[i])
	{
		update_quote_status(lst->content[i], &quote);
		if (lst->content[i] == '$' && quote != '\'')
		{
			if (lst->content[i + 1] == '?')
			{
				lst->type = 7;
				lst->expand = 1;
			}
			else if (ft_isalnum(lst->content[i + 1])
				|| lst->content[i + 1] == '_')
			{
				lst->type = 6;
				lst->expand = 1;
			}
			break ;
		}
		i++;
	}
}

int	get_after_dollar(char *str)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	while (str[i])
	{
		update_quote_status(str[i], &quote);
		if (str[i] == '$' && quote != '\'' && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			return (i + 1);
		}
		i++;
	}
	return (0);
}
