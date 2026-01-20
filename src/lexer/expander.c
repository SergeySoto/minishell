/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:12:38 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/20 20:12:50 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_checker(t_token *lst)
{
	int		i;
	char	quote;

	if (!lst || !lst->content)
		return ;
	quote = 0;
	i = 0;
	while (lst->content[i])
	{
		update_quote_status(lst->content[i], &quote);
		if (lst->content[i] == '$' && quote != '\'')
		{
			lst->expand = 1;
			break ;
		}
		i++;
	}
}

void	ft_lstiter(t_token *lst, void (*f)(t_token *))
{
	if (!lst)
		return ;
	while (lst != NULL)
	{
		f(lst);
		lst = lst->next;
	}
}
