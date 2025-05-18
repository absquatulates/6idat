
.equ LCD_ADDR  = $20

LCD_INIT:
	rcall	DELAY
	ldi		r16, LCD_ADDR	
	lsl		r16 
	rcall	START
	rcall	DATA_SEND ; skickar ut adressen

	ldi		r16 ,$34 // 
	rcall	DATA_SEND ; data ut
	ldi		r16, $30
	rcall	DATA_SEND ; data ut 
;	rcall	DELAY
	ldi		r16, $34
	rcall	DATA_SEND ; data ut 
	ldi		r16, $30
	rcall	DATA_SEND ; data ut 
	;rcall	DELAY

	ldi		r16, $34
	rcall	DATA_SEND ; data ut 
	ldi		r16, $30
	rcall	DATA_SEND ; data ut 
	;rcall	DELAY

	ldi		r16, $24
	rcall	DATA_SEND ; data ut 
	ldi		r16, $20
	rcall	DATA_SEND ; data ut 
	rcall	WAIT

	rcall	STOP


	//////////// Funktion set 4 bites, 2 lines disp, /// tror 
	ldi		r18, $20
	ldi		r19, $80
	rcall	LCD_SEND_BYTE
	rcall	WAIT 

	//////////// display control
	ldi		r18, $00
	ldi		r19, $E0
	rcall	LCD_SEND_BYTE
	rcall	WAIT 

	//Entry mode set
	ldi		r18, $00
	ldi		r19, $60
	rcall	LCD_SEND_BYTE
	///// "ren" kallstart slutar här. 
	ret

UPPSTART_LCD:
	rcall	LCD_INIT
	rcall	DELAY
	rcall	CLEAR_LCD

	ldi		r23, 2	
UPPDATERING:
	rcall	LEDTEXT_OUT
	rcall	CLEAR_LCD
	dec		r23
	brne	UPPDATERING

MAIN_SCREEN:
	rcall	MAIN_SCREEN_TEXT
	ret



MENY_CHOICE: // väljer tillhörande meny med r24
	cpi		r24, 0
	breq	MENY_ZERO
	cpi		r24,  1 
	breq	MENY_ONE
	cpi		r24,  2
	breq	MENY_TWO
// hamnar här om val 3
	ldi		ZH,HIGH(SPELA_UPP2*2) 	
	ldi		ZL,LOW(SPELA_UPP2*2)	
	rjmp	MENY_OUT
MENY_ZERO:
	ldi		ZH,HIGH(SPELA_IN1*2) 	
	ldi		ZL,LOW(SPELA_IN1*2)	
	rjmp	MENY_OUT
MENY_ONE:
	ldi		ZH,HIGH(SPELA_UPP1*2) 	
	ldi		ZL,LOW(SPELA_UPP1*2)	
	rjmp	MENY_OUT
MENY_TWO:
	ldi		ZH,HIGH(SPELA_IN2*2) 	
	ldi		ZL,LOW(SPELA_IN2*2)	
	rjmp	MENY_OUT
MENY_OUT:
	rcall	TWO_ROWS_TXT
	ret		
	


MAIN_SCREEN_TEXT:
	ldi		ZH,HIGH(LEDTEXT_TXT*2) 	
	ldi		ZL,LOW(LEDTEXT_TXT*2)	

	rcall	TWO_ROWS_TXT
	ret


TWO_ROWS_TXT: // tar det z pekar på och skriver ut det på två rader. 
	ldi		r19, $00  
	rcall	SET_RAM_ADDR; har r19 som adress, vart adressen hörtill finns i databladet

	rcall	STRING_OUT
	ldi		r19, 40
	rcall	SET_RAM_ADDR; har r19 som adress, vart adressen hörtill finns i databladet
	rcall	STRING_OUT
	ret

LEDTEXT_OUT:
	ldi		ZH,HIGH(UPPDATE_TXT1*2) 	
	ldi		ZL,LOW(UPPDATE_TXT1*2)

	rcall	TWO_ROWS_TXT ;"Windows uppdateras"

	rcall	DELAYX4
	rcall	DELAYX4
	rcall	CLEAR_LCD

	ldi		ZH,HIGH(UPPDATE_TXT2*2) 	
	ldi		ZL,LOW(UPPDATE_TXT2*2)
	rcall	TWO_ROWS_TXT ;"var god dröj. Stäng ej av !" 

	rcall	DELAYx4
	rcall	DELAYX4
	rcall	DELAYX4
	ret

LCD_LETTER: ; skriver nu ut r18 som ascii på lcd:n
	mov		r19, r18
	andi	r18, $F0
	swap	r19 
	andi	r19, $F0

	ldi		r16, $01
	add		r18, r16
	add		r19, r16

	rcall	LCD_SEND_BYTE
	ret

CLEAR_LCD:
	ldi		r18, $00
	ldi		r19, $10
	rcall	LCD_SEND_BYTE
	rcall	DELAY 
	ret

HOME_LCD:
	ldi		r18, $00
	ldi		r19, $20
	rcall	LCD_SEND_BYTE
	ret



SET_RAM_ADDR:	; har r19 som adress ,tex r19 = 40, $28 in hex, kom ihåg att txt:en är misaligmed med ett just nu 
	mov		r18, r19
	andi	r18, $F0
	ldi		r17, $80
	add		r18, r17 
	andi	r19, $0F
	swap	r19

	call	LCD_SEND_BYTE; tar r18 som högre nibbles , och r19 som läggre nibbles
	ret

LCD_SEND_BYTE: ; tar r18 som högre nibbles , och r19 som läggre nibbles
	ldi		r16, LCD_ADDR
	ldi		r17, $0C

	lsl		r16 
	rcall	START
	rcall	DATA_SEND ; skickar ut adressen

	mov		r16,r18
	add		r16, r17
	rcall	DATA_SEND ; data ut 

	rcall	WAIT 

	subi	r16, $04
	rcall	DATA_SEND ; e dras låg

	mov		r16, r19
	add		r16, r17
	rcall	DATA_SEND ; data ut 

	rcall	WAIT 

	subi	r16, $04
	rcall	DATA_SEND ; e dras låg
		
	rcall	STOP
	
	ret

GET_CHAR: 
	lpm		r18,Z+
	ret



DELAYX4:
	rcall	DELAY
	rcall	DELAY
	rcall	DELAY
	ret


STRING_OUT:
	rcall	GET_CHAR
	cpi		r18, $00
	breq	NEXT_WORD
	rcall	LCD_LETTER
	rjmp	STRING_OUT
NEXT_WORD:
	ret