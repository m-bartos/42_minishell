/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/08 16:15:19 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./minishell.h"

void	free_program(t_cmd *cmd_tab, char *line, char *prompt)
{
	ft_delete_nodes(cmd_tab);
	free(line);
	free(prompt);
	printf(RESET);
}

void	check_exit(t_cmd *cmd_tab, char *line, char *prompt)
{
	if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{
		free_program(cmd_tab, line, prompt);
		printf("exit\n");
		exit(0);
	}
}

void	handle_if_last_is_pipe(t_cmd *cmd_tab)
{
	char	*line;

	while (is_pipe_type(cmd_tab->last_token))
	{
		line = readline("> ");
		parser(cmd_tab, line);
		free(line);
	}
}

void	check_unclosed_quotes(t_cmd *cmd_tab, char *line, char *prompt)
{
	if (is_unclosed_quotes(line) == 1)
	{
		printf("Minishell cannot handle open quotes (\", \').\n");
		free_program(cmd_tab, line, prompt);
		exit(0);
	}
}

// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out
int	main (void)
{
	char		*line;
	char		*prompt;
	t_cmd	cmd_tab;

	line = NULL;
	ft_init_command_table(&cmd_tab);
	while (1)
	{
		printf(BLUE);
		prompt = get_prompt();
		line = readline(prompt);
		if (*line)
			add_history(line);
		check_exit(&cmd_tab, line, prompt);
		check_unclosed_quotes(&cmd_tab, line, prompt);
		parser(&cmd_tab, line);
		check_double_redirect(&cmd_tab, line, prompt);
		handle_if_last_is_pipe(&cmd_tab);
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
//         t_token  *node;
//         node = cmd_table.first_token;
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
