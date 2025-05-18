#include <libepc.h>

int main(int argc, char *argv[])
{
   ClearScreen(0x07);
   SetCursorPosition(0, 0);
   
   PutString(">>>>>>> Empty Floppy Used as VT24 <<<<<<<\r\n");
   
   return 0;
}
