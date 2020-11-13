Build:$(wildcard *.o)
	gcc -o MyHash.exe $^
