#include "../../includes/minishell.h"

//! EN pre_pars_utils tengo ya is_space!

int	is_numeric_av(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_space(str[i]))
			continue ;
		else if ((str[i] == '-' || str[i] == '+') && !ft_isdigit(str[i + 1]))
			return (0);
		else if (!ft_isdigit(str[i]))
			return (0);
		else if (ft_isdigit(str[i]) && ((str[i + 1] == '-' || str[i + 1] == '+')))
			return (0);
		i++;
	}
	return (1);
}
