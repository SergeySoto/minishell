#ifndef UTILS_H
# define UTILS_H

/**
 * @brief Frees a string and a NULL-terminated char** array of strings.
 * @param str Heap-allocated string to free (may be NULL).
 * @param env NULL-terminated array of heap-allocated strings to free 
 * (may be NULL).
 * @return Always NULL.
 */
void	*free_token(char *str, char **env);

/**
 * @brief Frees the entire t_token linked list and sets the head pointer 
 * to NULL.
 * @param token Address of the head pointer of the token list.
 * @return void
 */
void	free_struct_token(t_token **token);

/**
 * @brief Frees all resources held by the shell: iteration data, environment
 *		list, input string and env_array.
 * @param mini Pointer to the main shell structure.
 * @return void
 */
void	free_struct_mini(t_mini *mini);

/**
 * @brief Frees the entire t_env linked list, including keys and values,
 *		and sets the head pointer to NULL.
 * @param envp Address of the head pointer of the env list.
 * @return void
 */
void	free_env(t_env **envp);

/**
 * @brief Frees the entire t_cmd linked list: args, cmd_path, infile, outfile,
 *		closes open FDs (> 2) and sets the head pointer to NULL.
 * @param cmd Address of the head pointer of the cmd list.
 * @return void
 */
void	free_cmd(t_cmd **cmd);

/**
 * @brief Frees per-iteration data: token list, cmd list and input string.
 *		Called at the end of every shell iteration before the next readline.
 * @param mini Pointer to the main shell structure.
 * @return void
 */
void	free_iteration_data(t_mini *mini);

/**
 * @brief Prints all tokens in the list to stdout for debugging purposes.
 * @param head Pointer to the head of the token list.
 * @return void
 */
void	print_tokens(t_token *head);

/**
 * @brief Prints all environment variable nodes to stdout for debugging.
 * @param envp Pointer to the head of the t_env list.
 * @return void
 */
void	print_env(t_env *envp);

/**
 * @brief Removes all quote characters from a token's content string in place.
 *		Designed to be passed to ft_lstiter().
 * @param lst Pointer to the token to trim.
 * @return void
 */
void	trim_quotes(t_token *lst);

/**
 * @brief Iterates over a t_token linked list and calls f() on each node.
 * @param lst Pointer to the head of the token list.
 * @param f Function pointer to call on each t_token node.
 * @return void
 */
void	ft_lstiter(t_token *lst, void (*f)(t_token *));

/**
 * @brief Duplicates a NULL-terminated char** array, allocating new strings
 *		for each element.
 * @param envp The NULL-terminated array to duplicate.
 * @return Heap-allocated deep copy of the array, or NULL on malloc failure.
 */
char	**dup_arr(char **envp);


#endif
