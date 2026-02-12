#include ".././includes/minishell.h"

char	*shell_loop(t_mini *mini)
{
	char	*input;
	t_token	*tokens;
/*
	Gestionar mas adelante el Enter sin salto de linea
*/
	while (1)
	{
		tokens = NULL;
		input = readline("Minishell$> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] != '\0')
		{
			input_to_token(input, &tokens, mini);
		}
		if (mini->tokens)
			free_struct_token(&mini->tokens);
		free(input);
	}
	rl_clear_history();
	return (NULL);
}

/* int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	mini.env_array = dup_arr(envp);
	shell_loop(&mini);
	free_struct_mini(&mini);
	return (0);
} */
