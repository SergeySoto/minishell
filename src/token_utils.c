/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:55:36 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/12 19:42:09 by ssoto-su         ###   ########.fr       */
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
	if (!head || !(*head))
	{
		//El 1 se sustituye por la funcion que nos asigne el type.
		(*head) = create_token(token, get_type(token));
		return ;
	}
	while ((*head))
	{
		printf("Token: %s\n", (*head)->content);
		printf("Type: %d\n", (*head)->type);
		printf("Expand: %d\n", (*head)->expand);
		printf("Next: %p\n", (void *)(*head)->next);
		(*head) = (*head)->next;
	}
	(*head) = create_token(token, get_type(token));
}
