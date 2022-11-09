/**
 *  
 * The student needs to compile, test and comment the source code file.
 * 
 * Enumerate those Rules and Recommendation associated that are broken in the 
 *     previous source code file.
 * Enumerate he compilation tools and paramenters (gcc vs g++ ), -Wall ...
 * Enumerate the standard associated  -std=c99, -std=c11
 * 
 * There are several variants. You should choose at least two. You can also try clang.
 * At the end the source code  should compile without warnings to the variant 
 *     selected (you can remove/change instructions).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
char array1[] = "Foo" "bar";
char array2[] = { 'F', 'o', 'o', 'b', 'a', 'r', '\0' };
 
enum { BUFFER_MAX_SIZE = 1024 };

//Regla STR30-C. Do not attempt to modify string literals
//R no se puede utilizar en C es solo de C++
//Hay que poner el char en la misma linea o separarlo con '\'
const char* s1 = "foo(\nHello\nWorld\n)foo";
const char* s2 = "\nHello\nWorld\n";

//Si retorna un valor no puede ser void
int gets_example_func(void) {
  char buf[BUFFER_MAX_SIZE];
 
  if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 1;
  }
  buf[strlen(buf) - 1] = '\0';

  //Al ser int hay que aniadir un return si no da warning
  return 0; 
}

const char *get_dirname(const char *pathname) {
  char *slash;
  slash = strrchr(pathname, '/');
  if (slash) {
    *slash = '\0'; /* Undefined behavior */
  }
  return pathname;
}
 

void get_y_or_n(void) {  
	char response[8];

	printf("Continue? [y] n: ");  

  //warning implicit declaration of function ‘gets’; did you mean ‘fgets’? [-Wimplicit-function-declaration]
  //gets esta deprecated utilizar fgets en su lugar
	fgets(response, sizeof(response), stdin); 

	if (response[0] == 'n') 
		exit(0);  

	return;
}

 
int main(int argc, char *argv[])
{
    char key[24];
    char response[8];
    char array3[16];
    char array4[16];
    char array5 []  = "01234567890123456";

    //warning variable ‘ptr_char’ set but not used [-Wunused-but-set-variable]
    //Comento esta variable ya que no esta siendo utilizada solo se cambia un valor pero no se utiliza y da warning
    //char ptr_char[]  = "new string literal";


    //Las dos variables de abajo no se utilizan con lo cual da un warning
    //int size_array1 = strlen("аналитик");
    //int size_array2 = 100;
    
   // char analitic1[size_array1]="аналитик";
   // char analitic2[size_array2]="аналитик";

    //Esta variable no se utiliza con lo cual da un warning
    //char analitic3[100]="аналитик"; 

    puts(get_dirname(__FILE__));

        
    strcpy(key, argv[1]);  
    strcat(key, " = ");  
    strcat(key, argv[2]);


    fgets(response,sizeof(response),stdin);
    
    get_y_or_n();

    printf ("%s",array1);
    printf ("\n");
    printf ("%s",array2);
    printf ("\n");
 
    puts (s1);
    printf ("\n");
    puts (s2);
    printf ("\n");
    
    strncpy(array3, array5, sizeof(array3));  
    strncpy(array4, array3, strlen(array3));
    
    array5 [0] = 'M';

    //Al comentar la linea en la que se declara da error al no estar definida
    //ptr_char [0] = 'N';
    
    array3[sizeof(array3)-1]='\0';
    
    
    return 0;
}