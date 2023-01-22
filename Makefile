# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 12:25:30 by him               #+#    #+#              #
#    Updated: 2023/01/10 13:42:45 by woohyeong        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
#CFLAGS = -Wall -Wextra -Werror
CFLAGS =
INCLUDES = -I./includes
#SRCS = $(addprefix ./mandatory/, ${SRCS_FILES})
SRCS = ${SRCS_FILES}
SRCS_FILES = parse/parse.c \
			 parse/chunks.c \
             parse/tokens.c \
             parse/cmds.c \
             parse/utils.c \
             parse/utils2.c \
             parse/replace.c \
             main.c \
             execute/builtin.c \
             execute/execute.c \
             execute/ft_cd.c \
             execute/ft_echo.c \
             execute/ft_env.c \
             execute/ft_exe.c \
             execute/ft_exit.c \
             execute/ft_export.c \
             execute/ft_fork.c \
             execute/ft_here_doc.c \
             execute/ft_pipe.c \
             execute/ft_unset.c \
             execute/ft_rdir.c \
             execute/ft_pwd.c \
             util/find_env.c \
             util/find_env_add.c \
             util/ft_strcmp.c \
             util/ft_strjoin2.c
OBJS = $(SRCS:.c=.o)
NAME = minishell
TOTAL_OBJS = $(OBJS)
LIBFT = -Llibft -lft
READLINE = -L/opt/homebrew/opt/readline/lib -lreadline -I/opt/homebrew/opt/readline/include
all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

$(NAME) : $(TOTAL_OBJS)
	make re -C ./libft
	$(CC) $(CFLAGS) $(TOTAL_OBJS) $(INCLUDES) $(READLINE) $(LIBFT) -o ${NAME}

clean :
	make fclean -C ./libft
	rm -rf $(OBJS)

fclean : clean
	make fclean -C ./libft
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re%