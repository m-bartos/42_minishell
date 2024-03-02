/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:49:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/02 13:05:36 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_cmd(t_command_table *cmd_table)
{
	t_node	*node;

	node = cmd_table->first_node;
	while (node != NULL)
	{
		ft_printf(" %s", node->token);
		node = node->next;
	}
	ft_putstr_fd("\n", 1);
}
