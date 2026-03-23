#include "../../includes/minishell.h"

int	ft_export(t_mini *mini, char **av)
{
	char	*invalid;

	if (!av || !*av)
		return (0);
	invalid = return_av_failed(av);
	if (update_or_add_env(mini, av) == 1)
	{
		ft_fprintf(2, ERR_EXPORT_NOT_VALID, invalid);
		mini->exit_status = 1;
		return (1);
	}
	if (av[0] && !av[1])
		order_env(mini);
	return (0);
}
