SRCS_LIBFT	= ft_strcpy.c 			\
			  ft_strlen.c 			\
			  ft_strncmp.c			\
			  ft_strncpy.c 			\
			  ft_bzero.c			\
			  ft_calloc.c			\
			  ft_memcpy.c			\
			  ft_strjoin.c			\
			  ft_split.c			\

SRCS		= pipex.c				\
			  utils.c				\

SRCS_BONUS	= main_bonus.c			\

OBJS_LIBFT	= $(addprefix srcs/libft/, $(SRCS_LIBFT:.c=.o))

OBJS		= $(addprefix srcs/, $(SRCS:.c=.o))

OBJS_BONUS	= $(addprefix srcs/bonus/, $(SRCS_BONUS:.c=.o))

LIBFT		= libft.a

INC			= -I include/

CC			= cc

AR			= ar rcs

CFLAGS		= -g3 -Wall -Wextra -Werror

RM			= rm -f

NAME		= pipex

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) 

$(LIBFT):	$(OBJS_LIBFT)
	$(AR) $(LIBFT) $(OBJS_LIBFT)

all:		$(NAME)

bonus:		$(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) $(OBJS_LIBFT)

fclean:		clean
	$(RM) $(NAME) $(LIBFT)

re:		fclean all

.PHONY:		all bonus clean fclean re
