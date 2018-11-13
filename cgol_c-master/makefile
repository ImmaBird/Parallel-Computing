compiler = gcc
linker = gcc
project = cgol

all:$(project).cx

$(project).cx:$(project).o
	$(linker) -fopenmp $< -o $@

%.o:%.c
	$(compiler) -fopenmp -c $^ -o $@

clean:
	rm -rf *.o *.cx

run:
	./$(project).cx 30

lazy:
	make all
	make run
	make clean

submit:
	qsub pbs