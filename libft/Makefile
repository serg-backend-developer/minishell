NAME 			=	libft.a
CC 				=	cc
CC_FLAGS 		=	-Wall -Wextra -Werror
RM 				=	rm -rf
AR 				=	ar rcs

SRCS            =   $(wildcard *.c)
OBJS            =   $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $?

%.o: %.c
	@$(CC) -c $(CC_FLAGS) $?

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re