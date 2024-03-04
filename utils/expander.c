/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:33:30 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/04 14:43:25 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Expands a string by replacing a single variable with its value.
 *
 * This function takes a string `str` and a variable `expanded_var` and returns
 * a new string where the first occurrence of the variable in `str` is replaced
 * with its value.
 *
 * @param str The original string to be expanded.
 * @param expanded_var The value of the variable to be replaced.
 * @return A new string with the replaced variable, or NULL if mallocat fails.
 */
char	*malloc_new_expanded_str(char *str, char *str_expanded_variable)
{
	size_t	size;
	char	*str_out;

	size = ft_strchr(str, '$') - str;
	if (str_expanded_variable != NULL)
		size = size + ft_strlen(str_expanded_variable);
	size = size + ft_strchr(str, '\0') - end_of_var(ft_strchr(str, '$') + 1);
	str_out = (char *) malloc(sizeof(char) * (size + 1));
	if (!str_out)
		return (NULL);
	return (str_out);
}

/**
 * @brief Expands a string by replacing a single variable with its value.
 * 
 * This function takes a string `str` and a variable `expanded_var` and returns
 * a new string where the first occurrence of the variable in `str` is replaced
 * with its value.
 * 
 * @param str The original string to be expanded.
 * @param expanded_var The value of the variable to be replaced.
 * @return A new string with the variable replaced, or NULL if memory allocation
 *         fails.
 */
char	*get_str_with_one_expanded_var(char *str, char *expanded_var)
{
	size_t	index;
	size_t	j;
	char	*str_out;
	char	*str_rest;

	str_out = malloc_new_expanded_str(str, expanded_var);
	if (!str_out)
		return (NULL);
	index = 0;
	while (str[index] != '$')
	{
		str_out[index] = str[index];
		index++;
	}
	j = 0;
	while (expanded_var != NULL && expanded_var[j] != '\0')
		str_out[index++] = expanded_var[j++];
	str_rest = end_of_var(ft_strchr(str, '$') + 1);
	j = 0;
	while (str_rest[j] != '\0')
		str_out[index++] = str_rest[j++];
	str_out[index] = '\0';
	return (str_out);
}

/**
 * @brief Expands all variables in a given string.
 * 
 * This function expands all variables in the input string by replacing
 * them with their corresponding values. It searches for variables marked
 * with a '$' symbol and replaces them with their expanded values.
 * 
 * @param str The input string to expand variables in.
 * @return The string with all variables expanded.
 */
char	*expand_all_vars_in_str(char *str)
{
	char	*expanded_var;
	char	*str_old;

	while (ft_strchr(str, '$'))
	{
		str_old = str;
		expanded_var = get_expanded_var(str);
		str = get_str_with_one_expanded_var(str, expanded_var);
		free(str_old);
	}
	return (str);
}

/**
 * @brief Expands variables that should be expanded in a given command table.
 * 
 * This function expands all variables in the input command table 
 * that should be expanded by replacing them with their corresponding values.
 * 
 * @param str The input string to expand variables in.
 * @return The string with all variables expanded.
 */
void	expand_cmd_tab(t_command_table *ptr_cmd_tab)
{
	t_node	*ptr_node;

	ptr_node = ptr_cmd_tab->first_node;
	while (ptr_node != NULL)
	{
		if (!is_operator_type(ptr_node) && !is_in_single_quotes(ptr_node))
			ptr_node->token = expand_all_vars_in_str(ptr_node->token);
		ptr_node = ptr_node->next;
	}
}