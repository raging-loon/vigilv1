#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>
int main(){
  const char * password = "password";
  unsigned char real_hash[SHA256_DIGEST_LENGTH];
  unsigned char hash[32];
		SHA256_CTX ctx;
		memset(&ctx,0,sizeof(ctx));
		// memset(&,0,sizeof(hash));
		SHA256_Init(&ctx);
		SHA256_Update(&ctx,password,sizeof(password));
		SHA256_Final((unsigned char *)&hash,&ctx);
		
		for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
			sprintf(real_hash + (i * 2),"%02x",hash[i]);
		}
		printf("%s\n",real_hash);

}
