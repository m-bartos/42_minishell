/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:53:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/03/08 16:14:34 by mbartos          ###   ########.fr       */
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
// 	t_cmd	cmd_tab;

// 	line = readline("Write command: ");
// 	printf("What I got:    %s\n", line);
// 	parser(&cmd_tab, line);
// 	print_cmd_tab(&cmd_tab);

// 	//THIS IS JUST TEST - needs to be rewritten!!
// 	char	*user;
// 	char	*session_manager;
// 	char	*old_session_manager;
// 	char	*computer;
// 	char	*display_line;
// 	char	*old_display_line;

// 	user = getenv("USER");
// 	session_manager = getenv("SESSION_MANAGER");
// 	session_manager = ft_strdup(session_manager);
// 	old_session_manager = session_manager;
// 	session_manager = ft_strchr(session_manager, '/') + 1;
// 	session_manager[6] = '\0';
// 	computer = ft_strdup(session_manager);
// 	free(old_session_manager);
// 	display_line = ft_strjoin(user, "@");
// 	old_display_line = display_line;
// 	display_line = ft_strjoin(display_line, computer);
// 	free(old_display_line);
// 	free(computer);
// 	old_display_line = display_line;
// 	display_line = ft_strjoin(display_line, ":~");
// 	old_display_line = display_line;
// 	display_line = ft_strjoin(display_line, getenv("PWD")); // PWD needs to be cut
// 	free(old_display_line);
// 	printf("%s", display_line);
// 	printf("\n");
// 	free(display_line);
// 	//THIS IS JUST TEST - needs to be rewritten!!

// 	return (0); 
// }

