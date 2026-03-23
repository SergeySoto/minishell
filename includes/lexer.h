#ifndef LEXER_H
# define LEXER_H

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                             tokenizer.c                                    */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Allocates and initialises a new t_token node.
 * @param str The token content string (ownership transferred to the node).
 * @param type The token type integer.
 * @return Pointer to the new t_token node, or NULL on malloc failure.
 */
t_token	*create_token(char *str, int type);

/**
 * @brief Adds input to readline history, runs pre-parsing validation,
 *		smart-splits the input and builds the token linked list in mini->tokens.
 * @param input The raw input string from readline().
 * @param tokens Address of the token list head pointer.
 * @param mini Pointer to the main shell structure.
 * @return void
 */
void	input_to_token(char *input, t_token **tokens, t_mini *mini);

/**
 * @brief Appends a new token at the end of the token linked list.
 *		Creates the head node if the list is empty.
 * @param head Address of the head pointer of the token list.
 * @param token The raw token string to wrap in a new t_token node.
 * @return void
 */
void	add_token_back(t_token **head, char *token);

/**
 * @brief Orchestrates the post-tokenization pipeline: marks expandable tokens,
 *		blocks heredoc delimiter expansion, expands variables, trims quotes,
 *		parses into t_cmd list, resolves command paths and dispatches execution.
 * @param mini Pointer to the main shell structure.
 * @return void
 */
void	process_and_execute(t_mini *mini);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                             smart_split.c                                  */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Fills the pre-allocated str array with all tokens from input,
 *		splitting on whitespace and operators while respecting quotes.
 * @param str Pre-allocated destination array (must have enough slots).
 * @param input The raw input string.
 * @return void
 */
void	fill_mem(char **str, char *input);

/**
 * @brief Splits the input string into a NULL-terminated array of tokens,
 *		treating shell operators as individual tokens and respecting quotes.
 * @param input The raw input string.
 * @return Heap-allocated NULL-terminated array of token strings,
 *		or NULL if input is NULL or on malloc failure.
 */
char	**smart_split(char *input);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                           split_utils_wc.c                                 */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Returns 1 if c is a shell operator character (|, < or >).
 * @param c The character to check.
 * @return 1 if operator, 0 otherwise.
 */
int		is_op(char c);

/**
 * @brief Counts the number of tokens in the input string, treating operators
 *		as individual tokens and respecting quote boundaries.
 * @param str The raw input string.
 * @return Total number of tokens found.
 */
int		word_count(char *str);


/* ═══════════════════════════════════════════════════════════════════════════ */
/*                             expander.c                                     */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Iterates over all tokens and expands those marked with expand == 1.
 *		Removes tokens that become empty after expansion.
 * @param mini Pointer to the main shell structure.
 * @return void
 */
void	expander(t_mini *mini);

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                           expander_utils.c                                 */
/* ═══════════════════════════════════════════════════════════════════════════ */

/**
 * @brief Prevents expansion of the delimiter token that follows a heredoc
 *		operator (<<). Sets expand = 0 on the token after a HEREDOC token.
 * @param lst Pointer to a token in the list (checks if it is type HEREDOC).
 * @return void
 */
void	heredoc_bf_dollar(t_token *lst);

/**
 * @brief Scans a token's content and sets its type and expand flag if a
 *		$VAR or $? pattern is found outside single quotes.
 * @param lst Pointer to the token to inspect and potentially modify.
 * @return void
 */
void	expand_checker(t_token *lst);

/**
 * @brief Finds the index of the character right after the first '$' that
 *		begins a valid variable reference ($VAR or $?) outside single quotes.
 * @param str The string to scan.
 * @return Index (> 0) of the char after '$', or 0 if no valid '$' is found.
 */
int		get_after_dollar(char *str);

/**
 * @brief Extracts the variable name from a string starting right after '$'.
 *		Returns "?" for $?, otherwise reads alnum/underscore characters.
 * @param str Pointer to the character immediately after '$'.
 * @return Heap-allocated variable name string, or NULL on malloc failure.
 */
char	*get_var_name(char *str);

/**
 * @brief Looks up a variable name in the shell's environment and returns
 *		its value. Handles $? by converting mini->exit_status to a string.
 * @param var_name The variable name to look up.
 * @param mini Pointer to the main shell structure.
 * @return Heap-allocated value string (empty string "" if not found),
 *		or NULL on malloc failure.
 */
char	*get_env_content(char *var_name, t_mini *mini);

#endif
