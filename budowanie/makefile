CC = g++

main.out: hello.o main.o
	${CC} $^ -o $@	# $@ - target; $^ - all of the prerequisites

hello.o: hello.cpp
	${CC} -c $^ -o $@

main.o: main.cpp
	${CC} -c $^ -o $@
