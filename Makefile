NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./MLX42/include
MLX_PATH = ./MLX42/build
MLX_LIB = $(MLX_PATH)/libmlx42.a
MLX_FLAGS = -ldl -lglfw -pthread -lm
RM = rm -f

SRCS = main.c \
       src/color.c \
       src/canvas.c \
       src/matrix2.c \
       src/matrix3.c \
       src/matrix4.c \
       src/transformations.c \
       src/simulation.c \
       src/math/tuple.c \
       src/math/arithmetic.c \
       src/math/vector.c
       src/ray.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_LIB) $(MLX_FLAGS)


%.o: %.c miniRT.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
