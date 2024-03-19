/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:33:30 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/19 10:51:49 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file expander.c
 * @brief Functions for expanding variables within strings and command tables.
 *
 * This file contains functions related to expanding variables within strings
 * and command tables. It includes functionality for replacing variables marked
 * with a '$' symbol with their corresponding values.
 */

#include "../minishell.h"

/**
 * @brief Expands a single variable within a string.
 * 
 * This function expands a single variable within the input string by replacing
 * it with its corresponding value. It replaces variable with the expanded value
 * at position of pointer i.
 * 
 * @param str The input string containing the variable to be expanded.
 * @param i A pointer to the index in the string where the variable is found.
 * @return The string with the variable expanded.
 */
char	*expand_one_var_in_str(char *str, size_t *i, t_env_list *env_list)
{
	size_t	old_i;
	char	*str_begin;
	char	*str_expanded_var;
	char	*str_rest;
	char	*str_out;

	old_i = *i;
	str_begin = ft_substr_e(str, 0, *i);
	str_expanded_var = get_expanded_var(str, i, env_list);
	str_out = ft_strjoin_e(str_begin, str_expanded_var);
	free(str_begin);
	free(str_expanded_var);
	str_begin = str_out;
	str_rest = end_of_var(&str[old_i + 1]);
	str_out = ft_strjoin_e(str_begin, str_rest);
	free(str_begin);
	return (str_out);
}

/**
 * @brief Determines whether a character is within quotes in a string.
 * 
 * This function determines whether a character at a given index within a string
 * is within single or double quotes. It helps identify whether variables at
 * index position should be expanded or not.
 * 
 * @param str The input string to analyze.
 * @param index The index of the character to check.
 * @return The type of quotes surrounding the character.
 */
t_quote	in_which_quotes(char *str, size_t index)
{
	int		search_single_q;
	int		search_double_q;
	size_t	i;

	search_single_q = 1;
	search_double_q = 1;
	if (str == NULL)
		return (STR_ERR);
	i = -1;
	while (++i < index)
	{
		if (str[i] == '\"' && search_double_q == 1 && search_single_q == 1)
			search_single_q = 0;
		else if (str[i] == '\'' && search_double_q == 1 && search_single_q == 1)
			search_double_q = 0;
		else if (str[i] == '\"' && search_double_q == 1 && search_single_q == 0)
			search_single_q = 1;
		else if (str[i] == '\'' && search_double_q == 0 && search_single_q == 1)
			search_double_q = 1;
	}
	if (search_single_q == search_double_q)
		return (OUT_OF_QUOTES);
	else if (search_single_q < search_double_q)
		return (IN_DOUBLE_QUOTES);
	else
		return (IN_SINGLE_QUOTES);
}

/**
 * @brief Expands variables within a string.
 * 
 * This function expands variables within the input string by replacing
 * them with their corresponding values. It searches for variables marked
 * with a '$' symbol and replaces them with their expanded values, taking
 * into account whether they are within single or double quotes.
 * 
 * @param str The input string to expand variables in.
 * @return The string with all variables expanded.
 */
char	*expand_all_vars_in_str(char *str, t_env_list *env_list)
{
	char	*temp_str;
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && in_which_quotes(str, i) != IN_SINGLE_QUOTES)
		{
			temp_str = str;
			str = expand_one_var_in_str(str, &i, env_list);
			free(temp_str);
		}
		else
			i++;
	}
	return (str);
}

/**
 * @brief Expands variables within a command struct.
 * 
 * This function expands variables within the input command struct by replacing 
 * them with their corresponding values. It iterates through the tokens of
 * the command table and expands variables found in non-operator tokens.
 * 
 * @param cmd The command table to expand variables in.
 */
void	expand_cmd(t_cmd *cmd, t_mini_data *minidata)
{
	t_token		*token;
	t_env_list	*env_list;

	env_list = minidata->env_list;
	token = cmd->first_token;
	while (token != NULL)
	{
		if (!is_operator_type(token))
			token->text = expand_all_vars_in_str(token->text, env_list);
		token = token->next;
	}
}
