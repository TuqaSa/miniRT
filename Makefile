NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./MLX42/include
MLX_PATH = ./MLX42/build
MLX_LIB = $(MLX_PATH)/libmlx42.a
MLX_FLAGS = -ldl -lglfw -pthread -lm
RM = rm -f

SRCS = main.c \
       color.c \
       src/canvas.c \
       src/matrix2.c \
       src/matrix3.c \
       src/matrix4.c \
       src/transformations.c \
       src/simulation.c \
       src/math/tuple.c \
       src/math/arithmetic.c \
       src/math/vector.c

CANVAS_TEST_SRCS = canvas_test.c \
                   color.c \
                   src/canvas.c \
                   src/math/tuple.c \
                   src/math/arithmetic.c

MATRIX_TEST_SRCS = matrix_test.c \
                   src/matrix2.c \
                   src/matrix3.c \
                   src/matrix4.c \
                   src/transformations.c \
                   src/math/tuple.c \
                   src/math/arithmetic.c

OBJS = $(SRCS:.c=.o)
CANVAS_TEST_OBJS = $(CANVAS_TEST_SRCS:.c=.o)
MATRIX_TEST_OBJS = $(MATRIX_TEST_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_LIB) $(MLX_FLAGS)

canvas_test: $(CANVAS_TEST_OBJS)
	$(CC) $(CFLAGS) -o canvas_test $(CANVAS_TEST_OBJS) $(MLX_LIB) $(MLX_FLAGS)

matrix_test: $(MATRIX_TEST_OBJS)
	$(CC) $(CFLAGS) -o matrix_test $(MATRIX_TEST_OBJS)

%.o: %.c miniRT.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(CANVAS_TEST_OBJS) $(MATRIX_TEST_OBJS)

fclean: clean
	$(RM) $(NAME) canvas_test matrix_test

re: fclean all

.PHONY: all clean fclean re canvas_test matrix_test
