/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_remove_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:44:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/08 16:24:31 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quotes(t_token *ptr_token)
{
	char	*token;
	int		len;

	token = ptr_token->text;
	if (is_in_double_quotes(ptr_token) || is_in_single_quotes(ptr_token))
	{
		len = ft_strlen(token);
		token[len - 1] = '\0';
		ptr_token->text = ft_strdup(&token[1]);
		free(token);
	}
}

void	remove_quotes_from_cmd_tab(t_cmd *ptr_cmd)
{
	t_token	*ptr_token;

	ptr_token = ptr_cmd->first_token;
	while (ptr_token != NULL)
	{
		if (!is_operator_type(ptr_token))
			remove_quotes(ptr_token);
		ptr_token = ptr_token->next;
	}
}