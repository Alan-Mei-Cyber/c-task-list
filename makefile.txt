lab9:	main.c list.c file.c
	gcc -o lab9 main.c list.c file.c -lpthread
	./lab9 x y

lab9_test:	main.c list.c file.c
	gcc -o lab9 main.c list.c file.c -lpthread
	./lab9 empty_text.txt empty_bin.bin

# The clean command has been added by TA
clean:
	@ rm -f lab3 lab4 lab5 lab6 lab7 lab8 lab9 empty_text empty_bin x y
