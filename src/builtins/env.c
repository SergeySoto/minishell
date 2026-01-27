#include "../../includes/minishell.h"

int	ft_env(t_mini *mini, char **av)
{
	int	i;
	
	if (!mini || !mini->env)
		return (0);
	
	if (av[1] != NULL)
	{
		printf("env: '%s': No such file or directory\n", av[1]);
		return (127);
	}
	i = 0;
	while (mini->env[i] != NULL)
	{
		printf("%s\n", mini->env[i]);
		i++;
	}
	return (1);
}
