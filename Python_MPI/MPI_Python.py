from mpi4py import MPI
import numpy as np
import time

N = 10
MASTER = 0

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

A = None
if rank == MASTER:
    A = np.random.rand(N, N)

if N % size != 0:
    if rank == MASTER:
        print("ошибка: размер матрицы")
    MPI.Finalize()
    exit()

local_rows = N // size
local_A = np.zeros((local_rows, N))

comm.Scatter(A, local_A, root=MASTER)

start_time = MPI.Wtime()

local_inv = np.linalg.pinv(local_A)

inv_A = None
if rank == MASTER:
    inv_A = np.zeros((N, N))
comm.Gather(local_inv, inv_A, root=MASTER)

end_time = MPI.Wtime()

if rank == MASTER:
    print("Inverted Matrix A^-1:")
    print(inv_A)
MPI.Finalize()
