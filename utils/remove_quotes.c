/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_remove_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:44:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 16:56:32 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cmd_struct_remove_quotes.c
 * @brief Functions for removing quotes from tokens within command structures.
 *
 * This file contains functions related to removing quotes from tokens within
 * command structures. It includes functionality for parsing token text, 
 * removing quotes surrounding words, and updating token text accordingly to
 * eliminate quotes.
 */

#include "../minishell.h"

/**
 * @brief Removes quotes from the text of a token.
 * 
 * This function removes quotes from the text of the specified token. It parses
 * the token text, removes quotes surrounding words, and updates the token text
 * accordingly to eliminate the quotes.
 * 
 * @param token The token to remove quotes from.
 */
void	remove_quotes_in_token(t_token *token)
{
	char	*new_token;
	char	*temp_token_text;
	char	**arr_of_strs;

	arr_of_strs = parse_token_text(token->text);
	arr_of_strs = remove_quotes_encaptulates_words(arr_of_strs);
	new_token = ft_arr_to_str(arr_of_strs);
	ft_free_array(arr_of_strs);
	temp_token_text = token->text;
	token->text = new_token;
	free(temp_token_text);
}

/**
 * @brief Removes quotes from tokens within a command.
 * 
 * This function removes quotes from tokens within the specified command. It
 * iterates through the tokens of the command and calls the 
 * 'remove_quotes_in_token' function to remove quotes from non-operator tokens.
 * 
 * @param cmd The command to remove quotes from its tokens.
 */
void	remove_quotes_in_cmd_tokens(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token != NULL)
	{
		if (!is_operator_type(token))
			remove_quotes_in_token(token);
		token = token->next;
	}
}
