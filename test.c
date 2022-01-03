#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void rule_parser(const char * );
int strloc(const char * restrict haystack,const char needle);
int main(int argc, char ** argv){
	FILE * fp = fopen(argv[1],"r");
	size_t pos, len = 0;
	char * line = NULL;	

	while((pos = getline(&line,&len,fp)) != -1){
		if(strstr(line,"#") != NULL) continue;
		rule_parser(line);
	}
}

void rule_parser(const char * line){
	int filled = 0;
	
	char * parser_line;
	char ruletype[32];
	char rulename[32];
	char target_chars[64];
	char alert_type[32];
	char protocol[10];
	char port[14];

	// the first par always needs to be "alert"
	int chars_parsed = 6;
	while(filled != 6){
		parser_line = line + chars_parsed;
		char target[64];
		memset(&target,0,sizeof(target));
		strncpy(target,parser_line ,strloc(parser_line,' ') + 1);
		chars_parsed += strlen(target);

		if(filled == 0){
			strcpy(alert_type,target);
		} 
		else if(filled == 1){
			strcpy(port,target);
		} 
		else if(filled == 2){
			strcpy(protocol,target);
		}
		else if(filled == 3){
			char * name = target + 1;
			name[strcspn(name,"\"")] = 0;
			strcpy(rulename,name);
		}
		else if(filled == 4){
			strcpy(ruletype,target);
		}
		else if(filled == 5){
			memset(&target_chars,0,sizeof(target_chars));
			strncpy(target_chars,parser_line + 1,strlen(parser_line) - 5);
		}
		filled++;
	}
	printf("alert_type: %s\n",alert_type);
	printf("port: %s\n",port);
	printf("protocol: %s\n",protocol);
	printf("rule_name: %s\n",rulename);
	printf("rule_type: %s\n",ruletype);
	printf("target_chars: %s\n",target_chars);
}




int strloc(const char * restrict haystack,const char needle){
  for(int i = 0; haystack[i] != NULL; i++){
    if(haystack[i] == needle){
      return i;
    }
  }
  return -1;
}