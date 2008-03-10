all:
	gcc -o bin/tetris src/*.c -lglut -ggdb
	
run:
	cd bin && ./tetris
	
clean:
	rm bin/*
	
count:
	wc -l src/*
