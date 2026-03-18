#include "../../../includes/minishell.h"

int	ft_exit_pipe(t_mini *mini)
{
	int	i;
	
	i = 0;
	while (mini->input[i])
	{
		if (mini->input[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

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
