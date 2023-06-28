CC = cc 
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx  -framework OpenGL -framework AppKit
SRCS = mandatory/main.c mandatory/parse.c mandatory/parse2.c mandatory/valid_path.c mandatory/graphic.c mandatory/graphic2.c 
BSRCS = bonus/main_bonus.c bonus/parse_bonus.c bonus/parse2_bonus.c  bonus/valid_path_bonus.c bonus/graphic_bonus.c bonus/graphic2_bonus.c bonus/graphic3_bonus.c
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)
LIBFT = libft/libft.a
LIB_DIR = libft
HEADERS = incudes/libft.h incudes/so_long.h includes/so_long_bonus.h
NAME = so_long
NAME2 = so_long_bonus

all : $(NAME)
$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJS) $(LIBFT) -o $@
$(LIBFT) :
	make -C $(LIB_DIR)
%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<
bonus : $(NAME2)
$(NAME2) : $(LIBFT) $(BOBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(MLX_FLAGS) $(BOBJS) -o $(NAME2)
clean :
	make -C $(LIB_DIR) clean
	rm -f $(OBJS)
	rm -f $(BOBJS)
fclean : clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)
	rm -f $(NAME2)
re : fclean all
