#include "../../includes/minishell.h"

int	count_av(char **av)
{
	int	i;
	if (!av || !*av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	try_getcwd(t_mini *mini, char *path)
{
	if (path)
		create_new_env(mini, ft_strdup("PWD"), ft_strdup(path));
	else
	{
		ft_fprintf(2, "Error de change_dir\n");
		return (1);
	}
	free(path);
	return (0);
}

int	change_directory(t_mini *mini, char **av)
{
	char	*new_pwd;

	if (chdir(av[0]) == -1)
	{
		ft_fprintf(2, "primer chdir de change_directory\n");
		return (1);
	}
	else
	{
		new_pwd = getcwd(NULL, 0);
		//poner aqui try_getcwd
		if (new_pwd)
		{
			create_new_env(mini, ft_strdup("PWD"), ft_strdup(new_pwd));
			free(new_pwd);
		}
		else
		{
			ft_fprintf(2, "Error de change_dir\n");
			return (1);
		}
	}
	return (0);
}
// Esta funcion posiblemente vaya a fuera
char	*update_home_directory(t_mini *mini)
{
	char	*home;
	
	home = get_env_val("HOME", mini);
	if (chdir(home) == -1)
	{
		ft_fprintf(2, ERR_CD_NO_HOME);
		mini->exit_status = 1;
		return (NULL);
	}
	else
	{
		if (home)
			create_new_env(mini, ft_strdup("HOME"), ft_strdup(home));
		else
		{
			ft_fprintf(2, "Error de update_home\n");
			return (NULL);
		}
	}
	home = get_env_val("HOME", mini);
	return (ft_strdup(home));
}

int	go_home(t_mini *mini)
{
	char	*home;

	home = get_env_val("HOME", mini);
	if (!home)
		return (1);
	if (chdir(home) == -1)
	{
		ft_fprintf(2, ERR_CD_NO_HOME);
		mini->exit_status = 1;
		return (mini->exit_status);
	}
	// Aqui iria la llamada a la nueva funcion try_getcwd
	else
	{
		create_new_env(mini, ft_strdup("PWD"), ft_strdup(home));
		free(home);
	}
	return (0);
}

int	old_pwd(t_mini *mini, char *str)
{
	if (str)
		create_new_env(mini, ft_strdup("OLDPWD"), ft_strdup(str));
	else
	{
		ft_fprintf(2, "Saliendo de old_pwd\n");
		return (1);
	}
	return (0);
}

int	ft_cd(t_mini *mini, char **av)
{
	char	*temp;
	int		status;

	if (!av || !*av)
		return (0);

	status = 1;
	temp = getcwd(NULL, 0);
	if (count_av(av) == 1)
		status = go_home(mini);
	else if (count_av(av) == 2)
		status = change_directory(mini, &av[1]);
	else
	{
		perror("cd");
		free(temp);
		return (1);
	}
	if (status == 0 && temp)
		old_pwd(mini, temp);
	free(temp);
	return (0);
}
