KEYBOARD_INIT:
	ldi r16,(0<<ISC00)
	sts EICRA, r16
	ret

KEYBOARD_ON:
	push r16
	ldi r16,(1<<INT0)		;PS/2 interrupt enabled
	out EIMSK, r16
	pop r16
	ret

KEYBOARD_OFF:
	push r16
	ldi r16,(0<<INT0)		;PS/2 interrupt disabled
	out EIMSK, r16
	pop r16
	ret


KEY_PRESSED:
	push r16
	in r16,SREG
	push r16
	push r19
	push r20
	push r18
	push r17

	;rcall rotled_green

	clr r19			//Dataregister
	clr r18			//Paritetsräknare
	ldi r17,$08		//loopräknare för 8 data (bortse från paritet)
BEGIN:
	rcall WAIT_UNTIL_DATA
	sbis PINB,2		//Kollar status på SDA
	rjmp shift_data
	inc r18			//räknare för paritet
	sec				//Sätter Carry att skifta in i dataregister
shift_data:
	ror r19			//Skiftar in biten
	dec r17			
	brne BEGIN		//loopar x8
	rcall WAIT_UNTIL_DATA
PARITET:
	sbic PINB,2
	inc r18
	lsr r18
	brcs ERROR
	rjmp STOPP
ERROR:				//Hanteras ej ännu. Borde tilldela r19 dess gamla värde eller hur det nu kan se ut.
STOPP:
	rcall WAIT_UNTIL_DATA
WAIT_STOP:
	sbis PIND,2		//Väntar tills CLK HÖG
	rjmp WAIT_STOP
	
	cpi r25,$F0
	brne NOT_BREAK
	ldi r19,$FF			;Ändrar så att r25 = prev_key != F0 vid sista byte i break-key
NOT_BREAK:
	rcall MAKE_TO_SOUND

	cpi r24,0				;OM MENYVAL = inspelning 2
	breq RECORDING_1
	cpi r24,2				;OM MENYVAL = inspelning 2
	breq RECORDING_2

RECORDING_1:
	ldi YL,LOW(SONG1+song_length-5)
	ldi YH,HIGH(SONG1+song_length-5)
	cp XL,YL
	brne SAVE
	cp XH,YH
	brne SAVE
MEMORY1_FULL:
	ldi r19,$69  ;förekommer ej annars
	rjmp DONE_RECORDING

RECORDING_2:
	ldi r16,LOW(SONG2+song_length-5)
	ldi r17,HIGH(SONG2+song_length-5)
	cp XL,r16
	brne SAVE
	cp XH,r17
	brne SAVE
MEMORY2_FULL:
	ldi r19,$69 ;förekommer ej annars
	rjmp DONE_RECORDING
SAVE:
	rcall SAVE_IF_UNIQUE
DONE_RECORDING:
	mov r25,r19 ; prev = new

	clr r16
	sts EIFR,r16

	pop r17
	pop r18
	pop r20
	pop r19
	pop r16
	out SREG,r16
	pop r16
	reti

SAVE_IF_UNIQUE:
	cp r25,r19				;	if r25 != r19 and r25 != $F0  
	breq DONT_SAVE_KEY		;	
	cpi r25,$F0				;	
	breq DONT_SAVE_KEY		;	

	rcall IS_VALID_KEY
	brcc DONT_SAVE_KEY

	in r18,SREG ;atomic-read. knsk Onödigt men inte skadligt
	cli
	lds	r17, TCNT1L
	lds	r17, TCNT1H

	st X+, r17 ; Spara tiden (OCR1AH) i "musik-stacken" 
	st X+, r19 ; Spara MAKE-key eller F0 i musikstacken

	clr	r17
	sts TCNT1H,	r17
	sts TCNT1L,	r17
	out SREG,	r18
DONT_SAVE_KEY:

	ret


WAIT_UNTIL_DATA:
	sbis PIND,2
	rjmp WAIT_UNTIL_DATA
CLK_HIGH:
	sbic PIND,2
	rjmp CLK_HIGH
	ret

IS_VALID_KEY:
	ldi ZH,HIGH(MAKE_SOUND_MAP*2)
	ldi ZL,LOW(MAKE_SOUND_MAP*2)
	CLC
LOOK_NEXT:
	lpm r17,Z
	cp r19,r17
	breq IS_IN
	cpi r19,$FF
	breq NOT_IN
	adiw Z,2
	rjmp LOOK_NEXT
IS_IN:
	SEC
NOT_IN:
	ret



HEX_VAL_LOOKUP:							//tillfällig - Översätter tangenttryck till motsv. 1-bytes hex tal
	push r21
	push ZL
	push ZH

	ldi ZL,LOW(PS2_TABELL*2)
	ldi ZH,HIGH(PS2_TABELL*2)
	ldi r20,255		//eftersom vill börja på 0
LOOP_TABLE:
	inc r20			//Loopar genom PS2_TABELL tills matchning mellan tabellvärde och Make Code. r20 motsvarar det decimala talet för 0-F HEX
	cpi r20,$10
	breq LOOKUP_DONE
	lpm r21,Z+
	cp r21,r19
	brne LOOP_TABLE
LOOKUP_DONE:

	pop ZH
	pop ZL
	pop r21
	ret

PS2_TABELL:
	.db $45, $16, $1E, $26, $25, $2E, $36, $3D, $3E, $46, $1C, $32, $21, $23, $24, $2B,$F0,$00