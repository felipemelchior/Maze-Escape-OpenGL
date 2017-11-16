output:	main.o
	g++ main.o -o jogo

main.o:	main.cpp
	g++ -o -lGL -lGLU -lglut main.cpp -c

clean:
	rm *.o jogo