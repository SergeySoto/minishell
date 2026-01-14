/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmegon <carmegon@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 20:03:15 by carmegon          #+#    #+#             */
/*   Updated: 2026/01/14 18:39:54 by carmegon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

//Maybe we should include an ENV_VAR (enviroment variables )for the $USER
typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN, //<
	REDIR_OUT, //>
	HEREDOC, //<< [cite: 115]
	APPEND, //>> [cite: 117]
}	t_type;

/* 
	Añado otra variable a esta struct para saber si tiene el metacaracter '$'.
	En caso de NO tenerlo, expand = 0; en caso afirmativo expand = 1.
	Asi sabemos que luego debemos expandir este token!
*/
typedef struct s_token
{
	char			*content;
	t_type			type;
	int				expand;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args; //Arguments for execve {"ls", "-l"}
	char			*cmd_path; //Route "/bin/ls"
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next; //Next command
	int				pid;
}	t_cmd;

typedef struct s_mini
{
	// ---MEMORY AND ENVIROMENT---
	char	**env;
	// ---READ AND PARSE---
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
	// ---STATUS---
	// -- Añadido exit_status para el futuro -- //
	int		exit_status; // Símbolo especial $?
	// ---CONTROL---
	int		stdin_backup;
	int		stdout_backup;
}	t_mini;

// -- Error function -- //
void	*free_token(char *str, char **env);
// -- Lists functions -- //
t_token	*create_token(char *token, int type);
void	add_token_back(t_token **head, char *token);
// -- Check and get the quotes --//
int		check_quotes(char *str);
char	get_quote(char *input);
// -- Validator tokens -- //
int		validator(char	*input);
// -- Types tokens -- //
int		get_type(char *line);


#endif
