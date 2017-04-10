NAME  = libtp.a

CC   := gcc
CF   += -Wall -Wextra -Werror
CF   += -I include

SRC  := _kill_thread.c _work_loop.c _zalloc.c
SRC  += create.c exec_queue_add.c wait_for_queue.c
SRC  += get_nbr_proc.c
SRC  += evfire.c evwait.c lock.c unlock.c ncpu.c
SRC  += qpop.c qpush.c qwait.c
OBJ  := $(addprefix build/,$(SRC:.c=.o))
SRC  := $(addprefix src/,$(SRC))

# ------------------------------------------------------------------------------

all: $(NAME)

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)

re: fclean all

# ------------------------------------------------------------------------------

$(NAME): $(OBJ)
	libtool -static -o $@ $^

build/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CF) -c -o $@ $<
