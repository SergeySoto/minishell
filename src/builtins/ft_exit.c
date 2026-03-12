#include "../../includes/minishell.h"

int	is_numeric_av(char *str)
{
	int	i;
	int	found_digit;

	i = 0;
	found_digit = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) && found_digit == 1)
			return (0);
		else if (!ft_isdigit(str[i]) && !is_space(str[i]))
			return (0);
		else if (is_space(str[i]) && i > 0 && ft_isdigit(str[i - 1]))
			found_digit = 1;
		else if (is_overflow(&str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_overflow(char *str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i] == '0')
		i++;
	count = 0;
	while (str[i])
	{
		if (count > 10)
			return (1);
		i++;
		count++;
	}
	return (0);
}

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
// !CONTEMPLAR exit | exit
int	ft_exit(t_mini *mini, t_cmd *cmd)
{
	int	av;
	int	n;

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
