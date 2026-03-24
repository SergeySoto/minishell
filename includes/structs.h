/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoto-su <ssoto-su@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:49:01 by ssoto-su          #+#    #+#             */
/*   Updated: 2026/03/24 15:49:02 by ssoto-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	ENV_VAR,
	EXIT_STATUS,
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
}	t_env;

typedef struct s_cmd
{
	char			**args;
	char			*cmd_path;
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_cmd	*next;
	int				pid;
}	t_cmd;

typedef struct s_mini
{
	char	**arg_vector;
	t_env	*env;
	char	**env_array;
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
	int		is_interactive;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}	t_mini;

#endif
