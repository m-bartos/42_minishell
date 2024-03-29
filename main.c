/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/29 10:42:19 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"


// valgrind -s --leak-check=full --show-reachable=yes --error-limit=no --suppressions=minishell.supp --trace-children=yes --track-fds=yes ./minishell
// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out


// Todo
// Implement:

//1) Preexec to update exit status
//2) Preexec to work with infile and outfile (fd0 and fd01) - done
//3) Preexec to properly clean and prepare for a new input

volatile sig_atomic_t sigint_received = 0; // Declaration of the flag

void sigint_handler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line(); // Move to a new line
	rl_replace_line("", 0); // Clear the current buffer
	// rl_redisplay(); // Redisplay the prompt on a new line
	sigint_received = 1; // Signal handler sets the flag
}

void setup_signal_handling() {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // Ensure certain interrupted system calls are automatically restarted
    sigaction(SIGINT, &sa, NULL);
}

void disable_ctrl_c_output() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main (int argc, char *argv[], char *envp[])
{
	char		*prompt;
	char		*line;
	t_cmd_tab	cmd_tab;
	t_mini_data	minidata;

	// Disable ^C
	disable_ctrl_c_output();
    // Setup the SIGINT handler
    setup_signal_handling();


	line = NULL;
	ft_init_cmd_tab(&cmd_tab);
	ft_init_mini_data(&minidata, &cmd_tab, envp);
	exit_minishell(&minidata, 0);
	clean_minishell(&minidata);
	// Get PID to see process information
	// ft_printf("%d\n", getpid());
	while (1)
	{
		// ft_putstr_fd(BLUE, 1);
		// ft_putstr_fd(BLUE, 2);
		if (sigint_received)
		{
			sigint_received = 0; // Reset the flag
		}
		prompt = get_prompt(&minidata);
		line = readline(prompt);
		free(prompt);
		if (is_empty_line(line))
			continue ;
		// check_exit(line);
		if (*line)
			add_history(line);
		if (check_unclosed_quotes(line))
			continue ;
		if (parser(&cmd_tab, line, &minidata) == -1)
			continue ;
		// print_cmd_tab(&cmd_tab); // just to show cmd_tab
		if (ft_pre_exec(&cmd_tab, &minidata))
		{
			clean_minishell(NULL);
			continue ;
		}
		ft_exec_input(&cmd_tab, &minidata);
		clean_minishell(NULL);
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
