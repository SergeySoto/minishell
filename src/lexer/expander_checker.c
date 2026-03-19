#include "../../includes/minishell.h"

static int	check_and_set_expand_type(t_token *lst, int i)
{
	if (lst->content[i + 1] == '?')
	{
		lst->type = 7;
		lst->expand = 1;
		return (1);
	}
	else if (ft_isalnum(lst->content[i + 1]) || lst->content[i + 1] == '_')
	{
		lst->type = 6;
		lst->expand = 1;
		return (1);
	}
	return (0);
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
			if (check_and_set_expand_type(lst, i))
				break ;
		}
		i++;
	}
}
