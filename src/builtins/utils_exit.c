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
	int		i;
	int		sign;
	long	n;

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
/* 		else if (str[i] < '0' || str[i] > '9')
			return (n * sign); */
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

int	is_valid_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
}

void	ft_exit(t_cmd *cmd)
{
	if (!cmd->args || !*cmd->args)
		return ;
}
