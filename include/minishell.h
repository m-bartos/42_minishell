/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldokezer <aldokezer@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:24:52 by aldokezer         #+#    #+#             */
/*   Updated: 2024/05/14 19:41:01 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <termios.h>
# include <signal.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define FALSE 0
# define TRUE 1

# define HEREDOC_FILE ".hd_X[Aj0J-]}1038.93'-=;';!@A_cmd_"
# define HOSTNAME_FILE "/proc/sys/kernel/hostname"

# define CMD_NOT_FOUND 127
# define NO_FILE_OR_DIR 127
# define IS_DIRECTORY 126
# define IS_EMPTY 0
# define PERMISSION_DENIED 126

// Global variable for signal handling
extern volatile sig_atomic_t	g_sigint_received;

typedef enum s_in_quotes
{
	STR_ERR = -1,
	OUT_OF_QUOTES,
	IN_DOUBLE_QUOTES,
	IN_SINGLE_QUOTES
}		t_quote;

typedef enum s_type
{
	NOT_ASSIGNED = -1,
	CMD,
	CMD_BUILT,
	CMD_ERR,
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

typedef struct s_token
{
	char			*text;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_cmd
{
	char			**execve_cmd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	t_token			*first_token;
	t_token			*last_token;
	int				size;
}		t_cmd;

typedef struct s_cmd_tab
{
	t_cmd	*first_cmd;
	t_cmd	*last_cmd;
	int		size;
}	t_cmd_tab;

typedef struct s_exec_data
{
	int		fd_in;
	int		fd_out;
	int		ori_fd_in;
	int		ori_fd_out;
	int		pipe_fd[2];
	int		num_children;
	int		num_commands;
	t_cmd	*cmd;
	pid_t	pid;
	pid_t	*child_pids;
}		t_exec_data;

// Enviromental vars structures
// Env node
typedef struct s_env
{
	struct s_env	*next;
	char			*env_text;
	char			*env_name;
	char			*env_value;
}	t_env;

// Env table
typedef struct s_env_list
{
	t_env	*top;
	int		size;
}	t_env_list;

// Minishell state data
typedef struct s_mini_data
{
	t_env_list	*env_list;
	char		**env_arr;
	t_cmd_tab	*cmd_tab;
}	t_minidata;

// libft_extended
char	*ft_itoa_e(int n);
char	**ft_split_e(const char *s, char c);
char	*ft_strdup_e(const char *s1);
char	*ft_strjoin_e(const char *s1, const char *s2);
char	*ft_strtrim_e(char const *s1, char const *set);
char	*ft_substr_e(const char *s1, unsigned int start, size_t len);

// ft_array_utils.c
int		ft_len_of_arr(char **arr);
char	*ft_arr_to_str(char **arr_of_strs);
char	**ft_init_array(int size);
void	ft_free_array(char **arr_of_str);
void	ft_print_array(char **arr);

// cmd_struct_assign_types.c
t_type	assign_file_type(t_type prev_token_type, int *search_file);
t_type	assign_cmd_type(char *text, int *search_cmd);
void	assign_operator_types(t_cmd *cmd);
void	assign_cmd_and_arg_types(t_token *token);
void	assign_types_to_tokens(t_cmd *cmd);

// cmd_struct_filler_utils.c
int		is_pipe_type(t_token *ptr_node);
int		is_redirection_type(t_token *ptr_node);
int		is_operator_type(t_token *ptr_node);

// cmd_struct_filler.c
void	fill_cmd_tab(t_cmd *ptr_cmd_tab, char **tokens_arr);

// cmd_struct_ops
void	ft_init_cmd_struct(t_cmd *cmd);
void	ft_cmdjoin(t_cmd *cmd, t_cmd *cmd_add);
void	ft_append_new_token_to_cmd(t_cmd *cmd, char *text, t_type type);
void	ft_delete_cmd(t_cmd *cmd_table);
void	ft_move_token(t_cmd *cmd, t_token *ptr_token);

// token_struct_ops.c
void	ft_init_token_struct(t_token *token);
t_token	*ft_create_new_token(char *text, t_type type);

// cmd_struct_remove_quotes_utils.c
char	**remove_quotes_encaptulates_words(char **arr_of_str);
char	*get_substr_from_word(char const *str, size_t *i);
int		count_substrs_in_word(char const *word);
char	**parse_token_text(char *word);

// cmd_struct_remove_quotes.c
void	remove_quotes_in_token(t_token *token);
void	remove_quotes_in_cmd_tokens(t_cmd *cmd);

// cmd_tab_struct_utils.c
void	make_cmd_tab_from_cmd(t_cmd_tab *cmd_tab, t_cmd *cmd);
void	delete_empty_tokens_in_cmd_tab(t_cmd_tab *cmd_tab);
void	delete_pipes_in_cmd_tab(t_cmd_tab *cmd_tab);
void	check_and_fill_empty_cmds_in_cmd_tab(t_cmd_tab *cmd_tab);

// cmd_tab_struct_ops.c
void	ft_init_cmd_tab(t_cmd_tab *cmd_tab);
t_cmd	*ft_create_cmd(void);
void	ft_append_new_cmd_to_tab(t_cmd_tab *cmd_tab);
void	ft_delete_token(t_cmd *cmd, t_token *token);
void	ft_delete_cmds_in_cmd_tab(t_cmd_tab *cmd_tab);

// error_check.c
int		check_unclosed_quotes(char *line);
void	redirection_error(t_cmd *cmd, char *text);
int		check_redirection_errors(t_cmd *cmd);
int		line_error(char *line);

// init_free_exit.c
void	init_minishell(t_minidata *minidata, t_cmd_tab *cmd_tab, char **envp);
void	clean_minishell(t_minidata *minidata);
void	exit_minishell(t_minidata *minidata, int exit_status);
void	clean_cmd(t_cmd *cmd, int fd, char *eof);

// expander_var.c
char	*end_of_var(char *str);
char	*get_variable_name(char	*str, size_t *i);
char	*get_expanded_var(char *str, size_t *i, t_env_list *env_list);

// expander.c
char	*expand_one_var_in_str(char *str, size_t *i, t_env_list *env_list);
t_quote	in_which_quotes(char *str, size_t i);
char	*expand_all_vars_in_str(char *str, t_env_list *env_list);
void	expand_cmd(t_cmd *cmd, t_minidata *minidata);

// get_prompt_errors.c
int		is_var_in_env_list(t_env_list *env_list, char *var_name);
int		is_user(void);
int		check_prompt_vars(t_env_list *env_list);

// get_prompt.c
char	*get_hostname(void);
char	*get_user_and_computer(void);
char	*get_relative_path(void);
char	*get_prompt(t_minidata *minidata);

// helpers.c
void	print_execve_cmd(char	**execve_cmd);
void	print_cmd(t_cmd *ptr_cmd_tab);
void	print_cmd_tab(t_cmd_tab *cmd_tab);

// here_doc.c
void	unlink_heredoc_files(t_cmd_tab *cmd_tab);
char	*expand_all_vars_in_heredoc_line(char *str, t_env_list *env_list);
char	*create_heredoc_filename(int i);
void	get_heredoc_file(char *eof, char *filename, t_env_list *env_list);
void	expand_heredocs(t_cmd *cmd, t_minidata *minidata);

// make_cmd_paths.c
char	*get_cmd_path(t_token *token, t_env_list *env_list);
void	expand_token_cmd_path(t_token *token, t_env_list *env_list);
void	make_cmd_paths(t_cmd_tab *cmd_tab, t_minidata *minidata);

// make_execve_cmds.c
int		count_cmd_length(t_cmd *cmd);
void	make_one_execve_cmd(t_cmd *cmd);
void	make_execve_cmds(t_cmd_tab *cmd_tab);

// parser.c
void	handle_if_last_token_is_pipe(t_cmd *cmd, t_minidata *minidata);
int		parse_to_one_cmd(t_cmd *cmd, char **tokens_arr, t_minidata *minidata);
int		parser(t_cmd_tab *cmd_tab, char *line, t_minidata *minidata);

// splitter_handlers.c
char	*handle_redirections(char *str, size_t *index);
char	*handle_pipe(char *str, size_t *index);
char	*handle_word(char *str, size_t *index);

// splitter_utils.c
int		is_whitespace(char c);
int		is_quote(char c);
int		is_operator(char c);
size_t	count_word_length(char *str);

// splitter.c
int		count_tokens(char *line);
char	**init_tokens_arr(char *line);
char	**splitter(char *line);

// EXECUTION //
// exec functions
void	ft_exec_input(t_cmd_tab *cmd_tab, t_minidata *data);
void	ft_exec_commands(t_cmd *cmd, t_minidata *minidata);
void	ft_execve(t_cmd *cmd, t_minidata *minidata);
void	ft_select_built_cmd(t_cmd *cmd, t_env_list env_list);
void	ft_cmd_error(t_cmd *cmd);
void	ft_parent_process(t_exec_data *data, t_minidata *minidata);
void	ft_init_exec_data(t_exec_data *exec_data, t_cmd_tab *tab);
void	ft_exit_status(int *status);

// exit status
void	ft_update_exit_status(int *status, t_minidata *minidata);

// error exec functions
int		ft_is_path_valid(const char *path);
int		ft_is_path(char *token);
void	ft_error(char *cmd_name, char *err_text, int err_code);

// I/O functions
int		ft_input_file(char *file_name);
int		ft_output_file(char *file_name);
int		ft_append_file(char *file_name);

// Redirection functions
void	ft_input_redirection(char *file_name, int *fd_in);
void	ft_output_redirection(char *file_name, int *fd_out);
void	ft_append_redirection(char *file_name, int *fd_out);
void	ft_redirect_io(t_cmd *cmd, int *fd_in, int *fd_out);
void	ft_redir_process_io(t_exec_data *data, t_cmd *cmd);

// Redirection utils
int		ft_has_out_redir(t_cmd *cmd);

// Signals
void	sigint_handler(int sig);
void	setup_signal_handling(void);
void	disable_ctrl_c_output(void);
void	handle_sigint_heredoc(int sig_num);
void	handle_sigint_heredoc_parent(int sig_num);

// Built in cmds;
// utils
char	*ft_find_arg(t_cmd *cmd);
// echo
void	ft_echo(t_cmd *cmd, t_env_list *env_list, int is_child);
int		ft_has_option(t_cmd *cmd);
char	*ft_get_echo_input(t_cmd *cmd);
// exit
void	ft_exit(t_cmd *cmd);
void	ft_exit_minishell(t_cmd *cmd, t_env_list *env_list, t_exec_data *data);
// cd
void	ft_cd(t_cmd *cmd, t_env_list *env_list, int is_child);
// cd helpers
void	ft_too_many_args(t_env_list *env_list, int is_child);
void	ft_cd_valid_path(t_env_list *env_list, int is_child);
void	ft_cd_not_valid_path(t_env_list *env_list, int is_child, char *path);
char	*ft_find_arg(t_cmd *cmd);
void	ft_update_pwd(t_env_list *env_list);
// pwd
void	ft_pwd(t_env_list *env_list, int is_child);
// export
void	ft_export(t_env_list *env_list, t_cmd *cmd, int is_child);
// export helpers
int		ft_is_cmd_valid_export(t_cmd *cmd);
int		ft_is_str_alpha(char *str);
int		ft_is_str_digit(char *str);
int		ft_is_cmd_valid_export(t_cmd *cmd);
int		ft_is_key_valid(char *str);
void	ft_exit_export(t_env_list *env_list, int is_child, int exit_code,
			int is_ident);
// unset
void	ft_unset(t_env_list *env_list, t_cmd *cmd, int is_child);
// env
void	ft_env(t_env_list *env_list, int is_child);

// Environmental functions
void	ft_init_env_list(t_env_list *env_list);
void	ft_init_env(t_env *env);
char	*ft_extract_env_name(char *str);
void	ft_add_env(t_env_list *env_list, char *env);
int		ft_remove_env(t_env_list *env_list, char *var_name);
int		ft_remove_str(t_env_list *env_list, char *str);
void	ft_list_env(t_env_list *env_list);
void	ft_convert_arr_to_list(t_env_list *env_list, char **envp);
char	**ft_convert_list_to_arr(t_env_list *env_list);
char	*ft_get_env(t_env_list *env_list, char *var_name);
void	ft_remove_env_list(t_env_list *env_list);

// Pre-processing
void	ft_pre_exec_select_built_cmd(t_cmd *cmd, t_env_list	*env_list,
			t_exec_data *data);
void	ft_pre_exec_redir_process_io(t_exec_data *data, t_cmd *cmd);
void	ft_redir_original_io(int *ori_in, int *ori_out);
int		ft_pre_exec(t_cmd_tab *tab, t_minidata *minidata);
void	ft_pre_redirect_io(t_cmd *cmd, int *fd_in, int *fd_out);
// Pre-processing utils
int		ft_is_inbuilt(t_cmd *cmd);
int		ft_has_in_redir(t_cmd *cmd);

// Minidata
void	ft_init_minidata(t_minidata *minidata, t_cmd_tab *cmd_tab, char **envp);

#endif
