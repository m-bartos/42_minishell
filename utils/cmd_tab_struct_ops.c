/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab_struct_ops.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:42:04 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/12 12:50:34 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_cmd_tab(t_cmd_tab *cmd_tab)
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
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	ft_init_cmd_struct(cmd);
	cmd->next = cmd_tab->first_cmd;
	cmd->prev = NULL;
	if (cmd_tab->first_cmd != NULL)
		cmd_tab->first_cmd->prev = cmd;
	if (cmd_tab->first_cmd == NULL)
		cmd_tab->last_cmd = cmd;
	cmd_tab->first_cmd = cmd;
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
	t_cmd	*current_cmd;
	t_cmd	*temp_cmd;
	t_token	*current_token;
	t_token	*temp_token;

	current_cmd = cmd_tab->first_cmd;
	while (current_cmd != NULL)
	{
		temp_cmd = current_cmd->next;
		current_token = current_cmd->first_token;
		while(current_token != NULL)
		{
			temp_token = current_token->next;
			free(current_token->text);
			free(current_token);
			current_token = temp_token;
		}
		free(current_cmd->execve_cmd);
		free(current_cmd);
		current_cmd = temp_cmd;
		temp_cmd = NULL;
	}
	cmd_tab->first_cmd = NULL;
	cmd_tab->last_cmd = NULL;
	cmd_tab->size = 0;
}

void	print_cmd_tab(t_cmd_tab *cmd_tab)
{
	t_cmd	*cmd;
	int		i;

	cmd = cmd_tab->first_cmd;
	i = 0;
	printf("************************************************\n");
	while(cmd != NULL)
	{
		printf("%*i. CMD\n", 2, i);
		print_cmd(cmd);
		i++;
		cmd = cmd->next;
	}
	printf("************************************************\n");
}