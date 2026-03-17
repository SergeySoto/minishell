/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:28:58 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/03/17 16:53:32 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/minishell.h"

int g_signal;

static int	minishell_iteration(t_mini *mini)
{
	t_token	*tokens;

	tokens = NULL;
	set_signals_interactive();
	if (mini->is_interactive)
		mini->input = readline("Minishell$> ");
	else
		mini->input = get_next_line(STDIN_FILENO);
	g_signal = 0;
	if (!mini->input)
	{
		if (mini->is_interactive)
			printf("exit\n");
		return (0);
	}
	if (mini->input[0] != '\0')
	{
		input_to_token(mini->input, &tokens, mini);
		if (mini->tokens)
			process_and_execute(mini);
	}
	free_iteration_data(mini);
	printf("minishell_iteration %d\n", mini->exit_status);
	return (1);
}

char	*shell_loop(t_mini *mini)
{
	while (minishell_iteration(mini))
		continue ;	
	free_struct_mini(mini);
	rl_clear_history();
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)envp;
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	mini.arg_vector = av;
	mini.env = init_env(envp);
	mini.is_interactive = isatty(STDIN_FILENO);
	shell_loop(&mini);
	return (0);
}
