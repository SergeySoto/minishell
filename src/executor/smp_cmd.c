
#include "../../includes/minishell.h"

void	exec_built_father(t_mini *mini, t_cmd *cmd)
{
	save_std_fds(mini);
	if (!apply_redirections(cmd))
	{
		restore_std_fds(mini);
		return ;
	}
	run_builtin(mini, cmd);
	restore_std_fds(mini);
}

static void	run_external_cmd(t_mini *mini, t_cmd *cmd)
{
	char	**env;

	if (!cmd->cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_struct_mini(mini);
		exit(127);
	}
	env = env_to_array(mini->env);
	if (execve(cmd->cmd_path, cmd->args, env) == -1)
		free_token(NULL, env);
	perror(cmd->args[0]);
	free_struct_mini(mini);
	exit(126);
}

void	exec_built_child(t_mini *mini, t_cmd *cmd)
{
	if (!apply_redirections(cmd))
	{
		free_struct_mini(mini);
		exit(1);
	}
	if (is_builtin(cmd->args[0]))
	{
		run_builtin(mini, cmd);
		exit(mini->exit_status);
	}
	run_external_cmd(mini, cmd);
}

void	exec_child_smp(t_mini *mini, t_cmd *cmd)
{
	if (cmd->pid == 0)
	{
		if (cmd->args[0])
			exec_built_child(mini, cmd);
		else
		{
			if(!apply_redirections(cmd))
				exit(1);
			exit(0);
		}
	}
}

void	wait_father_smp(t_mini *mini, t_cmd *cmd)
{
	waitpid(cmd->pid, &mini->exit_status, 0);
	if (WIFEXITED(mini->exit_status))
		mini->exit_status = WEXITSTATUS(mini->exit_status);
	else if (WIFSIGNALED(mini->exit_status))
		mini->exit_status = 128 + WTERMSIG(mini->exit_status);
	//close(cmd->fd_in);
	//close(cmd->fd_out);
}
