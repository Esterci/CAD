CC = mpicc
CFLAGS = -Wall -g
LDFLAGS = -lm

all: mpi_hello mpi_struct mpi_scatter mpi_gather mpi_allgather \
   mpi_reduce mpi_reduce2 mpi_comm mpi_vector mpi_grid mpi_send mpi_count \
   mpi_isend

mpi_hello: mpi_hello.o
	$(CC) $(CFLAGS) -o mpi_hello mpi_hello.o $(LDFLAGS)

mpi_send: mpi_send.o
	$(CC) $(CFLAGS) -o mpi_send mpi_send.o $(LDFLAGS)

mpi_count: mpi_count.o
	$(CC) $(CFLAGS) -o mpi_count mpi_count.o $(LDFLAGS)

mpi_isend: mpi_isend.o
	$(CC) $(CFLAGS) -o mpi_isend mpi_isend.o $(LDFLAGS)

mpi_scatter: mpi_scatter.o
	$(CC) $(CFLAGS) -o mpi_scatter mpi_scatter.o $(LDFLAGS)

mpi_gather: mpi_gather.o
	$(CC) $(CFLAGS) -o mpi_gather mpi_gather.o $(LDFLAGS)

mpi_allgather: mpi_allgather.o
	$(CC) $(CFLAGS) -o mpi_allgather mpi_allgather.o $(LDFLAGS)

mpi_reduce: mpi_reduce.o
	$(CC) $(CFLAGS) -o mpi_reduce mpi_reduce.o $(LDFLAGS)

mpi_reduce2: mpi_reduce2.o
	$(CC) $(CFLAGS) -o mpi_reduce2 mpi_reduce2.o $(LDFLAGS)

mpi_comm: mpi_comm.o
	$(CC) $(CFLAGS) -o mpi_comm mpi_comm.o $(LDFLAGS)

mpi_vector: mpi_vector.o
	$(CC) $(CFLAGS) -o mpi_vector mpi_vector.o $(LDFLAGS)

mpi_struct: mpi_struct.o
	$(CC) $(CFLAGS) -o mpi_struct mpi_struct.o $(LDFLAGS)

mpi_grid: mpi_grid.o
	$(CC) $(CFLAGS) -o mpi_grid mpi_grid.o $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o mpi_hello mpi_struct mpi_scatter mpi_gather \
	mpi_allgather mpi_reduce mpi_reduce2 mpi_comm mpi_vector mpi_grid mpi_send \
	mpi_count mpi_isend 