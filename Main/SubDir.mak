Build : $(patsubst %.c,%.o,$(wildcard *.c))
	cp $^ $(HomeDir)/O_files
	rm -f $^
%.o:%.c
	gcc -c $^