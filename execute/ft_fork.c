/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:06:20 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/25 11:08:34 by woohyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(int pipe_cnt)
{
	int	i;
	int	status;

	i = -1;
	while (++i <= pipe_cnt)
		wait(&status);
	status = status >> 8;
	g_info.last_exit_num = status;
}

void	child_pro(int pipes[2][2], int pipe_cnt, int i, t_cmd *cmd)
{
	close(pipes[0][0]);
	if (pipe_cnt && i != pipe_cnt)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
		close(pipes[0][1]);
	}
	if (i != 0)
	{
		dup2(pipes[1][0], STDIN_FILENO);
		close(pipes[1][0]);
	}
	if (cmd->rdir)
	{
		if (ft_rdir(cmd->rdir))
			exit (1);
	}
	if (check_builtin(cmd->name))
		is_builtin(cmd);
	else
		ft_exe(cmd, g_info.env_lst);
	exit(0);
}

void	ft_fork(int pipe_cnt, t_cmd *cmd)
{
	int		pipes[2][2];
	int		i;
	pid_t	pid;

	i = -1;
	while (++i <= pipe_cnt)
	{
		if (pipe(pipes[0]) == -1)
			ft_error_exit("pipe error", 1);
		if (!pipe_cnt)
			close(pipes[0][1]);
		ignore_signal();
		pid = fork();
		define_signal();
		if (pid == -1)
			ft_error_exit("fork error", 1);
		if (pid == 0)
			child_pro(pipes, pipe_cnt, i, cmd);
		close(pipes[0][1]);
		if (i > 0)
			close(pipes[1][0]);
		pipes[1][0] = pipes[0][0];
		if (i == pipe_cnt)
			close((pipes[0][0]));
		cmd = cmd->next;
	}
	wait_child(pipe_cnt);
	return ;
}
