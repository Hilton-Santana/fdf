NAME = fdf

CC = gcc

ECHO = @printf

CFLAGS = -Wall -Wextra -Werror

SRC_PATH = src

OBJ_PATH = obj

SRC_NAME = cam.c colors.c errors.c main.c parser_map.c raster.c render.c transformations.c

OBJ_NAME = $(SRC_NAME:.c=.o)

RM = rm -rf

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFLAGS = -lmlx -lm -lft

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	LIBFX_FD = ./minilibx_macos
	LIBFLAGS += -framework OpenGl -framework AppKit
else
	LIBFX_FD = ./mlx
	LIBFLAGS += -lXext -lX11
endif

LIBS = ./libft/libft.a $(LIBFX_FD)/libmlx.a

LDFLAGS = -L ./libft -L $(LIBFX_FD)

INFLAGS = -I ./ -I $(LIBFX_FD) -I ./libft

all: $(NAME)

libft/libft.a :
	$(ECHO) "$(RED) Making libft ...$(EOC)\n"
	make all -C ./libft

$(LIBFX_FD)/libmlx.a :
	$(ECHO) "$(RED) Making libX ...$(EOC)\n"
	make all -C $(LIBFX_FD)

$(NAME) : $(LIBS) $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LIBFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH) 2> /dev/null
	$(CC) $(CFLAGS) $(INFLAGS) -o $@ -c $<

clean :
	make clean -C ./minilibx_macos
	make fclean -C ./libft
	$(RM) $(OBJ_PATH)

fclean : clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean re fclean

RED = \033[1;31m
GRN = \033[1;32m
EOC = \033[0m

