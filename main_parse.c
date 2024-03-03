/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:53:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/03 12:35:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ------- TEST MAIN FOR SPLITTER FUNCTION ------- 

// cc splitter.c splitter_handlers.c splitter_utils.c ../libft/ft_putnbr_fd.c ../libft/ft_putchar_fd.c -Wall -Wextra -Werror -L/opt/homebrew/opt/readline/lib -lreadline
// int	main(void)
// {
// 	char	*line;
// 	char	**array_of_words;
// 	// char line[] = "a | b";

// 	line = readline("Write command: ");
// 	printf("What I got:    %s\n", line);
// 	array_of_words = splitter(line);
// 	// testing:
// 	int	j;
// 	printf("-----------------------------------\n");
// 	printf("----EACH WORD ON SEPERATED LINE----\n");
// 	printf("-----------------------------------\n");
// 	j = 0;
// 	while (array_of_words[j] != NULL)
// 	{
// 		printf("%s", array_of_words[j]);
// 		printf("\n");
// 		j++;
// 	}
// 	printf("-----------------------------------\n");
// 	printf("-----------------END---------------\n");
// 	printf("-----------------------------------\n");
// 	j = 0;
// 	while (array_of_words[j] != NULL)
// 	{
// 		free(array_of_words[j]);
// 		j++;
// 	}
// 	free(array_of_words[j]);
// 	free(array_of_words);
// 	free(line);
// 	// char	*args[] = {"/bin/echo", "\\n", NULL};
// 	// execve(args[0], args, NULL);
// 	return (0);
// }


// ------- TEST MAIN FOR EXPANDER FUNCTION ------- 
// cc expander.c ../libft/ft_strchr.c ../libft/ft_strlen.c ../libft/ft_strdup.c
// int	main (void)
// {
// 	// char	str[] = "a/$PATaH:a";
// 	char	*str_dynamic;

// 	str_dynamic = readline("TEST: ");
// 	printf("INPUT:\n%s\n\n", str_dynamic);
// 	str_dynamic = expand_all_vars_in_str(str_dynamic);
// 	printf("OUTPUT:\n%s\n", str_dynamic);
// 	free(str_dynamic);
// }

// ---- FILLING THE STRUCT------ 

// int	main (void)
// {
// 	char			*line;
// 	char			**array_of_tokens;
// 	t_command_table	cmd_tab;
// 	t_command_table	*ptr_cmd_tab;

// 	ptr_cmd_tab = &cmd_tab;

// 	line = readline("Write command: ");
// 	printf("What I got:    %s\n", line);

// 	// line = ft_strdup("< << < > >> > | aha 'jojo$PATH><' \"$USER\" $USER$PAPERSIZE");
// 	array_of_tokens = splitter(line);
// 	printf("INITIAL FILLING OF CMD TABLE: \n");
// 	init_and_fill_cmd_tab(ptr_cmd_tab, array_of_tokens);
// 	print_cmd_tab(ptr_cmd_tab);
// 	printf("TYPES ASSIGNED IN CMD TABLE: \n");
// 	assign_types_to_tokens(ptr_cmd_tab);
// 	print_cmd_tab(ptr_cmd_tab);
// 	printf("CMD TABLE EXPANDED: \n");
// 	expand_cmd_table(ptr_cmd_tab);
// 	print_cmd_tab(ptr_cmd_tab);
// 	return (0);
// }

