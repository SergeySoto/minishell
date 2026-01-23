/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:12:38 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/23 21:02:13 by carmegon         ###   ########.fr       */
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

int	get_name_len(t_token *lst)
{
	int	i;
	int	j;

	i = 0;
	if (lst->expand == 1)
	{
		while (lst->content[i])
		{
			if (lst->content[i] == '$')
			{
				j = i + 1;
				while (lst->content[j])
					j++;
				return (j - i);
			}
			i++;
		}
	}
}

void	get_env_value(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], aqui el comando sin el $, get_name_len(mini->tokens)))
	}
}
