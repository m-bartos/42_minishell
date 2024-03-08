/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_remove_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:44:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/08 16:14:58 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quotes(t_token *ptr_node)
{
	char	*token;
	int		len;

	token = ptr_node->token;
	if (is_in_double_quotes(ptr_node) || is_in_single_quotes(ptr_node))
	{
		len = ft_strlen(token);
		token[len - 1] = '\0';
		ptr_node->token = ft_strdup(&token[1]);
		free(token);
	}
}

void	remove_quotes_from_cmd_tab(t_cmd *ptr_cmd_tab)
{
	t_token	*ptr_node;

	ptr_node = ptr_cmd_tab->first_token;
	while (ptr_node != NULL)
	{
		if (!is_operator_type(ptr_node))
			remove_quotes(ptr_node);
		ptr_node = ptr_node->next;
	}
}
