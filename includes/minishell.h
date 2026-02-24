#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "utils.h"
# include "executor.h"

extern int	g_signal;

// FUNCIONES BUILTINS AQUI POR AHORA
int		ft_pwd(void);
int		ft_env(t_mini *mini, char **av);
int	ft_unset(t_mini *mini, t_cmd *cmd);
int		check_flag(char *str);
int		whitout_n(char **av);
int		whit_n(char **av);
int		ft_echo(char **av);
int		is_valid(char c);
char	*key(char *str);


#endif
