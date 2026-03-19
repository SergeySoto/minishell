#include "../../includes/minishell.h"

void	heredoc_bf_dollar(t_token *lst)
{
	if (!lst || !lst->content)
		return ;
	if (lst->type == 4 && lst->next && lst->next->expand == 1)
		lst->next->expand = 0;
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

char	*get_var_name(char *str)
{
	int		i;

	if (str[0] == '?')
		return (ft_strdup("?"));
	else
	{
		i = 0;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		return (ft_substr(str, 0, i));
	}
}

char	*get_env_content(char *var_name, t_mini *mini)
{
	int		len_name;
	t_env	*temp;

	temp = mini->env;
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(mini->exit_status));
	len_name = ft_strlen(var_name);
	while (temp)
	{
		if ((ft_strncmp(temp->key, var_name, len_name) == 0)
			&& (len_name == (int)ft_strlen(temp->key)))
		{
			if (temp->value)
				return (ft_strdup(temp->value));
			return (ft_strdup(""));
		}
		temp = temp->next;
	}
	return (ft_strdup(""));
}
