##
## Makefile for Makefile in /home/Epitech
##
## Made by moriss_h
## Login   <moriss_h@epitech.net>
##
## Started on  Sun Jun  9 03:35:24 2013 Hugues
## Last update Sun Apr 13 15:05:03 2014 Hugues
##

SRC			=	inet.c \
				inet_accept.c \
				path.c \
				ptr_tab.c \
				clean_tab.c \
				ls.c \
				cd.c \
				send_recv_file.c \
				commands_handling.c \
				get_next_line.c

SRCCLIENT		=	client/main.c \
				client/handle_input.c \
				client/client_commands.c \
				client/command.c \
				client/pasv.c \
				client/response.c \
				client/cmd.c

SRCSERVER	=	server/main.c \
			server/handle_client.c \
			server/ftpcommands.c \
			server/commands.c \
			server/authcommands.c \
			server/pasv.c

SRCCLIENT	+=	$(SRC)
SRCSERVER	+=	$(SRC)

CC		=	gcc

RM		=	rm -f

CLIENT		=	client
SERVER		=	serveur
NAME		=	my_ftp

OBJDIR		=	obj/
SRCDIR		=	src/
INCDIR		=	inc/

CFLAGS		+=	-I$(INCDIR)
CFLAGS		+=	-Wall -Wextra -Winit-self
CFLAGS		+=	-Wunused-function -pipe -Winit-self

LDFLAGS		+=	-Wl,-O1

OBJCLIENT		=	$(patsubst %.c,${OBJDIR}%.o, $(SRCCLIENT))
OBJSERVER	=	$(patsubst %.c,${OBJDIR}%.o, $(SRCSERVER))

dummy		:=	$(shell test -d $(OBJDIR) || mkdir -p $(OBJDIR))
dummy		:=	$(shell test -d $(SRCDIR) || mkdir -p $(SRCDIR))
dummy		:=	$(shell test -d $(INCDIR) || mkdir -p $(INCDIR))

.PHONY:	all clean fclean re help $(NAME) nm objdump

$(NAME):	$(SERVER) $(CLIENT)

all:	$(NAME)

$(OBJDIR)%.o:		$(patsubst %.c,${SRCDIR}%.c, %.c)
			@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
			@echo -e "Compiling $< { $(CFLAGS) }" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' \
			| sed 's/[{}]/\x1B[34m&\x1B[0m/g' \
			| sed 's/[─┬─├─└│]/\x1B[35m&\x1B[0m/g'
			@$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT):	$(OBJCLIENT)
	@echo -e "Linking $@ { $(LDFLAGS) }" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[34m&\x1B[0m/g'
	@$(CC) $(LDFLAGS) -o $(CLIENT) $(OBJCLIENT)

$(SERVER):	$(OBJSERVER)
	@echo -e "Linking $@ { $(LDFLAGS) }" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[34m&\x1B[0m/g'
	@$(CC) $(LDFLAGS) -o $(SERVER) $(OBJSERVER)

clean:
	@echo -e "Removing object !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[35m&\x1B[0m/g'
	@$(RM) $(OBJSERVER) $(OBJCLIENT)

fclean:	clean
	@echo -e "Removing ${CLIENT} ${SERVER} !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[36m&\x1B[0m/g'
	@$(RM) $(CLIENT) $(SERVER)

re:	fclean all

help:
	@echo -e "\033[37mTarget available: all, clean, fclean\033[00m" \
	| sed 's/^-e //'

