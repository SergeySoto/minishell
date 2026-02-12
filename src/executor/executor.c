
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

void	exec_built_father(t_mini *mini, t_cmd *cmd)
{
	save_std_fds(mini);
	if (!apply_redirections(cmd))
	{
		restore_std_fds(mini);
		return ;
	}
	//funcion del builtin correspondiente
	restore_std_fds(mini);
}

void	exec_simple_cmd(t_mini *mini, t_cmd *cmd)
{
	if (cmd && cmd->args[0])
	{
		if (is_builtin(cmd->args[0]) && is_built_father(cmd->args[0]))
		{
			exec_built_father(mini, cmd);
			return ;
		}
	}
	else
		return ;
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		close(cmd->fd_in);
		close(cmd->fd_out);
		perror("fork");
		return ;
	}
	if (cmd->pid == 0)
		exec_built_child(mini, cmd);
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

void	exec_built_child(t_mini *mini, t_cmd *cmd)
{
	char **env;
	if (!apply_redirections(cmd))
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		//ejecutar aqui
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
	execve(cmd->cmd_path, cmd->args, env);
	perror("Error");
	free_struct_mini(mini);
	exit(126);
}
