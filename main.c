/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/19 12:16:37 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"


// valgrind -s --leak-check=full --show-reachable=yes --error-limit=no --suppressions=minishell.supp --trace-children=yes --track-fds=yes ./minishell
// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out
int	main (int argc, char *argv[], char *envp[])
{
	char		*prompt;
	char		*line;
	t_cmd_tab	cmd_tab;
	t_mini_data	minidata;

	line = NULL;
	ft_init_cmd_tab(&cmd_tab);
	ft_init_mini_data(&minidata, envp);
	printf(BLUE);
	while (1)
	{
		prompt = get_prompt(&minidata);
		line = readline(prompt);
		free(prompt);
		// if(signal(SIGINT, ft_ctrl_c_sig) == SIG_ERR)
		// {
			// free(line);
			// continue ;
		// }
		if (is_empty_line(line))
			continue ;
		check_exit(line);
		if (*line)
			add_history(line);
		check_unclosed_quotes(line);
		parser(&cmd_tab, line, &minidata);
		print_cmd_tab(&cmd_tab); // just to show cmd_tab
		ft_exec_input(&cmd_tab, &minidata);
		unlink_heredoc_files(&cmd_tab);
		ft_delete_cmds_in_cmd_tab(&cmd_tab);
		// free minidata
	}
	return (0);
}



/*
int	main(int argc, char *argv[], char *envp[])
{

//ENV Vars
	t_mini_data	 minidata;

	ft_init_mini_data(&minidata, envp);


	// ft_printf("Size of ENV list is: %d\n", minidata.env_list->size);
	// ft_list_env(minidata.env_list);
	// ft_printf("End -------------------End\n");
	ft_add_env(minidata.env_list, "?=10");
	ft_add_env(minidata.env_list, "?=11");
	ft_add_env(minidata.env_list, "?=12");
	ft_add_env(minidata.env_list, "?=13");
	ft_add_env(minidata.env_list, "?=20");
	// ft_list_env(minidata.env_list);
	// ft_printf("End -------------------End\n");
	// ft_remove_env(minidata.env_list, "?");
	// ft_add_env(minidata.env_list, "?=0");
	// ft_list_env(minidata.env_list);
	// ft_printf("End -------------------End\n");
	// ft_printf("%s\n", ft_get_env(minidata.env_list, "USER"));
	// ft_printf("End -------------------End\n");
	// //ft_remove_env(&env_list, "?");
	// //ft_remove_env(&env_list, "?");
	// ft_list_env(minidata.env_list);
	// ft_printf("Size of ENV list is: %d\n", minidata.env_list->size);
	// ft_printf("End -------------------End\n");
	// while(*minidata.env_arr != NULL)
	// {
	// 	ft_printf("%s\n", *minidata.env_arr);
	// 	minidata.env_arr++;
	// }
	// ft_printf("End -------------------End\n");


// Elements declaration
	t_cmd	cmd1;
	t_cmd	cmd2;
	t_cmd	cmd3;
	t_cmd	cmd4;
	t_cmd	cmd5;
	t_cmd	cmd6;

	t_cmd_tab	tab;

	ft_init_cmd(&cmd1);
	ft_init_cmd(&cmd2);
	ft_init_cmd(&cmd3);
	ft_init_cmd(&cmd4);
	ft_init_cmd(&cmd5);
	ft_init_cmd(&cmd6);
	ft_init_cmd_table(&tab);

// ENV
	char *exe_cmd6[] = {"env"};
	ft_append_token_to_cmd(&cmd6, "env", CMD_BUILT);
	cmd6.execve_cmd = exe_cmd6;
// PWD
	char *exe_cmd5[] = {"pwd"};
	ft_append_token_to_cmd(&cmd5, "pwd", CMD_BUILT);
	cmd5.execve_cmd = exe_cmd5;

// CD
	char *exe_cmd4[] = {"cd", ".."};
	ft_append_token_to_cmd(&cmd4, "cd", CMD_BUILT);
	ft_append_token_to_cmd(&cmd4, ".", ARG);
	cmd4.execve_cmd = exe_cmd4;

// ECHO
	char *exe_cmd3[] = {"echo", "lorem ipsum command"};
	ft_append_token_to_cmd(&cmd3, "echo", CMD_BUILT);
	ft_append_token_to_cmd(&cmd3, "lorem ipsum command", ARG);
	ft_append_token_to_cmd(&cmd3, "-n", ARG);
	cmd3.execve_cmd = exe_cmd3;

// CAT
	char *exec_cmd1[] = {"/bin/cat", NULL};
	ft_append_token_to_cmd(&cmd1, "<", R_IN);
	ft_append_token_to_cmd(&cmd1, "infile.txt", R_INFILE);
	ft_append_token_to_cmd(&cmd1, "cat", CMD);
	cmd1.execve_cmd = exec_cmd1;

// WC
	char *exec_cmd2[] = {"/usr/bin/wc", "-lcw", NULL};
	ft_append_token_to_cmd(&cmd2, "wc", CMD);
	ft_append_token_to_cmd(&cmd2, "-lcw", ARG);
	ft_append_token_to_cmd(&cmd2,">>", R_OUT_APP);
	ft_append_token_to_cmd(&cmd2, "output.txt", R_OUTFILE_APP);
	cmd2.execve_cmd = exec_cmd2;


// Add comands to the table
	//ft_append_cmd_to_tab(&tab, &cmd4);
	//ft_append_cmd_to_tab(&tab, &cmd5);
	//ft_append_cmd_to_tab(&tab, &cmd3);
	ft_append_cmd_to_tab(&tab, &cmd1);
	ft_append_cmd_to_tab(&tab, &cmd2);
	ft_append_cmd_to_tab(&tab, &cmd6);

// Printing commands and types
	print_cmd_tab(&tab);
	//ft_print_cmd_types(&tab);
// Signal testing

//Ctrl + c testing
	// if(signal(SIGINT, ft_ctrl_c_sig) == SIG_ERR)
	// 	printf("Cannot print sigint\n");

	// // Ctrl + \ testing
	// if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	// 	ft_putstr_fd("Cannot print sigquit", 1);

// Execute the commands from the table
	//pause();
	ft_cd(&cmd4, 0);
	ft_pwd(0);
	ft_exec_input(&tab, &minidata);
	ft_printf("%s\n", ft_get_env(minidata.env_list, "?"));
	ft_pwd(0);
	ft_printf("After signal action - tests if the process is not really interupted.\n");
	ft_list_env(minidata.env_list);
	return (0);
}

*/