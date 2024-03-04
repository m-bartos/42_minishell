/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:53:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/04 14:53:25 by mbartos          ###   ########.fr       */
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
// echo "jojo" 'nene' > outfile.txt | < infile.txt echo "jojo" 'nene' aha "$USER" '$USER' $USER >> test.out
// int	main (void)
// {
// 	char			*line;
// 	t_command_table	cmd_tab;

// 	line = readline("Write command: ");
// 	printf("What I got:    %s\n", line);
// 	parser(&cmd_tab, line);
// 	print_cmd_tab(&cmd_tab);
// 	return (0);
// }

