/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:13:06 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/22 19:46:53 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	print_tokens(t_token *head)
{
	t_token	*temp;
	t_token	*next;

	temp = head;
	printf("\n--- VISTAS DE NODOS ---\n");
	while (temp)
	{
		printf("Token: [%s] | Type: %u | Expand: %d\n", temp->content, temp->type, temp->expand);
		next = temp->next;
		free(temp->content);
		free(temp);
		temp = next;
	}
	head = NULL;
	printf("-------------------------\n\n");
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
		if (quote == 0 && (lst->content[i] == '"' || lst->content[i] == '\''))
			i++;
		else if (lst->content[i] == quote && quote != 0)
			i++;
		else
		{
			result[j] = lst->content[i];
			j++;
			i++;
		}
	}
	result[j] = '\0';
	free(lst->content);
	lst->content = result;
}

void	trim_quotes(t_token *lst)
{
	char	quote;
	char	*result;

	if (!lst || !lst->content)
		return ;
	quote = 0;
	result = malloc(ft_strlen(lst->content) + 1);
	if (!result)
		return ;
	trim_loop(lst, result);
}
