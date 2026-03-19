#include "../../includes/minishell.h"

/**
 * @brief Searches and removes an environment variable from the linked list
 * 	(non-head nodes)
 * @param mini The minishell instance
 * @param cmd The command structure containing the variable name at args[i]
 * @param i Index of the variable name in cmd->args
 */
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
		if (ft_strcmp(cmd->args[i], "_") == 0)
		{
			i++;
			continue ;
		}
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
