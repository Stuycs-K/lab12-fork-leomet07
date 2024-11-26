.PHONY: compile run clean
compile program.out: main.c
	@gcc -g -Wall -o program.out main.c
run: program.out
	@./program.out
clean:
	rm program.out