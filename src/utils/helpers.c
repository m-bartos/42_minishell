/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:49:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/15 09:52:31 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints the execve command array.
 * 
 * This function prints the elements of the execve command array. If the array
 * is NULL, it prints "Execve cmds: NULL". Otherwise, it prints the array
 * elements in a comma-separated format enclosed in braces.
 * 
 * @param execve_cmd The array of command strings to be printed.
 */
void	print_execve_cmd(char	**execve_cmd)
{
	int	i;

	i = 0;
	printf("-------------\n");
	if (execve_cmd == NULL)
		printf("Execve cmds: NULL\n");
	else
	{
		printf("Execve cmds: {");
		while (execve_cmd[i] != NULL)
		{
			printf("%s", execve_cmd[i]);
			if (execve_cmd[i + 1] != NULL)
				printf(", ");
			i++;
		}
		printf("}\n");
	}
	printf("-------------\n");
}

/**
 * @brief Prints the details of a command structure.
 * 
 * @param cmd The command structure to be printed.
 */
void	print_cmd(t_cmd *cmd)
{
	t_token	*token;
	int		i;

	if (!cmd)
		return ;
	print_execve_cmd(cmd->execve_cmd);
	token = cmd->first_token;
	i = 0;
	while (token != NULL)
	{
		printf("%*i. Token: |%*s|     ", 2, i, 20, token->text);
		printf("Type: %i\n", token->type);
		token = token->next;
		i++;
	}
	printf("-------------\n");
}

/**
 * @brief Prints the details of a command table.
 * 
 * @param cmd_tab The command table structure to be printed.
 */
void	print_cmd_tab(t_cmd_tab *cmd_tab)
{
	t_cmd	*cmd;
	int		i;

	if (!cmd_tab)
		return ;
	cmd = cmd_tab->first_cmd;
	i = 0;
	printf("************************************************\n");
	printf("*******************CMD_TAB**********************\n");
	printf("************************************************\n");
	while (cmd != NULL)
	{
		printf("%*i. CMD of size = %i\n", 2, i, cmd->size);
		print_cmd(cmd);
		i++;
		cmd = cmd->next;
	}
	printf("************************************************\n\n");
}
