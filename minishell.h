/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:24:52 by aldokezer         #+#    #+#             */
/*   Updated: 2024/03/16 17:49:43 by aldokezer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define FALSE 0
# define TRUE 1

# define CMD_NOT_FOUND 127

// new types to categorize tokens
typedef enum s_type
{
	CMD,
	CMD_ERR,
	CMD_BUILT,
	ARG,
	PIPE,
	R_IN,
	R_INFILE,
	R_OUT,
	R_OUTFILE,
	R_OUT_APP,
	R_OUTFILE_APP,
	HERE_DOC,
	HERE_DOC_EOF
}		t_type;

// new struct to hold parsed token and commands
typedef struct s_token
{
	char			*text;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_command
{
	char				**execve_cmd;
	struct s_command	*next_cmd;
	struct s_command	*prev_cmd;
	t_token				*first_token;
	t_token				*last_token;
	int					size;
}		t_command;

typedef struct s_cmd_tab
{
	t_command	*first_cmd;
	t_command	*last_cmd;
	int			size;
}		t_cmd_tab;

typedef struct s_exec_data
{
	int	exit_status;
	int	fd_in;
	int	fd_out;
	int	pipe_fd[2];
}		t_exec_data;

// Enviromental vars structures
// Env node
typedef struct s_env
{
	struct s_env	*next;
	char			*value;
}	t_env;
// Env table
typedef struct s_env_list
{
	t_env	*top;
	int		size;
}	t_env_list;

// exec functions
void	ft_exec_input(t_cmd_tab *cmd_tab);

// I/O functions
int		ft_input_file(char *file_name);
int		ft_output_file(char *file_name);
int		ft_append_file(char *file_name);

// Redirection functions
void	ft_input_redirection(char *file_name, int *fd_in);
void	ft_output_redirection(char *file_name, int *fd_out);
void	ft_append_redirection(char *file_name, int *fd_out);

// Redirection utils
int	ft_has_out_redir(t_command *cmd);

// NEW command table ops
void	ft_init_token(t_token *token);
void	ft_init_cmd(t_command *cmd);
void	ft_init_cmd_table(t_cmd_tab *cmd_tab);
void	ft_push_cmd_to_tab(t_cmd_tab *cmd_table, t_command *cmd);
void	ft_append_cmd_to_tab(t_cmd_tab *cmd_table, t_command *cmd);
void	ft_append_token_to_cmd(t_command *cmd, t_token *token);
void	ft_append_token_to_cmd_v2(t_command *cmd, char *text, t_type type);
t_token	*ft_create_token(char *text, t_type type);

// Signals
void	ft_ctrl_c_sig(int signal);
void	ft_ctrl_slash_sig (int signal);

// Built in cmds;
// utils
char	*ft_find_arg(t_command *cmd);
// echo
void	ft_echo(t_command *cmd);
int		ft_is_option(t_command *cmd);
char	*ft_get_echo_input(t_command *cmd);
// exit
void	ft_exit(t_command *cmd);
// cd
void	ft_cd(t_command *cmd);
void	ft_cd_no_exit(t_command *cmd);
// pwd
void	ft_pwd(void);
void	ft_pwd_no_exit(void);

// Environmental functions
void	ft_init_env_list(t_env_list *env_list);
void	ft_init_env(t_env *env);
void	ft_add_env(t_env_list *env_list, char *env);
int		ft_remove_env(t_env_list *env_list, char *var_name);
int		ft_remove_str(t_env_list *env_list, char *str);
void	ft_list_env(t_env_list *env_list);
void	ft_convert_arr_to_list(t_env_list *env_list, char **envp);
char	**ft_convert_list_to_arr(t_env_list *env_list);
char	*ft_get_env(t_env_list *env_list, char *var_name);

// Helpers to print cmds
void	ft_print_cmd(t_cmd_tab *cmd_tab);
void	ft_print_cmd_types(t_cmd_tab *cmd_tab);
#endif
