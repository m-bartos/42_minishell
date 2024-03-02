/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:33:30 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/02 12:59:53 by mbartos          ###   ########.fr       */
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
		str_out[index++] = str[index];
	j = 0;
	if (expanded_var != NULL)
	{
		while (expanded_var[j] != '\0')
			str_out[index++] = expanded_var[j++];
	}
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

// cc expander.c ../libft/ft_strchr.c ../libft/ft_strlen.c ../libft/ft_strdup.c
// int	main (void)
// {
// 	char	str[] = "a/$PATH:a";
// 	char	*str_dynamic;

// 	str_dynamic = ft_strdup(str);
// 	printf("INPUT:\n%s\n\n", str_dynamic);
// 	str_dynamic = expand_all_vars_in_str(str_dynamic);
// 	printf("OUTPUT:\n%s\n", str_dynamic);
// 	free(str_dynamic);
// }
// ---CHECKERS BEFORE EXECUTION---
// folder permission check
// double PIPE, double < <, double > >
// INFILE checker