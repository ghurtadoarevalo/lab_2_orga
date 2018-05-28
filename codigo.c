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
	for (int i = 0; i < linesNumber; i++)
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

//Función encargada de leer todas las lineas de control del archivo con el nombre que contenga la variable fp_source_name_2
//Entradas: String
//Salidas: Arreglo de caracteres que representan las lineas de control
char* populateControlLinesMemory(char* fp_source_name_2)
{
    char*** controlLines = NULL;
    controlLines = readData(fp_source_name_2);
    char* controlLinesMemory = malloc(sizeof(char)*9);
    for (int i = 1; i < atoi(controlLines[0][0])+1; i++)
    {
        if (strcmp(controlLines[i][0],"Regdst") == 0 || strcmp(controlLines[i][0],"regdst") == 0)
        {
            controlLinesMemory[0] = controlLines[i][1][0];
        }

        else if (strcmp(controlLines[i][0],"Jump") == 0 || strcmp(controlLines[i][0],"jump") == 0)
        {
            controlLinesMemory[1] = controlLines[i][1][0];
        }

        else if (strcmp(controlLines[i][0],"Branch") == 0 || strcmp(controlLines[i][0],"branch") == 0)
        {
            controlLinesMemory[2] =controlLines[i][1][0];

        }

        else if (strcmp(controlLines[i][0],"Memread") == 0 || strcmp(controlLines[i][0],"memread") == 0)
        {
            controlLinesMemory[3] =controlLines[i][1][0];

        }

        else if (strcmp(controlLines[i][0],"Memtoreg") == 0 || strcmp(controlLines[i][0],"memtoreg") == 0)
        {
            controlLinesMemory[4] =controlLines[i][1][0];

        }

        else if (strcmp(controlLines[i][0],"Aluop") == 0 || strcmp(controlLines[i][0],"aluop") == 0)
        {
            controlLinesMemory[5] =controlLines[i][1][0];

        }

        else if (strcmp(controlLines[i][0],"Memwrite") == 0 || strcmp(controlLines[i][0],"memwrite") == 0)
        {
            controlLinesMemory[6] =controlLines[i][1][0];

        }

        else if (strcmp(controlLines[i][0],"Alusrc") == 0 || strcmp(controlLines[i][0],"alusrc") == 0)
        {
            controlLinesMemory[7] =controlLines[i][1][0];
        }

        else if (strcmp(controlLines[i][0],"Regwrite") == 0 || strcmp(controlLines[i][0],"regwrite") == 0)
        {
            controlLinesMemory[8] = controlLines[i][1][0];
        }
    }

    return controlLinesMemory;
}

//Función encargada de escribir las instrucciones realizadas en el archivo de salida que contiene fp_output_name_1
//Entradas: Una instruccion, un error en caso de haberlo, un booleano que indica si ya fue creado el archivo de salida y el nombre del archivo de salida
//Salidas: Archivo de salida nuevo o modificado, agregando instrucciones ejecutadas.
void writeInstructions(char ** instruction, char* error, bool* created_1, char* fp_output_name_1)
{
    if (*created_1 == false)
    {
        FILE *fp;
        fp=fopen(fp_output_name_1, "w");
        if(fp == NULL)
        {
            printf("Error al crear el archivo de salida 1\n");
            exit (1);
        }

        if (strcmp(error,"") == 0)
        {
            if (strcmp(instruction[0],"j") == 0 || strcmp(instruction[0],"J") == 0 )
            {
                fprintf(fp,"%s %s\n", instruction[0], instruction[1]);
            }

            if (strcmp(instruction[0],"sw") == 0 ||  strcmp(instruction[0],"lw") == 0 )
            {
                fprintf(fp,"%s %s %s\n", instruction[0], instruction[1], instruction[2]);
            }

            if (strcmp(instruction[0],"subi") == 0 || strcmp(instruction[0],"sub") == 0 ||
                strcmp(instruction[0],"add") == 0  || strcmp(instruction[0],"addi") == 0 ||
                strcmp(instruction[0],"mul") == 0  || strcmp(instruction[0],"div") == 0||
                strcmp(instruction[0],"beq") == 0)

            {
                fprintf(fp,"%s %s %s %s\n", instruction[0], instruction[1], instruction[2], instruction[3]);
            }

            *created_1 = true;
            fclose(fp);

        }

        else
        {
            printf("%s\n",error);
            fprintf(fp, "%s\n", error);
            fclose(fp);
            exit(1);
        }
    }

    else
    {

        FILE *fp;
        fp=fopen(fp_output_name_1, "a");
        if(fp == NULL)
        {
            printf("Error al modoficar el archivo %s\n", fp_output_name_1);
            exit (1);
        }

        if (strcmp(error,"") == 0)
        {
            if (strcmp(instruction[0],"j") == 0 || strcmp(instruction[0],"J") == 0 )
            {
                fprintf(fp,"%s %s\n", instruction[0], instruction[1]);
            }


            if (strcmp(instruction[0],"sw") == 0 ||  strcmp(instruction[0],"lw") == 0 )
            {
                fprintf(fp,"%s %s %s\n", instruction[0], instruction[1], instruction[2]);
            }

            if (strcmp(instruction[0],"subi") == 0 || strcmp(instruction[0],"sub") == 0 ||
                strcmp(instruction[0],"add") == 0  || strcmp(instruction[0],"addi") == 0 ||
                strcmp(instruction[0],"mul") == 0  || strcmp(instruction[0],"div") == 0||
                strcmp(instruction[0],"beq") == 0)
            {
                fprintf(fp,"%s %s %s %s\n", instruction[0], instruction[1], instruction[2], instruction[3]);
            }

            fclose(fp);
        }

        else
        {
            printf("%s\n",error);
            fprintf(fp, "%s\n", error);
            fclose(fp);
            exit(1);
        }
    }
}

