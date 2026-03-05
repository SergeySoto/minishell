#include ".././includes/minishell.h"

char	*shell_loop(t_mini *mini)
{
	t_token	*tokens;

	while (1)
	{
		tokens = NULL;
		set_signals_interactive();
		if (mini->is_interactive)
			mini->input = readline("Minishell$> ");
		else
			mini->input = get_next_line(STDIN_FILENO);
		if (!mini->input)
		{
			if (mini->is_interactive)
				printf("exit\n");
			break ;
		}
		if (mini->input[0] != '\0')
			input_to_token(mini->input, &tokens, mini);
		if (is_numeric_av(mini->input))
			ft_putstr_fd("Av valido\n", 1);
		else
			ft_putstr_fd("Av invalido\n", 1);
		free_iteration_data(mini);
	}
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
	free_struct_mini(&mini);
	return (0);
}
