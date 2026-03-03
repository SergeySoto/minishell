#include "../../includes/minishell.h"

//! EN pre_pars_utils tengo ya is_space!

int	is_numeric_av(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && is_space(str[i]))
		i++;
	while (str[i])
	{
		if (is_space(str[i]) && ft_isdigit(str[i + 1]))
			return (0);
		else if ((str[i] == '-' || str[i] == '+') && !ft_isdigit(str[i + 1]))
			return (0);
		else if (!ft_isdigit(str[i]))
			return (0);
		else if (ft_isdigit(str[i]) && ((str[i + 1] == '-' || str[i + 1] == '+')))
			return (0);
		else if (str[i] && is_space(str[i]))
		{
			i++;
			continue ;
		}
		i++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	if (!cmd->args || !*cmd->args)
		return (0);
}
