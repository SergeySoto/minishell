#include "../../../includes/minishell.h"

void	create_new_env(t_mini *mini, char *k, char *v)
{
	t_env	*current;

	current = mini->env;
	if (!current || !k)
		return ;
	while (current)
	{
		if (ft_strcmp(k, current->key) == 0)
		{
			free(k);
			if (v == NULL)
				return ;
			free(current->value);
			current->value = v;
			break ;
		}
		else if (current->next == NULL)
		{
			add_env_back(&(mini->env), k, v);
			break ;
		}
		current = current->next;
	}
}

int	update_or_add_env(t_mini *mini, char **av)
{
	char	*k;
	char	*v;
	int		i;

	if (!mini || !av)
		return (1);
	i = 1;
	while (av[i])
	{
		if (is_valid(av[i]) == 1)
			return (1);
		k = key(av[i]);
		v = value(av[i]);
		create_new_env(mini, k, v);
		i++;
	}
	return (0);
}

char	*return_av_failed(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (is_valid(av[i]) == 1)
			return (av[i]);
		i++;
	}
	return (NULL);
}
