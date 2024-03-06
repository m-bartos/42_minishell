/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_remove_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:44:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/06 09:39:11 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_quotes(t_node *ptr_node)
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

void	remove_quotes_from_cmd_tab(t_cmd_tab *ptr_cmd_tab)
{
	t_node	*ptr_node;

	ptr_node = ptr_cmd_tab->first_node;
	while (ptr_node != NULL)
	{
		if (!is_operator_type(ptr_node))
			remove_quotes(ptr_node);
		ptr_node = ptr_node->next;
	}
}
