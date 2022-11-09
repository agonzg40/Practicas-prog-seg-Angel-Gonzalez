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
#include <stddef.h>

char array1[] = "Foo" "bar";
char array2[] = { 'F', 'o', 'o', 'b', 'a', 'r', '\0' };
 
enum { BUFFER_MAX_SIZE = 1024 };
 
const char* s1 = R"foo(
Hello
World
)foo";
const char* s2 = "\nHello\nWorld\n";

int gets_example_func(void) {
  char buf[BUFFER_MAX_SIZE];
 
  if (fgets(buf, sizeof(buf), stdin) == NULL) {

        //Error return-statement with a value, in function returning ‘void’ [-fpermissive]
        //no se puede devolver un valor en una funcion void
        return 1;
  }
  buf[strlen(buf) - 1] = '\0';
}

//STR30-C. Do not attempt to modify string literals
//Noncompliant Code Example (Result of strrchr())
//No cumple la regla paso a hacerlo debajo con la regla correcta

/*const char *get_dirname(const char *pathname) {

  const char *slash;

  //error invalid conversion from ‘const char*’ to ‘char*’ [-fpermissive]
  //Se soluciona al cumplir la norma
  slash = strrchr(pathname, '/');

  if (slash) {*/
    //*slash = '\0'; /* Undefined behavior */
  //}
  //return pathname;
//}*/

//Asi cumple la norma
char *get_dirname(const char *pathname, char *dirname, size_t size) {
  const char *slash;
  slash = strrchr(pathname, '/');
  if (slash) {
    ptrdiff_t slash_idx = slash - pathname;
    if ((size_t)slash_idx < size) {
      memcpy(dirname, pathname, slash_idx);
      dirname[slash_idx] = '\0';     
      return dirname;
    }
  }
  return 0;
}
 

void get_y_or_n(void) {  
	char response[8];

	printf("Continue? [y] n: "); 

  //Error ‘gets’ was not declared in this scope; did you mean ‘fgets’?
  //gets ya esta deprecated y no se utiliza, en su lugar se utiliza fgets
	fgets(response, sizeof(response), stdin);//gets esta deprecado hay que utilizar fgets en g++ da error


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

    //Warning ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings] 
    //Por la regla STR30-C. Do not attempt to modify string literals hay que ponerlo como array
    //Warning variable ‘ptr_char’ set but not used [-Wunused-but-set-variable] con lo cuál la comento
    //char ptr_char[]  = "new string literal"; 

    //warning unused variable ‘size_array1’ [-Wunused-variable]
    //Estas dos variables no se utiliza y da un warning con lo cual las comento
    //int size_array1 = strlen("аналитик");
    //int size_array2 = 100;
    
   // char analitic1[size_array1]="аналитик";
   // char analitic2[size_array2]="аналитик";

    //warning unused variable ‘size_array1’ [-Wunused-variable]
    //Esta variable no se utiliza y da un warning con lo cual la comento
    //char analitic3[100]="аналитик";

    //No cumple la regla mencionada en el metodo
    //puts(get_dirname(__FILE__));

    //Con este cambio si cumple la norma
    char dirname[260];
    if (get_dirname(__FILE__, dirname, sizeof(dirname))) {
      puts(dirname);
    }

        
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

    //Solo se cambia el valor pero no se utiliza la variable entonces da un warning
    //ptr_char [0] = 'N';
    
    array3[sizeof(array3)-1]='\0';
    
    
    return 0;
}