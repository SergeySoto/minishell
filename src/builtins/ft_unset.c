
#include "../../includes/minishell.h"

int	ft_unset(t_mini *mini, t_cmd *cmd)
{
	t_env	*prev;
	t_env	*env;
	int		i;

	i = 1;
	env = mini->env;
	while (cmd->args[i])
	{
		while (env)
		{
			prev = env;
			if (ft_strncmp(env->key, cmd->args[i], ft_strlen(cmd->args[i])))
			{
				
				env = env->next;
			}
		}
	}
}