#include <stdio.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  unsigned char * digest;
  unsigned int type;
  char alert_str[256];
} vmal_def;
vmal_def definitions[256];
int num_def = 0;
void load_hashes();
void def_alloc(vmal_def *, const char *);

#define D_SHA256      0x65

int main(int argc, char ** argv){
  // FILE * malware_def = fopen("definitions.txt","r");
  load_hashes();
  FILE * suspect_fp = fopen(argv[1],"rb");
  unsigned char * sha256_digest = (unsigned char *)malloc(sizeof(char) * SHA256_DIGEST_LENGTH); 
  char * digest_str = (unsigned char * )malloc(SHA256_DIGEST_LENGTH * 2);
  memset(digest_str,0, sizeof(digest_str));
  fseek(suspect_fp, 0L, SEEK_END);
  int sz = ftell(suspect_fp);
  rewind(suspect_fp);
  unsigned char buffer[sz];

  fread(&buffer,sizeof(buffer),sz,suspect_fp);
  
  
  SHA256((const unsigned char *)&buffer,sz,sha256_digest);
  int loc = 0;
  for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
    sprintf(digest_str + strlen(digest_str),"%02x",sha256_digest[i]);
    // loc += 2;
  }

  for(int i = 0; i < num_def; i++){
    vmal_def * t_def = &definitions[i];
    if(strcmp(t_def->digest,digest_str) == 0){
      printf("%s\n",t_def->alert_str);
    }
  }

  free(sha256_digest);
  free(digest_str);
  fclose(suspect_fp);
}

void load_hashes(){
  FILE * fp = fopen("definitions.txt","r");
  char * line = NULL;
  size_t len, pos = 0;
  while((pos = getline(&line,&len,fp)) != -1){
    line[strcspn(line,"\n")] = 0;
    if(line[0] == '#') continue;
    
    vmal_def * def = &definitions[num_def++];
    
    char * tok = strtok(line,":");
    int loc = 0;
    while(tok != NULL){
      // printf("%s\n",tok);
      switch(loc){
        case 0: /* TYPE */
          def_alloc(def,tok);
          break;
        case 1:
          strcpy(def->digest,tok);
          break;
        case 2:
          strcpy(def->alert_str,tok);
          break;
      }
      loc++;
      tok = strtok(NULL, ":");
    }
  }
  
  fclose(fp);
}

void def_alloc(vmal_def * def, const char * digest_type){
  if(strcmp(digest_type,"sha256") == 0){
    def->type = D_SHA256;
    def->digest = (unsigned char *)malloc(SHA256_DIGEST_LENGTH * 2);
  }
}