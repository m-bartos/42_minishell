/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 22:46:28 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/06 09:36:01 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// initiate command table
/*
Declare the command table to be in the stack not heap! The compiler takes care of the memmory.
Example:
t_cmd_tab cmd_table;
ft_init_command_table(&cmd_table)
*/
void	ft_init_command_table(t_cmd_tab *cmd_table)
{
	cmd_table->first_node = NULL;
	cmd_table->last_node = NULL;
	cmd_table->size = 0;
}

// rotates token from top to bottom and promotes the second to be first
void	ft_rotate_token(t_cmd_tab *cmd_table)
{
	t_node	*temp_first_next;
	// prevents any action if there is nothing to rotata = cmd_table is empty or has one token
	if (cmd_table->size > 1)
	{
		temp_first_next = cmd_table->first_node->next;
		cmd_table->last_node->next = cmd_table->first_node;
		cmd_table->first_node->next = NULL;
		cmd_table->first_node->prev = cmd_table->last_node;
		cmd_table->last_node = cmd_table->first_node;
		temp_first_next->prev = NULL;
		cmd_table->first_node = temp_first_next;
	}
}
// insert token on top of a stack
void	ft_push_token(t_cmd_tab *cmd_table, char *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return ;
	node->token = token;
	node->next = cmd_table->first_node;
	node->prev = NULL;
	node->type = -1;
	if (cmd_table->first_node != NULL)
		cmd_table->first_node->prev = node;
	if (cmd_table->first_node == NULL)
		cmd_table->last_node = node;
	cmd_table->first_node = node;
	cmd_table->size++;
}

/*
Use it for actual token insertion.
Two action function:
	Inserts a node to cmd_table on the top = first node
	Moves the inserted node to the bottom and promotes the second to be first
When applied to a loop it will always keep the very first inserted node to be first node in the cmd_table
*/
void	ft_push_rotate_token(t_cmd_tab *cmd_table, char *token)
{
	ft_push_token(cmd_table, token);
	ft_rotate_token(cmd_table);
}

// cleanup method
void	ft_delete_nodes(t_cmd_tab *cmd_table)
{
	t_node	*current;
	t_node	*temp;

	current = cmd_table->first_node;
	while (current != NULL)
	{
		temp = current->next;
		free(current);
		current = temp;
		temp = NULL;
	}
	cmd_table->first_node = NULL;
	cmd_table->last_node = NULL;
	cmd_table->size = 0;
}
