
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
	(void)mini;
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "echo") == 0)
		return (0); //(ft_echo(cmd))
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "cmd") == 0)
		return (0); //ft_cd(mini, cmd)
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "pwd") == 0)
		return (0); //ft_pwd()
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "export") == 0)
		return (0); //ft_export()
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "unset") == 0)
		return (0); //ft_unset()
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "env") == 0)
		return (0); //ft_env()
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "exit") == 0)
		return (0); //ft_exit()
	return (0);
}
