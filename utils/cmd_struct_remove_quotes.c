/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_remove_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:44:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/18 16:52:06 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
