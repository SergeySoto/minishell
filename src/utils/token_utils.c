/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:13:06 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/20 20:26:52 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_token **head)
{
	t_token	*temp;
	t_token	*next;

	temp = *head;
	printf("\n--- VISTAS DE NODOS ---\n");
	while (temp)
	{
		printf("Token: [%s] | Expand: %d\n", temp->content, temp->expand);
		next = temp->next;
		free(temp->content);
		free(temp);
		temp = next;
	}
	*head = NULL;
	printf("-------------------------\n\n");
}

/**
 * @brief Removes surrounding quotes from a string while handling nested quotes.
 *
 * This function iterates through the input string and copies characters to a
 * new string, omitting quoting characters (' or ") unless they are preserved
 * by context. It maintains a state to track whether the current character is
 * inside quotes to correctly handle nested or escaped sequences (though logic
 * for escaping is delegated to `update_quote_status`).
 *
 * @param input The input string containing potential quotes to be trimmed.
 * @return A newly allocated string with the quotes removed. The caller is
 *         responsible for freeing this memory.
 */
// char	*trim_quotes(char *input)
// {
// 	int		i;
// 	int		j;
// 	char	quote;
// 	char	*result;

// 	i = 0;
// 	j = 0;
// 	quote = 0;
// 	result = malloc(ft_strlen(input) + 1);
// 	while (input[i])
// 	{
// 		update_quote_status(input[i], &quote);
// 		if (quote == 0 && (input[i] == '"' || input[i] == '\''))
// 			i++;
// 		else if (input[i] == quote && quote != 0)
// 			i++;
// 		else
// 		{
// 			result[j] = input[i];
// 			j++;
// 			i++;
// 		}
// 	}
// 	result[j] = '\0';
// 	return (result);
// }

void	trim_quotes(t_token *lst)
{
	int		i;
	int		j;
	char	quote;
	char	*result;

	i = 0;
	j = 0;
	quote = 0;
	result = malloc(ft_strlen(lst->content) + 1);
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
	lst->content = result;
}
