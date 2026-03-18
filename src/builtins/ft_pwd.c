#include "../../includes/minishell.h"

int	ft_pwd(t_mini *mini)
{
	char	*cwd;
	char	*temp_cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		temp_cwd = get_env_val("PWD", mini);
		if (!temp_cwd)
		{
			ft_fprintf(2, ERR_NOT_FILEORDIR);
			return (0);
		}
		ft_putstr_fd(temp_cwd, 1);
		ft_putchar_fd('\n', 1);
		return (0);
	}
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	free(cwd);
	return (0);
}
