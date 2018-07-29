#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "functions.h"

#define REGISTERSNUMBER 31

//Función encargada de remover todos los espacios de un string
//Entradas: String
//Salidas: String sin espacios
void removeSpaces(char *str)
{
    int count = 0;


    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];

    str[count] = '\0';
}

//Función encargada de leer todas las lineas del archivo con el nombre que contenga la variable fp_source_name_1
//Entradas: String
//Salidas: Arreglo de arreglos de strings (Instrucciones o Lineas de control)
char*** readData(char* fp_source_name_1)
{
	FILE *fp = NULL;
	int size = 0;
	int count = 0;
	int linesNumber = 0;
	int lineLen = 1;
	char* dataFileChar = NULL;
	char* temp = NULL;
	char* token = NULL;
	char** lines = NULL;
	char* token2 = NULL;
	char* temp2 = NULL;


	fp = fopen (fp_source_name_1, "r" );

    if (fp==NULL)
    {
        printf("No existe archivo con nombre: %s, asegúrese de que se encuentre en el directorio correcto o exista el archivo.\n", fp_source_name_1);
        exit (1);
    }

	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	rewind(fp);

	dataFileChar = malloc(sizeof(char)*(size+1));
	fread(dataFileChar,sizeof(char), size, fp);
	fclose(fp);
    dataFileChar[size] = '\0';
	//Se recorre el char* para encontrar la cantidad de palabras
	for (int i = 0; i < size ; ++i)
	{
		if(dataFileChar[i] == '\n' || dataFileChar[i] == '\0')
		{
			linesNumber++;
		}
	}

	//Se asigna memoria para cada linea dentro del arreglo
	lines = (char**)malloc(sizeof(char*)*(linesNumber+1));

	//Se asigna memoria para cada linea dentro del arreglo
	linesNumber = 0;
	for (int i = 0; i <= size; ++i)
	 {
	 	if(dataFileChar[i] == '\n' || dataFileChar[i] == '\0')
		{
			lines[linesNumber] = malloc(sizeof(char)*(lineLen));
			linesNumber++;
			lineLen = 1;
		}

		else if(dataFileChar[i] != '\n')
		{
			lineLen++;;
		}
	}

	//Se separan las palabras por \n
	temp = malloc(sizeof(char)*(size+1));
	strcpy(temp,dataFileChar);
	token = strtok(temp, "\n");

	while(token != NULL)
	{
		lines[count] = token;
        lines[count][strlen(token)-1] = '\0';
		token = strtok(NULL, "\n");
		count++;
	}

	char*** registers = malloc(sizeof(char**)*(linesNumber+1));
	char** reg = NULL;
    count = 1;
    char* linesNumberStr = malloc(sizeof(char)*5);
    sprintf(linesNumberStr, "%d", linesNumber);
    linesNumberStr[strlen(linesNumberStr)] = '\0';

    char** linesNumberStrArray = malloc(sizeof(char*)*1);
    linesNumberStrArray[0] = linesNumberStr;
    registers[0] = linesNumberStrArray;
	for (int i = 0; i < linesNumber-1; i++)
	{
		temp2 = malloc(sizeof(char)*(size+1));
		strcpy(temp2,lines[i]);
        token2 = strtok(temp2, " ");
        reg = malloc(sizeof(char*)*(strlen(lines[i])));

        int count2 = 1;
		while(token2 != NULL)
		{
            if (token2 == NULL) {
                break;
            }
            char * variable = malloc(sizeof(char)*(strlen(token2+1)));
            removeSpaces(token2);
            strcpy(variable,token2);
            variable[strlen(variable)] = '\0';
            //printf("%s y count %d\n",variable,count2);
            reg[count2] = variable;
			token2 = strtok(NULL, ",");
            count2++;
		}

        reg[0] = (count2-1) + '0';
		registers[count] = reg;
        count++;
	}

    return registers;
}

//Función encargada de generar un arreglo que contiene todos los registros, con su nombre y valores (inicialmente en 0), respectivamente.
//Entradas: Ninguna.
//Salidas: Arreglo de registros.
reg** populateRegisters()
{
    reg ** registers = malloc(sizeof(reg*)*REGISTERSNUMBER);

    reg * $sp = malloc(sizeof(reg));
    $sp->value = 0;
    $sp->name = malloc(sizeof(char)*7);
    strcpy($sp->name,"$sp\0");
    registers[0] = $sp;

    reg * $at = malloc(sizeof(reg));
    $at->value = 0;
    $at->name = malloc(sizeof(char)*7);
    strcpy($at->name,"$at\0");
    registers[1] = $at;

    reg * $fp = malloc(sizeof(reg));
    $fp->value = 0;
    $fp->name = malloc(sizeof(char)*7);
    strcpy($fp->name,"$fp\0");
    registers[2] = $fp;

    reg * $v0 = malloc(sizeof(reg));
    $v0->value = 0;
    $v0->name = malloc(sizeof(char)*7);
    strcpy($v0->name,"$v0\0");
    registers[3] = $v0;

    reg * $v1 = malloc(sizeof(reg));
    $v1->value = 0;
    $v1->name = malloc(sizeof(char)*7);
    strcpy($v1->name,"$v1\0");
    registers[4] = $v1;

    reg * $a0 = malloc(sizeof(reg));
    $a0->value = 0;
    $a0->name = malloc(sizeof(char)*7);
    strcpy($a0->name,"$a0\0");
    registers[5] = $a0;

    reg * $a1 = malloc(sizeof(reg));
    $a1->value = 0;
    $a1->name = malloc(sizeof(char)*7);
    strcpy($a1->name,"$a1\0");
    registers[6] = $a1;

    reg * $a2 = malloc(sizeof(reg));
    $a2->value = 0;
    $a2->name = malloc(sizeof(char)*7);
    strcpy($a2->name,"$a2\0");
    registers[7] = $a2;

    reg * $a3 = malloc(sizeof(reg));
    $a3->value = 0;
    $a3->name = malloc(sizeof(char)*7);
    strcpy($a3->name,"$a3\0");
    registers[8] = $a3;

    reg * $t0 = malloc(sizeof(reg));
    $t0->value = 0;
    $t0->name = malloc(sizeof(char)*7);
    strcpy($t0->name,"$t0\0");
    registers[9] = $t0;

    reg * $t1 = malloc(sizeof(reg));
    $t1->value = 0;
    $t1->name = malloc(sizeof(char)*7);
    strcpy($t1->name,"$t1\0");
    registers[10] = $t1;

    reg * $t2 = malloc(sizeof(reg));
    $t2->value = 0;
    $t2->name = malloc(sizeof(char)*7);
    strcpy($t2->name,"$t2\0");
    registers[11] = $t2;

    reg * $t3 = malloc(sizeof(reg));
    $t3->value = 0;
    $t3->name = malloc(sizeof(char)*7);
    strcpy($t3->name,"$t3\0");
    registers[12] = $t3;

    reg * $t4 = malloc(sizeof(reg));
    $t4->value = 0;
    $t4->name = malloc(sizeof(char)*7);
    strcpy($t4->name,"$t4\0");
    registers[13] = $t4;

    reg * $t5 = malloc(sizeof(reg));
    $t5->value = 0;
    $t5->name = malloc(sizeof(char)*7);
    strcpy($t5->name,"$t5\0");
    registers[14] = $t5;

    reg * $t6 = malloc(sizeof(reg));
    $t6->value = 0;
    $t6->name = malloc(sizeof(char)*7);
    strcpy($t6->name,"$t6\0");
    registers[15] = $t6;

    reg * $t7 = malloc(sizeof(reg));
    $t7->value = 0;
    $t7->name = malloc(sizeof(char)*7);
    strcpy($t7->name,"$t7\0");
    registers[16] = $t7;

    reg * $t8 = malloc(sizeof(reg));
    $t8->value = 0;
    $t8->name = malloc(sizeof(char)*7);
    strcpy($t8->name,"$t8\0");
    registers[17] = $t8;

    reg * $t9 = malloc(sizeof(reg));
    $t9->value = 0;
    $t9->name = malloc(sizeof(char)*7);
    strcpy($t9->name,"$t9\0");
    registers[18] = $t9;

    reg * $s0 = malloc(sizeof(reg));
    $s0->value = 0;
    $s0->name = malloc(sizeof(char)*7);
    strcpy($s0->name,"$s0\0");
    registers[19] = $s0;

    reg * $s1 = malloc(sizeof(reg));
    $s1->value = 0;
    $s1->name = malloc(sizeof(char)*7);
    strcpy($s1->name,"$s1\0");
    registers[20] = $s1;

    reg * $s2 = malloc(sizeof(reg));
    $s2->value = 0;
    $s2->name = malloc(sizeof(char)*7);
    strcpy($s2->name,"$s2\0");
    registers[21] = $s2;

    reg * $s3 = malloc(sizeof(reg));
    $s3->value = 0;
    $s3->name = malloc(sizeof(char)*7);
    strcpy($s3->name,"$s3\0");
    registers[22] = $s3;

    reg * $s4 = malloc(sizeof(reg));
    $s4->value = 0;
    $s4->name = malloc(sizeof(char)*7);
    strcpy($s4->name,"$s4\0");
    registers[23] = $s4;

    reg * $s5 = malloc(sizeof(reg));
    $s5->value = 0;
    $s5->name = malloc(sizeof(char)*7);
    strcpy($s5->name,"$s5\0");
    registers[24] = $s5;

    reg * $s6 = malloc(sizeof(reg));
    $s6->value = 0;
    $s6->name = malloc(sizeof(char)*7);
    strcpy($s6->name,"$s6\0");
    registers[25] = $s6;

    reg * $s7 = malloc(sizeof(reg));
    $s7->value = 0;
    $s7->name = malloc(sizeof(char)*7);
    strcpy($s7->name,"$s7\0");
    registers[26] = $s7;

    reg * $k0 = malloc(sizeof(reg));
    $k0->value = 0;
    $k0->name = malloc(sizeof(char)*7);
    strcpy($k0->name,"$k0\0");
    registers[27] = $k0;

    reg * $k1 = malloc(sizeof(reg));
    $k1->value = 0;
    $k1->name = malloc(sizeof(char)*7);
    strcpy($k1->name,"$k1\0");
    registers[28] = $k1;

    reg * $gp = malloc(sizeof(reg));
    $gp->value = 0;
    $gp->name = malloc(sizeof(char)*7);
    strcpy($gp->name,"$gp\0");
    registers[29] = $gp;

    reg * $zero = malloc(sizeof(reg));
    $zero->value = 0;
    $zero->name = malloc(sizeof(char)*7);
    strcpy($zero->name,"$zero\0");
    registers[30] = $zero;

    return registers;
}

