/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:57:57 by mbartos           #+#    #+#             */
/*   Updated: 2024/05/15 09:58:19 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a variable exists in the environment list.
 * 
 * This function searches for a variable by name in the environment list.
 * If the variable is not found, it prints an error message and returns FALSE.
 * If the variable is found, it returns TRUE.
 * 
 * @param env_list A pointer to the environment list to search.
 * @param var_name The name of the variable to search for.
 * @return TRUE if the variable is found, FALSE otherwise.
 */
int	is_var_in_env_list(t_env_list *env_list, char *var_name)
{
	char	*test_var;
	int		is_ok;

	is_ok = TRUE;
	test_var = ft_get_env(env_list, var_name);
	if (test_var == NULL)
	{
		ft_putstr_fd("Cannot find '", 2);
		ft_putstr_fd(var_name, 2);
		ft_putstr_fd("' variable needed for prompt!\n", 2);
		is_ok = FALSE;
	}
	free(test_var);
	return (is_ok);
}

/**
 * @brief Checks if the USER environment variable is set.
 * 
 * This function checks if the USER environment variable is set in the current
 * environment. If the variable is not found, it prints an error message and
 * returns FALSE. Otherwise, it returns TRUE.
 * 
 * @return TRUE if the USER variable is set, FALSE otherwise.
 */
int	is_user(void)
{
	char	*user;
	int		is_ok;

	is_ok = TRUE;
	user = getenv("USER");
	if (user == NULL)
	{
		ft_putstr_fd("Cannot find '", 2);
		ft_putstr_fd("USER", 2);
		ft_putstr_fd("' variable in parent process needed for prompt!\n", 2);
		is_ok = FALSE;
	}
	return (is_ok);
}

/**
 * @brief Checks for necessary environment variables for the prompt.
 * 
 * This function checks if the necessary environment variables (USER and PWD)
 * are set in the environment. If any of the required variables are missing,
 * it returns TRUE indicating an error.
 * 
 * @param env_list A pointer to the environment list to search.
 * @return TRUE if there is an error (missing variables), FALSE otherwise.
 */
int	check_prompt_vars(t_env_list *env_list)
{
	int		is_error;

	is_error = FALSE;
	if (is_user() == FALSE)
		is_error = TRUE;
	if (is_var_in_env_list(env_list, "PWD") == FALSE)
		is_error = TRUE;
	return (is_error);
}
