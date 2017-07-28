#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myhelp(char **arguman);
int myexit(char **arguman);
int plustwo(char **arguman);
int minustwo(char **arguman);
int factorial(char **arguman);



char *komutDizisi[] = {"help","exit","plustwo","minustwo","factorial"};


int (*komutFonk[]) (char **) = 
{&myhelp,
&myexit,
&plustwo,
&minustwo,
&factorial};



int komutSayisi() {
  return sizeof(komutDizisi) / sizeof(char *);
}


int myhelp(char **arguman)
{
  int i;
  printf("Tuğba Ay Komut Seti\n");

  for (i = 0; i < komutSayisi(); i++) {
    printf("  %s\n", komutDizisi[i]);
  }

  printf("Komutları Başka Programlar Hakkında Bilgi Almak için Kullanabilirsiniz.\n");
  return 1;
}


int myexit(char **arguman){
  printf("Terminal Kapatılıyor.\n");
  return 0;
}


int plustwo(char **arguman){
  pid_t pid;
  int durum,t;
  pid = fork();
  if (pid == 0) {

   if(arguman[1] == NULL && arguman[2] == NULL){
	printf("Komuttan sonra iki parametre giriniz ! 1 2 gibi\n");
   }
    else if(arguman[1] == NULL || arguman[2] == NULL){
	printf("Eksik ya da hatalı parametre girdiniz !\n");
    }
    
	 t=execve("plustwo",arguman,NULL);
	
    return 0;
    } 

    else if (pid < 0) {
      perror("error");
    } 

    else {
      durum = wait(&durum);
    }
  return 1;
}



int minustwo(char **arguman){
  pid_t pid;
  int durum,t;
  pid = fork();
  if (pid == 0) {
   
   if(arguman[1] == NULL && arguman[2] == NULL){
	printf("Komuttan sonra iki parametre giriniz ! 1 2 gibi\n");
   }
    else if(arguman[1] == NULL || arguman[2] == NULL){
	printf("Eksik ya da hatalı parametre girdiniz !\n");
    }
    
     t=execve("minustwo",arguman,NULL);
    	
    return 0;

   } 
  
  else if (pid < 0) {
    perror("error");
   } 
   else {
    durum = wait(&durum);
   }
  return 1;
}

int factorial(char **arguman){
  pid_t pid;
  int durum,t;
  pid = fork();
  if (pid == 0) {
    
	if(arguman[1] == NULL && arguman[1] != NULL ){
	printf("Eksik ya da hatalı parametre girdiniz.Komuttan sonra tek parametre giriniz ! 1 gibi\n");
    } 
else {
	 t=execve("factorial",arguman,NULL);
	}
    return 0;
    }

    else if (pid < 0) {
       perror("error");
    } 
  return 1;
}


int komutlar(char **arguman)
{
  pid_t pid, wpid;
  int durum;

  pid = fork();
  if (pid == 0) {
    if (execvp(arguman[0], arguman) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("lsh");
  } else {
    do {
      wpid = waitpid(pid, &durum, WUNTRACED);
    } while (!WIFEXITED(durum) && !WIFSIGNALED(durum));
  }

  return 1;
}



int execute(char **arguman){
	

  if (arguman[0] == NULL) {
    return 1;
  }
  
  if (strcmp(arguman[0], komutDizisi[0]) == 0)  { 
     return myhelp(arguman); 
  }
  
  else if (strcmp(arguman[0], komutDizisi[1]) == 0) { 
    return myexit(arguman); 
  }
  
  else if (strcmp(arguman[0], komutDizisi[2]) == 0) { 
    return plustwo(arguman); 
  }
  
  else if (strcmp(arguman[0], komutDizisi[3]) == 0) { 
    return minustwo(arguman); 
  }
  
  else if (strcmp(arguman[0], komutDizisi[4]) == 0) { 
    return factorial(arguman); 
  }
  
  else if(strcmp(arguman[0], "clear") == 0 || strcmp(arguman[0], "cat") == 0) { 
    return komutlar(arguman); 
  }
  
  else { 
    printf("Yanlış Bir Komut Girdiniz.\n"); 
  } 

  return 1;
}


char *readLine(){
  int bufsize = 100;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "Hata : allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize) {
      bufsize += 100;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "Hata: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}


#define BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
char **splitLine(char *komut){
  int bufsize = BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens){
    fprintf(stderr, "Buffer Hatası\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(komut, TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "Buffer Hatası\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}


int myshell() {
 
  char *komut;
  char **arguman;
  int durum;
  do{
    printf("myShell-->> ");
    komut = readLine();
    arguman = splitLine(komut);
    durum = execute(arguman);
    
  }while(durum);
  return 0;
}



int main() {
  myshell();

return EXIT_SUCCESS;
}
