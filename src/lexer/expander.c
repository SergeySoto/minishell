/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:12:38 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/22 18:27:33 by ssoto-su         ###   ########.fr       */
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


