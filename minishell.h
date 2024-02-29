/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:24:52 by aldokezer         #+#    #+#             */
/*   Updated: 2024/02/29 10:14:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "unistd.h"
# include "./libft/libft.h"
// rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
# include <readline/readline.h>
// adds rl_clear_history()
# include <readline/history.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define FALSE 0
# define TRUE 1

typedef enum s_tokens
{
	COMAND,
	ARGUMENT,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_OUT_APPEND,
	HERE_DOC
}		t_tokens;

typedef struct s_node
{
	char		*text;
	t_tokens	token;
	t_node		*next;
}		t_node;

// is it necessary to have s_tabulcicka struct?
typedef struct s_tabulcicka
{
	t_node	*first_node;
}		t_tabulcicka

#endif