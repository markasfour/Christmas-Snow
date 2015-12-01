all:
	if [ ! -d "./bin" ];\
		then mkdir bin;\
	fi
	g++ main.cpp -w -lSDL2 -lSDL2_image -o bin/a.out

clean:
	rm -rf bin