void writePipeline(bufferIF_ID * buffIF_ID,bufferID_EX * buffID_EX,bufferEX_MEM * buffEX_MEM,bufferMEM_WB * buffMEM_WB, bufferMWB_END * buffMWB_END, bool* created_2, int option, int cycle, int *PC, char *** instructions)
{
    if (*created_2 == false)
    {
        FILE *fp;
        fp=fopen("file1.csv", "w");

        if(fp == NULL)
        {
            printf("Error al crear el archivo %s\n","fp_output_name_2");
            exit(1);
        }
        fprintf(fp,"Ciclo, Fetch , Identification, Execution, Memory, WriteBack,\n");
        fprintf(fp,"%d,",cycle);
        if ((strcmp(buffIF_ID->instruction_2[1],"j") == 0 || strcmp(buffIF_ID->instruction_2[1],"J") == 0) )
        {
            fprintf(fp, "%s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[1]);
        }

        if ((strcmp(buffIF_ID->instruction_2[1],"subi") == 0 || strcmp(buffIF_ID->instruction_2[1],"sub") == 0 ||
            strcmp(buffIF_ID->instruction_2[1],"add") == 0  || strcmp(buffIF_ID->instruction_2[1],"addi") == 0 ||
            strcmp(buffIF_ID->instruction_2[1],"mul") == 0  || strcmp(buffIF_ID->instruction_2[1],"div") == 0||
            strcmp(buffIF_ID->instruction_2[1],"beq") == 0) )
        {
            fprintf(fp, "%s %s %s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2],buffIF_ID->instruction_2[3],buffIF_ID->instruction_2[4]);
        }

        if ((strcmp(buffIF_ID->instruction_2[1],"sw") == 0 || strcmp(buffIF_ID->instruction_2[1],"lw") == 0) )
        {
            fprintf(fp, "%s %s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2],buffIF_ID->instruction_2[3]);
        }

        fprintf(fp, "\n");
        *created_2 = true;
        fclose(fp);

    }

    else
    {
        FILE *fp;
        fp=fopen("file1.csv", "a");

        if(fp == NULL)
        {
            printf("Error al crear el archivo %s\n", "fp_output_name_2");
            exit(1);
        }

        switch (option)
        {
            case 2:
                fprintf(fp,"%d,",cycle);

                if ((strcmp(buffIF_ID->instruction_2[1],"j") == 0 || strcmp(buffIF_ID->instruction_2[1],"J") == 0))
                {
                    fprintf(fp, "%s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2]);
                }

                if ((strcmp(buffIF_ID->instruction_2[1],"subi") == 0 || strcmp(buffIF_ID->instruction_2[1],"sub") == 0 ||
                    strcmp(buffIF_ID->instruction_2[1],"add") == 0  || strcmp(buffIF_ID->instruction_2[1],"addi") == 0 ||
                    strcmp(buffIF_ID->instruction_2[1],"mul") == 0  || strcmp(buffIF_ID->instruction_2[1],"div") == 0||
                    strcmp(buffIF_ID->instruction_2[1],"beq") == 0))
                {
                    fprintf(fp, "%s %s %s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2],buffIF_ID->instruction_2[3],buffIF_ID->instruction_2[4]);
                }

                if ((strcmp(buffIF_ID->instruction_2[1],"sw") == 0 || strcmp(buffIF_ID->instruction_2[1],"lw") == 0))
                {
                    fprintf(fp, "%s %s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2],buffIF_ID->instruction_2[3]);
                }

                ///////////////////////

                if ((strcmp(buffID_EX->instruction_2[1],"j") == 0 || strcmp(buffID_EX->instruction_2[1],"J") == 0) )
                {
                    fprintf(fp, "%s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2]);
                }

                if ((strcmp(buffID_EX->instruction_2[1],"subi") == 0 || strcmp(buffID_EX->instruction_2[1],"sub") == 0 ||
                    strcmp(buffID_EX->instruction_2[1],"add") == 0  || strcmp(buffID_EX->instruction_2[1],"addi") == 0 ||
                    strcmp(buffID_EX->instruction_2[1],"mul") == 0  || strcmp(buffID_EX->instruction_2[1],"div") == 0||
                    strcmp(buffID_EX->instruction_2[1],"beq") == 0) )
                {
                    fprintf(fp, "%s %s %s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2],buffID_EX->instruction_2[3],buffID_EX->instruction_2[4]);
                }

                if ((strcmp(buffID_EX->instruction_2[1],"sw") == 0 || strcmp(buffID_EX->instruction_2[1],"lw") == 0)  )
                {
                    fprintf(fp, "%s %s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2],buffID_EX->instruction_2[3]);
                }

                break;

            case 3:
                fprintf(fp,"%d,",cycle);

                if ((strcmp(buffIF_ID->instruction_2[1],"j") == 0 || strcmp(buffIF_ID->instruction_2[1],"J") == 0))
                {
                    fprintf(fp, "%s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2]);
                }

                if ((strcmp(buffIF_ID->instruction_2[1],"subi") == 0 || strcmp(buffIF_ID->instruction_2[1],"sub") == 0 ||
                    strcmp(buffIF_ID->instruction_2[1],"add") == 0  || strcmp(buffIF_ID->instruction_2[1],"addi") == 0 ||
                    strcmp(buffIF_ID->instruction_2[1],"mul") == 0  || strcmp(buffIF_ID->instruction_2[1],"div") == 0||
                    strcmp(buffIF_ID->instruction_2[1],"beq") == 0))
                {
                    fprintf(fp, "%s %s %s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2],buffIF_ID->instruction_2[3],buffIF_ID->instruction_2[4]);
                }

                if ((strcmp(buffIF_ID->instruction_2[1],"sw") == 0 || strcmp(buffIF_ID->instruction_2[1],"lw") == 0))
                {
                    fprintf(fp, "%s %s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2],buffIF_ID->instruction_2[3]);
                }

                ///////////////////////

                if ((strcmp(buffID_EX->instruction_2[1],"j") == 0 || strcmp(buffID_EX->instruction_2[1],"J") == 0))
                {
                    fprintf(fp, "%s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2]);
                }

                if ((strcmp(buffID_EX->instruction_2[1],"subi") == 0 || strcmp(buffID_EX->instruction_2[1],"sub") == 0 ||
                    strcmp(buffID_EX->instruction_2[1],"add") == 0  || strcmp(buffID_EX->instruction_2[1],"addi") == 0 ||
                    strcmp(buffID_EX->instruction_2[1],"mul") == 0  || strcmp(buffID_EX->instruction_2[1],"div") == 0||
                    strcmp(buffID_EX->instruction_2[1],"beq") == 0))
                {
                    fprintf(fp, "%s %s %s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2],buffID_EX->instruction_2[3],buffID_EX->instruction_2[4]);
                }

                if ((strcmp(buffID_EX->instruction_2[1],"sw") == 0 || strcmp(buffID_EX->instruction_2[1],"lw") == 0))
                {
                    fprintf(fp, "%s %s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2],buffID_EX->instruction_2[3]);
                }

                /////////////////////////

                if ((strcmp(buffEX_MEM->instruction_2[1],"j") == 0 || strcmp(buffEX_MEM->instruction_2[1],"J") == 0) )
                {
                    fprintf(fp, "%s %s,",buffEX_MEM->instruction_2[1],buffEX_MEM->instruction_2[2]);
                }

                if ((strcmp(buffEX_MEM->instruction_2[1],"subi") == 0 || strcmp(buffEX_MEM->instruction_2[1],"sub") == 0 ||
                    strcmp(buffEX_MEM->instruction_2[1],"add") == 0  || strcmp(buffEX_MEM->instruction_2[1],"addi") == 0 ||
                    strcmp(buffEX_MEM->instruction_2[1],"mul") == 0  || strcmp(buffEX_MEM->instruction_2[1],"div") == 0||
                    strcmp(buffEX_MEM->instruction_2[1],"beq") == 0) )
                {
                    fprintf(fp, "%s %s %s %s,",buffEX_MEM->instruction_2[1],buffEX_MEM->instruction_2[2],buffEX_MEM->instruction_2[3],buffEX_MEM->instruction_2[4]);
                }

                if ((strcmp(buffEX_MEM->instruction_2[1],"sw") == 0 || strcmp(buffEX_MEM->instruction_2[1],"lw") == 0) )
                {
                    fprintf(fp, "%s %s %s,",buffEX_MEM->instruction_2[1],buffEX_MEM->instruction_2[2],buffEX_MEM->instruction_2[3]);
                }

                break;

            case 4:
                fprintf(fp,"%d,",cycle);
                if ((strcmp(buffIF_ID->instruction_2[1],"j") == 0 || strcmp(buffIF_ID->instruction_2[1],"J") == 0))
                {
                    fprintf(fp, "%s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2]);
                }

                if ((strcmp(buffIF_ID->instruction_2[1],"subi") == 0 || strcmp(buffIF_ID->instruction_2[1],"sub") == 0 ||
                    strcmp(buffIF_ID->instruction_2[1],"add") == 0  || strcmp(buffIF_ID->instruction_2[1],"addi") == 0 ||
                    strcmp(buffIF_ID->instruction_2[1],"mul") == 0  || strcmp(buffIF_ID->instruction_2[1],"div") == 0||
                    strcmp(buffIF_ID->instruction_2[1],"beq") == 0))
                {
                    fprintf(fp, "%s %s %s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2],buffIF_ID->instruction_2[3],buffIF_ID->instruction_2[4]);
                }

                if ((strcmp(buffIF_ID->instruction_2[1],"sw") == 0 || strcmp(buffIF_ID->instruction_2[1],"lw") == 0))
                {
                    fprintf(fp, "%s %s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2],buffIF_ID->instruction_2[3]);
                }


                ///////////////////////

                if ((strcmp(buffID_EX->instruction_2[1],"j") == 0 || strcmp(buffID_EX->instruction_2[1],"J") == 0)  )
                {
                    fprintf(fp, "%s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2]);
                }

                if ((strcmp(buffID_EX->instruction_2[1],"subi") == 0 || strcmp(buffID_EX->instruction_2[1],"sub") == 0 ||
                    strcmp(buffID_EX->instruction_2[1],"add") == 0  || strcmp(buffID_EX->instruction_2[1],"addi") == 0 ||
                    strcmp(buffID_EX->instruction_2[1],"mul") == 0  || strcmp(buffID_EX->instruction_2[1],"div") == 0||
                    strcmp(buffID_EX->instruction_2[1],"beq") == 0) )
                {
                    fprintf(fp, "%s %s %s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2],buffID_EX->instruction_2[3],buffID_EX->instruction_2[4]);
                }

                if ((strcmp(buffID_EX->instruction_2[1],"sw") == 0 || strcmp(buffID_EX->instruction_2[1],"lw") == 0)  )
                {
                    fprintf(fp, "%s %s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2],buffID_EX->instruction_2[3]);
                }

                /////////////////////////

                if ((strcmp(buffEX_MEM->instruction_2[1],"j") == 0 || strcmp(buffEX_MEM->instruction_2[1],"J") == 0) )
                {
                    fprintf(fp, "%s %s,",buffEX_MEM->instruction_2[1],buffEX_MEM->instruction_2[2]);
                }

                if ((strcmp(buffEX_MEM->instruction_2[1],"subi") == 0 || strcmp(buffEX_MEM->instruction_2[1],"sub") == 0 ||
                    strcmp(buffEX_MEM->instruction_2[1],"add") == 0  || strcmp(buffEX_MEM->instruction_2[1],"addi") == 0 ||
                    strcmp(buffEX_MEM->instruction_2[1],"mul") == 0  || strcmp(buffEX_MEM->instruction_2[1],"div") == 0||
                    strcmp(buffEX_MEM->instruction_2[1],"beq") == 0) )
                {
                    fprintf(fp, "%s %s %s %s,",buffEX_MEM->instruction_2[1],buffEX_MEM->instruction_2[2],buffEX_MEM->instruction_2[3],buffEX_MEM->instruction_2[4]);
                }

                if ((strcmp(buffEX_MEM->instruction_2[1],"sw") == 0 || strcmp(buffEX_MEM->instruction_2[1],"lw")) == 0 )
                {
                    fprintf(fp, "%s %s %s,",buffEX_MEM->instruction_2[1],buffEX_MEM->instruction_2[2],buffEX_MEM->instruction_2[3]);
                }


                /////////////////////////

                if ((strcmp(buffMEM_WB->instruction_2[1],"j") == 0 || strcmp(buffMEM_WB->instruction_2[1],"J") == 0) )
                {
                    fprintf(fp, "%s %s,",buffMEM_WB->instruction_2[1],buffMEM_WB->instruction_2[2]);
                }

                if ((strcmp(buffMEM_WB->instruction_2[1],"subi") == 0 || strcmp(buffMEM_WB->instruction_2[1],"sub") == 0 ||
                    strcmp(buffMEM_WB->instruction_2[1],"add") == 0  || strcmp(buffMEM_WB->instruction_2[1],"addi") == 0 ||
                    strcmp(buffMEM_WB->instruction_2[1],"mul") == 0  || strcmp(buffMEM_WB->instruction_2[1],"div") == 0||
                    strcmp(buffMEM_WB->instruction_2[1],"beq") == 0))
                {
                    fprintf(fp, "%s %s %s %s,",buffMEM_WB->instruction_2[1],buffMEM_WB->instruction_2[2],buffMEM_WB->instruction_2[3],buffMEM_WB->instruction_2[4]);
                }

                if ((strcmp(buffMEM_WB->instruction_2[1],"sw") == 0 || strcmp(buffMEM_WB->instruction_2[1],"lw") == 0))
                {
                    fprintf(fp, "%s %s %s,",buffMEM_WB->instruction_2[1],buffMEM_WB->instruction_2[2],buffMEM_WB->instruction_2[3]);
                }

                break;

            case 5:
                fprintf(fp,"%d,",cycle);
                printf("Soy PC %d %d \n", *PC, atoi(instructions[0][0]));
                if (*PC >= atoi(instructions[0][0]) + 1)
                {
                    fprintf(fp, " ,");
                }

                else
                {
                    if ((strcmp(buffIF_ID->instruction_2[1],"j") == 0 || strcmp(buffIF_ID->instruction_2[1],"J") == 0))
                    {
                        fprintf(fp, "%s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2]);
                    }

                    if ((strcmp(buffIF_ID->instruction_2[1],"subi") == 0 || strcmp(buffIF_ID->instruction_2[1],"sub") == 0 ||
                        strcmp(buffIF_ID->instruction_2[1],"add") == 0  || strcmp(buffIF_ID->instruction_2[1],"addi") == 0 ||
                        strcmp(buffIF_ID->instruction_2[1],"mul") == 0  || strcmp(buffIF_ID->instruction_2[1],"div") == 0||
                        strcmp(buffIF_ID->instruction_2[1],"beq") == 0))
                    {
                        fprintf(fp, "%s %s %s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2],buffIF_ID->instruction_2[3],buffIF_ID->instruction_2[4]);
                    }

                    if ((strcmp(buffIF_ID->instruction_2[1],"sw") == 0 || strcmp(buffIF_ID->instruction_2[1],"lw") == 0))
                    {
                        fprintf(fp, "%s %s %s,",buffIF_ID->instruction_2[1],buffIF_ID->instruction_2[2],buffIF_ID->instruction_2[3]);
                    }

                }

                ///////////////////////

                if (*PC >= atoi(instructions[0][0]) + 2)
                {
                    fprintf(fp, " ,");
                }

                else
                {
                    if ((strcmp(buffID_EX->instruction_2[1],"j") == 0 || strcmp(buffID_EX->instruction_2[1],"J") == 0) )
                    {
                        fprintf(fp, "%s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2]);
                    }

                    if ((strcmp(buffID_EX->instruction_2[1],"subi") == 0 || strcmp(buffID_EX->instruction_2[1],"sub") == 0 ||
                        strcmp(buffID_EX->instruction_2[1],"add") == 0  || strcmp(buffID_EX->instruction_2[1],"addi") == 0 ||
                        strcmp(buffID_EX->instruction_2[1],"mul") == 0  || strcmp(buffID_EX->instruction_2[1],"div") == 0||
                        strcmp(buffID_EX->instruction_2[1],"beq") == 0))
                    {
                        fprintf(fp, "%s %s %s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2],buffID_EX->instruction_2[3],buffID_EX->instruction_2[4]);
                    }

                    if ((strcmp(buffID_EX->instruction_2[1],"sw") == 0 || strcmp(buffID_EX->instruction_2[1],"lw") == 0) )
                    {
                        fprintf(fp, "%s %s %s,",buffID_EX->instruction_2[1],buffID_EX->instruction_2[2],buffID_EX->instruction_2[3]);
                    }
                }


                /////////////////////////

                if (*PC >= atoi(instructions[0][0]) + 3)
                {
                    fprintf(fp, " ,");
                }

                else
                {
                    if ((strcmp(buffEX_MEM->instruction_2[1],"j") == 0 || strcmp(buffEX_MEM->instruction_2[1],"J") == 0))
                    {
                        fprintf(fp, "%s %s,",buffEX_MEM->instruction_2[1],buffEX_MEM->instruction_2[2]);
                    }

                    if ((strcmp(buffEX_MEM->instruction_2[1],"subi") == 0 || strcmp(buffEX_MEM->instruction_2[1],"sub") == 0 ||
                        strcmp(buffEX_MEM->instruction_2[1],"add") == 0  || strcmp(buffEX_MEM->instruction_2[1],"addi") == 0 ||
                        strcmp(buffEX_MEM->instruction_2[1],"mul") == 0  || strcmp(buffEX_MEM->instruction_2[1],"div") == 0||
                        strcmp(buffEX_MEM->instruction_2[1],"beq") == 0))
                    {
                        fprintf(fp, "%s %s %s %s,",buffEX_MEM->instruction_2[1],buffEX_MEM->instruction_2[2],buffEX_MEM->instruction_2[3],buffEX_MEM->instruction_2[4]);
                    }

                    if ((strcmp(buffEX_MEM->instruction_2[1],"sw") == 0 || strcmp(buffEX_MEM->instruction_2[1],"lw") == 0))
                    {
                        fprintf(fp, "%s %s %s,",buffEX_MEM->instruction_2[1],buffEX_MEM->instruction_2[2],buffEX_MEM->instruction_2[3]);
                    }

                }

                /////////////////////////

                if (*PC >= atoi(instructions[0][0]) + 4)
                {
                    fprintf(fp, " ,");
                }

                else
                {
                    if ((strcmp(buffMEM_WB->instruction_2[1],"j") == 0 || strcmp(buffMEM_WB->instruction_2[1],"J") == 0) )
                    {
                        fprintf(fp, "%s %s,",buffMEM_WB->instruction_2[1],buffMEM_WB->instruction_2[2]);
                    }

                    if ((strcmp(buffMEM_WB->instruction_2[1],"subi") == 0 || strcmp(buffMEM_WB->instruction_2[1],"sub") == 0 ||
                        strcmp(buffMEM_WB->instruction_2[1],"add") == 0  || strcmp(buffMEM_WB->instruction_2[1],"addi") == 0 ||
                        strcmp(buffMEM_WB->instruction_2[1],"mul") == 0  || strcmp(buffMEM_WB->instruction_2[1],"div") == 0||
                        strcmp(buffMEM_WB->instruction_2[1],"beq") == 0))
                    {
                        fprintf(fp, "%s %s %s %s,",buffMEM_WB->instruction_2[1],buffMEM_WB->instruction_2[2],buffMEM_WB->instruction_2[3],buffMEM_WB->instruction_2[4]);
                    }

                    if ((strcmp(buffMEM_WB->instruction_2[1],"sw") == 0 || strcmp(buffMEM_WB->instruction_2[1],"lw") == 0))

                    {
                        fprintf(fp, "%s %s %s,",buffMEM_WB->instruction_2[1],buffMEM_WB->instruction_2[2],buffMEM_WB->instruction_2[3]);
                    }
                }


                ///////////////////////////

                if (*PC >= atoi(instructions[0][0]) + 5)
                {
                    fprintf(fp, " ,");
                }
                else
                {
                    if ((strcmp(buffMWB_END->instruction_2[1],"j") == 0 || strcmp(buffMWB_END->instruction_2[1],"J") == 0))
                    {
                        fprintf(fp, "%s %s,",buffMWB_END->instruction_2[1],buffMWB_END->instruction_2[2]);
                    }

                    if ((strcmp(buffMWB_END->instruction_2[1],"subi") == 0 || strcmp(buffMWB_END->instruction_2[1],"sub") == 0 ||
                        strcmp(buffMWB_END->instruction_2[1],"add") == 0  || strcmp(buffMWB_END->instruction_2[1],"addi") == 0 ||
                        strcmp(buffMWB_END->instruction_2[1],"mul") == 0  || strcmp(buffMWB_END->instruction_2[1],"div") == 0||
                        strcmp(buffMWB_END->instruction_2[1],"beq") == 0) )
                    {
                        fprintf(fp, "%s %s %s %s,",buffMWB_END->instruction_2[1],buffMWB_END->instruction_2[2],buffMWB_END->instruction_2[3],buffMWB_END->instruction_2[4]);
                    }

                    if ((strcmp(buffMWB_END->instruction_2[1],"sw") == 0 || strcmp(buffMWB_END->instruction_2[1],"lw") == 0) )
                    {
                        fprintf(fp, "%s %s %s,",buffMWB_END->instruction_2[1],buffMWB_END->instruction_2[2],buffMWB_END->instruction_2[3]);
                    }

                }

                break;
        }

        fprintf(fp, "\n");

        fclose(fp);
    }
}

void fetch(bufferIF_ID* buffIF_ID, char*** instructions, int* PC)
{
    if (buffIF_ID->status == false)
    {
        *PC+=1;
    }

    else
    {
        printf("%s\n","///////////////////// Inicio Fetch /////////////////////////" );
        int lenInstruction = instructions[*PC][0] - '0';
        buffIF_ID->instruction_1 = malloc(sizeof(char*)*(lenInstruction+2));
        buffIF_ID->instruction_1[0] = instructions[*PC][0];
        buffIF_ID->instruction_2 = malloc(sizeof(char*)*(lenInstruction+2));
        memcpy(buffIF_ID->instruction_2, instructions[*PC], sizeof(char*)*(lenInstruction+2));

        // lw $t0 $t1 1000 = lw $t0 1000($t1)
        if (strcmp(instructions[*PC][1],"sw") == 0 || strcmp(instructions[*PC][1],"lw") == 0 )
        {
            buffIF_ID->instruction_1 = malloc(sizeof(char*)*(lenInstruction+3));
            buffIF_ID->instruction_1[0] = (lenInstruction+1) + '0';

            char * offset_variable = malloc(sizeof(char)*5);
            char * offset_number = malloc(sizeof(char)*5);

            char* token;
            char * aux = malloc(sizeof(char)*strlen(instructions[*PC][3]));
            strcpy(aux,instructions[*PC][3]);
            token = strtok(aux,"(");
            strcpy(offset_number,token);
            token = strtok(NULL,")");
            strcpy(offset_variable,token);
            buffIF_ID->instruction_1[1] = instructions[*PC][1];
            buffIF_ID->instruction_1[2] = instructions[*PC][2];
            buffIF_ID->instruction_1[3] = offset_variable;
            buffIF_ID->instruction_1[4] = offset_number;
        }

        else
        {
            for (int i = 1; i <= lenInstruction; i++)
            {
                buffIF_ID->instruction_1[i] = malloc(sizeof(char)*(5));
                buffIF_ID->instruction_1[i] = instructions[*PC][i];
            }
        }

        *PC+=1;


        if (*PC == atoi(instructions[0][0]))
        {
            buffIF_ID->status = false;
        }

        if ( (strcmp(buffIF_ID->instruction_1[1], "end:") == 0))
        {
            //printf("%c\n", buffIF_ID->instruction_1[0]);
            printf("%s\n", buffIF_ID->instruction_1[1]);
            printf("\n");
        }

        else if((strcmp(buffIF_ID->instruction_1[1],"j") == 0))
        {
            //printf("%c\n", buffIF_ID->instruction_1[0]);
            printf("%s\n", buffIF_ID->instruction_1[1]);
            printf("%s\n", buffIF_ID->instruction_1[2]);
            printf("\n");

        }

        else
        {
            //printf("%c\n", buffIF_ID->instruction_1[0]);
            printf("%s\n", buffIF_ID->instruction_1[1]);
            printf("%s\n", buffIF_ID->instruction_1[2]);
            printf("%s\n", buffIF_ID->instruction_1[3]);
            printf("%s\n", buffIF_ID->instruction_1[4]);

            printf("\n");
        }
        printf("%s\n\n","///////////////////// Fin Fetch /////////////////////////" );
    }
}

void identification(bufferIF_ID* buffIF_ID, bufferID_EX* buffID_EX, reg** registersMemory, char*** instructions, int*PC)
{
    if (buffID_EX->status == false)
    {
    }

    else
    {
        printf("%s\n","///////////////////// Inicio Identification /////////////////////////" );

        int lenInstruction = buffIF_ID->instruction_1[0] - '0';
        buffID_EX->instruction_1 = malloc(sizeof(char*)*(lenInstruction+1));
        buffID_EX->instruction_2 = malloc(sizeof(char*)*(lenInstruction+1));
        memcpy(buffID_EX->instruction_2, buffIF_ID->instruction_2, sizeof(char*)*(lenInstruction+1));
        memcpy(buffID_EX->instruction_1, buffIF_ID->instruction_1, sizeof(char*)*(lenInstruction+1));

        //Listo
        if (strcmp(buffIF_ID->instruction_1[1],"sub") == 0 || strcmp(buffIF_ID->instruction_1[1],"subi") == 0 ||
            strcmp(buffIF_ID->instruction_1[1],"add") == 0 || strcmp(buffIF_ID->instruction_1[1],"addi") == 0 ||
            strcmp(buffIF_ID->instruction_1[1],"mul") == 0 || strcmp(buffIF_ID->instruction_1[1],"div") == 0)
        {
            int j;

            //Se recorren la memoria de registros
            for (j = 0; j < REGISTERSNUMBER; j++)
            {
                //Se verifica si la segunda variable de la instrucción existe
                //En caso de hacerlo, se toma su valor de memoria
                if (strcmp(buffIF_ID->instruction_1[3],registersMemory[j]->name) == 0)
                {
                    buffID_EX->instruction_1[3] = registersMemory[j]->value + "0";
                    break;
                }
            }

            //En caso de que no exista la segunda variable en memoria, error.
            if (j == REGISTERSNUMBER)
            {
                printf("%s\n","Error holaaaa2");
                exit(1);
            }

            //Se recorren la memoria de registros
            for (j = 0; j < REGISTERSNUMBER; j++)
            {
                //Se verifica si la tercera variable de la instrucción existe
                //En caso de hacerlo, se toma su valor de memoria
                if (strcmp(buffIF_ID->instruction_1[4],registersMemory[j]->name) == 0)
                {
                    buffID_EX->instruction_1[4] = registersMemory[j]->value + "0";
                    break;
                }
            }

            //En caso de que no exista la tercera variable en memoria
            if (j == REGISTERSNUMBER)
            {
                //Si la instrucción es subi, entonces se toma el número de la instrucción
                if (strcmp(buffIF_ID->instruction_1[1],"subi") == 0 || strcmp(buffIF_ID->instruction_1[1],"addi") == 0 )
                {
                    buffID_EX->instruction_1[4] = buffIF_ID->instruction_1[4];
                }

                else
                {
                    exit(1);
                }
            }

            //Se recorren la memoria de registros
            for (j = 0; j < REGISTERSNUMBER; j++)
            {
                //Se verifica si la segunda variable de la instrucción existe
                //En caso de hacerlo, se toma su valor de memoria
                if (strcmp(buffIF_ID->instruction_1[2],registersMemory[j]->name) == 0)
                {
                    break;
                }
            }

            //En caso de que no exista la segunda variable en memoria, error.
            if (j == REGISTERSNUMBER)
            {
                printf("%s\n","Error 3");
                exit(1);
            }
        }

        //Listo
        else if(strcmp(buffIF_ID->instruction_1[1],"sw") == 0)
        {
            int j;

            //Se recorren la memoria de registros
            for (j = 0; j < REGISTERSNUMBER; j++)
            {
                //Se verifica si la segunda variable de la instrucción existe
                //En caso de hacerlo, se toma su valor de memoria
                if (strcmp(buffIF_ID->instruction_1[2],registersMemory[j]->name) == 0)
                {
                    break;
                }
            }

            if (j == REGISTERSNUMBER)
            {
                exit(1);
            }

            //Se recorren la memoria de registros
            for (j = 0; j < REGISTERSNUMBER; j++)
            {
                //Se verifica si la segunda variable de la instrucción existe
                //En caso de hacerlo, se toma su valor de memoria
                if (strcmp(buffIF_ID->instruction_1[3],registersMemory[j]->name) == 0)
                {

                    buffID_EX->instruction_1[3] = registersMemory[j]->value + "0";
                    break;
                }
            }

            if (j == REGISTERSNUMBER)
            {
                exit(1);
            }
        }

        //Listo
        else if (strcmp(buffIF_ID->instruction_1[1],"lw") == 0)
        {
            int j;
            //Se recorren la memoria de registros
            for (j = 0; j < REGISTERSNUMBER; j++)
            {
                //Se verifica si la segunda variable de la instrucción existe
                //En caso de hacerlo, se toma su valor de memoria
                if (strcmp(buffIF_ID->instruction_1[3],registersMemory[j]->name) == 0)
                {

                    buffID_EX->instruction_1[3] = registersMemory[j]->value + "0";
                    break;
                }
            }

            if (j == REGISTERSNUMBER)
            {
                exit(1);
            }


            //Se recorren la memoria de registros
            for (j = 0; j < REGISTERSNUMBER; j++)
            {
                //Se verifica si la segunda variable de la instrucción existe
                //En caso de hacerlo, se toma su valor de memoria
                if (strcmp(buffIF_ID->instruction_1[2],registersMemory[j]->name) == 0)
                {

                }
            }

            if (j == REGISTERSNUMBER)
            {
                exit(1);
            }
        }

        //Lineas de control
        if (strcmp(buffIF_ID->instruction_1[1], "add") == 0 || strcmp(buffIF_ID->instruction_1[1], "addi") == 0 ||
            strcmp(buffIF_ID->instruction_1[1], "sub") == 0 || strcmp(buffIF_ID->instruction_1[1], "subi") == 0 ||
            strcmp(buffIF_ID->instruction_1[1], "mul") == 0 || strcmp(buffIF_ID->instruction_1[1], "div") == 0 )
        {
            buffID_EX->AluSrc = '0';
            buffID_EX->AluOp_0 = '0';
            buffID_EX->AluOp_1 = '1';
            buffID_EX->RegDst = '1';

            buffID_EX->Branch = '0';
            buffID_EX->Jump = '0';
            buffID_EX->MemWrite = '0';
            buffID_EX->MemRead = '0';

            buffID_EX->MemToreg = '0';
            buffID_EX->RegWrite = '1';
        }

        else if (strcmp(buffIF_ID->instruction_1[1], "j") == 0)
        {
            buffID_EX->AluSrc = '0';
            buffID_EX->AluOp_0 = '0';
            buffID_EX->AluOp_1 = '1';
            buffID_EX->RegDst = 'x';

            buffID_EX->Branch = '0';
            buffID_EX->Jump = '1';
            buffID_EX->MemWrite = '0';
            buffID_EX->MemRead = '0';

            buffID_EX->MemToreg = 'x';
            buffID_EX->RegWrite = '0';
        }

        else if (strcmp(buffIF_ID->instruction_1[1], "beq") == 0)
        {
            buffID_EX->AluSrc = '0';
            buffID_EX->AluOp_0 = '0';
            buffID_EX->AluOp_1 = '1';
            buffID_EX->RegDst = 'x';

            buffID_EX->Branch = '1';
            buffID_EX->Jump = '0';
            buffID_EX->MemWrite = '0';
            buffID_EX->MemRead = '0';

            buffID_EX->MemToreg = 'x';
            buffID_EX->RegWrite = '0';
        }

        else if (strcmp(buffIF_ID->instruction_1[1], "sw") == 0)
        {
            buffID_EX->AluSrc = '1';
            buffID_EX->AluOp_0 = '0';
            buffID_EX->AluOp_1 = '0';
            buffID_EX->RegDst = 'x';

            buffID_EX->Branch = '0';
            buffID_EX->Jump = '0';
            buffID_EX->MemWrite = '1';
            buffID_EX->MemRead = '0';

            buffID_EX->MemToreg = 'x';
            buffID_EX->RegWrite = '0';
        }

        else if (strcmp(buffIF_ID->instruction_1[1], "lw") == 0)
        {
            buffID_EX->AluSrc = '1';
            buffID_EX->AluOp_0 = '0';
            buffID_EX->AluOp_1 = '0';
            buffID_EX->RegDst = '0';

            buffID_EX->Branch = '0';
            buffID_EX->Jump = '0';
            buffID_EX->MemWrite = '0';
            buffID_EX->MemRead = '1';

            buffID_EX->MemToreg = '1';
            buffID_EX->RegWrite = '0';
        }


        //DEBUg
        if ( (strcmp(buffID_EX->instruction_1[1], "end:") == 0))
        {
            //printf("%c\n", buffID_EX->instruction_1[0]);
            printf("%s\n", buffID_EX->instruction_1[1]);
            printf("\n");
        }

        else if((strcmp(buffID_EX->instruction_1[1],"j") == 0))
        {
            //printf("%c\n", buffID_EX->instruction_1[0]);
            printf("%s\n", buffID_EX->instruction_1[1]);
            printf("%s\n", buffID_EX->instruction_1[2]);
            printf("\n");

        }

        else
        {
            //printf("%c\n", buffID_EX->instruction_1[0]);
            printf("%s\n", buffID_EX->instruction_1[1]);
            printf("%s\n", buffID_EX->instruction_1[2]);
            printf("%s\n", buffID_EX->instruction_1[3]);
            printf("%s\n", buffID_EX->instruction_1[4]);
            printf("\n");
        }

        if (buffIF_ID->status == false)
        {
            buffID_EX->status = false;
        }

        printf("%s\n\n","///////////////////// Fin Identification /////////////////////////" );

    }


}

void execution(bufferID_EX* buffID_EX, bufferEX_MEM* buffEX_MEM, int* PC, char*** instructions)
{

    if (buffEX_MEM->status == false)
    {

    }

    else
    {
        printf("%s\n","///////////////////// Inicio Execution /////////////////////////" );

        int result = 0;
        int lenInstruction = buffID_EX->instruction_1[0] - '0';
        buffEX_MEM->instruction_1 = malloc(sizeof(char*)*(lenInstruction+1));
        buffEX_MEM->instruction_2 = malloc(sizeof(char*)*(lenInstruction+1));
        memcpy(buffEX_MEM->instruction_2, buffID_EX->instruction_2, sizeof(char*)*(lenInstruction+1));
        memcpy(buffEX_MEM->instruction_1, buffID_EX->instruction_1, sizeof(char*)*(lenInstruction+1));

        //En caso de que la instrucción sea j
        if (strcmp(buffID_EX->instruction_1[1],"j") == 0)
        {
            //Si linea de control jump no tiene stuck at 0
            char * label = malloc(sizeof(char)*(strlen(buffID_EX->instruction_1[2])+1));
            strcpy(label, buffID_EX->instruction_1[2]);
            strcat(label, ":\0");

            int j;
            for (j = 1; j < atoi(instructions[0][0]); j++)
            {
                if (strcmp(instructions[j][1],label) == 0)
                {
                    break;
                }
            }

            *PC = j;
        }


        else if (strcmp(buffID_EX->instruction_1[1],"beq") == 0)
        {
            //Si linea de control jump no tiene stuck at 0
            char * label = malloc(sizeof(char)*(strlen(buffID_EX->instruction_1[4])+1));
            strcpy(label, buffID_EX->instruction_1[4]);
            strcat(label, ":\0");

            int j;
            for (j = 1; j < atoi(instructions[0][0]); j++)
            {
                if (strcmp(instructions[j][1],label) == 0)
                {
                    break;
                }
            }
            buffID_EX->previus_PC = *PC;
            *PC = j+1;
        }

        // else if (strcmp(buffID_EX->instruction_1[1],"beq") == 0)
        // {
        //     int variable_1 = atoi(buffID_EX->instruction_1[2]);
        //     int variable_2 = atoi(buffID_EX->instruction_1[3]);
        //
        //     if(variable_1 != variable_2)
        //     {
        //         *PC = buffID_EX->previus_PC;
        //     }
        // }

        else if (strcmp(buffID_EX->instruction_1[1],"sub") == 0 || strcmp(buffID_EX->instruction_1[1],"subi") == 0)
        {
            int variable_1 = atoi(buffID_EX->instruction_1[4]);
            int variable_2 = atoi(buffID_EX->instruction_1[3]);
            int result = variable_1 - variable_2;
            buffEX_MEM->alu_result = result;
        }

        else if (strcmp(buffID_EX->instruction_1[1],"add") == 0 || strcmp(buffID_EX->instruction_1[1],"addi") == 0)
        {
            int variable_1 = atoi(buffID_EX->instruction_1[4]);
            int variable_2 = atoi(buffID_EX->instruction_1[3]);
            int result = variable_1 + variable_2;
            buffEX_MEM->alu_result = result;

        }

        else if (strcmp(buffID_EX->instruction_1[1],"mul") == 0)
        {
            int variable_1 = atoi(buffID_EX->instruction_1[4]);
            int variable_2 = atoi(buffID_EX->instruction_1[3]);
            int result = variable_1 * variable_2;
            buffEX_MEM->alu_result = result;

        }

        else if (strcmp(buffID_EX->instruction_1[1],"div") == 0)
        {
            int variable_1 = atoi(buffID_EX->instruction_1[4]);
            int variable_2 = atoi(buffID_EX->instruction_1[3]);

            if (variable_2 == 0)
            {
                exit(1);
            }

            //Se realiza la operación
            int result = variable_1 / variable_2;
            buffEX_MEM->alu_result = result;
        }

        else if (strcmp(buffID_EX->instruction_1[1],"lw") == 0)
        {
            char * offset_variable = malloc(sizeof(char)*5);
            int offset_variable_number = atoi(buffID_EX->instruction_1[3]);
            int offset_number = atoi(buffID_EX->instruction_1[4]);
            int memory_direction = 0;
            memory_direction = (offset_variable_number + offset_number)/4;

            buffEX_MEM->alu_result = memory_direction;
        }

        else if (strcmp(buffID_EX->instruction_1[1],"sw") == 0)
        {
            char * offset_variable = malloc(sizeof(char)*5);
            int offset_variable_number = atoi(buffID_EX->instruction_1[3]);
            int memory_direction = 0;
            int offset_number = atoi(buffID_EX->instruction_1[4]);

            memory_direction = (offset_variable_number + offset_number)/4;

            buffEX_MEM->alu_result = memory_direction;
        }

        printf("Soy Aluresult : %d\n\n", buffEX_MEM->alu_result );

        printf("%s\n\n","///////////////////// Fin Execution /////////////////////////" );

        if (buffID_EX->status == false)
        {
            buffEX_MEM->status = false;
        }
    }

}

void memory(bufferEX_MEM* buffEX_MEM, bufferMEM_WB* buffMEM_WB, int* virtualMemory, reg** registersMemory)
{
    if (buffMEM_WB->status == false)
    {
    }

    else
    {
        printf("%s\n","///////////////////// Inicio Memory /////////////////////////" );

        int lenInstruction = buffEX_MEM->instruction_1[0] - '0';
        buffMEM_WB->instruction_1 = malloc(sizeof(char*)*(lenInstruction+1));
        buffMEM_WB->instruction_2 = malloc(sizeof(char*)*(lenInstruction+1));
        memcpy(buffMEM_WB->instruction_2, buffEX_MEM->instruction_2, sizeof(char*)*(lenInstruction+1));
        memcpy(buffMEM_WB->instruction_1, buffEX_MEM->instruction_1, sizeof(char*)*(lenInstruction+1));

        //En caso de que la instrucción sea j
        if (strcmp(buffEX_MEM->instruction_1[1],"j") == 0)
        {
        }

        else if (strcmp(buffEX_MEM->instruction_1[1],"lw") == 0)
        {
            for (int j = 0; j < REGISTERSNUMBER; j++)
            {
                //Se verifica si la segunda variable de la instrucción existe
                //En caso de hacerlo, se toma su valor de memoria
                if (strcmp(buffEX_MEM->instruction_1[2],registersMemory[j]->name) == 0)
                {
                    buffMEM_WB->memory_data =  virtualMemory[buffEX_MEM->alu_result];
                    break;
                }

                else
                {
                    printf("%s\n","holaaaa");
                    exit(1);
                }
            }
        }

        else if (strcmp(buffEX_MEM->instruction_1[1],"sw") == 0)
        {
            virtualMemory[buffEX_MEM->alu_result] = buffEX_MEM->instruction_1[2];
        }


        buffMEM_WB->alu_result = buffEX_MEM->alu_result;

        printf("%s\n\n","///////////////////// Fin Memory /////////////////////////" );

        if (buffEX_MEM->status == false)
        {
            buffMEM_WB->status = false;
        }

    }

}

void writeBack(bufferMEM_WB* buffMEM_WB, bufferMWB_END* buffMWB_END,reg** registersMemory)
{
    if (buffMWB_END->status == false) {

    }

    else
    {
        printf("%s\n","///////////////////// Inicio WriteBack /////////////////////////" );

        int lenInstruction = buffMEM_WB->instruction_1[0] - '0';
        buffMWB_END->instruction_1 = malloc(sizeof(char*)*(lenInstruction+1));
        buffMWB_END->instruction_2 = malloc(sizeof(char*)*(lenInstruction+1));
        memcpy(buffMWB_END->instruction_2, buffMEM_WB->instruction_2, sizeof(char*)*(lenInstruction+1));
        memcpy(buffMWB_END->instruction_1, buffMEM_WB->instruction_1, sizeof(char*)*(lenInstruction+1));

        int j;

        if (strcmp(buffMEM_WB->instruction_1[1],"sub") == 0 || strcmp(buffMEM_WB->instruction_1[1],"subi") == 0 ||
            strcmp(buffMEM_WB->instruction_1[1],"add") == 0 || strcmp(buffMEM_WB->instruction_1[1],"addi") == 0 ||
            strcmp(buffMEM_WB->instruction_1[1],"mul") == 0 || strcmp(buffMEM_WB->instruction_1[1],"div") == 0)
        {
            //Se recorren la memoria de registros
            for (j = 0; j < REGISTERSNUMBER; j++)
            {
                //Se verifica si la primera variable de la instrucción existe
                //En caso de hacerlo, guarda el resultado en memoria
                if (strcmp(buffMEM_WB->instruction_1[2],registersMemory[j]->name) == 0)
                {
                    registersMemory[j]->value = buffMEM_WB->alu_result;
                    break;
                }
            }

            if (j == REGISTERSNUMBER)
            {
                printf("Error\n");
                exit(1);
            }
        }

        else if (strcmp(buffMEM_WB->instruction_1[1],"lw") == 0)
        {
            //Se recorren la memoria de registros
            for (j = 0; j < REGISTERSNUMBER; j++)
            {
                //Se verifica si la primera variable de la instrucción existe
                //En caso de hacerlo, guarda el resultado en memoria
                if (strcmp(buffMEM_WB->instruction_1[2],registersMemory[j]->name) == 0)
                {
                    registersMemory[j]->value = buffMEM_WB->memory_data;
                    break;
                }
            }

            if (j == REGISTERSNUMBER)
            {
                printf("Error\n");
                exit(1);
            }
        }

        printf("%s\n\n","///////////////////// Fin writeBack /////////////////////////" );

        if (buffMEM_WB->status == false)
        {
            buffMWB_END->status = false;
        }
    }

}

int main(int argc, char** argv)
{
    char fp_source_name_1[100];
    char fp_source_name_2[100];
    char fp_output_name_1[100];
    char fp_output_name_2[100];

    printf("%s\n","Bienvenido al simulador de MIPS V0.01\n\n" );

    // printf("%s","Ingrese el nombre del archivo que contiene las Instrucciones del programa: " );
    // fgets(fp_source_name_1,100,stdin);
    // fp_source_name_1[strcspn(fp_source_name_1, "\n")] = 0;
    // printf("\n");

    //
    // printf("%s","Ingrese el nombre del archivo que contiene las Instrucciones del programa: ");
    // fgets(fp_source_name_2,100,stdin);
    // fp_source_name_2[strcspn(fp_source_name_2, "\n")] = 0;
    // printf("\n");
    //
    //
    // printf("%s","Ingrese el nombre del archivo que contendrá las Instrucciones ejecutadas al terminar el programa: " );
    // fgets(fp_output_name_1,100,stdin);
    // fp_output_name_1[strcspn(fp_output_name_1, "\n")] = 0;
    // printf("\n");
    //
    // printf("%s","Ingrese el nombre del archivo que contendrá los valores de los registros al terminar el programa (Usar extensión .csv para mejor visualización): " );
    // fgets(fp_output_name_2,100,stdin);
    // fp_output_name_2[strcspn(fp_output_name_2, "\n")] = 0;
    // printf("\n");

    bool created_1 = false;
    bool created_2 = false;

    bufferIF_ID * buffIF_ID = malloc(sizeof(bufferIF_ID));
    bufferID_EX * buffID_EX = malloc(sizeof(bufferID_EX));
    bufferEX_MEM * buffEX_MEM = malloc(sizeof(bufferEX_MEM));
    bufferMEM_WB * buffMEM_WB = malloc(sizeof(bufferMEM_WB));
    bufferMWB_END * buffMWB_END = malloc(sizeof(bufferMWB_END));

    buffIF_ID->status = true;
    buffID_EX->status = true;
    buffEX_MEM->status = true;
    buffMEM_WB->status = true;
    buffMWB_END->status = true;

    //printf("%p\n",buffIF_ID);
    //initializeBuffers(buffIF_ID,buffID_EX,buffEX_MEM,buffMEM_WB);
    char* controlLinesMemory;
    //regdst,jump,branch,memread,memtoreg,aluop,memwrite,alusrc,regwrite;
    reg ** registersMemory;
    char*** instructions = NULL;
    int* virtualMemory = NULL;
    strcpy(fp_source_name_1,"entrada1.txt");
	instructions = readData(fp_source_name_1);
    virtualMemory = calloc(1025,sizeof(int));
    registersMemory = malloc(sizeof(reg*)*27);
    char* error = malloc(sizeof(char)*50);
    strcpy(error,"");
    registersMemory = populateRegisters();

    int PC = 1;
    int lenInstructions = atoi(instructions[0][0]);
    int option = 1;
    int cycle = 1;

    while(buffIF_ID->status == true || buffID_EX->status == true || buffEX_MEM->status == true ||
          buffMEM_WB->status == true || buffMWB_END->status == true)
    {
        printf("Ciclo %d\n", cycle);
        switch (option)
        {
            case 1 :

                fetch(buffIF_ID,instructions,&PC);
                writePipeline(buffIF_ID,buffID_EX, buffEX_MEM, buffMEM_WB, buffMWB_END, &created_2, option,cycle, &PC, instructions);

                option = 2;
                break;
            case 2 :
                identification(buffIF_ID,buffID_EX,registersMemory, instructions, &PC);
                fetch(buffIF_ID,instructions,&PC);
                writePipeline(buffIF_ID,buffID_EX, buffEX_MEM, buffMEM_WB, buffMWB_END, &created_2, option,cycle, &PC, instructions);
                option = 3;
                break;
            case 3 :
                execution(buffID_EX,buffEX_MEM,&PC, instructions);
                identification(buffIF_ID,buffID_EX,registersMemory ,instructions, &PC);
                fetch(buffIF_ID,instructions,&PC);
                writePipeline(buffIF_ID,buffID_EX, buffEX_MEM, buffMEM_WB, buffMWB_END, &created_2, option,cycle, &PC, instructions);

                option = 4;
                break;
            case 4 :
                memory(buffEX_MEM,buffMEM_WB, virtualMemory, registersMemory);
                execution(buffID_EX,buffEX_MEM,&PC, instructions);
                identification(buffIF_ID,buffID_EX,registersMemory ,instructions, &PC);
                fetch(buffIF_ID,instructions,&PC);
                writePipeline(buffIF_ID,buffID_EX, buffEX_MEM, buffMEM_WB, buffMWB_END, &created_2, option,cycle, &PC, instructions);

                option = 5;
                break;
            case 5 :
                writeBack(buffMEM_WB,buffMWB_END, registersMemory);
                memory(buffEX_MEM,buffMEM_WB, virtualMemory, registersMemory);
                execution(buffID_EX,buffEX_MEM,&PC, instructions);
                identification(buffIF_ID,buffID_EX,registersMemory ,instructions, &PC);
                fetch(buffIF_ID,instructions,&PC);
                writePipeline(buffIF_ID,buffID_EX, buffEX_MEM, buffMEM_WB, buffMWB_END, &created_2, option,cycle, &PC, instructions);
                break;
        }
        cycle++;

    }

    printf("Ha terminado la ejecución del programa, por favor revise los archivos de salida: %s y %s\n", fp_output_name_1, fp_output_name_2);

    return 0;
}
