/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:04:12 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/15 20:35:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "../LIBFT/libft.h"

#define LINE_SPILL 0

// parse_part
t_cmd	*parse_data(char *str);
t_list	*seperate_string(char *str);
void	set_pipe_n(t_list **root);
void	set_env(t_list **root);
// heredoc_part
void	set_here(t_list **pre_parse);
int	read_heredoc_infile(char *limiter);
int	create_temp_file(void);
// heredoc_part end

// merge_string_part
t_list	*merge_string(t_list **root);
t_list	*meta_add(t_list *temp, t_list **return_val);
// merge_string_part end

// meta_parse_part
char	*parse_meta(char *str, t_list **root);
int		is_meta(char c);
void	double_quote_task(char *return_val, t_list **root);
char	*read_string_before_redirection(char *str, t_list **root);
char	*read_string_before_dollar(char *str, t_list **root);
// meta_parse_part end

// redirection_part
void	del_redi_read_here(t_list **merged_lst);
// redirection_part end

// final_parse_part
t_cmd	*ft_lstnew_cmd(char *cmd, char **args);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd	*final_parse(t_list **pre_lst);
// final_parse_part end

// parse_part end

// execute_part
void	organize_execute(t_list **root);
// execute_part end

// error_handle_part
void	minishell_error(char *error_msg);
void	unexpected_token_error(char *token);
void	unexpected_token_newline(void);
void	unexpected_token_end(void);
// error_handle_part end


// !!!temp
// tempend

// gnl
char	*get_next_line(int fd, int trg);
// gnl end

#endif