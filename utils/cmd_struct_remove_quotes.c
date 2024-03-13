/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct_remove_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:44:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/13 12:11:54 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quotes(t_token *token)
{
	char	*token_text;
	int		length;

	token_text = token->text;
	if (is_in_double_quotes(token) || is_in_single_quotes(token))
	{
		length = ft_strlen(token_text);
		token_text[length - 1] = '\0';
		token->text = ft_strdup(&token_text[1]);
		free(token_text);
	}
}

void	remove_quotes_from_cmd(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token != NULL)
	{
		if (!is_operator_type(token))
			remove_quotes(token);
		token = token->next;
	}
}
