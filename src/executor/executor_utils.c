
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
		exit(mini->exit_status);
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
