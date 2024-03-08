/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:36:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/08 22:36:21 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	// char *cmd1[] = {"/bin/ls", "-la", NULL};
	// char *cmd2[] = {"/usr/bin/wc", "-l", NULL};
	// char **cmds[] = {cmd1, cmd2, NULL};
*/

int	main(void)
{
// Elements declaration
	t_token	*token10;
	t_token	*token11;
	t_token *token12;

	t_token	*token20;
	t_token	*token21;
	t_token	*token22;
	t_token	*token23;

	t_command	cmd1;
	t_command	cmd2;

	t_cmd_tab	tab;

	ft_init_cmd(&cmd1);
	ft_init_cmd(&cmd2);
	ft_init_cmd_table(&tab);

// First command
	char *exec_cmd1[] = {"/bin/cat", NULL};
	token10 = ft_create_token("<", R_IN);
	token11 = ft_create_token("infile.txt", R_INFILE);
	token12 = ft_create_token("cat", CMD);
	ft_append_token_to_cmd(&cmd1, token10);
	ft_append_token_to_cmd(&cmd1, token11);
	ft_append_token_to_cmd(&cmd1, token12);
	cmd1.execve_cmd = exec_cmd1;

// Second command
	char *exec_cmd2[] = {"/usr/bin/wc", "-l", NULL};
	token20 = ft_create_token("wc", CMD);
	token21 = ft_create_token("-l", ARG);
	token22 = ft_create_token(">", R_OUT);
	token23 = ft_create_token("output.txt", R_OUTFILE);
	ft_append_token_to_cmd(&cmd2, token20);
	ft_append_token_to_cmd(&cmd2, token21);
	ft_append_token_to_cmd(&cmd2, token22);
	ft_append_token_to_cmd(&cmd2, token23);
	cmd2.execve_cmd = exec_cmd2;

// Add comands to the table
	ft_append_cmd_to_tab(&tab, &cmd1);
	ft_append_cmd_to_tab(&tab, &cmd2);

// Test print various values from the table
	t_command	*command;
	t_token		*token;
	command = tab.first_cmd;

	while (command != NULL)
	{
		token = command->first_token;
		while (token != NULL)
		{
			if (token->next != NULL)
				ft_printf("%s ", token->text);
			else
				ft_printf("%s", token->text);
			token = token->next;
		}
		command = command->next_cmd;
		if (command != NULL)
			ft_printf(" | ");
	}
	ft_putstr_fd("\n", 1);
	command = tab.first_cmd;
	while (command != NULL)
	{
		token = command->first_token;
		while (token != NULL)
		{
			if (token->next != NULL)
				ft_printf("%d ", token->type);
			else
				ft_printf("%d", token->type);
			token = token->next;
		}
		command = command->next_cmd;
		if (command != NULL)
			ft_printf(" | ");
	}

	ft_putstr_fd("\n", 1);
// End of test

// Execute the commands from the table
	ft_exec_commands(&tab);

	return (0);
}
