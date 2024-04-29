#include "shell.h"

int main(void)  {
char command [120];
while (true) {
display_prompt ();
read_command (command, sizeof (command) ) ;
execute_command (command);
 }
Return 0;
}
