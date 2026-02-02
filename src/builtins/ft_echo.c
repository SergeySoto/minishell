#include "../../includes/minishell.h"

// Funcion para checkear el comando -n valido
int	check_flag(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	
	i = 0;
	if (str[0] != '-' || str[i + 1] == '\0')
		return (0);
	else
		i++;

	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	