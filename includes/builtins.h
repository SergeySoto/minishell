#ifndef BUILTINS_H
# define BUILTINS_H

// =========== PWD ============ //
/**
 * @brief Built-in pwd command: prints the current working directory to stdout
 * @return 0 on success, 1 if getcwd fails
 */
int		ft_pwd(t_mini *mini);

// ========== ENV =========== //
/**
 * @brief Built-in env command: prints all environment variables to stdout
 * @param mini The minishell instance
 * @param av Array of arguments (av[1] must be NULL, no arguments accepted)
 * @return 0 on success, 1 if env_array is NULL, 127 if extra arguments are
 * 	passed
 */
int		ft_env(t_mini *mini, char **av);

// ========== UNSET =========== //

/**
 * @brief Built-in unset command: removes one or more environment variables
 * @param mini The minishell instance
 * @param cmd The command structure containing the variable names to unset
 * @return Always returns 0
 */
int		ft_unset(t_mini *mini, t_cmd *cmd);

// ========== ECHO =========== //
/**
 * @brief Checks whether a string is a valid -n flag (e.g. "-n", "-nn", etc.)
 * @param str The string to check
 * @return 1 if it is a valid -n flag, 0 otherwise
 */
int		check_flag(char *str);

/**
 * @brief Prints arguments without a trailing newline, skipping leading 
 * -n flags
 * @param av Array of arguments starting from av[1]
 * @return 1 on success, 0 if av is NULL or empty
 */
int		whitout_n(char **av);

/**
 * @brief Prints arguments with a trailing newline (default echo behavior)
 * @param av Array of arguments where av[0] is "echo"
 * @return 1 on success, 0 if av is NULL or empty
 */
int		whit_n(char **av);

/**
 * @brief Built-in echo command: prints arguments to stdout 
 * with optional -n flag
 * @param av Array of arguments where av[0] is "echo"
 * @return 0 on success, 1 if av is NULL or empty
 */
int		ft_echo(char **av);

// ========= EXPORT =========== //

/**
 * @brief Checks whether a character is invalid as the first character 
 * of a variable name
 * @param c The character to validate
 * @return 1 if invalid (not alpha and not '_'), 0 if valid
 */
int		is_valid(char *av);

/**
 * @brief Extracts the key part from a "KEY=value" or "KEY" string
 * @param str The input string to parse
 * @return A newly allocated string containing the key, or NULL if str is empty
 */
char	*key(char *str);

/**
 * @brief Extracts the value part from a "KEY=value" string
 * @param str The input string to parse
 * @return A newly allocated string with the value, an empty string if "KEY=",
 * or NULL if no '=' found
 */
char	*value(char *str);

/**
 * @brief Creates or updates an environment variable in the linked list
 * @param mini The minishell instance
 * @param k The key (variable name) to create or update
 * @param v The value to assign (NULL keeps the key without updating the value)
 */
void	create_new_env(t_mini *mini, char *k, char *v);

/**
 * @brief Parses and updates or adds all key=value pairs from an argument array
 * @param mini The minishell instance
 * @param av Array of arguments in "KEY=value" or "KEY" format
 * @return 0 on success, 1 if av is NULL/empty or a key starts with an 
 * invalid character
 */
int		update_or_add_env(t_mini *mini, char **av);

/**
 * @brief Returns the first argument with an invalid variable name 
 * (invalid first char)
 * @param av The NULL-terminated array of argument strings
 * @return Pointer to the first invalid argument, or NULL if all are valid
 */
char	*return_av_failed(char **av);

/**
 * @brief Performs a single pass of bubble sort on the environment 
 * linked list by key
 * @param mini The minishell instance whose env list will be partially sorted
 */
void	swap_nodes(t_mini *mini);

/**
 * @brief Prints all environment variables in "declare -x KEY="value"" format
 * @param mini The minishell instance
 */
void	print_order_env(t_mini *mini);

/**
 * @brief Sorts the environment linked list alphabetically and prints it
 * @param mini The minishell instance
 * @return Always returns 0
 */
int		order_env(t_mini *mini);

/**
 * @brief Built-in export command: validates and adds or updates 
 * environment variables
 * @param mini The minishell instance
 * @param av Array of arguments in "KEY=value" or "KEY" format 
 * (av[0] = "export")
 * @return 0 on success, 1 if an invalid variable name is found
 */
int		ft_export(t_mini *mini, char **av);

// =========== CD ============= //

/**
 * @brief Counts the number of strings in a NULL-terminated array
 * @param av The NULL-terminated array of strings
 * @return The number of elements in the array, 0 if NULL or empty
 */
int		count_av(char **av);

/**
 * @brief Prints the appropriate error message for a failed chdir 
 * call based on errno
 * @param av Array where av[0] is the path that caused the failure
 */
void	chdir_fail(char **av);

/**
 * @brief Updates the PWD environment variable with the current 
 * working directory
 * @param mini The minishell instance
 * @param path The new current working directory path
 * @return 0 on success, 1 if path is NULL
 */
int		try_getcwd(t_mini *mini, char *path);

/**
 * @brief Changes the current directory to the given path and updates PWD
 * @param mini The minishell instance
 * @param av Array where av[0] is the target directory path
 * @return 0 on success, 1 on chdir failure
 */
int		change_directory(t_mini *mini, char **av);

/**
 * @brief Changes the current directory to the HOME environment variable
 * @param mini The minishell instance
 * @return 0 on success, 1 if HOME is not set or chdir fails
 */
int		go_home(t_mini *mini);

/**
 * @brief Built-in cd command: changes the current directory and 
 * updates OLDPWD/PWD
 * @param mini The minishell instance
 * @param av Array of arguments (av[0] = "cd", av[1] = optional target path)
 * @return 0 on success, 1 on failure
 */
int		ft_cd(t_mini *mini, char **av);

// ========== EXIT =========== //

/**
 * @brief Checks whether a string represents a valid numeric exit code
 * @param str The string to validate
 * @return 1 if the string is a valid number, 0 otherwise
 */
int		is_numeric_av(char *str);

/**
 * @brief Checks whether a numeric string overflows a valid range (> 10 digits)
 * @param str The numeric string to check for overflow
 * @return 1 if overflow is detected, 0 otherwise
 */
int		is_overflow(char *str);

/**
 * @brief Handles exit with a non-numeric argument: prints an error 
 * and exits with code 2
 * @param mini The minishell instance
 * @param cmd The command structure containing the arguments
 * @return 0 if no error (numeric argument), does not return if non-numeric
 */
int		ft_error_exit(t_mini *mini, t_cmd *cmd);

/**
 * @brief Handles the case where exit should NOT proceed due to 
 * too many arguments
 * @param mini The minishell instance
 * @param cmd The command structure containing the arguments
 * @return 1 if too many arguments are given, 0 otherwise
 */
int		ft_not_exit(t_mini *mini, t_cmd *cmd);

/**
 * @brief Checks if the user input contains a pipe character.
 * @param mini Pointer to the main shell structure, uses mini->input.
 * @return 1 if a pipe '|' is found, 0 otherwise.
 */
int	ft_exit_pipe(t_mini *mini);

/**
 * @brief Built-in exit command: exits the shell with an optional 
 * numeric status code
 * @param mini The minishell instance
 * @param cmd The command structure containing the arguments
 * @return 1 if exit is aborted due to too many arguments, does not 
 * return otherwise
 */
int		ft_exit(t_mini *mini, t_cmd *cmd);

#endif