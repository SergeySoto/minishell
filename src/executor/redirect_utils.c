
#include "../../includes/minishell.h"

void	save_std_fds(t_mini *mini)
{
	mini->stdin_backup = dup(STDIN_FILENO);
	mini->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_std_fds(t_mini *mini)
{
	dup2(mini->stdin_backup, STDIN_FILENO);
	dup2(mini->stdout_backup, STDOUT_FILENO);
	close(mini->stdin_backup);
	close(mini->stdout_backup);
}
