/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:28:58 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/14 20:39:24 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*shell_loop(void)
{
	char	*input;
	t_token	*tokens;
	char	**temp_split;
	int		i;
/*
	Gestionar mas adelante el Enter sin salto de linea
*/
	tokens = NULL;
	while (1)
	{
		input = readline("Minishell$> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] != '\0')
		{
			add_history(input);
			if (!validator(input))
			{
				free(input);
				continue ;
			}
		}
		else
		{
			free(input);
			continue ;
		}
		printf("Input Valido: %s\n", input);
		temp_split = ft_split(input, ' ');
		i = 0;
		while (temp_split && temp_split[i])
		{
			add_token_back(&tokens, temp_split[i]);
			i++;
		}
		free(temp_split);
		print_tokens(&tokens);
		free(input);
	}
	rl_clear_history();
	return (NULL);
}

int	main(void)
{
	shell_loop();
	return (0);
}
