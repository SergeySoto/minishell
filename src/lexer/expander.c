/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:12:38 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/23 21:16:47 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	heredoc_bf_dollar(t_token *lst)
{
	if (!lst || !lst->content)
		return ;
	if (lst->type == 4 && lst->next->expand == 1)
		lst->next->expand = 0;
}

static int	get_after_dollar(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			return (i + 1);
		}
		i++;
	}
	return (0);
}

static int	get_len(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

static t_token	*is_expander(t_token *tokens)
{
	if (tokens->expand == 1)
		return (tokens);
	else
		return (tokens);
}

void	get_env_value(t_mini *mini)
{
	int		i;
	t_token	*tokens;
	char	**envp;
	int		pos;
	char	*str;

	tokens = (*mini).tokens;
	envp = mini->env;
	i = 0;
	while (tokens)
	{
		if (is_expander(tokens))
		{
			pos = get_after_dollar(tokens->content);
			str = tokens->content;
			while (envp[i])
			{
				//revisar la longitud completa y el caracter siguiente si es un '='
				if (ft_strncmp(envp[i], &tokens->content[pos], ft_strlen(str)))
				i++;
			}
		}
		tokens = tokens->next;
	}
}
