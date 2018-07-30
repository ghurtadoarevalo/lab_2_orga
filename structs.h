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

	bool block;
} bufferIF_ID;

typedef struct {
	bool status;
	//ID
	char AluSrc;
	char AluOp_0;
	char AluOp_1;
	char RegDst;
	//EX
	char Branch;
	char Jump;
	char MemWrite;
	char MemRead;
	//WB
	char MemToreg;
	char RegWrite;

	char** instruction_1;
	char** instruction_2;

	int previus_PC;

	bool block;


} bufferID_EX;

typedef struct {
	bool status;
	//EX
	char Branch;
	char Jump;
	char MemWrite;
	char MemRead;

	//WB
	char MemToreg;
	char RegWrite;

	int alu_result;
	char** instruction_1;
	char** instruction_2;

	int previus_PC;
	bool block;


} bufferEX_MEM;

typedef struct {
	bool status;
	//WB
	char MemToreg;
	char RegWrite;

	char** instruction_1;
	char** instruction_2;

	int alu_result;
	int memory_data;
	bool block;

} bufferMEM_WB;

typedef struct {
	bool status;

	char** instruction_1;
	char** instruction_2;
	bool block;

} bufferMWB_END;


#endif
