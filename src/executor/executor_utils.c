
#include "../../includes/minishell.h"

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}

int	is_built_father(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}

int	run_builtin(t_mini *mini, t_cmd *cmd)
{
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "cmd") == 0)
		return (ft_cd(mini, cmd));
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export());
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset());
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env());
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit());
}

void	exec_simple_cmd(t_mini *mini, t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args[0] && is_builtin(cmd->args[0])
		&& is_built_father(cmd->args[0]))
	{
		exec_built_father(mini, cmd);
		return ;
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		close(cmd->fd_in);
		close(cmd->fd_out);
		perror("fork");
		return ;
	}
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
	else
	{
		waitpid(cmd->pid, &mini->exit_status, 0);
		if (WIFEXITED(mini->exit_status))
			mini->exit_status = WEXITSTATUS(mini->exit_status);
		close(cmd->fd_in);
		close(cmd->fd_out);
	}
	return ;
}
