/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:28:58 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/01/09 18:33:41 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_loop()
{
	char *input;
	while(1)
	{
		input = readline("Minishell$>");
		if (input == NULL)
		{
			rl_clear_history();
			printf("exit");
			exit(0);
		}
		printf("%s\n", input);
		add_history(input);
		free(input);
	}
	return (input);
}

int main(void)
{
	shell_loop();
	return (0);
}
