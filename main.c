#include <stdio.h>

#include "include/memory.h"
#include "include/control_unit.h"

/**
 * Reads instructions and data from memory and handles the instruction cycle until the end of the instructions.
 */
int main() {

    ir = NULL;
    cycles = 0;

//    char *instructionsMemoryFileName = "instructions-memory_arithmetic.txt";
//    char *dataMemoryFileName = "data-memory_arithmetic.txt";
//    char *instructionsMemoryFileName = "instructions-memory_factorial.txt";
//    char *dataMemoryFileName = "data-memory_factorial.txt";
//    char *instructionsMemoryFileName = "instructions-memory_fibonacci.txt";
//    char *dataMemoryFileName = "data-memory_fibonacci.txt";
//    char *instructionsMemoryFileName = "instructions-memory_bubble-sort.txt";
//    char *dataMemoryFileName = "data-memory_bubble-sort.txt";

    char *instructionsMemoryFileName = "instructions-memory_matrix.txt";
    char *dataMemoryFileName = "data-memory_matrix.txt";

    if (!load_memory(instructionsMemoryFileName, dataMemoryFileName)) {
        puts("ERROR: Could not load memory");
        return 0;
    }

    state = FETCH;

    // Handle the instruction cycle
    while (state != FINISH) {
        switch (state) {
            case FETCH:
                ir = fetch(instruction_memory);
                if (ir == NULL) {
                    if (LOG) {
                        puts("End of instructions #");
                    }
                    // There is no more instructions
                    state = FINISH;
                    break;
                }
                state = DECODE;
                break;
            case DECODE:
                decode(ir);
                state = EXECUTE;
                break;
            case EXECUTE:
                execute(operation);
                state = FETCH;
                break;
        }
    }

    write_memory(dataMemoryFileName, mar, mbr);
    printf("Process finished with %d cycles.\n", cycles);
    return 0;
}