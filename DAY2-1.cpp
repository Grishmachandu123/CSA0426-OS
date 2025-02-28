#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_KEY 0x1234

int main() {
    int shmid;
    char *shared_memory;

    // Create shared memory segment
    shmid = shmget(SHM_KEY, 1024, 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory segment
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Write to the shared memory
    strcpy(shared_memory, "Hello from writer!");

    printf("Writer: Data written to shared memory: %s\n", shared_memory);

    // Detach from the shared memory segment
    shmdt(shared_memory);

    return 0;
}

