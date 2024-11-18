all:
	make -C server
	make -C client

clean:
	make clean -C server
	make clean -C client

server:
	make -C server

client:
	make -C client

fclean: clean
	make fclean -C server
	make fclean -C client

debug:
	make debug -C server
	make debug -C client

re: fclean all

.PHONY: server client fclean clean debug all re