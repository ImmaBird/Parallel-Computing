CC = gcc #compiler
LDC = gcc #linker
RM = /bin/rm
PARAM = -fopenmp
CPROGS = mmp.cx

#all rule
all: $(CPROGS)

mmp.cx:mmp.o
	$(LDC) $(PARAM) $< -o $@

%.o:%.c
	$(CC) $(PARAM) -c $^ -o $@

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod

run:
	./mmp.cx 1300

cluster_run:
	qsub pbs_PA1
