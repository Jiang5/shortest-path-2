a: 
	g++ -std=c++11 -g -o a main.cpp
c:
	rm -f *.o a
t:	
	make c
	make
	./a
g:
	gdb -x dbg.txt a