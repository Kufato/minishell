/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:22:32 by arforgea          #+#    #+#             */
/*   Updated: 2023/06/16 16:24:15 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	########## START ##########

#ifndef MINISHELL_H
# define MINISHELL_H

//	########## INCLUDES ##########

# include "../src/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/time.h>
# include <termios.h>

//	########## GLOBAL ##########

extern int	g_status;

//	########## STRCTURE ##########

typedef struct s_exec
{
	int				fd_in;
	int				fd_out;
	char			*abs_path;
	char			**full_cmd;
	char			*cmd;
	struct s_exec	*next;
	struct s_exec	*back;
}				t_exec;

typedef struct s_data
{
	int		nb_cmd;
	int		flag;
	pid_t	*tab_pid;
	char	*input;
	char	**envp;
	t_exec	*dtt;
}				t_data;

//	########## FONCTIONS ##########

//	builtins

int		ft_pwd(t_exec *dtt);
void	ft_echo(char **tab);
int		check_builtins(char *cmd);
int		ft_env(t_exec *dtt, char **envp);
int		ft_cd(t_data *data, t_exec *dtt);
int		ft_exit(t_data *data, t_exec *dtt);
int		ft_unset(char ***envp, char **tab_cmd);
int		ft_export(char ***envp, char **tab_cmd);
int		check_after_fork(t_data *data, t_exec *dtt);
int		check_before_fork(t_data *data, t_exec *dtt);

void	print_tab(char **arrey);
void	print_tab_sort(char **tab);

int		get_var_size(char *str);
int		get_env_size(char **envp);
int		get_name_var_size(char *var);
int		is_var(char **envp, char *var);

//	execution

int		check_exec(char *str);
void	free_fork(t_data *data);
int		exec_pipeline(t_data *data);
void	close_all(int *fds, int fd);
void	wait_all_pid(t_data *data, int *tab_pid);

//	heredoc

t_exec	*heredoc(t_data *data, t_exec *dtt, char **tab, char *cmd);
t_exec	*heredoc_call(t_data *data, t_exec *dtt, char **tab, char *cmd);
t_exec	*write_heredoc(t_data *data, t_exec *dtt, char **tab, char *word);

//	lst

t_exec	*exec_lst_init(int nb);
t_data	*dtt_init(t_data *data);
void	lst_destroy(t_exec *ptr);
t_data	*dtt_refile(t_data *data);
void	exec_lst_free(t_exec *ptr);

//	parsing

//	input

int		check_syntax(char *str);

int		is_rdir(char c);
char	*get_file(char *str);
int		check_chevrons(char *str);
t_exec	*left_chevrons(t_exec *dtt, char *cmd);
t_exec	*right_chevrons(t_exec *dtt, char *cmd);

char	*add_spaces_rdir(char *str);
void	input_restructure(t_data *data);
char	*remove_spaces_pipes(char *cmd);
char	*remove_extra_spaces(char *cmd);
void	add_no_spaces(char *cmd, char *new_cmd, int *i, int *j);

char	**input_to_tab(char *input);

char	**turbo_split(char *input, char c);

//	refile

char	*get_abs_path(char *cmd, char **envp);

t_exec	*refile_exec(t_data *data, t_exec *dtt, char **tab, char **cmd);

int		check_heredoc(char *str);
int		get_good_nb_word(char **tab_cmd);

//	utils

int		skip_argument(char *c);

//	variables

int		char_is_valid(char c);
int		check_flag(int flag, char c);
int		check_just_dollar(char *str);
char	*replace_variables(t_data *data);
int		check_var_heredoc(char *str, int i);

//	signals

void	signal_exec(void);
void	signals_heredoc(void);
void	signals_disabled(void);
void	mini_sigint(int signal);
void	mini_sigint_fork(int signal);
void	mini_sigquit_fork(int signal);
void	mini_sigint_heredoc(int signal);

//	utils

//	get_everything_nbr

int		get_pipes_number(char *cmd);
int		get_chevrons_number(char *cmd);
int		get_chars_number(char *str, char c);

void	free_tab(char **tab);

int		is_space(char c);
int		is_separator(char c);
int		strlen_word(char *str);
int		str_is_empty(char *str);
char	**ft_tab_dup(char **tab);
char	*get_next_word(char *str);
int		string_is_empty(char *str);
char	*str_without_quotes(char *str);
char	*ft_secur_cat(char *s1, char *s2);

// main

int		main(int argc, char **argv, char **envp);

//	########## END ##########

#endif
