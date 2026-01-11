/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:28:58 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/09 20:54:47 by ssoto-su         ###   ########.fr       */
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
		t_mini	*mini;
		mini->input = readline("Minishell$> ");
		if (!mini->input)
		{
			rl_clear_history();
			printf("exit");
			exit(0);
		}
		add_history(mini->input);
		free(mini->input);
	}
	return (mini->input);
}

int	main(void)
{
	shell_loop();
	return (0);
}
