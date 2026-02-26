#include "../../includes/minishell.h"

int	more_than_2_av(char **av)
{
	int	i;
	if (!av || !*av)
		return (0);
	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	change_directory(t_mini *mini, char **av)
{
	char	*new_pwd;

	if (chdir(av[0]) == -1)
	{
		perror("cd");
		return (1);
	}
	else
	{
		new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			create_new_env(mini, ft_strdup("PWD"), ft_strdup(new_pwd));
			free(new_pwd);
		}
		else
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}

char	*update_home_directory(t_mini *mini)
{
	char	*home;
	
	home = get_env_val(strdup("HOME"), mini);
	if (chdir(home) == -1)
		return (NULL);
	else
	{
		if (home)
			create_new_env(mini, ft_strdup("HOME"), ft_strdup(home));
		else
		{
			perror("cd");
			return (NULL);
		}
	}
	home = get_env_val(strdup("HOME"), mini);
	return (home);
}

int	go_home(t_mini *mini)
{
	char	*home;

	home = update_home_directory(mini);
	if (!home)
		return (1);
	else
	{
		create_new_env(mini, ft_strdup("PWD"), ft_strdup(home));
		free(home);
	}
	return (0);
}

int	old_pwd(t_mini *mini)
{
	char	*old_pwd;

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
	return (0);
}

int	ft_cd(t_mini *mini, char **av)
{
	if (!av || !*av)
	return (0);

	old_pwd(mini);
	if (more_than_2_av(av) == 1)
		go_home(mini);
	else if (more_than_2_av(av) == 2)
		change_directory(mini, &av[1]);
	else
	{
		perror("cd");
		return (1);
	}
	return (0);
}
