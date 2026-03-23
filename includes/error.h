#ifndef ERROR_H
# define ERROR_H

# define ERR_NOT_FILEORDIR "minishell: No such file or directory\n"
# define ERR_EXIT_TOO_MANY "minishell: exit: too many arguments\n"
# define ERR_EXIT_NUMERIC "minishell: exit: %s: numeric argument required\n"
# define ERR_CMD_NOT_FOUND "minishell: %s: command not found\n"
# define ERR_ENV_NOT_FILORDIR "minishell: %s: Not such file or directory\n"
# define ERR_EXPORT_NOT_VALID "minishell: export: %s: not a valid identifier\n"
# define ERR_CD_NO_FIL_OR_DIR "minishell: cd: %s: No such file or directory\n"
# define ERR_CD_NO_HOME "minishell: cd: HOME not set\n"
# define ERR_CD_RETDIR "minishell: cd: error retrieving current directory\n"
# define ERR_CD_NOT_DIR "minishell: cd: Not a directory: %s\n"
# define ERR_CD_TOO_MANY "minishell: cd: too many arguments\n"
# define ERR_CD_PERMISSION "minishell: cd: permission denied: %s\n"
# define ERR_HD_PERMISSION "minishell: heredoc: permission denied: %s\n"
# define ERR_SYNTERR_ONE_PIPE "Error: syntax error near" \
" unexpected token '|'\n"
# define ERR_SYNTERR_TWO_PIPE "Error: syntax error near unexpected token '||'\n"
# define ERR_UNCL_QUOTE "Error: Unclosed quotes\n"
# define ERR_FORBIDDEN_CHAR "Error: Forbidden character found\n"
# define ERR_SYNTERR_REDIR "Error: syntax error near unexpected token `%s'\n"
# define ERR_SYNTERR_1D "Error: syntax error near unexpected token `%c'\n"
# define ERROR_HD "minishell: warning: here-document\
delimited by end-of-file (wanted `%s')\n"

# endif