/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_struct_ops.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:42:04 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/08 23:19:52 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_cmd_tab_struct(t_cmd_tab *cmd_tab)
{
	cmd_tab->first_cmd = NULL;
	cmd_tab->last_cmd = NULL;
	cmd_tab->size = 0;
}

// rotates token from top to bottom and promotes the second to be first
void	ft_rotate_cmd(t_cmd_tab *cmd_tab)
{
	t_cmd	*temp_first_next;
	// prevents any action if there is nothing to rotata = cmd is empty or has one token
	if (cmd_tab->size > 1)
	{
		temp_first_next = cmd_tab->first_cmd->next;
		cmd_tab->last_cmd->next = cmd_tab->first_cmd;
		cmd_tab->first_cmd->next = NULL;
		cmd_tab->first_cmd->prev = cmd_tab->last_cmd;
		cmd_tab->last_cmd = cmd_tab->first_cmd;
		temp_first_next->prev = NULL;
		cmd_tab->first_cmd = temp_first_next;
	}
}
// insert token on top of a stack
void	ft_push_cmd(t_cmd_tab *cmd_tab)
{
	t_cmd	*ptr_cmd;

	ptr_cmd = malloc(sizeof(t_cmd));
	if (!ptr_cmd)
		return ;
	ft_init_cmd_struct(ptr_cmd);
	ptr_cmd->next = cmd_tab->first_cmd;
	ptr_cmd->prev = NULL;
	if (cmd_tab->first_cmd != NULL)
		cmd_tab->first_cmd->prev = ptr_cmd;
	if (cmd_tab->first_cmd == NULL)
		cmd_tab->last_cmd = ptr_cmd;
	cmd_tab->first_cmd = ptr_cmd;
	cmd_tab->size++;
}

/*
Use it for actual cmd insertion.
Two action function:
	Inserts a node to cmd on the top = first node
	Moves the inserted node to the bottom and promotes the second to be first
When applied to a loop it will always keep the very first inserted node to be first node in the cmd
*/
void	ft_push_rotate_cmd(t_cmd_tab *cmd_tab)
{
	ft_push_cmd(cmd_tab);
	ft_rotate_cmd(cmd_tab);
}

// cleanup method
void	ft_delete_cmds_in_cmd_tab(t_cmd_tab *cmd_tab)
{
	t_cmd	*current;
	t_cmd	*temp;
	t_token	*current_token;
	t_token	*temp_token;

	current = cmd_tab->first_cmd;
	while (current != NULL)
	{
		temp = current->next;
		current_token = current->first_token;
		while(current_token != NULL)
		{
			temp_token = current_token->next;
			free(current_token->text);
			free(current_token);
			current_token = temp_token;
		}
		free(current);
		current = temp;
		temp = NULL;
	}
	cmd_tab->first_cmd = NULL;
	cmd_tab->last_cmd = NULL;
	cmd_tab->size = 0;
}
