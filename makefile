dependencies = ./lib/main.o ./lib/siparis.o ./lib/libfdr.a 

program: $(dependencies)
	gcc $(dependencies) -o ./bin/program
	./bin/program
	
./lib/main.o: ./src/main.c
	gcc -c ./src/main.c -I ./include -o ./lib/main.o

./lib/siparis.o:
	gcc -c ./src/siparis.c -I ./include -o ./lib/siparis.o

clean:
	rm ./lib/main.o ./lib/siparis.o ./bin/program 