#ifndef PARSER_H
# define PARSER_H

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                           pre_pars_utils.c                                 */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Returns 1 if c is a whitespace character (space or ASCII 9-13).
 * @param c The character to check.
 * @return 1 if whitespace, 0 otherwise.
 */
int		is_space(char c);

/**
 * @brief Checks that the input does not start with a pipe operator.
 * @param str The raw input string.
 * @return 1 if valid, 0 if the string starts with | or ||
 *		(also prints an error message to stderr).
 */
int		check_pipe(char *str);

/**
 * @brief Checks that the input does not end with a pipe operator.
 * @param str The raw input string.
 * @return 1 if valid, 0 if the string ends with | or ||
 *		(also prints an error message to stderr).
 */
int		check_pending_pipe(char *str);

/**
 * @brief Checks that all quote characters in the string are properly closed.
 * @param str The raw input string.
 * @return 1 if all quotes are balanced, 0 if there is an unclosed quote
 *		(also prints an error message to stderr).
 */
int		check_quotes(char *str);

/**
 * @brief Checks that the input contains no forbidden characters (\ and ;)
 *		outside of quotes.
 * @param str The raw input string.
 * @return 1 if no forbidden characters are found, 0 otherwise
 *		(also prints an error message to stderr).
 */
int		check_forbidden(char *str);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                          pre_pars_utils_2.c                                */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Checks that a pipe character at position i is not part of ||, and
 *		that it is followed by a non-pipe, non-NUL token.
 * @param str The raw input string.
 * @param i Index of the '|' character in str.
 * @return 1 if the pipe is valid, 0 otherwise
 *		(also prints an error message to stderr).
 */
int		check_double_pipes(char *str, int i);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                              pre_pars.c                                    */
/* ═══════════════════════════════════════════════════════════════════════════ */
/**
 * @brief Toggles the quote tracking state for a single character.
 *		Opens a quote context when c matches an unquoted ' or ", closes it
 *		when c matches the currently open quote character.
 * @param c The current character being scanned.
 * @param quotes Pointer to the current quote state (0 = none, '\'' or '"').
 * @return void
 */

void	update_quote_status(char c, char *quotes);

/**
 * @brief Runs all pre-parsing validation checks on the raw input string.
 * @param input The raw input string to validate.
 * @return 1 if the input passes all checks, 0 if any check fails.
 */
int		pre_pars(char	*input);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                               envp.c                                       */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Appends a new environment variable node at the end of the list.
 * @param env Address of the head pointer of the t_env linked list.
 * @param key Heap-allocated string for the variable name.
 * @param value Heap-allocated string for the variable value.
 * @return void
 */
void	add_env_back(t_env **env, char *key, char *value);

/**
 * @brief Builds the t_env linked list from the envp array passed to main().
 *		Splits each "KEY=VALUE" string at the first '=' character.
 * @param envp NULL-terminated array of "KEY=VALUE" strings from the OS.
 * @return Pointer to the head of the new t_env list, or NULL if envp is empty.
 */
t_env	*init_env(char **envp);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                             envp_utils.c                                   */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Converts the t_env linked list into a NULL-terminated char** array
 *		suitable for use with execve().
 * @param envp Pointer to the head of the t_env linked list.
 * @return Heap-allocated NULL-terminated array of "KEY=VALUE" strings,
 *		or NULL on malloc failure.
 */
char	**env_to_array(t_env *envp);

/**
 * @brief Creates a minimal t_env list for when the shell is launched without
 *		an environment. Sets PWD to the current working directory and
 *		_ to "/usr/bin/env".
 * @param envp The original envp array (unused, reserved for future use).
 * @return Pointer to the head of the newly created t_env list.
 */
t_env	*create_basic_env(char **envp);

/**
 * @brief Reads $SHLVL from the environment and increments it by 1.
 *		If SHLVL is not set, initialises it to "1".
 * @param mini Pointer to the main shell structure.
 * @return void
 */
void	in_or_de_shlvl(t_mini *mini);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                              parser.c                                      */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Counts the number of argument tokens in the current command segment
 *		(stops at PIPE or end of list). Skips over redirect operator pairs.
 * @param token Pointer to the first token of the current command.
 * @return Number of argument tokens (WORD, ENV_VAR, EXIT_STATUS).
 */
int		count_args(t_token *token);

/**
 * @brief Iterates over the token list for one command segment, filling
 *		cmd->args and processing redirections. Stops at PIPE or list end.
 * @param mini Address of the main shell structure pointer.
 * @param c_token Address of the current token pointer (advanced in place).
 * @param cmd Pointer to the t_cmd being populated.
 * @return 0 on success, -1 if a redirection error occurs (fd_in == -1).
 */
int		process_cmd_tokens(t_mini **mini, t_token **c_token, t_cmd *cmd);

/**
 * @brief Builds the t_cmd linked list from mini->tokens. Creates one t_cmd
 *		per pipeline segment and stores it in mini->cmds.
 * @param mini Address of the main shell structure pointer.
 * @return void
 */
void	init_cmd(t_mini **mini);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                              heredoc.c                                     */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Handles a heredoc redirection: creates a temp file, reads lines
 *		into it until the delimiter is found, then returns a read-only FD
 *		to that file. The temp file is unlinked immediately after opening
 *		for reading.
 * @param delimiter String that closes the heredoc input.
 * @param mini Pointer to the main shell structure.
 * @return Read-only FD of the heredoc content, or -1 on error/interruption.
 */
int		handle_heredoc(char *demiliter, t_mini *mini);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                            parser_utils.c                                  */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Dispatches a redirection token to the appropriate handler:
 *		sets cmd->infile, opens output file, or calls handle_heredoc().
 * @param mini Pointer to the main shell structure.
 * @param token Address of the current token pointer (advanced by 2 after call)
 * @param cmd Pointer to the t_cmd being populated.
 * @return void
 */
void	set_redirects(t_mini *mini, t_token **token, t_cmd *cmd);

/**
 * @brief Processes a single token: if it is a redirect operator, calls
 *		set_redirects(); if it is a WORD/ENV_VAR/EXIT_STATUS, copies it
 *		into cmd->args[i] and increments i.
 * @param mini Pointer to the main shell structure.
 * @param token Address of the current token pointer (advanced in place).
 * @param cmd Pointer to the t_cmd being populated.
 * @param i Pointer to the current argument index (incremented for WORD tokens)
 * @return void
 */
void	handler_redirects(t_mini *mini, t_token **token, t_cmd *cmd, int *i);

#endif
