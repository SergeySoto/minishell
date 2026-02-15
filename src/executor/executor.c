
#include "../../includes/minishell.h"

void	execute_cmd(t_mini *mini)
{
	t_cmd	*cmd;

	cmd = mini->cmds;
	if (!cmd)
		return ;
	if (cmd->next == NULL)
		exec_simple_cmd(mini, cmd);
	else
		exec_pipelines(mini, cmd);
	return ;
}

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

void	exec_built_child(t_mini *mini, t_cmd *cmd)
{
	char	**env;

	if (!apply_redirections(cmd))
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		run_builtin(mini, cmd);
		//exit(status);
	}
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
		free_env(env);
	perror("Error");
	free_struct_mini(mini);
	exit(126);
}
