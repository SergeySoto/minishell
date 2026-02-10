/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:52:52 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/02/03 19:51:46 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type
{
	WORD,
	PIPE, //|
	REDIR_IN, //<
	REDIR_OUT, //>
	HEREDOC, //<< [cite: 115]
	APPEND, //>> [cite: 117]
	ENV_VAR, //$USER
	EXIT_STATUS, //$?
}	t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	int				expand;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

typedef struct s_cmd
{
	char			**args; //Arguments for execve {"ls", "-l"}
	char			*cmd_path; //Route "/bin/ls"
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	int				append; // flag for > or >>
	struct s_cmd	*next; //Next command
	int				pid;
}	t_cmd;

typedef struct s_mini
{
	// ---MEMORY AND ENVIROMENT---
	t_env	*env;
	char	**env_array;
	// ---READ AND PARSE---
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
	// ---STATUS---
	int		exit_status; // Símbolo especial $?
	// ---CONTROL---
	int		stdin_backup;
	int		stdout_backup;
}	t_mini;

#endif
