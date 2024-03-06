/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/06 16:17:47 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

void	free_program(t_cmd_tab *cmd_tab, char *line, char *prompt)
{
	ft_delete_nodes(cmd_tab);
	free(line);
	free(prompt);
}

void	check_exit(t_cmd_tab *cmd_tab, char *line, char *prompt)
{
	if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{
		free_program(cmd_tab, line, prompt);
		printf("exit\n");
		exit(0);
	}
}

// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out
int	main (void)
{
	char		*line;
	char		*prompt;
	t_cmd_tab	cmd_tab;

	line = NULL;
	while (1)
	{
		prompt = get_prompt();
		printf(BLUE);
		line = readline(prompt);
		printf(RESET);
		if (*line)
			add_history(line);
		check_exit(&cmd_tab, line, prompt);
		parser(&cmd_tab, line);
		print_cmd_tab(&cmd_tab); // just show table
		free_program(&cmd_tab, line, prompt);
	}
	return (0);
}
// int main() {
//     t_command_table cmd_table;
// 	char 	*prompt;
//     char	*input;

//     ft_init_command_table(&cmd_table);
// 	prompt = "minishell> ";
//     while ((input = readline(prompt)) != NULL) {
// 		// Add non-empty lines to history - push the arrow up on you keyboard buddy
//         if (*input)
// 			add_history(input);

//         // Process the input
//         ft_printf("You entered: %s\n", input);
// 		// Test the command_table and push_rotate ops - every input will be in the table
// 		ft_push_rotate_token(&cmd_table, ft_strdup(input));
//         t_node  *node;
//         node = cmd_table.first_node;
//         while (node != NULL)
//         {
//             ft_printf("Content of cmd_table: %s\n", node->token);
//             node = node->next;
//         }
//         free(input);
//     }
// 	ft_delete_nodes(&cmd_table);
//     return 0;
// }
