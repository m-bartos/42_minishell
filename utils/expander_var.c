/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:41:18 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/16 19:08:37 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Finds the end of a variable in a string.
 * 
 * This function iterates through the given string until it reaches the end of
 * a variable. The function stops when it encounters a character that is not
 * part of a variable name, such as '$', '/', ':', '^', ';', '-', '%', '&',
 * '*', '#', or '@'.
 * 
 * @param str The string to search for the end of a variable.
 * @return A pointer to the character that marks the end of the variable in the
 *         string.
 */
char	*end_of_var(char *str)
{
	while (*str != '$' && *str != '\0' && *str != '/' && *str != ':'
		&& *str != '^' && *str != ';' && *str != '-' && *str != '%'
		&& *str != '&' && *str != '*' && *str != '#' && *str != '@'
		&& *str != '"' && *str != '\'' && *str != '\n' && *str != ' ')
		str++;
	return (str);
}

/**
 * @brief Retrieves the name of a variable from a string.
 *
 * This function takes a string as input and searches for a variable name
 * starting with a '$' character. It returns a dynamically allocated string
 * containing the variable name without the '$' character. The caller is
 * responsible for freeing the memory allocated for the returned string.
 *
 * @param str The input string.
 * @return A dynamically allocated string containing the variable name,
 *         or NULL if memory allocation fails.
 */
char	*get_variable_name(char	*str, size_t *i)
{
	size_t	size;
	char	*str_start_var;
	char	*str_out;

	str_start_var = &str[*i + 1];
	size = end_of_var(str_start_var) - str_start_var;
	str_out = ft_substr(str_start_var, 0, size);
	if (str_out == NULL)
		return (NULL);
	*i = *i - size;
	return (str_out);
}

/**
 * @brief Retrieves the value of an environment variable and returns it.
 *
 * This function takes a string as input and extracts the variable name from
 * it. It then retrieves the corresponding value from the environment variables
 * and returns it. The variable name is obtained using the get_variable_name()
 * function.
 *
 * @param str The input string containing the variable name.
 * @return The value of the environment variable, or NULL if the variable is
 *         not found.
 */
char	*get_expanded_var(char *str, size_t *i)
{
	char	*str_var_name;
	char	*str_expanded_var;

	str_var_name = get_variable_name(str, i);
	str_expanded_var = getenv(str_var_name);
	*i = *i + ft_strlen(str_expanded_var);
	free(str_var_name);
	return (str_expanded_var);
}
