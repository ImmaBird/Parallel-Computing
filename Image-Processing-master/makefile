CC=gcc
LDC=gcc
LD_FLAGS = -lstdc++ -lopencv_core -lopencv_highgui -lopencv_imgproc -fopenmp
FLAGS= -I/usr/include/opencv -fopenmp
PROGC = test.cx
OBJSC = imageTestC.o imageToolsC.o
OBJSF = imageToolsC.o imgBindingF.o imageTestF.o 
RM = /bin/rm

#all rule
all: $(PROGC)

$(PROGC): $(OBJSC)
	$(LDC) $^ $(LD_FLAGS) -o $@
%C.o: %.c*
	$(CC) $(FLAGS) -c $^ -o $@

#clean rule
clean:
	$(RM) -rf *.o $(PROGF) $(PROGC) *.mod

run:
	make
	./test.cx blur 15
	make clean

windows:
	g++ -I"C:/Program Files/opencv/build/include" -L"C:\Program Files\opencv\build\x64\vc15\lib" -c imageTools.cpp -lopencv_core243 -lopencv_highgui243
	gcc -c  imageTest.c
	g++ -I"C:/Program Files/opencv/build/include" -L"C:\Program Files\opencv\build\x64\vc15\lib" imageTools.o -lopencv_core243 -lopencv_highgui243

