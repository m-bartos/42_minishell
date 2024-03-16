/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:33:30 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/16 18:51:48 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_str_with_one_expanded_var(char *str, size_t *i)
{
	size_t	old_i;
	char	*str_begin;
	char	*str_expanded_var;
	char	*str_rest;
	char	*str_out;

	old_i = *i;
	str_begin = ft_substr(str, 0, *i);
	str_expanded_var = get_expanded_var(str, i);
	str_out = ft_strjoin(str_begin, str_expanded_var);
	if (str_out == NULL)
		return (NULL);
	free(str_begin);
	str_begin = str_out;
	str_rest = end_of_var(&str[old_i + 1]);
	str_out = ft_strjoin(str_begin, str_rest);
	if (str_out == NULL)
		return (NULL);
	free(str_begin);
	return (str_out);
}

t_in_quotes	in_which_quotes(char *str, size_t index)
{
	int		search_single_q;
	int		search_double_q;
	size_t	i;

	search_single_q = 1;
	search_double_q = 1;
	if (str == NULL)
		return (STR_ERR);
	i = 0;
	while (i < index)
	{
		if (str[i] == '\"' && search_double_q == 1 && search_single_q == 1)
			search_single_q = 0;
		else if (str[i] == '\'' && search_double_q == 1 && search_single_q == 1)
			search_double_q = 0;
		else if (str[i] == '\"' && search_double_q == 1 && search_single_q == 0)
			search_single_q = 1;
		else if (str[i] == '\'' && search_double_q == 0 && search_single_q == 1)
			search_double_q = 1;
		i++;
	}
	if (search_single_q == search_double_q)
		return (OUT_OF_QUOTES);
	else if (search_single_q < search_double_q)
		return (IN_DOUBLE_QUOTES);
	else
		return (IN_SINGLE_QUOTES);
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
	char	*str_old;
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && in_which_quotes(str, i) != IN_SINGLE_QUOTES)
		{
			str_old = str;
			str = get_str_with_one_expanded_var(str, &i);
			free(str_old);
		}
		else
			i++;
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
void	expand_cmd(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token != NULL)
	{
		if (!is_operator_type(token))
			token->text = expand_all_vars_in_str(token->text);
		token = token->next;
	}
}
