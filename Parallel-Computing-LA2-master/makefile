CC = gcc #compiler
LDC = gcc #linker
RM = /bin/rm
PARAM = -fopenmp
CPROGS = mvp-student.cx

#all rule
all: $(CPROGS) $(FPROGS)

mvp-student.cx:mvp-student.o
	$(LDC) $(PARAM) $< -o $@

%.o:%.c
	$(CC) $(PARAM) -c $^ -o $@

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod

