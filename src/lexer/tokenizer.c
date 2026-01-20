/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:55:36 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/20 18:52:03 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../.././includes/minishell.h"

static void	print_tokens(t_token **head)
{
	t_token	*temp;
	t_token	*next;

	temp = *head;
	printf("\n--- VISTAS DE NODOS ---\n");
	while (temp)
	{
		printf("Token: [%s] | Type: %d\n", temp->content, temp->type);
		next = temp->next;
		free(temp->content);
		free(temp);
		temp = next;
	}
	*head = NULL;
	printf("-------------------------\n\n");
}

static int	get_type(char *line)
{
	if (ft_strncmp(line, "|", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "<", 2) == 0)
		return (2);
	else if (ft_strncmp(line, ">", 2) == 0)
		return (3);
	else if (ft_strncmp(line, "<<", 3) == 0)
		return (4);
	else if (ft_strncmp(line, ">>", 3) == 0)
		return (5);
	else
		return (0);
}

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
		temp = temp->next;
	temp->next = create_token(token, get_type(token));
}

void	input_to_token(char *input, t_token **tokens)
{
	char	**temp_split;
	//char	*trimmed;
	int		i;

	add_history(input);
	if (!parser(input))
		return ;
	printf("Input Valido: %s\n", input);
	temp_split = smart_split(input);
	i = 0;
	while (temp_split && temp_split[i])
	{
		//trimmed = trim_quotes(temp_split[i]);
		//add_token_back(tokens, trimmed);
		add_token_back(tokens, temp_split[i]);
		//free(temp_split[i]);
		i++;
	}
	free(temp_split);
	print_tokens(tokens);
}
