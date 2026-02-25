#include "../../includes/minishell.h"

int	ft_cd(t_mini *mini, char **av)
{
	char	*old_pwd;
	char	*new_pwd;
	//t_env	*env;

	if (!av || !*av)
		return (0);
	//env = mini->env;
	old_pwd = getcwd(NULL, 0);
	if (old_pwd)
	{
		create_new_env(mini, ft_strdup("OLDPWD"), ft_strdup(old_pwd));
		free(old_pwd);
	}
	else
	{
		perror("cd");
		return (1);
	}
	new_pwd = chdir(av[1]);
	ft_printf("%s\n", new_pwd);
	return (0);
}
