
#include "../../includes/minishell.h"

static void	find_var(t_mini *mini, t_cmd *cmd, int i)
{
	t_env	*current;
	t_env	*tmp;

	current = mini->env;
	while (current && current->next)
	{
		if (ft_strcmp(current->next->key, cmd->args[i]) == 0)
		{
			tmp = current->next;
			current->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			break ;
		}
		else
			current = current->next;
	}
}

int	ft_unset(t_mini *mini, t_cmd *cmd)
{
	t_env	*tmp;
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		if (mini->env && ft_strcmp(mini->env->key, cmd->args[i]) == 0)
		{
			tmp = mini->env;
			mini->env = mini->env->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		else
			find_var(mini, cmd, i);
		i++;
	}
	return (0);
}
