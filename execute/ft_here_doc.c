#include "../minishell.h"

// char *here_doc_end_point(t_cmd *cmd)
// {
// 	t_rdir *rdir;
// 	char	*end_point;
	
// 	rdir = cmd->rdir;
// 	while (rdir)
// 	{
// 		if (rdir->type == HEREDOC)
// 			break ;
// 		rdir = rdir->next;
// 	}
// 	if (!rdir)
// 		exit(1);
// 	end_point = ft_strdup(rdir->with);
// 	return (end_point);
// }

// void make_here_doc(t_cmd *cmd)
// {
// 	pid_t pid;
// 	int fd[2];
// 	char *buff;
// 	char *end_point;

// 	end_point = here_doc_end_point(cmd);
// 	if (!pipe(fd) || !end_point)
// 		exit(1);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		while (1)
// 		{
// 			buff = readline(">");
// 			if (!strcmp(buff, end_point))
// 				break ;
// 			while(buff++)
// 				write(fd[1], buff, 1);
// 			write(fd[1], "\n", 1);
// 		}
// 	}
// 	return ();
// }


// char *here_doc_end_point(t_cmd *cmd)
// {
// 	t_rdir *rdir;
// 	char	*end_point;
	
// 	rdir = cmd->rdir;
// 	while (rdir)
// 	{
// 		if (rdir->type == HEREDOC)
// 			break ;
// 		rdir = rdir->next;
// 	}
// 	if (!rdir)
// 		exit(1);
// 	end_point = ft_strdup(rdir->with);
// 	return (end_point);
// }

void make_here_doc(t_rdir *rdir)
{
	pid_t pid;
	int fd[2];
	char *buff;
	char *temp;

	if (pipe(fd) == -1 || !rdir->with)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			buff = readline("> ");
			if (ft_strcmp(buff, rdir->with) == 0)
            {
                write(fd[1], "\0", 1);
				break ;
            }
			write(fd[1], buff, ft_strlen(buff));
			write(fd[1], "\n", 1);
			free(buff);
		}
		free(buff);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	wait(0);
	rdir->here_doc_fd = fd[0];
}

void ft_heredoc(t_cmd *cmd)
{
	t_rdir *tmp;

	tmp = cmd->rdir;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			make_here_doc(tmp);
		tmp = tmp->next;
	}
}

void	check_heredoc(t_cmd	*cmd)
{
	int		heredoc_cnt;

    if (!cmd)
        return ;
	while (cmd) {
		if (cmd->is_heredoc)
			ft_heredoc(cmd);
		cmd = cmd->next;
	}
	return  ;
}