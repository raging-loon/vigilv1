// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdint.h>

// structure for message queue

typedef struct{
  char data[256];
} ipc_queue_mem;

int main()
{
	key_t key = ftok("progfile",'b');
	int msgid;
	msgid = msgget(key, 0666 | IPC_CREAT);
	printf("%d\n",key);
  while(1){
    ipc_queue_mem message;
	  msgrcv(msgid, &message, sizeof(message), 1, 0);
	  printf("Data Received is : %s \n",			message.data);
  }
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}
