FROM nlknguyen/alpine-mpich

COPY * ./

RUN make

CMD ["mpirun", "-n", "1", "./matmult.cx", "2000"]