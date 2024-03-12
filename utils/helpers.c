/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:49:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/12 12:55:22 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_cmd(t_cmd *cmd)
{
	t_token	*token;

	token = cmd->first_token;
	while (token != NULL)
	{
		ft_printf(" %s", token->text);
		token = token->next;
	}
	ft_putstr_fd("\n", 1);
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

// this function will not be needed
void	print_cmd(t_cmd *cmd)
{
	t_token	*token;
	char	**execve_cmd_arr;
	int		i;

	printf("-------------\n");
	i = 0;
	if (cmd->execve_cmd != NULL)
	{
		printf("Execve cmds: {");
		execve_cmd_arr = cmd->execve_cmd;
		while (execve_cmd_arr[i] != NULL)
		{
			printf("%s", execve_cmd_arr[i]);
			if (execve_cmd_arr[i + 1] != NULL)
				printf(", ");
			execve_cmd_arr++;
		}
		printf("}\n");
		printf("-------------\n");
	}
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
