CC = tau_cc.sh
LDC = tau_cc.sh
LD_FLAGS = -lm -fopenmp
FLAGS = -fopenmp
PROGC = LA4.cx
RM= /bin/rm


#all rule

OBJSC=$(PROGC:%.cx=%.o)

all: $(PROGC)

$(PROGC): $(OBJSC)
	$(LDC)  $(OBJS) $< $(LD_FLAGS) -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod profile.*

run:
	qsub pbs_LA4
