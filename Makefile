main.o:
	g++ -Wall -Wextra -Werror -o main.o main.cpp
	chmod +x main.o

run: main.o
	./main.o

clean:
	rm main.o
