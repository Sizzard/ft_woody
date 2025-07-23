

all:
	cd vagrant && vagrant up && vagrant ssh
	make -C code

clean:
	make clean -C code

fclean:
	cd vagrant && vagrant destroy
	make fclean -C code

re: fclean all