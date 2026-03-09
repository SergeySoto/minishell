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
		i++;
	}
	return (1);
}

long long	ft_atoll(char *str)
{
	int			i;
	int			sign;
	long long	n;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	n = 0;
	while (str[i])
	{
		if (n > LLONG_MAX || n < LLONG_MIN)
			return (LLONG_MAX);
		else if (is_overflow_av(str[i], sign, n)
			return (LLONG_MAX);
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

int	is_overflow_av(char c, int sign, long long n)
{
	if (LLONG_MAX / 10 < n)
		return (1);
	else if ((n == LLONG_MAX / 10) && ((sign == 1) && (c >= '8')))
		return (1);
	else if ((n == LLONG_MAX / 10) && ((sign == -1) && (c == '9')))
		return (1);
	else
		return (0);
}

void	ft_exit(t_mini *mini, t_cmd *cmd)
{
	int			av;
	long long	n;

	ft_putstr_fd("exit\n", 2);
	av = count_av(cmd->args);
	if (av == 1)
	{
		free_struct_mini(mini);
		exit(0);
	}
	else if (av == 2 && is_numeric_av(cmd->args[1]))
	{
		if (ft_atoll(cmd->args[1]))
		
		n = ft_atoi(cmd->args[1]);
		mini->exit_status = n;
		free_struct_mini(mini);
		exit(n);
	}
}
