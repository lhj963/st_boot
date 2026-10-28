	AREA    |.text|, CODE, READONLY
		
cpu_int_en PROC
	EXPORT cpu_int_en
	CPSIE   I				;开中断
	BX LR
	ENDP

cpu_int_dis PROC
	EXPORT cpu_int_dis
	CPSID   I				;关中断
	BX LR
	ENDP

start_thread PROC
	;start_thread(void)
	EXPORT start_thread
	IMPORT pCurThread
	
	LDR R0,=pCurThread		;SP = pCurThread->sp
	LDR R0,[R0]
	LDR SP,[R0]
	
	MOV R1,SP				;pCurThread->sp += 0x40;
	ADD R1,R1,#0x40
	STR R1,[R0]

	POP {R4-R11}
	POP {R0-R3,R12,LR}
	POP {R1}
	POP {R0}
	PUSH {R1}
	POP {PC}

	ENDP


triger_pendsv PROC
	EXPORT triger_pendsv
	PUSH {R0-R1,LR}

	LDR R0,=0xE000ED22
	LDR R1,=0xFF
	STRB R1,[R0]
	LDR R0,=0xE000ED04
	LDR R1,=0x10000000
	STR R1,[R0]

	POP {R0-R1,PC}
	ENDP

context_sw PROC
	EXPORT context_sw
	
	PUSH {LR}
	BL triger_pendsv
	POP {PC}
	ENDP

context_sw_int PROC
	EXPORT context_sw_int

	PUSH {LR}
	BL triger_pendsv
	POP {PC}

	ENDP

PendSV_Handler PROC
	EXPORT PendSV_Handler
	IMPORT pCurThread;
	IMPORT pHighThread;

	CPSID   I
	PUSH {R4-R11}
	;update the cur sp
	LDR R0,=pCurThread
	LDR R0,[R0]
	STR SP,[R0]

	LDR R0,=pHighThread
	LDR R0,[R0]
	LDR SP,[R0]

	POP {R4-R11}
	CPSIE   I
	BX LR
	NOP
	ENDP

	END





