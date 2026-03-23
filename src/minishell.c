#include ".././includes/minishell.h"

int	g_signal;

/**
 * @brief Runs a single shell iteration: reads input, tokenizes it 
 * and executes it.
 * @param mini Pointer to the main shell structure.
 * @return 1 to continue the shell loop, 0 if input is NULL (EOF / Ctrl+D).
 */
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
	return (1);
}

/**
 * @brief Main shell loop. Calls minishell_iteration() until it returns 0,
 *        then frees all resources and clears readline history.
 * @param mini Pointer to the main shell structure.
 * @return Always NULL.
 */
char	*shell_loop(t_mini *mini)
{
	while (minishell_iteration(mini))
		continue ;
	free_struct_mini(mini);
	rl_clear_history();
	return (NULL);
}

/**
 * @brief Entry point. Initializes the shell structure, environment and
 *        launches the main loop.
 * @param ac Argument count (unused).
 * @param av Argument vector, stored in mini.arg_vector.
 * @param envp Environment variables array used to build the t_env linked list.
 * @return Always 0.
 */
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	mini.arg_vector = av;
	mini.env = init_env(envp);
	in_or_de_shlvl(&mini);
	mini.is_interactive = isatty(STDIN_FILENO);
	shell_loop(&mini);
	return (0);
}
