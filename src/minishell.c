/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:28:58 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/02/25 17:36:53 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/minishell.h"

char	*shell_loop(t_mini *mini)
{
	t_token	*tokens;
/*
	Gestionar mas adelante el Enter sin salto de linea
*/
	while (1)
	{
		tokens = NULL;
		mini->input = readline("Minishell$> ");
		if (!mini->input)
		{
			printf("exit\n");
			break ;
		}
		if (mini->input[0] != '\0')
			input_to_token(mini->input, &tokens, mini);
		free_iteration_data(mini);
	}
	free_struct_mini(mini);
	rl_clear_history();
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	mini.arg_vector = av;
	mini.env = init_env(envp);
	mini.is_interactive = isatty(STDIN_FILENO);
	shell_loop(&mini);
	free_struct_mini(&mini);
	return (0);
}
