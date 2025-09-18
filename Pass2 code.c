#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void passTwo();
void display();

void main()
{
    passTwo();
    display();
}

void passTwo()
{
    char label[10], opcode[10], operand[10];
    char code[10], mnemonic[10], symLabel[10], symAddr[10];
    char objCode[50], addr[10];
    int start = 0, locctr, length;
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;

    fp1 = fopen("intermediate.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "r");
    fp4 = fopen("output.txt", "w");
    fp5 = fopen("length.txt", "r");

    if (!fp1 || !fp2 || !fp3 || !fp4 || !fp5)
    {
        printf("Error opening files!\n");
        exit(1);
    }

    // First line check for START
    fscanf(fp1, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0)
    {
        start = (int)strtol(operand, NULL, 16);
        fprintf(fp4, "H^%s^%06X^", label, start);

        fscanf(fp5, "%s", addr);
        length = (int)strtol(addr, NULL, 16);
        fprintf(fp4, "%06X\n", length);

        fscanf(fp1, "%s %s %s %s", addr, label, opcode, operand);
    }

    locctr = start;
    int first_record = 1;

    while (strcmp(opcode, "END") != 0)
    {
        int found = 0;
        objCode[0] = '\0'; // reset object code
        rewind(fp2);

        // Search OPTAB
        while (fscanf(fp2, "%s %s", code, mnemonic) != EOF)
        {
            if (strcmp(opcode, code) == 0)
            {
                found = 1;
                strcpy(objCode, mnemonic);

                if (operand[0] != '\0' && operand[0] != '#')
                {
                    rewind(fp3);
                    while (fscanf(fp3, "%s %s", symLabel, symAddr) != EOF)
                    {
                        if (strcmp(operand, symLabel) == 0)
                        {
                            strcat(objCode, symAddr);
                            break;
                        }
                    }
                }
                else
                {
                    strcat(objCode, "0000");
                }
                break;
            }
        }

        // Handle WORD / BYTE
        if (!found)
        {
            if (strcmp(opcode, "WORD") == 0)
            {
                sprintf(objCode, "%06X", atoi(operand));
            }
            else if (strcmp(opcode, "BYTE") == 0)
            {
                if (operand[0] == 'C')
                {
                    objCode[0] = '\0';
                    for (int i = 2; i < (int)strlen(operand) - 1; i++)
                    {
                        char temp[10];
                        sprintf(temp, "%02X", operand[i]);
                        strcat(objCode, temp);
                    }
                }
                else if (operand[0] == 'X')
                {
                    strncpy(objCode, operand + 2, strlen(operand) - 3);
                    objCode[strlen(operand) - 3] = '\0';
                }
            }
        }

        // Write to output if object code exists
        if (strcmp(objCode, "") != 0)
        {
            fprintf(fp4, "T^%06X^%02X^%s\n", locctr, (int)strlen(objCode) / 2, objCode);
        }

        locctr += (int)strlen(objCode) / 2;

        fscanf(fp1, "%s %s %s %s", addr, label, opcode, operand);
    }

    fprintf(fp4, "E^%06X\n", start);

    fclose(fp4);
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);
    fclose(fp5);
}

void display()
{
    int ch;
    FILE *fp1, *fp2, *fp3;

    printf("\nThe contents of Input Table :\n\n");
    fp1 = fopen("input.txt", "r");
    if (fp1)
    {
        while ((ch = fgetc(fp1)) != EOF)
            printf("%c", ch);
        fclose(fp1);
    }
    else
    {
        printf("Error opening input.txt!\n");
    }

    printf("\n\nThe contents of Output Table :\n\n");
    fp2 = fopen("output.txt", "r");
    if (fp2)
    {
        while ((ch = fgetc(fp2)) != EOF)
            printf("%c", ch);
        fclose(fp2);
    }
    else
    {
        printf("Error opening output.txt!\n");
    }

    printf("\n\nThe contents of Symbol Table :\n\n");
    fp3 = fopen("symtab.txt", "r");
    if (fp3)
    {
        while ((ch = fgetc(fp3)) != EOF)
            printf("%c", ch);
        fclose(fp3);
    }
    else
    {
        printf("Error opening symtab.txt!\n");
    }
}
