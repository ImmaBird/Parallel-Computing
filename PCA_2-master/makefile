CC = mpicc #compiler
LDC = mpicc #linker
RM = /bin/rm
PARAM = --std=c11
CPROGS = ring.cx ping_pong.cx

#all rule
all: $(CPROGS)

ping_pong.cx:ping_pong.o
	$(LDC) $(PARAM) $< -o $@

ring.cx:ring.o
	$(LDC) $(PARAM) $< -o $@

%.o:%.c
	$(CC) $(PARAM) -c $^ -o $@

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod

cluster_run:
	qsub pbs
