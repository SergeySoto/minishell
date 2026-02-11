
#include "../../includes/minishell.h"

int	save_std_fds(t_mini *mini)
{
	mini->stdin_backup = dup(STDIN_FILENO);
	if (mini->stdin_backup < 0)
		return (perror("Dup failed"), -1);
	mini->stdout_backup = dup(STDOUT_FILENO);
	if (mini->stdout_backup < 0)
	{
		close(mini->stdin_backup);
		return (perror("Dup failed"), -1);
	}
	return (0);
}

int	restore_std_fds(t_mini *mini)
{
	if (dup2(mini->stdin_backup, STDIN_FILENO) < 0)
		return (perror("Dup failed"), -1);
	if (dup2(mini->stdout_backup, STDOUT_FILENO) < 0)
	{
		close(mini->stdin_backup);
		close(mini->stdout_backup);
		return (perror("Dup failed"), -1);
	}
	close(mini->stdin_backup);
	close(mini->stdout_backup);
	return (0);
}
