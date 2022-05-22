// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
typedef struct ipc_queue_mem {
	long mesg_type;
	char mesg_text[256];
} ipc_queue_mem;

int main(){
	key_t key;
	int msgid;
	key = ftok("progfile", 65);
	msgid = msgget(key, 0666 | IPC_CREAT);
	while(1){
		ipc_queue_mem message;
		msgrcv(msgid, &message, sizeof(message), 1, 0);
		printf("%s", message.mesg_text);
	}
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}
