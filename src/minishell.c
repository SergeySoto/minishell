/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:28:58 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/12 17:01:33 by carmegon         ###   ########.fr       */
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
	char	*token1;
	char	*token2;
	t_token	*node;

	token1 = "echo";
	token2 = "hola";
	//shell_loop();
	node = create_token(token1, 1);
	if (!node)
	{
		printf("No se pudo crear el nodo\n");
		return (1);
	}
	// Prueba de que puto funciona nuestras funciones de nodos
	int i = 0;
	while (i < 2)
	{
		add_token_back(&node, token2);
		i++;
	}
	free(node);
	return (0);
}
