#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum { false, true } bool;


//Estructura que se utiliza para almacenar las stopwords
typedef struct {
	int value;
	char* name;
} reg;

typedef struct {
	bool status;
	char** instruction_1;
	char** instruction_2;
} bufferIF_ID;

typedef struct {
	bool status;
	//ID
	char AluSrc;
	char* AluOp;
	char RegDst;
	//EX
	char Branch;
	char MemWrite;
	char MemRead;
	//WB
	char MemToreg;
	char RegWrite;

	char** instruction_1;
	char** instruction_2;
} bufferID_EX;

typedef struct {
	bool status;
	//EX
	char Branch;
	char MemWrite;
	char MemRead;

	//WB
	char MemToreg;
	char RegWrite;

	char** instruction_1;
	char** instruction_2;
} bufferEX_MEM;

typedef struct {
	bool status;
	//WB
	char MemToreg;
	char RegWrite;

	char** instruction_1;
	char** instruction_2;
} bufferMEM_WB;


#endif
