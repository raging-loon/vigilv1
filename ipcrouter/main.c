// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue

typedef struct{
  pid_t pid;
  uint type;
  char data[256];
} ipc_queue_mem;

int main()
{
	key_t key = ftok("progfile", 65);
	int msgid;

  while(1){
    ipc_queue_mem message;
	  msgid = msgget(key, 0666 | IPC_CREAT);
	  msgrcv(msgid, &message, sizeof(message), 1, 0);
	  printf("Data Received is : %s \n",			message.data);
  }
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}
