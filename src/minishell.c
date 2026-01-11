/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:28:58 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/11 19:02:16 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*shell_loop(void)
{
	char	*input;
/*
	Gestionar mas adelante el Enter sin salto de linea
*/
	while (1)
	{
		input = readline("Minishell$> ");
		if (!input)
		{
			rl_clear_history();
			printf("exit");
			exit(0);
		}
		add_history(input);
		free(input);
	}
	return (input);
}

int	main(void)
{
	char	*token;
	t_token	*node;

	token = "echo";
	//shell_loop();
	node = create_token(token);
	if (!node)
	{
		printf("No se pudo crear el nodo\n");
		return (1);
	}
	printf("Token: %s\n", node->content);
	printf("Type: %d\n", node->type);
	printf("Expand: %d\n", node->expand);
	printf("Next: %p\n", (void *)node->next);
	free(node);
	return (0);
}
