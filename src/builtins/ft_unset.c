
#include "../../includes/minishell.h"

int	ft_unset(t_mini *mini, t_cmd *cmd)
{
	t_env	*tmp;
	t_env	*current;
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		if (mini->env && ft_strncmp(mini->env->key, cmd->args[i], ft_strlen(cmd->args[i]) + 1) == 0)
		{
			tmp = mini->env;
			mini->env = mini->env->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		else
		{
			current = mini->env;
			while (current && current->next)
			{
				if (ft_strncmp(current->next->key, cmd->args[i], ft_strlen(cmd->args[i]) + 1) == 0)
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
		i++;
	}
	return (0);
}
