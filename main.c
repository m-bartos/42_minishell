/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/02 00:13:10 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <readline/readline.h>

int main() {
    t_command_table cmd_table;
	char 	*prompt;
    char	*input;

    ft_init_command_table(&cmd_table);
	prompt = "minishell> ";
    while ((input = readline(prompt)) != NULL) {
		// Add non-empty lines to history - push the arrow up on you keyboard buddy
        if (*input)
			add_history(input);

        // Process the input
        ft_printf("You entered: %s\n", input);
		// Test the command_table and push_rotate ops - every input will be in the table
		ft_push_rotate_token(&cmd_table, ft_strdup(input));
        t_node  *node;
        node = cmd_table.first_node;
        while (node != NULL)
        {
            ft_printf("Content of cmd_table: %s\n", node->token);
            node = node->next;
        }
        free(input);
    }
	ft_delete_nodes(&cmd_table);
    return 0;
}
