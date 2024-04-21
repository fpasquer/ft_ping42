NAME = ft_ping

SRC_NAME = main.c freePing.c parseArgs.c usage.c parseArgsErrors.c \
	parseArgsHelper.c signalHandler.c loopPing.c ipHelper.c statisticsPing.c

INCLUDES = ft_ping.h

LIBRARY = libft/libft.a

GCC = gcc
CFLAGS = -Wall -Wextra -Werror -g
OTHER_FLAGS = -lm

OBJ_NAME = $(SRC_NAME:.c=.o)

SRCDIR = srcs
OBJDIR = objs
INCDIR = incs

SRC = $(addprefix $(SRCDIR)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJDIR)/, $(OBJ_NAME))
INC = $(addprefix $(INCDIR)/, $(INCLUDES))

All : $(NAME)

$(NAME) : $(OBJDIR) $(OBJ) $(LIBRARY)
	$(GCC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBRARY) $(OTHER_FLAGS)
	@echo "\033[0;32m"$(NAME) "DONE\033[0m"

$(LIBRARY) :
	@echo "\033[0;32mCOMPILE LIBFT\033[0m"
	make -C libft

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -o $@ -c $<

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(OBJDIR)
	make -C libft fclean

re : fclean All

.PHONY : All clean fclean re