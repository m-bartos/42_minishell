/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:36:32 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/16 14:52:41 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_command	cmd4;
	t_command	cmd5;

	t_cmd_tab	tab;

	ft_init_cmd(&cmd1);
	ft_init_cmd(&cmd2);
	ft_init_cmd(&cmd3);
	ft_init_cmd(&cmd4);
	ft_init_cmd(&cmd5);
	ft_init_cmd_table(&tab);

// Fifth command
	char *exe_cmd5[] = {"pwd"};
	ft_append_token_to_cmd_v2(&cmd5, "pwd", CMD_BUILT);
	cmd5.execve_cmd = exe_cmd5;

// Forth command
	char *exe_cmd4[] = {"cd", ".."};
	ft_append_token_to_cmd_v2(&cmd4, "cd", CMD_BUILT);
	ft_append_token_to_cmd_v2(&cmd4, "./utils", ARG);
	cmd4.execve_cmd = exe_cmd4;

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
	ft_append_cmd_to_tab(&tab, &cmd4);
	//ft_append_cmd_to_tab(&tab, &cmd5);
	// ft_append_cmd_to_tab(&tab, &cmd3);
	// ft_append_cmd_to_tab(&tab, &cmd1);
	// ft_append_cmd_to_tab(&tab, &cmd2);

// Printing commands and types
	ft_print_cmd(&tab);
	ft_print_cmd_types(&tab);
// Signal testing

// Ctrl + c testing
	// if(signal(SIGINT, ft_ctrl_c_sig) == SIG_ERR)
	// 	printf("Cannot print sigint\n");

	// // Ctrl + \ testing
	// if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	// 	ft_putstr_fd("Cannot print sigquit", 1);

// Execute the commands from the table
	//pause();
	//ft_cd_no_exit(tab.first_cmd);
	//ft_pwd_no_exit();
	ft_exec_input(&tab);
	ft_pwd_no_exit();
	//ft_printf("After signal action - tests if the process is not really interupted.\n");
	return (0);
}
