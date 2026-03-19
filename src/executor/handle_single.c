#include "../../includes/minishell.h"

void	execute_builtin_in_parent(t_mini *mini, t_cmd *cmd)
{
	int	exit_code;

	backup_std_fds(mini);
	if (!setup_redirections(cmd))
	{
		exit_code = restore_std_fds(mini);
		mini->exit_status = exit_code;
		return ;
	}
	exit_code = execute_builtin_func(mini, cmd);
	mini->exit_status = exit_code;
	restore_std_fds(mini);
}

void	single_cmd_child_process(t_mini *mini, t_cmd *cmd)
{
	if (cmd->pid == 0)
	{
		set_signals_default();
		if (cmd->args[0])
			execute_command_node(mini, cmd);
		else
		{
			if (!setup_redirections(cmd))
			{
				free_struct_mini(mini);
				rl_clear_history();
				exit(1);
			}
			free_struct_mini(mini);
			rl_clear_history();
			exit(0);
		}
	}
}

void	single_cmd_parent_wait(t_mini *mini, t_cmd *cmd)
{
	set_signals_child();
	waitpid(cmd->pid, &mini->exit_status, 0);
	if (WIFEXITED(mini->exit_status))
		mini->exit_status = WEXITSTATUS(mini->exit_status);
	else if (WIFSIGNALED(mini->exit_status))
	{
		g_signal = 128 + WTERMSIG(mini->exit_status);
		if (WTERMSIG(mini->exit_status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		mini->exit_status = g_signal;
	}
}
