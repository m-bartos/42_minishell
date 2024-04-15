/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:41:18 by mbartos           #+#    #+#             */
/*   Updated: 2024/04/15 13:42:52 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expander_var.c
 * @brief Functions for expanding variables within strings.
 *
 * This file contains functions related to expanding variables within strings.
 * It includes functionality for identifying variable names, retrieving their
 * values from the environment, and replacing occurrences of variables within
 * strings with their corresponding values.
 */

#include "../minishell.h"

/**
 * @brief Finds the end of a variable in a string.
 * 
 * This function iterates through the given string until it reaches the end of
 * a variable. The function stops when it encounters a character that is not
 * part of a variable name, such as '$', '/', ':', '^', ';', '-', '%', '&',
 * '*', '#', '@', '"', '\'', '\n', ' ' or '.'.
 * 
 * @param str The string to search for the end of a variable.
 * @return A pointer to the character that marks the end of the variable in the
 *         string.
 */
char	*end_of_var(char *str)
{
	if (*str == '?')
		return (++str);
	while (*str != '$' && *str != '\0' && *str != '/' && *str != ':'
		&& *str != '^' && *str != ';' && *str != '-' && *str != '%'
		&& *str != '&' && *str != '*' && *str != '#' && *str != '@'
		&& *str != '"' && *str != '\'' && *str != '\n' && *str != ' '
		&& *str != '.' && *str != '?' && *str != '!')
		str++;
	return (str);
}

/**
 * @brief Extracts the name of a variable from a string.
 * 
 * This function retrieves the name of a variable from the given string,
 * starting from the specified index. It identifies the variable name until
 * it reaches the end of the variable, using the 'end_of_var' function.
 * 
 * @param str The string containing the variable.
 * @param i A pointer to the index where the variable starts.
 * @return The name of the variable extracted from the string.
 */

char	*get_variable_name(char	*str, size_t *i)
{
	size_t	size;
	char	*str_start_var;
	char	*str_out;

	str_start_var = &str[*i + 1];
	size = end_of_var(str_start_var) - str_start_var;
	str_out = ft_substr_e(str_start_var, 0, size);
	return (str_out);
}

/**
 * @brief Retrieves the value of a variable from the environment.
 * 
 * This function retrieves the value of a variable with the specified name
 * from the environment. It then returns the value to be used for variable
 * expansion within strings.
 * 
 * @param str The string containing the variable name.
 * @param i A pointer to the index where the variable starts.
 * @return The value of the variable retrieved from the environment.
 */
char	*get_expanded_var(char *str, size_t *i, t_env_list *env_list)
{
	char	*str_var_name;
	char	*str_expanded_var;

	str_var_name = get_variable_name(str, i);
	str_expanded_var = ft_get_env(env_list, str_var_name);
	*i = *i + ft_strlen(str_expanded_var);
	free(str_var_name);
	return (str_expanded_var);
}
