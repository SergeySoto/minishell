/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:55:36 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/12 20:42:00 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(char *str, int type)
{
	t_token	*token;

	token = malloc(1 * sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = str;
	token->type = type;
	token->expand = 0;
	token->next = NULL;
	return (token);
}

void	add_token_back(t_token **head, char *token)
{
	t_token *temp;

	if (!head || !*head)
	{
		*head = create_token(token, get_type(token));
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
	{
		printf("Token: %s\n", temp->content);
		printf("Type: %d\n", temp->type);
		printf("Expand: %d\n", temp->expand);
		printf("Next: %p\n", (void *)temp->next);
		temp = temp->next;
	}
	temp->next = create_token(token, get_type(token));
}
