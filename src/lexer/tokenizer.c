/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:55:36 by carmegon          #+#    #+#             */
/*   Updated: 2026/02/05 17:45:13 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	input_to_token(char *input, t_token **tokens, t_mini *mini)
{
	char	**temp_split;
	int		i;
	/* creo que debemos crear la estructura t_mini aqui y asignar la estructura
	t_token al puntero de la estrutura t_mini. */
	add_history(input);
	if (!pre_pars(input))
		return ;
	printf("Input Valido: %s\n", input);
	temp_split = smart_split(input);
	i = 0;
	while (temp_split && temp_split[i])
	{
		add_token_back(tokens, temp_split[i]);
		i++;
	}
	free(temp_split);
	ft_lstiter(*tokens, expand_checker);
	ft_lstiter(*tokens, heredoc_bf_dollar);
	mini->tokens = (*tokens);
	expander(mini);
	ft_lstiter(*tokens, trim_quotes);
	init_cmd(&mini);
	print_cmds(mini->cmds);
	//print_tokens(mini->tokens);
	//print_env(mini->env);
}
