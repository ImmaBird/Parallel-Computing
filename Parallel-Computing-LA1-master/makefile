CC = gcc #compiler
LDC = gcc #linker
RM = /bin/rm

CPROGS = mvp-student.cx

#all rule
all: $(CPROGS) $(FPROGS)

mvp-student.cx:mvp-student.o
	$(LDC) $< -o $@

%C.o: %.c
	$(CC) -c $^ -o $@

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod

