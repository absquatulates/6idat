		SECTION	.data
		EXTERN	inbound_queue	; (defined in main.C)
data		DB	0		; put rcvd byte here

		SECTION	.text
		ALIGN	16
		BITS	32

BASE_PORT	EQU	3F8h		; we have this in our lab

LSR_PORT	EQU	BASE_PORT+5
RBR_PORT	EQU	BASE_PORT
THR_PORT	EQU	BASE_PORT

; ---------------------------------------------------------------------
; void SerialPut(char ch)
; ---------------------------------------------------------------------
; This function uses programmed waiting loop I/O
; to output the ASCII character 'ch' to the UART.

		GLOBAL	SerialPut

SerialPut:	
	MOV DX, LSR_PORT
WAIT_FOR_THRE: ; (1) Wait for THRE = 1
	IN 	AL, DX
	AND AL, 0x20
	JZ 	WAIT_FOR_THRE

	; (2) Output character to UART
	MOV DX, THR_PORT
	MOV AL, [ESP+4]
	OUT DX, AL

	RET ; (3) Return to caller

; ---------------------------------------------------------------------
; void interrupt SerialISR(void)
; ---------------------------------------------------------------------
; This is an Interrupt Service Routine (ISR) for
; serial receive interrupts.  Characters received
; are placed in a queue by calling Enqueue(char).

		GLOBAL	SerialISR
		EXTERN	QueueInsert	; (provided by LIBPC)

SerialISR:	STI             	; Enable (higher-priority) IRQs 

	; (1) Preserve all registers
	PUSHA			

	; (2) Get character from UART
	MOV DX, LSR_PORT	
	IN	AL, DX
	AND AL, 0x1
	JZ	_Eoi
	
	MOV DX, RBR_PORT
	IN 	AL, DX

	; (3) Put character into queue
	MOV [data], AL
	PUSH data					; Param #2: address of data
	PUSH DWORD [inbound_queue]	; Param #1: address of queue

	CALL QueueInsert
	ADD	 ESP,8



_Eoi:		
	; (4) Enable lower priority interrupts
	MOV AL, 0x20	; (Send Non-Specific EOI to PIC)
	OUT 0x20, AL

	POPA		; (5) Restore all registers
	IRET		; (6) Return to interrupted code