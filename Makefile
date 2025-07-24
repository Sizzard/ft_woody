

all:
	make -C code
	cd vagrant && vagrant up && vagrant ssh

clean:
	make clean -C code

fclean:
	make fclean -C code
	cd vagrant && vagrant destroy

re: fclean all