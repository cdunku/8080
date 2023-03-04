#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "cpu.h"
#include "memory.h"


void cpm(i8080* const s)
{
   uint16_t addr = s->d << 8 | s->e;
   if(s->c == 2)
   {
     putchar((char)s->e);
   }
   else if(s->c == 9)
   {
      do
      {
        putchar(readByte(s, addr++));
        }while(readByte(s, addr) != '$');
   }

}

static inline int load_file(i8080* const s, const char *file_to_load)
{
    FILE* f = fopen(file_to_load, "rb");

    if(f == NULL) 
    {
      perror(file_to_load);
      return 1;
    }

    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    rewind(f);

    size_t file_read = fread(&s->memory[0x100], sizeof(uint8_t), 0x10000 - 0x100, f);

    if(file_read != file_size)
    {
      fprintf(stderr, "CAN'T READ: \"%s\" INTO MEMORY!\n", file_to_load);
      return 1;
    }

    fclose(f);

    return 0;
}

static inline void execute_file(i8080* const s, const char* file_to_load)
{
    init_state(s);
    memset(s->memory, 0, 0x10000);
    load_file(s, file_to_load);

    s->memory[0x0005] = 0xC9;
    s->pc = 0x0100;
    
    printf("\n\n*** FILE LOADED: %s\n", file_to_load);

    while(1)
    {
	if(s->pc == 0x0005) 
	{
	  cpm(s);
	}
        /* if(s->inte_pending == 1)
        {
          interrupt_handle(s, nextByte(s)); // INTERRUPT HANDLING IS DISABLED FOR CPU EXERCISERS!
        }
	*/
 	/* debug_output(s, true); */ // INSTRUCTION, REGISTER & FLAG VALUE OUTPUTS
        cpu_step(s);
        if(s->pc == 0x0000)
        {
          return;
        }
    }
}


int main()
{
    char* array[7];
    array[0] = " ________  ________  ________  ________                       \n";
    array[1] = "|\\   __  \\|\\   __  \\|\\   __  \\|\\   __  \\              \n";
    array[2] = "\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\    \n";
    array[3] = " \\ \\   __  \\ \\  \\|\\  \\ \\   __  \\ \\  \\|\\  \\         \n";
    array[4] = "  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\    \n";
    array[5] = "   \\ \\_______\\ \\_______\\ \\_______\\ \\_______\\         \n";
    array[6] = "    \\|_______|\\|_______|\\|_______|\\|_______|              \n";

    for(int i = 0; i < 7; i++) {
            printf("%s", array[i]);
    }

    i8080 state;
    const time_t time_start = time(NULL);
    execute_file(&state, "test_files/altairclone/TST8080.COM");
    execute_file(&state, "test_files/altairclone/CPUTEST.COM");
    execute_file(&state, "test_files/altairclone/8080PRE.COM");
    execute_file(&state, "test_files/altairclone/8080EXM.COM");
    const time_t time_end = time(NULL);

    printf("\nProgram executed in %ld seconds\n", time_end - time_start);
    return 0;
}
