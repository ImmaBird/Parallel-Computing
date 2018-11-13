CC = mpicc #compiler
LDC = mpicc #linker
RM = /bin/rm
PARAM =
CPROGS = mc.cx

#all rule
all: $(CPROGS)

mc.cx:mc.o
	$(LDC) $(PARAM) $< -o $@

%.o:%.c
	$(CC) $(PARAM) -c $^ -o $@

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod

run:
	qsub pbs_mc
