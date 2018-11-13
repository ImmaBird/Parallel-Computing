FC = gfortran
LD = gfortran
CC= gcc
LDC= gcc
LD_FLAGS = -fopenmp 
LDC_FLAGS= -lm -fopenmp
FLAGS = -fopenmp
PROGC = heatFTCS.cx
PROGF = heatFTCS.x
RM= /bin/rm

OBJSF=heatFTCSF.o
OBJSC = heatFTCSC.o

#all rule

all: $(PROGC)

$(PROGC): $(OBJSC)
	$(LDC) $(OBJSC) $(LDC_FLAGS) -o $(PROGC)

%C.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@


#clean rule
clean:
	$(RM) -rf *.o $(PROGC) *.x *.mod

run:
	cp ./heatFTCS.cx ./heatFTCS.exe
	./heatFTCS.exe