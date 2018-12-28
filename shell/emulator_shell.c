#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "chipset.h"
#include "descriptions.h"
#include "emulator.h"


//bool valid_codes(char *codes);
//void print_help(const char *codes, bool debug);
//void print_instructions(const char *codes);
void input(char program[], int size);
void run_program(chipset *chip, char *program);
void run_debug(chipset *chip, char *program);
void clear_screen(void);


int main(int argc, char **argv)
{
        chipset *chip;
        bool debug = false;

        if (argc == 2 && (strncmp(argv[1],"d", 1) == 0))
        {
                debug = true;
        }

        while (true)
        {
                char choice[3];
                printf("select '4' or '8' bit chip\n");
                input(choice, sizeof(choice));
                choice[strcspn(choice, "\n")] = '\0';

                if (strncmp(choice, "4", 1) == 0)
                {
                        chip = init_chip(4, 16);
                        break;
                }
                else if (strncmp(choice, "8", 1) == 0)
                {
                        chip = init_chip(8, 16);
                        break;
                }
                else
                {
                        fprintf(stderr, "Invalid chip bits\n");
                }
        }

        while (true)
        {
                char program[256];
                input(program, sizeof(program));
                program[strcspn(program, "\n")] = '\0';

                //if (strncmp(program, "help", 4) == 0)
                //{
                //        clear_screen();
                //        print_help(BASE_CODES, debug);
                //}
                if (strncmp(program, "clear", 5) == 0)
                {
                        clear_screen();
                }
                else if (strncmp(program, "debug", 5) == 0)
                {
                        debug = true;
                        clear_screen();
                        //print_help(BASE_CODES, debug);
                }
                else if (strncmp(program, "normal", 6) == 0)
                {
                        debug = false;
                        clear_screen();
                        //print_help(BASE_CODES, debug);
                }
                else if (strncmp(program, "quit", 4) == 0)
                {
                        break;
                }
                else
                {
                        if (debug)
                        {
                                run_debug(chip, program);
                        }
                        else
                        {
                                run_program(chip, program);
                        }
                }
        }

        return EXIT_SUCCESS;
}


void run_program(chipset *chip, char *program)
{
        printf("\n %d\n\n", execute(chip, program));
}


void run_debug(chipset *chip, char *program)
{
        printf("\n %d\n\n", debug(chip, program));
}


void input(char program[], int size)
{
        printf(" #> ");
        fgets(program, size, stdin);

        // discard input beyond memory size
        if (!strchr(program, '\n'))
        {
                while (fgetc(stdin) != '\n') {};
        }
}


//bool valid_codes(char *codes)
//{
//        if (strlen(codes) != MEM)
//        {
//                return false;
//        }
//
//        return true;
//}


void clear_screen(void)
{
        const char *clear_screen_unix = "\e[1;1H\e[2J";
        write(STDOUT_FILENO, clear_screen_unix, 12);
}


//void print_instructions(const char *codes)
//{
//        printf("\ncode   :    instruction\n\n");
//
//        for (int i = 0; i < MEM; i++)
//        {
//                int perm = map_to_instruction_code(*(codes+i));
//                printf(" %c     :    %s\n", map_to_input_code(i), instruction_description[perm]);
//        }
//        printf("\n");
//}
//
//
//void print_help(const char *codes, bool debug)
//{
//        if (debug)
//        {
//                printf("\nDEBUG MODE\n");
//        }
//
//        print_instructions(codes);
//        printf("Type 'quit' to exit, 'clear' to clear screen,  or 'help' to display all instructions\n\n");
//}
