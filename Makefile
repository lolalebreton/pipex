SRCS_LIBFT	= ft_isdigit.c			\
			  ft_atoi.c				\
			  ft_strcmp.c			\
			  ft_min.c				\
			  ft_itoa.c				\
			  ft_memset.c 			\
			  ft_strchr.c 			\
			  ft_strcpy.c 			\
			  ft_strlen.c 			\
			  ft_strncpy.c 			\
			  ft_toupper.c			\
			  ft_strtoupper.c		\
			  ft_uitoa.c			\
			  ft_memalloc.c			\
			  ft_bzero.c			\
			  ft_calloc.c			\
			  ft_strncat.c			\
			  ft_memcpy.c			\
			  ft_strjoin.c			\
			  get_next_line.c		\

SRCS_PRINTF	= ft_printf.c			\
			  parse.c				\
			  print.c				\
			  util.c				\
			  mode.c				\
			  flags.c				\
			  padding.c				\
			  convert.c				\
			  sort.c				\

SRCS		= main.c				\
			  pipex.c				\
			  

SRCS_BONUS	= main_bonus.c			\

OBJS_LIBFT	= $(addprefix srcs/libft/, $(SRCS_LIBFT:.c=.o))

OBJS_PRINTF	= $(addprefix srcs/printf/, $(SRCS_PRINTF:.c=.o))

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

$(LIBFT):	$(OBJS_LIBFT) $(OBJS_PRINTF)
	$(AR) $(LIBFT) $(OBJS_LIBFT) $(OBJS_PRINTF)

all:		$(NAME)

bonus:		$(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) $(OBJS_LIBFT) $(OBJS_PRINTF)

fclean:		clean
	$(RM) $(NAME) $(LIBFT)

re:		fclean all

.PHONY:		all bonus clean fclean re
