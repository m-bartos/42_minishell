/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_filler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:04:25 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/08 16:14:58 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// this function will not be needed
void	print_cmd_tab(t_cmd *ptr_cmd_tab)
{
	t_token	*ptr_node;
	int		i;

	ptr_node = ptr_cmd_tab->first_token;
	i = 0;
	printf("-------------\n");
	while (ptr_node != NULL)
	{
		printf("%*i. Token: |%*s|     ", 2, i, 20, ptr_node->token);
		printf("Type: %i\n", ptr_node->type);
		ptr_node = ptr_node->next;
		i++;
	}
	printf("-------------\n");
}

void	fill_cmd_tab(t_cmd *ptr_cmd_tab, char **arr_of_tokens)
{
	size_t	index;

	index = 0;
	while (arr_of_tokens[index])
	{
		ft_push_rotate_token(ptr_cmd_tab, arr_of_tokens[index]);
		index++;
	}
}
