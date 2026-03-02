#ifndef PARSER_H
# define PARSER_H

int		is_space(char c);
int		check_pipe(char *str);
int		check_pending_pipe(char *str);
int		check_quotes(char *str);
int		check_forbidden(char *str);
void	update_quote_status(char c, char *quotes);
int		pre_pars(char	*input);
void	add_env_back(t_env **env, char *key, char *value);
t_env	*init_env(char **envp);
char	**env_to_array(t_env *envp);
int		count_args(t_token *token);
void	init_cmd(t_mini **mini);
void	set_redirects(t_token **token, t_cmd *cmd);


#endif
