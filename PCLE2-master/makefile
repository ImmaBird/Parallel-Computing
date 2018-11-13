CC = mpicc #compiler
LDC = mpicc #linker
CPROGS = matmult.cx bug1.cx bug2.cx bug3.cx
FLAGS = -fopenmp

#all rule
all: $(CPROGS)

%.cx:%.o
	$(LDC) $(FLAGS) $< -o $@

%.o:%.c
	$(CC) $(FLAGS) -c $^ -o $@

#clean rule
clean:
	rm -rf *.o *.cx

bugs:
	qsub pbs_bugs

mm:
	qsub pbs_mm

docker-run:
	docker.exe build -t mm:latest .
	docker.exe run --rm mm:latest