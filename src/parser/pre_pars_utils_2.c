#include "../../includes/minishell.h"

int	check_double_pipes(char *str, int i)
{
	int	j;

	if (str[i] == '|' && str[i + 1] == '|')
	{
		ft_fprintf(2, ERR_SYNTERR_TWO_PIPE);
		return (0);
	}
	else
	{
		j = i + 1;
		while (is_space(str[j]))
			j++;
		if (str[j] == '|' || str[j] == '\0')
		{
			ft_fprintf(2, ERR_SYNTERR_ONE_PIPE);
			return (0);
		}
	}
	return (1);
}