//Función encargada de escribir los valores de los registros en el archivo de salida que contiene fp_output_name_2
//Entradas: Arreglo con todos los registros y sus valores, instrucción ejecutada, un booleano que indica si ya fue creado el archivo de salida y el nombre del archivo de salida
//Salidas: Archivo de salida nuevo o modificado, agregando valores registros para cada instruccion ejecutada.
void writeRegisters(reg ** registersMemory, char ** instruction, bool* created_2, char* fp_output_name_2)
{
    if (*created_2 == false)
    {
        FILE *fp;
        fp=fopen(fp_output_name_2, "w");

        if(fp == NULL)
        {
            printf("Error al crear el archivo %s\n",fp_output_name_2);
            exit(1);
        }

        fprintf(fp, "Instrucciones, $sp, $at, $fp, $v0, $v1, $a0, $a1, $a2, $a3, $t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7, $t8, $t9, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7, $k0, $k1,$gp, $zero\n");


        if (strcmp(instruction[0],"j") == 0 || strcmp(instruction[0],"J") == 0 )
        {
            fprintf(fp, "%s %s,",instruction[0],instruction[1]);
            for (size_t i = 0; i < REGISTERSNUMBER; i++)
            {
                fprintf(fp, "%d,", registersMemory[i]->value);
            }
            fprintf(fp, "\n");
        }


        if (strcmp(instruction[0],"sw") == 0 ||  strcmp(instruction[0],"lw") == 0 )
        {
            fprintf(fp, "%s %s %s,",instruction[0],instruction[1],instruction[2]);
            for (size_t i = 0; i < REGISTERSNUMBER; i++)
            {
                fprintf(fp, "%d,", registersMemory[i]->value);
            }
            fprintf(fp, "\n");
        }

        if (strcmp(instruction[0],"subi") == 0 || strcmp(instruction[0],"sub") == 0 ||
            strcmp(instruction[0],"add") == 0  || strcmp(instruction[0],"addi") == 0 ||
            strcmp(instruction[0],"mul") == 0  || strcmp(instruction[0],"div") == 0||
            strcmp(instruction[0],"beq") == 0)
        {
            fprintf(fp, "%s %s %s %s,",instruction[0],instruction[1],instruction[2],instruction[3]);
            for (size_t i = 0; i < REGISTERSNUMBER; i++)
            {
                fprintf(fp, "%d,", registersMemory[i]->value);
            }
            fprintf(fp, "\n");
        }
        *created_2 = true;
        fclose(fp);

    }

    else
    {
        FILE *fp;
        fp=fopen(fp_output_name_2, "a");

        if(fp == NULL)
        {
            printf("Error al crear el archivo %s\n", fp_output_name_2);
            exit(1);
        }


        if (strcmp(instruction[0],"j") == 0 || strcmp(instruction[0],"J") == 0 )
        {
            fprintf(fp, "%s %s,",instruction[0],instruction[1]);
            for (size_t i = 0; i < REGISTERSNUMBER; i++)
            {
                fprintf(fp, "%d,", registersMemory[i]->value);
            }
            fprintf(fp, "\n");
        }

        if (strcmp(instruction[0],"sw") == 0 ||  strcmp(instruction[0],"lw") == 0 )
        {
            fprintf(fp, "%s %s %s,",instruction[0],instruction[1],instruction[2]);
            for (size_t i = 0; i < REGISTERSNUMBER; i++)
            {
                fprintf(fp, "%d,", registersMemory[i]->value);
            }
            fprintf(fp, "\n");
        }

        if (strcmp(instruction[0],"subi") == 0 || strcmp(instruction[0],"sub") == 0 ||
            strcmp(instruction[0],"add") == 0  || strcmp(instruction[0],"addi") == 0 ||
            strcmp(instruction[0],"mul") == 0  || strcmp(instruction[0],"div") == 0||
            strcmp(instruction[0],"beq") == 0)
        {
            fprintf(fp, "%s %s %s %s,",instruction[0],instruction[1],instruction[2],instruction[3]);
            for (size_t i = 0; i < REGISTERSNUMBER; i++)
            {
                fprintf(fp, "%d,", registersMemory[i]->value);
            }
            fprintf(fp, "\n");
        }

        fclose(fp);
    }
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

void initializeBuffers(bufferIF_ID * buffIF_ID,bufferID_EX * buffID_EX,bufferEX_MEM * buffEX_MEM,bufferMEM_WB * buffMEM_WB)
{

}

void fetch(bufferIF_ID* buffIF_ID, char*** instructions, int* instructionCount)
{
    if (buffIF_ID->status == true)
    {
        int lenInstruction = instructions[*instructionCount][0] - '0';
        buffIF_ID->instruction_1 = malloc(sizeof(char*)*(lenInstruction+1));
        buffIF_ID->instruction_1 = instructions[*instructionCount];
        *instructionCount+=1;
    }

    if (atoi(instructions[0][0]) < *instructionCount)
    {
        buffIF_ID->status = false;
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
    buffID_EX->AluOp = malloc(sizeof(char)*3);
    buffIF_ID->status = true;
    buffID_EX->status = false;
    buffEX_MEM->status = false;
    buffMEM_WB->status = false;

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

    int  instructionCount = 1;

    //while(true)
    //{

    fetch(buffIF_ID,instructions,&instructionCount);
    identification(buffIF_ID,buffID_EX);
    //Se recorren todas las instrucciones leídas del archivo de entrada con las instrucciones a ejecutar.
        // for (int i = 1; i < atoi(instructions[0][0]); i++)
        // {
        //     //En caso de que la instrucción sea j
        //     if (strcmp(instructions[i][0],"j") == 0 || strcmp(instructions[i][0],"J") == 0)
        //     {
        //         //Si linea de control jump no tiene stuck at 0
        //         if (controlLinesMemory[1] == 'x')
        //         {
        //             char * label = malloc(sizeof(char)*(strlen(instructions[i][1])+1));
        //             strcpy(label,instructions[i][1]);
        //             strcat(label, ":\0");
        //             int j;
        //             for (j = 0; j < atoi(instructions[0][0]); j++)
        //             {
        //                 if (strcmp(instructions[j][0],label) == 0)
        //                 {
        //                     break;
        //                 }
        //             }
        //
        //             if (j == atoi(instructions[0][0]))
        //             {
        //                 strcpy(error,"No existe la etiqueta ");
        //                 strcat(error,instructions[i][1]);
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             i = j;
        //         }
        //
        //         //Si linea de control jump tiene stuck at 0
        //         else
        //         {
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             continue;
        //         }
        //     }
        //
        //     //En caso de que la instrucción sea sub o subi
        //     else if (strcmp(instructions[i][0],"sub") == 0 || strcmp(instructions[i][0],"subi") == 0)
        //     {
        //         int variable_1 = 0;
        //         int variable_2 = 0;
        //         int result = 0;
        //         int j;
        //
        //         //Se recorren la memoria de registros
        //         for (j = 0; j < REGISTERSNUMBER; j++)
        //         {
        //             //Se verifica si la segunda variable de la instrucción existe
        //             //En caso de hacerlo, se toma su valor de memoria
        //             if (strcmp(instructions[i][2],registersMemory[j]->name) == 0)
        //             {
        //                 variable_1 = registersMemory[j]->value;
        //                 break;
        //             }
        //         }
        //
        //         //En caso de que no exista la segunda variable en memoria, error.
        //         if (j == REGISTERSNUMBER)
        //         {
        //             strcpy(error,"No existe la variable ");
        //             strcat(error,instructions[i][2]);
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Se recorren la memoria de registros
        //         for (j = 0; j < REGISTERSNUMBER; j++)
        //         {
        //             //Se verifica si la tercera variable de la instrucción existe
        //             //En caso de hacerlo, se toma su valor de memoria
        //             if (strcmp(instructions[i][3],registersMemory[j]->name) == 0)
        //             {
        //                 variable_2 = registersMemory[j]->value;
        //                 break;
        //             }
        //         }
        //
        //         //En caso de que no exista la tercera variable en memoria
        //         if (j == REGISTERSNUMBER)
        //         {
        //             //Si la instrucción es subi, entonces se toma el número de la instrucción
        //             if (strcmp(instructions[i][0],"subi") == 0)
        //             {
        //                 variable_2 = atoi(instructions[i][3]);
        //             }
        //
        //             //Si es sub, error.
        //             else
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][3]);
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //         }
        //
        //         //Se realiza la operación
        //         result = variable_1 - variable_2;
        //
        //         //Si linea de control RegWrite no tiene stuck at 0
        //         if (controlLinesMemory[8] == 'x')
        //         {
        //             //Se recorren la memoria de registros
        //             for (j = 0; j < REGISTERSNUMBER; j++)
        //             {
        //                 //Se verifica si la primera variable de la instrucción existe
        //                 //En caso de hacerlo, guarda el resultado en memoria
        //                 if (strcmp(instructions[i][1],registersMemory[j]->name) == 0)
        //                 {
        //                     registersMemory[j]->value = result;
        //                     break;
        //                 }
        //             }
        //
        //             if (j == REGISTERSNUMBER)
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][1]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Si linea de control RegWrite tiene stuck at 0
        //         else
        //         {
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             continue;
        //         }
        //     }
        //
        //     //En caso de que la instrucción sea add o addi
        //     else if (strcmp(instructions[i][0],"add") == 0 || strcmp(instructions[i][0],"addi") == 0)
        //     {
        //         int variable_1 = 0;
        //         int variable_2 = 0;
        //         int result = 0;
        //         int j;
        //
        //         //Se recorren la memoria de registros
        //         for (j = 0; j < REGISTERSNUMBER; j++)
        //         {
        //             //Se verifica si la segunda variable de la instrucción existe
        //             //En caso de hacerlo, se toma su valor de memoria
        //             if (strcmp(instructions[i][2],registersMemory[j]->name) == 0)
        //             {
        //                 variable_1 = registersMemory[j]->value;
        //                 break;
        //             }
        //         }
        //
        //         //En caso de que no exista la segunda variable en memoria, error.
        //         if (j == REGISTERSNUMBER)
        //         {
        //             strcpy(error,"No existe la variable ");
        //             strcat(error,instructions[i][2]);
        //             strcat(error," en instrucción ");
        //             strcat(error,instructions[i][0] );
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Se recorren la memoria de registros
        //         for (j = 0; j < REGISTERSNUMBER; j++)
        //         {
        //             //Se verifica si la tercera variable de la instrucción existe
        //             //En caso de hacerlo, se toma su valor de memoria
        //             if (strcmp(instructions[i][3],registersMemory[j]->name) == 0)
        //             {
        //                 variable_2 = registersMemory[j]->value;
        //                 break;
        //             }
        //         }
        //
        //         //En caso de que no exista la tercera variable en memoria
        //         if (j == REGISTERSNUMBER)
        //         {
        //             //Si la instrucción es addi, entonces se toma el número de la instrucción
        //             if (strcmp(instructions[i][0],"addi") == 0)
        //             {
        //                 variable_2 = atoi(instructions[i][3]);
        //             }
        //
        //             //Si es sub, error.
        //             else
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][3]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //         }
        //
        //         //Se realiza la operación
        //         result = variable_1 + variable_2;
        //
        //         //Si linea de control RegWrite no tiene stuck at 0
        //         if (controlLinesMemory[8] == 'x')
        //         {
        //             //Se recorren la memoria de registros
        //             for (j = 0; j < REGISTERSNUMBER; j++)
        //             {
        //                 //Se verifica si la primera variable de la instrucción existe
        //                 //En caso de hacerlo, guarda el resultado en memoria
        //                 if (strcmp(instructions[i][1],registersMemory[j]->name) == 0)
        //                 {
        //                     registersMemory[j]->value = result;
        //                     break;
        //                 }
        //             }
        //
        //             if (j == REGISTERSNUMBER)
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][1]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Si linea de control RegWrite tiene stuck at 0
        //         else
        //         {
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             continue;
        //         }
        //     }
        //
        //     //En caso de que la instrucción sea mul
        //     else if (strcmp(instructions[i][0],"mul") == 0)
        //     {
        //         int variable_1 = 0;
        //         int variable_2 = 0;
        //         int result = 0;
        //         int j;
        //
        //         //Se recorren la memoria de registros
        //         for (j = 0; j < REGISTERSNUMBER; j++)
        //         {
        //             //Se verifica si la segunda variable de la instrucción existe
        //             //En caso de hacerlo, se toma su valor de memoria
        //             if (strcmp(instructions[i][2],registersMemory[j]->name) == 0)
        //             {
        //                 variable_1 = registersMemory[j]->value;
        //                 break;
        //             }
        //         }
        //
        //         //En caso de que no exista la segunda variable en memoria, error.
        //         if (j == REGISTERSNUMBER)
        //         {
        //             strcpy(error,"No existe la variable ");
        //             strcat(error,instructions[i][2]);
        //             strcat(error," en instrucción ");
        //             strcat(error,instructions[i][0] );
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Se recorren la memoria de registros
        //         for (j = 0; j < REGISTERSNUMBER; j++)
        //         {
        //             //Se verifica si la tercera variable de la instrucción existe
        //             //En caso de hacerlo, se toma su valor de memoria
        //             if (strcmp(instructions[i][3],registersMemory[j]->name) == 0)
        //             {
        //                 variable_2 = registersMemory[j]->value;
        //                 break;
        //             }
        //         }
        //
        //         //En caso de que no exista la tercera variable en memoria
        //         if (j == REGISTERSNUMBER)
        //         {
        //             //Si la instrucción es addi, entonces se toma el número de la instrucción
        //             if (strcmp(instructions[i][0],"addi") == 0)
        //             {
        //                 variable_2 = atoi(instructions[i][3]);
        //             }
        //
        //             //Si es sub, error.
        //             else
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][3]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //         }
        //
        //         //Se realiza la operación
        //         result = variable_1 * variable_2;
        //
        //          //Si linea de control RegWrite no tiene stuck at 0
        //         if (controlLinesMemory[8] == 'x')
        //         {
        //             //Se recorren la memoria de registros
        //             for (j = 0; j < REGISTERSNUMBER; j++)
        //             {
        //                 //Se verifica si la primera variable de la instrucción existe
        //                 //En caso de hacerlo, guarda el resultado en memoria
        //                 if (strcmp(instructions[i][1],registersMemory[j]->name) == 0)
        //                 {
        //                     registersMemory[j]->value = result;
        //                     break;
        //                 }
        //             }
        //
        //             if (j == REGISTERSNUMBER)
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][1]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Si linea de control RegWrite tiene stuck at 0
        //         else
        //         {
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             continue;
        //         }
        //     }
        //
        //     //En caso de que la instrucción sea div
        //     else if (strcmp(instructions[i][0],"div") == 0)
        //     {
        //         int variable_1 = 0;
        //         int variable_2 = 0;
        //         int result = 0;
        //         int j;
        //
        //         //Se recorren la memoria de registros
        //         for (j = 0; j < REGISTERSNUMBER; j++)
        //         {
        //             //Se verifica si la segunda variable de la instrucción existe
        //             //En caso de hacerlo, se toma su valor de memoria
        //             if (strcmp(instructions[i][2],registersMemory[j]->name) == 0)
        //             {
        //                 variable_1 = registersMemory[j]->value;
        //                 break;
        //             }
        //         }
        //
        //         //En caso de que no exista la segunda variable en memoria, error.
        //         if (j == REGISTERSNUMBER)
        //         {
        //             strcpy(error,"No existe la variable ");
        //             strcat(error,instructions[i][2]);
        //             strcat(error," en instrucción ");
        //             strcat(error,instructions[i][0] );
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Se recorren la memoria de registros
        //         for (j = 0; j < REGISTERSNUMBER; j++)
        //         {
        //             //Se verifica si la tercera variable de la instrucción existe
        //             //En caso de hacerlo, se toma su valor de memoria
        //             if (strcmp(instructions[i][3],registersMemory[j]->name) == 0)
        //             {
        //                 variable_2 = registersMemory[j]->value;
        //                 break;
        //             }
        //         }
        //
        //         //En caso de que no exista la tercera variable en memoria
        //         if (j == REGISTERSNUMBER)
        //         {
        //             //Si la instrucción es addi, entonces se toma el número de la instrucción
        //             if (strcmp(instructions[i][0],"addi") == 0)
        //             {
        //                 variable_2 = atoi(instructions[i][3]);
        //             }
        //
        //             //Si es sub, error.
        //             else
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][3]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //         }
        //
        //         //Si la viarable 2 es 0, es decir, variable_1/0, error.
        //         if (variable_2 == 0)
        //         {
        //             strcpy(error,"No se puede realizar división por 0 ");
        //             strcat(error," en instrucción ");
        //             strcat(error,instructions[i][0] );
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Se realiza la operación
        //         result = variable_1 / variable_2;
        //
        //         //Si linea de control RegWrite no tiene stuck at 0
        //         if (controlLinesMemory[8] == 'x')
        //         {
        //             //Se recorren la memoria de registros
        //             for (j = 0; j < REGISTERSNUMBER; j++)
        //             {
        //                 //Se verifica si la primera variable de la instrucción existe
        //                 //En caso de hacerlo, guarda el resultado en memoria
        //                 if (strcmp(instructions[i][1],registersMemory[j]->name) == 0)
        //                 {
        //                     registersMemory[j]->value = result;
        //                     break;
        //                 }
        //             }
        //
        //             if (j == REGISTERSNUMBER)
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][1]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Si linea de control RegWrite tiene stuck at 0
        //         else
        //         {
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             continue;
        //         }
        //     }
        //
        //     //En caso de que la instrucción sea beq
        //     else if (strcmp(instructions[i][0],"beq") == 0)
        //     {
        //         //Si linea de control Branch no tiene stuck at 0
        //         if (controlLinesMemory[2] == 'x')
        //         {
        //             int variable_1 = 0;
        //             int variable_2 = 0;
        //             int j;
        //
        //             //Se recorren la memoria de registros
        //             for (j = 0; j < REGISTERSNUMBER; j++)
        //             {
        //                 //Se verifica si la segunda variable de la instrucción existe
        //                 //En caso de hacerlo, se toma su valor de memoria
        //                 if (strcmp(instructions[i][1],registersMemory[j]->name) == 0)
        //                 {
        //                     variable_1 = registersMemory[j]->value;
        //                     break;
        //                 }
        //             }
        //
        //             //En caso de que no exista la segunda variable en memoria, error.
        //             if (j == REGISTERSNUMBER)
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][1]);
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //
        //             //Se recorren la memoria de registros
        //             for (j = 0; j < REGISTERSNUMBER; j++)
        //             {
        //                 //Se verifica si la tercera variable de la instrucción existe
        //                 //En caso de hacerlo, se toma su valor de memoria
        //                 if (strcmp(instructions[i][2],registersMemory[j]->name) == 0)
        //                 {
        //                     variable_2 = registersMemory[j]->value;
        //                     break;
        //                 }
        //             }
        //
        //             //En caso de que no exista la tercera variable en memoria
        //             if (j == REGISTERSNUMBER)
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][2]);
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //
        //             int k = i + 1;
        //             while (variable_1 != variable_2)
        //             {
        //                 if (strcmp(instructions[k][0],"j") == 0 || strcmp(instructions[k][0],"J") == 0)
        //                 {
        //                     if (controlLinesMemory[1] == 'x')
        //                     {
        //                         char * label = malloc(sizeof(char)*(strlen(instructions[k][1])+1));
        //                         strcpy(label,instructions[k][1]);
        //                         strcat(label, ":\0");
        //                         int j;
        //                         for (j = 0; j < atoi(instructions[0][0]); j++)
        //                         {
        //                             if (strcmp(instructions[j][0],label) == 0)
        //                             {
        //                                 break;
        //                             }
        //                         }
        //
        //
        //                         if (j == atoi(instructions[0][0]))
        //                         {
        //                             strcpy(error,"No existe la etiqueta ");
        //                             strcat(error,instructions[k][1]);
        //                             writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                             writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         }
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         i = j;
        //                         break;
        //                     }
        //
        //                     else if (controlLinesMemory[1] == '0')
        //                     {
        //                         continue;
        //                     }
        //                 }
        //
        //                 else if (strcmp(instructions[k][0],"sub") == 0 || strcmp(instructions[k][0],"subi") == 0)
        //                 {
        //                     int variable_1 = 0;
        //                     int variable_2 = 0;
        //                     int result = 0;
        //                     int j;
        //                     //Se recorren la memoria de registros
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la segunda variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(instructions[k][2],registersMemory[j]->name) == 0)
        //                         {
        //                             variable_1 = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     //En caso de que no exista la segunda variable en memoria, error.
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         strcpy(error,"No existe la variable ");
        //                         strcat(error,instructions[k][2]);
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //
        //                     //Se recorren la memoria de registros
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la tercera variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(instructions[k][3],registersMemory[j]->name) == 0)
        //                         {
        //                             variable_2 = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     //En caso de que no exista la tercera variable en memoria
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         //Si la instrucción es subi, entonces se toma el número de la instrucción
        //                         if (strcmp(instructions[k][0],"subi") == 0)
        //                         {
        //                             variable_2 = atoi(instructions[k][3]);
        //                         }
        //
        //                         //Si es sub, error.
        //                         else
        //                         {
        //                             strcpy(error,"No existe la variable ");
        //                             strcat(error,instructions[k][3]);
        //                             writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                             writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         }
        //                     }
        //
        //                     //Se realiza la operación
        //                     result = variable_1 - variable_2;
        //
        //                     if (controlLinesMemory[8] == 'x')
        //                     {
        //                         //Se recorren la memoria de registros
        //                         for (j = 0; j < REGISTERSNUMBER; j++)
        //                         {
        //                             //Se verifica si la primera variable de la instrucción existe
        //                             //En caso de hacerlo, guarda el resultado en memoria
        //                             if (strcmp(instructions[k][1],registersMemory[j]->name) == 0)
        //                             {
        //                                 registersMemory[j]->value = result;
        //                                 break;
        //                             }
        //                         }
        //
        //                         if (j == REGISTERSNUMBER)
        //                         {
        //                             strcpy(error,"No existe la variable ");
        //                             strcat(error,instructions[k][1]);
        //                             strcat(error," en instrucción ");
        //                             strcat(error,instructions[k][0] );
        //                             writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                             writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         }
        //
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //                 }
        //
        //                 else if (strcmp(instructions[k][0],"add") == 0 || strcmp(instructions[k][0],"addi") == 0)
        //                 {
        //                     int variable_1 = 0;
        //                     int variable_2 = 0;
        //                     int result = 0;
        //                     int j;
        //
        //                     //Se recorren la memoria de registros
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la segunda variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(instructions[k][2],registersMemory[j]->name) == 0)
        //                         {
        //                             variable_1 = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     //En caso de que no exista la segunda variable en memoria, error.
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         strcpy(error,"No existe la variable ");
        //                         strcat(error,instructions[k][2]);
        //                         strcat(error," en instrucción ");
        //                         strcat(error,instructions[k][0] );
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //
        //                     //Se recorren la memoria de registros
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la tercera variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(instructions[k][3],registersMemory[j]->name) == 0)
        //                         {
        //                             variable_2 = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     //En caso de que no exista la tercera variable en memoria
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         //Si la instrucción es addi, entonces se toma el número de la instrucción
        //                         if (strcmp(instructions[k][0],"addi") == 0)
        //                         {
        //                             variable_2 = atoi(instructions[k][3]);
        //                         }
        //
        //                         //Si es sub, error.
        //                         else
        //                         {
        //                             strcpy(error,"No existe la variable ");
        //                             strcat(error,instructions[k][3]);
        //                             strcat(error," en instrucción ");
        //                             strcat(error,instructions[k][0] );
        //                             writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                             writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         }
        //                     }
        //
        //                     //Se realiza la operación
        //                     result = variable_1 + variable_2;
        //
        //                     if (controlLinesMemory[8] == 'x')
        //                     {
        //                         //Se recorren la memoria de registros
        //                         for (j = 0; j < REGISTERSNUMBER; j++)
        //                         {
        //                             //Se verifica si la primera variable de la instrucción existe
        //                             //En caso de hacerlo, guarda el resultado en memoria
        //                             if (strcmp(instructions[k][1],registersMemory[j]->name) == 0)
        //                             {
        //                                 registersMemory[j]->value = result;
        //                                 break;
        //                             }
        //                         }
        //
        //                         if (j == REGISTERSNUMBER)
        //                         {
        //                             strcpy(error,"No existe la variable ");
        //                             strcat(error,instructions[k][1]);
        //                             strcat(error," en instrucción ");
        //                             strcat(error,instructions[k][0] );
        //                             writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                             writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         }
        //
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //
        //                     else
        //                     {
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         continue;
        //                     }
        //                 }
        //
        //                 else if (strcmp(instructions[k][0],"mul") == 0)
        //                 {
        //                     int variable_1 = 0;
        //                     int variable_2 = 0;
        //                     int result = 0;
        //                     int j;
        //
        //                     //Se recorren la memoria de registros
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la segunda variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(instructions[k][2],registersMemory[j]->name) == 0)
        //                         {
        //                             variable_1 = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     //En caso de que no exista la segunda variable en memoria, error.
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         strcpy(error,"No existe la variable ");
        //                         strcat(error,instructions[k][2]);
        //                         strcat(error," en instrucción ");
        //                         strcat(error,instructions[k][0] );
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //
        //                     //Se recorren la memoria de registros
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la tercera variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(instructions[k][3],registersMemory[j]->name) == 0)
        //                         {
        //                             variable_2 = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     //En caso de que no exista la tercera variable en memoria
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         //Si la instrucción es addi, entonces se toma el número de la instrucción
        //                         if (strcmp(instructions[k][0],"addi") == 0)
        //                         {
        //                             variable_2 = atoi(instructions[k][3]);
        //                         }
        //
        //                         //Si es sub, error.
        //                         else
        //                         {
        //                             strcpy(error,"No existe la variable ");
        //                             strcat(error,instructions[k][3]);
        //                             strcat(error," en instrucción ");
        //                             strcat(error,instructions[k][0] );
        //                             writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                             writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         }
        //                     }
        //
        //                     //Se realiza la operación
        //                     result = variable_1 * variable_2;
        //
        //                     if (controlLinesMemory[8] == 'x')
        //                     {
        //                         //Se recorren la memoria de registros
        //                         for (j = 0; j < REGISTERSNUMBER; j++)
        //                         {
        //                             //Se verifica si la primera variable de la instrucción existe
        //                             //En caso de hacerlo, guarda el resultado en memoria
        //                             if (strcmp(instructions[k][1],registersMemory[j]->name) == 0)
        //                             {
        //                                 registersMemory[j]->value = result;
        //                                 break;
        //                             }
        //                         }
        //
        //                         if (j == REGISTERSNUMBER)
        //                         {
        //                             strcpy(error,"No existe la variable ");
        //                             strcat(error,instructions[k][1]);
        //                             strcat(error," en instrucción ");
        //                             strcat(error,instructions[k][0] );
        //                             writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                             writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         }
        //
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //                 }
        //
        //                 else if (strcmp(instructions[k][0],"div") == 0)
        //                 {
        //                     int variable_1 = 0;
        //                     int variable_2 = 0;
        //                     int result = 0;
        //                     int j;
        //
        //                     //Se recorren la memoria de registros
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la segunda variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(instructions[k][2],registersMemory[j]->name) == 0)
        //                         {
        //                             variable_1 = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     //En caso de que no exista la segunda variable en memoria, error.
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         strcpy(error,"No existe la variable ");
        //                         strcat(error,instructions[k][2]);
        //                         strcat(error," en instrucción ");
        //                         strcat(error,instructions[k][0] );
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //
        //                     //Se recorren la memoria de registros
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la tercera variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(instructions[k][3],registersMemory[j]->name) == 0)
        //                         {
        //                             variable_2 = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     //En caso de que no exista la tercera variable en memoria
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         //Si la instrucción es addi, entonces se toma el número de la instrucción
        //                         if (strcmp(instructions[k][0],"addi") == 0)
        //                         {
        //                             variable_2 = atoi(instructions[k][3]);
        //                         }
        //
        //                         //Si es sub, error.
        //                         else
        //                         {
        //                             strcpy(error,"No existe la variable ");
        //                             strcat(error,instructions[k][3]);
        //                             strcat(error," en instrucción ");
        //                             strcat(error,instructions[k][0] );
        //                             writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                             writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         }
        //                     }
        //
        //                     //Se realiza la operación
        //
        //                     if (variable_2 == 0)
        //                     {
        //                         strcpy(error,"No se puede realizar división por 0 ");
        //                         strcat(error," en instrucción ");
        //                         strcat(error,instructions[k][0] );
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //
        //                     result = variable_1 / variable_2;
        //
        //                     if (controlLinesMemory[8] == 'x')
        //                     {
        //                         //Se recorren la memoria de registros
        //                         for (j = 0; j < REGISTERSNUMBER; j++)
        //                         {
        //                             //Se verifica si la primera variable de la instrucción existe
        //                             //En caso de hacerlo, guarda el resultado en memoria
        //                             if (strcmp(instructions[k][1],registersMemory[j]->name) == 0)
        //                             {
        //                                 registersMemory[j]->value = result;
        //                                 break;
        //                             }
        //                         }
        //
        //                         if (j == REGISTERSNUMBER)
        //                         {
        //                             strcpy(error,"No existe la variable ");
        //                             strcat(error,instructions[k][1]);
        //                             strcat(error," en instrucción ");
        //                             strcat(error,instructions[k][0] );
        //                             writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                             writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                         }
        //
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //                 }
        //
        //                 else if (strcmp(instructions[k][0],"lw") == 0)
        //                 {
        //                     char * offset_variable = malloc(sizeof(char)*5);
        //                     int offset_variable_number = 0;
        //                     int memory_direction = 0;
        //                     int offset_number = 0;
        //                     char* token;
        //                     char * aux = malloc(sizeof(char)*strlen(instructions[k][2]));
        //                     strcpy(aux,instructions[k][2]);
        //                     token = strtok(aux,"(");
        //                     offset_number = atoi(token);
        //                     token = strtok(NULL,")");
        //                     strcpy(offset_variable,token);
        //
        //                     int j;
        //                     //Se recorren la memoria de registros
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la segunda variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(offset_variable,registersMemory[j]->name) == 0)
        //                         {
        //                             offset_variable_number = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         strcpy(error,"No existe la variable ");
        //                         strcat(error,instructions[k][1]);
        //                         strcat(error," en instrucción ");
        //                         strcat(error,instructions[k][0] );
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //
        //                     memory_direction = (offset_variable_number + offset_number)/4;
        //
        //
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la segunda variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(instructions[k][1],registersMemory[j]->name) == 0)
        //                         {
        //                             registersMemory[j]->value =  virtualMemory[memory_direction];
        //                             break;
        //                         }
        //                     }
        //
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         strcpy(error,"No existe la variable ");
        //                         strcat(error,instructions[k][1]);
        //                         strcat(error," en instrucción ");
        //                         strcat(error,instructions[k][0] );
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //
        //                     writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                     writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                 }
        //
        //                 else if (strcmp(instructions[k][0],"sw") == 0)
        //                 {
        //                     char * offset_variable = malloc(sizeof(char)*5);
        //                     int offset_variable_number = 0;
        //                     int memory_direction = 0;
        //                     int offset_number = 0;
        //                     char* token;
        //                     char * aux = malloc(sizeof(char)*strlen(instructions[k][2]));
        //                     strcpy(aux,instructions[k][2]);
        //                     token = strtok(aux,"(");
        //                     offset_number = atoi(token);
        //                     token = strtok(NULL,")");
        //                     strcpy(offset_variable,token);
        //
        //                     int j;
        //                     //Se recorren la memoria de registros
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la segunda variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(offset_variable,registersMemory[j]->name) == 0)
        //                         {
        //                             offset_variable_number = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         strcpy(error,"No existe la variable ");
        //                         strcat(error,instructions[k][1]);
        //                         strcat(error," en instrucción ");
        //                         strcat(error,instructions[k][0] );
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //
        //                     memory_direction = (offset_variable_number + offset_number)/4;
        //
        //
        //                     for (j = 0; j < REGISTERSNUMBER; j++)
        //                     {
        //                         //Se verifica si la segunda variable de la instrucción existe
        //                         //En caso de hacerlo, se toma su valor de memoria
        //                         if (strcmp(instructions[k][1],registersMemory[j]->name) == 0)
        //                         {
        //                             virtualMemory[memory_direction] = registersMemory[j]->value;
        //                             break;
        //                         }
        //                     }
        //
        //                     if (j == REGISTERSNUMBER)
        //                     {
        //                         strcpy(error,"No existe la variable ");
        //                         strcat(error,instructions[k][1]);
        //                         strcat(error," en instrucción ");
        //                         strcat(error,instructions[k][0] );
        //                         writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                     }
        //
        //                     writeInstructions(instructions[k], error,&created_1, fp_output_name_1);
        //                     writeRegisters(registersMemory,instructions[k], &created_2, fp_output_name_2);
        //                 }
        //
        //                 //Se recorren la memoria de registros
        //                 for (j = 0; j < REGISTERSNUMBER; j++)
        //                 {
        //                     //Se verifica si la segunda variable de la instrucción existe
        //                     //En caso de hacerlo, se toma su valor de memoria
        //                     if (strcmp(instructions[i][1],registersMemory[j]->name) == 0)
        //                     {
        //                         variable_1 = registersMemory[j]->value;
        //                         break;
        //                     }
        //                 }
        //
        //                 //En caso de que no exista la segunda variable en memoria, error.
        //                 if (j == REGISTERSNUMBER)
        //                 {
        //                     strcpy(error,"No existe la variable ");
        //                     strcat(error,instructions[i][1]);
        //                     writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                     writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //                 }
        //
        //
        //                 //Se recorren la memoria de registros
        //                 for (j = 0; j < REGISTERSNUMBER; j++)
        //                 {
        //                     //Se verifica si la tercera variable de la instrucción existe
        //                     //En caso de hacerlo, se toma su valor de memoria
        //                     if (strcmp(instructions[i][2],registersMemory[j]->name) == 0)
        //                     {
        //                         variable_2 = registersMemory[j]->value;
        //                         break;
        //                     }
        //                 }
        //                 //En caso de que no exista la tercera variable en memoria
        //                 if (j == REGISTERSNUMBER)
        //                 {
        //                     strcpy(error,"No existe la variable ");
        //                     strcat(error,instructions[i][2]);
        //                     writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                     writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //                 }
        //
        //
        //                 if (variable_1 == variable_2)
        //                 {
        //                     char * label = malloc(sizeof(char)*(strlen(instructions[i][1])+1));
        //                     strcpy(label,instructions[i][3]);
        //                     strcat(label, ":\0");
        //                     int j;
        //                     for (j = 0; j < atoi(instructions[0][0]); j++)
        //                     {
        //                         if (strcmp(instructions[j][0],label) == 0)
        //                         {
        //                             break;
        //                         }
        //                     }
        //
        //                     if (j == atoi(instructions[0][0]))
        //                     {
        //                         strcpy(error,"No existe la etiqueta ");
        //                         strcat(error,instructions[i][1]);
        //                         writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                         writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //                     }
        //                     writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                     writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //                     i = j;
        //                     break;
        //                 }
        //                 k++;
        //             }
        //
        //             if (strcmp(instructions[k][0],"j") != 0)
        //             {
        //                 char * label = malloc(sizeof(char)*(strlen(instructions[i][1])+1));
        //                 strcpy(label,instructions[i][3]);
        //                 strcat(label, ":\0");
        //                 for (j = 0; j < atoi(instructions[0][0]); j++)
        //                 {
        //                     if (strcmp(instructions[j][0],label) == 0)
        //                     {
        //                         break;
        //                     }
        //                 }
        //
        //                 if (j == atoi(instructions[0][0]))
        //                 {
        //                     strcpy(error,"No existe la etiqueta ");
        //                     strcat(error,instructions[i][1]);
        //                     writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                     writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //                 }
        //
        //                 i = j;
        //                 continue;
        //             }
        //         }
        //
        //         //Si linea de control Branch tiene stuck at 0
        //         else
        //         {
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             continue;
        //         }
        //     }
        //
        //     //En caso de que la instrucción sea lw
        //     else if (strcmp(instructions[i][0],"lw") == 0)
        //     {
        //
        //         //Si linea de control MemRead no tiene stuck at 0
        //         if (controlLinesMemory[3] == 'x')
        //         {
        //             char * offset_variable = malloc(sizeof(char)*5);
        //             int offset_variable_number = 0;
        //             int memory_direction = 0;
        //             int offset_number = 0;
        //             char* token;
        //             char * aux = malloc(sizeof(char)*strlen(instructions[i][2]));
        //             strcpy(aux,instructions[i][2]);
        //             token = strtok(aux,"(");
        //             offset_number = atoi(token);
        //             token = strtok(NULL,")");
        //             strcpy(offset_variable,token);
        //
        //             int j;
        //             //Se recorren la memoria de registros
        //             for (j = 0; j < REGISTERSNUMBER; j++)
        //             {
        //                 //Se verifica si la segunda variable de la instrucción existe
        //                 //En caso de hacerlo, se toma su valor de memoria
        //                 if (strcmp(offset_variable,registersMemory[j]->name) == 0)
        //                 {
        //                     offset_variable_number = registersMemory[j]->value;
        //                     break;
        //                 }
        //             }
        //
        //             if (j == REGISTERSNUMBER)
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][1]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //
        //             memory_direction = (offset_variable_number + offset_number)/4;
        //
        //
        //             for (j = 0; j < REGISTERSNUMBER; j++)
        //             {
        //                 //Se verifica si la segunda variable de la instrucción existe
        //                 //En caso de hacerlo, se toma su valor de memoria
        //                 if (strcmp(instructions[i][1],registersMemory[j]->name) == 0)
        //                 {
        //                     registersMemory[j]->value =  virtualMemory[memory_direction];
        //                     break;
        //                 }
        //             }
        //
        //             if (j == REGISTERSNUMBER)
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][1]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Si linea de control MemRead tiene stuck at 0
        //         else
        //         {
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             continue;
        //         }
        //     }
        //
        //     //En caso de que la instrucción sea sw
        //     else if (strcmp(instructions[i][0],"sw") == 0)
        //     {
        //
        //         //Si linea de control MemWrite no tiene stuck at 0
        //         if (controlLinesMemory[6] == 'x')
        //         {
        //             char * offset_variable = malloc(sizeof(char)*5);
        //             int offset_variable_number = 0;
        //             int memory_direction = 0;
        //             int offset_number = 0;
        //             char* token;
        //             char * aux = malloc(sizeof(char)*strlen(instructions[i][2]));
        //             strcpy(aux,instructions[i][2]);
        //             token = strtok(aux,"(");
        //             offset_number = atoi(token);
        //             token = strtok(NULL,")");
        //             strcpy(offset_variable,token);
        //
        //             int j;
        //             //Se recorren la memoria de registros
        //             for (j = 0; j < REGISTERSNUMBER; j++)
        //             {
        //                 //Se verifica si la segunda variable de la instrucción existe
        //                 //En caso de hacerlo, se toma su valor de memoria
        //                 if (strcmp(offset_variable,registersMemory[j]->name) == 0)
        //                 {
        //                     offset_variable_number = registersMemory[j]->value;
        //                     break;
        //                 }
        //             }
        //
        //             if (j == REGISTERSNUMBER)
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][1]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //
        //             memory_direction = (offset_variable_number + offset_number)/4;
        //
        //
        //             for (j = 0; j < REGISTERSNUMBER; j++)
        //             {
        //                 //Se verifica si la segunda variable de la instrucción existe
        //                 //En caso de hacerlo, se toma su valor de memoria
        //                 if (strcmp(instructions[i][1],registersMemory[j]->name) == 0)
        //                 {
        //                     virtualMemory[memory_direction] = registersMemory[j]->value;
        //                     break;
        //                 }
        //             }
        //
        //             if (j == REGISTERSNUMBER)
        //             {
        //                 strcpy(error,"No existe la variable ");
        //                 strcat(error,instructions[i][1]);
        //                 strcat(error," en instrucción ");
        //                 strcat(error,instructions[i][0] );
        //                 writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //                 writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             }
        //
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //         }
        //
        //         //Si linea de control MemWrite tiene stuck at 0
        //         else
        //         {
        //             writeInstructions(instructions[i], error,&created_1, fp_output_name_1);
        //             writeRegisters(registersMemory,instructions[i], &created_2, fp_output_name_2);
        //             continue;
        //         }
        //     }
        // }

    //}
    printf("Ha terminado la ejecución del programa, por favor revise los archivos de salida: %s y %s\n", fp_output_name_1, fp_output_name_2);

    return 0;
}
