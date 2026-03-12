#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700
# define _POSIX_C_SOURCE 200809L
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "utils.h"
# include "executor.h"
# include "signals.h"
# include "error.h"
# include "builtins.h"

extern int	g_signal;

#endif
