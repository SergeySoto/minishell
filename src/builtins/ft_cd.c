#include "../../includes/minishell.h"

int	try_getcwd(t_mini *mini, char *path)
{
	if (path)
		create_new_env(mini, ft_strdup("PWD"), ft_strdup(path));
	else
	{
		ft_fprintf(2, ERR_CD_RETDIR);
		return (1);
	}
	return (0);
}

int	change_directory(t_mini *mini, char **av)
{
	char	*new_pwd;

	if (chdir(av[0]) == -1)
	{
		chdir_fail(av);
		return (1);
	}
	else
	{
		new_pwd = getcwd(NULL, 0);
		try_getcwd(mini, new_pwd);
	}
	free(new_pwd);
	return (0);
}

int	go_home(t_mini *mini)
{
	char	*home;

	home = get_env_val("HOME", mini);
	if (!home)
	{
		ft_fprintf(2, ERR_CD_NO_HOME);
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_fprintf(2, ERR_CD_NO_FIL_OR_DIR, home);
		free(home);
		return (1);
	}
	try_getcwd(mini, home);
	return (0);
}

static int	how_many_av(t_mini *mini, char **av)
{
	int	status;

	status = -1;
	if (count_av(av) == 1)
		status = go_home(mini);
	else if (count_av(av) == 2)
		status = change_directory(mini, &av[1]);
	else
	{
		ft_fprintf(2, ERR_CD_TOO_MANY);
		status = 1;
	}
	return (status);
}

int	ft_cd(t_mini *mini, char **av)
{
	char	*path;
	int		status;

	if (!av || !*av)
		return (0);

	path = getcwd(NULL, 0);
	status = how_many_av(mini, av);
	if (status == 1)
	{
		free(path);
		return (1);
	}
	else if (status == 0 && path)
		create_new_env(mini, ft_strdup("OLDPWD"), ft_strdup(path));
	free(path);
	return (0);
}
