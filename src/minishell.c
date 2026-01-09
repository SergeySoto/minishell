/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:28:58 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/09 20:34:36 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*shell_loop(void)
{
	char *input;
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
	shell_loop();
	return (0);
}
