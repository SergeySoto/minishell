/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:55:36 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/11 19:06:02 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(char *token)
{
	t_token	*head;

	head = malloc(1 * sizeof(t_token));
	if (!head)
		return (NULL);
	head->content = token;
	head->type = -1;
	head->expand = 0;
	head->next = NULL;
	return (head);
}

void	add_token_back(t_token *head, char *token)
{
	t_token	*new_token;
	
	new_token = create_token(token);
	if (!head)
		head = new_token;
	// Verifico aqui si mi head->next = NULL??
	// Le debo de poner un else para ver si el next de head apunta a NULL le meto el siguiente nodo??
	head->next = new_token;
}
