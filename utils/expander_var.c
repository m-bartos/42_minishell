/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:41:18 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/02 12:52:16 by mbartos          ###   ########.fr       */
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
		&& *str != '&' && *str != '*' && *str != '#' && *str != '@')
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
char	*get_variable_name(char	*str)
{
	size_t	size;
	size_t	index;
	char	*str_variable;
	char	*str_out;

	str_variable = ft_strchr(str, '$') + 1;
	size = end_of_var(str_variable) - str_variable;
	str_out = (char *) malloc(sizeof(char) * (size + 1));
	if (!str_out)
		return (NULL);
	index = 0;
	while (index < size)
	{
		str_out[index] = str_variable[index];
		index++;
	}
	str_out[index] = '\0';
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
char	*get_expanded_var(char *str)
{
	char	*str_variable;
	char	*str_extended_variable;

	str_variable = get_variable_name(str);
	str_extended_variable = getenv(str_variable);
	free(str_variable);
	return (str_extended_variable);
}
