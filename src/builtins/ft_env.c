#include "../../includes/minishell.h"

int	ft_env(t_mini *mini, char **av)
{
	int	i;

	mini->env_array = env_to_array(mini->env);
	if (!mini || !mini->env_array)
		return (1);
	
	if (av[1] != NULL)
	{
		printf("env: '%s': No such file or directory\n", av[1]);
		return (127);
	}
	i = 0;
	while (mini->env_array[i] != NULL)
	{
		printf("%s\n", mini->env_array[i]);
		i++;
	}

	/*
	t_env	*current;

	if (!mini || !mini->env_array)
		return (1);
	if (av[1] != NULL)
	{
		printf("env: '%s': No such file or directory\n", av[1]);
		return (127);
	}
	current = mini->env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	*/
	return (0);
}
