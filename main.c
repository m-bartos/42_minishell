/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:09:57 by aldokezer         #+#    #+#             */
/*   Updated: 2023/12/02 21:32:08 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <readline/readline.h>

int main() {
	char 	*prompt;
    char*	input;

	prompt = "minishell> ";
    while ((input = readline(prompt)) != NULL) {
		// Add non-empty lines to history - push the arrow up on you keyboard buddy
        if (*input)
			add_history(input);

        // Process the input
        ft_printf("You entered: %s\n", input);
        free(input);
    }

    return 0;
}
