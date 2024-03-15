/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:36:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/15 04:11:06 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	// char *cmd1[] = {"/bin/ls", "-la", NULL};
	// char *cmd2[] = {"/usr/bin/wc", "-l", NULL};
	// char **cmds[] = {cmd1, cmd2, NULL};
*/

void	signal_handler(int signal)
{
	ft_printf("\nSignal handled: %d\n", signal);
}


int	main(void)
{
// Elements declaration
	t_command	cmd1;
	t_command	cmd2;
	t_command	cmd3;

	t_cmd_tab	tab;

	ft_init_cmd(&cmd1);
	ft_init_cmd(&cmd2);
	ft_init_cmd(&cmd3);
	ft_init_cmd_table(&tab);

// Third command
	char *exe_cmd3[] = {"echo", "lorem ipsum command"};
	ft_append_token_to_cmd_v2(&cmd3, "echo", CMD_BUILT);
	ft_append_token_to_cmd_v2(&cmd3, "lorem ipsum command", ARG);
	//ft_append_token_to_cmd_v2(&cmd3, "-n", ARG);
	cmd3.execve_cmd = exe_cmd3;

// First command
	char *exec_cmd1[] = {"/bin/cat", NULL};
	// ft_append_token_to_cmd_v2(&cmd1, "<", R_IN);
	// ft_append_token_to_cmd_v2(&cmd1, "infile.txt", R_INFILE);
	ft_append_token_to_cmd_v2(&cmd1, "cat", CMD);
	cmd1.execve_cmd = exec_cmd1;

// Second command
	char *exec_cmd2[] = {"/usr/bin/wc", "-lcw", NULL};
	ft_append_token_to_cmd_v2(&cmd2, "wc", CMD);
	ft_append_token_to_cmd_v2(&cmd2, "-lcw", ARG);
	// ft_append_token_to_cmd_v2(&cmd2,">>", R_OUT_APP);
	// ft_append_token_to_cmd_v2(&cmd2, "output.txt", R_OUTFILE_APP);
	cmd2.execve_cmd = exec_cmd2;


// Add comands to the table
	ft_append_cmd_to_tab(&tab, &cmd3);
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
	// ft_putstr_fd("\n", 1);
	// command = tab.first_cmd;
	// while (command != NULL)
	// {
	// 	token = command->first_token;
	// 	while (token != NULL)
	// 	{
	// 		if (token->next != NULL)
	// 			ft_printf("%d ", token->type);
	// 		else
	// 			ft_printf("%d", token->type);
	// 		token = token->next;
	// 	}
	// 	command = command->next_cmd;
	// 	if (command != NULL)
	// 		ft_printf(" | ");
	// }

	ft_putstr_fd("\n", 1);
// End of test

// Signal testing

// Ctrl + c testing
	if(signal(SIGINT, ft_ctrl_c_sig) == SIG_ERR)
		printf("Cannot print sigint\n");

	// Ctrl + \ testing
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_putstr_fd("Cannot print sigquit", 1);

// Execute the commands from the table
	pause();
	ft_exec_input(&tab);
	ft_printf("After signal action - tests if the process is not really interupted.\n");
	return (0);
}
