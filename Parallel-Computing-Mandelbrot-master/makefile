CC = gcc #compiler
LDC = gcc #linker
RM = /bin/rm
PARAM = -fopenmp
CPROGS = mandelbrot.cx

#all rule
all: $(CPROGS)

mandelbrot.cx:mandelbrot.o
	$(LDC) $(PARAM) $< -o $@

%.o:%.c
	$(CC) $(PARAM) -c $^ -o $@

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod *.pgm *.png

run:
	./mandelbrot.cx 600 400
	pnmtopng -v img.pgm > img.png