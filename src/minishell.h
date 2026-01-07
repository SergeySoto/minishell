


typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN, //<
	REDIR_OUT, //>
	HEREDOC, //<< [cite: 115]
	APPEND, //>> [cite: 117]
}	t_type;

typedef struct s_token
{
	char	*content;
	t_type	type;
	struct s_token *next;
}	t_token;

typedef struct s_mini
{
	// ---MEMORY AND ENVIROMENT---
	char	**env;
	// ---READ AND PARSE---
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
	// ---STATUS---
	// ---CONTROL---
	int	stdin_backup;
	int	stdout_backup;
}	t_mini;
