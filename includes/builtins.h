#ifndef BUILTINS_H
# define BUILTINS_H

int		ft_pwd(void);
int		ft_env(t_mini *mini, char **av);
int		ft_unset(t_mini *mini, t_cmd *cmd);
int		check_flag(char *str);
int		whitout_n(char **av);
int		whit_n(char **av);
int		ft_echo(char **av);
int		is_valid(char c);
char	*key(char *str);
char	*value(char *str);
void	create_new_env(t_mini *mini, char *k, char *v);
int		update_or_add_env(t_mini *mini, char **av);
char	*return_av_failed(char **av);
void	swap_nodes(t_mini *mini);
void	print_order_env(t_mini *mini);
int		order_env(t_mini *mini);
int		ft_export(t_mini *mini, char **av);
int		count_av(char **av);
void	chdir_fail(char **av);
int		try_getcwd(t_mini *mini, char *path);
int		change_directory(t_mini *mini, char **av);
int		go_home(t_mini *mini);
int		old_pwd(t_mini *mini, char *str);
int		ft_cd(t_mini *mini, char **av);
int		is_numeric_av(char *str);
int		is_overflow(char *str);
int		ft_error_exit(t_mini *mini, t_cmd *cmd);
int		ft_not_exit(t_mini *mini, t_cmd *cmd);
int		ft_exit(t_mini *mini, t_cmd *cmd);

#endif