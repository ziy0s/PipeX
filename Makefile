CC=cc

CFLAGS= -Wextra -Wall -Werror

NAME = pipex

BNAME = .bonus

MDR = MDR/ft_strncmp.c MDR/ft_split.c MDR/main.c MDR/lib_utils.c\
		MDR/ft_allocte.c MDR/pipex_utils.c MDR/ft_putstr_fd.c

BNS = BNS/execution_bonus.c BNS/ft_split_bonus.c BNS/ft_strchr_bonus.c BNS/ft_strdup_bonus.c \
		BNS/ft_strjoin_bonus.c	BNS/get_next_line_bonus.c BNS/pipex_bonus.c BNS/put_message_bonus.c \
		BNS/ft_allocate_bonus.c

M_OBJ= $(MDR:%.c=%.o)

B_OBJ= $(BNS:%.c=%.o)

all: $(NAME)

$(NAME): $(M_OBJ)
	$(CC) $(CFLAGS) $(M_OBJ) -o $(NAME)

MDR/%.o: MDR/%.c MDR/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus:	$(BNAME)

$(BNAME): $(B_OBJ)
	$(CC) $(CFLAGS) $(B_OBJ) -o $(NAME)

BNS/%.o: BNS/%.c BNS/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@
	@touch $(BNAME)

clean:
	rm -rif $(M_OBJ) $(B_OBJ) $(BNAME)

fclean: clean
	rm -rif pipex

re: fclean all
