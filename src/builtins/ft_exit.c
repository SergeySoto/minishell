#include "../../includes/minishell.h"

int	ft_error_exit(t_mini *mini, t_cmd *cmd)
{
	int	av;

	av = count_av(cmd->args);
	if (av == 2 && !is_numeric_av(cmd->args[1]))
	{
		ft_fprintf(2, ERR_EXIT_NUMERIC, cmd->args[1]);
		free_struct_mini(mini);
	}
	else if (av > 2 && !is_numeric_av(cmd->args[1]))
	{
		ft_fprintf(2, ERR_EXIT_NUMERIC, cmd->args[1]);
		free_struct_mini(mini);
	}
	else
		return (0);
	exit (2);
}

int	ft_not_exit(t_mini *mini,t_cmd *cmd)
{
	int	av;

	av = count_av(cmd->args);
	if (av > 2 && is_numeric_av(cmd->args[1]))
	{
		mini->exit_status = 1;
		ft_putstr_fd(ERR_EXIT_TOO_MANY, 2);
		return (1);
	}
	return (0);
}

int	ft_exit(t_mini *mini, t_cmd *cmd)
{
	int	av;
	int	n;

	if (ft_exit_pipe(mini))
		return (0);
	ft_putstr_fd("exit\n", 2);
	av = count_av(cmd->args);
	if (av == 2 && is_numeric_av(cmd->args[1]))
	{
		n = ft_atoi(cmd->args[1]);
		mini->exit_status = n;
		free_struct_mini(mini);
		exit(mini->exit_status);
	}
	if (ft_not_exit(mini, cmd))
		return (1);
	ft_error_exit(mini, cmd);
	free_struct_mini(mini);
	exit(0);
}
