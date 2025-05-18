
.equ song_length = 500
.def zero=r2
.dseg
.org SRAM_START
SONG1:.byte song_length
SONG2:.byte song_length
.cseg

.org $0000 
rjmp HW_INIT

.org INT0addr ;0x0002 //INT0
rjmp KEY_PRESSED

.org $0016 //TIMER 1A
	rjmp TIMER1_ISR

HW_INIT:
	clr r20
	clr zero
	clr r16
	clr r23
	clr r25
	clr r24

	out DDRD,r16
	out DDRB,r16

	rcall TWI_INIT
	rcall MEMORY_TIMER_INIT
	rcall KEYBOARD_INIT
	rcall SOUND_INIT

	rcall	UPPSTART_LCD
	sei

ROT_WAIT:
	rcall	rotled_red
	rcall	WAIT_ROT_ENC
	rcall	CLEAR_LCD
	rcall	MENY_CHOICE
	rcall	KEYBOARD_ON
MAIN:
	rcall	ROTLED_BOTH

	rcall	ROTART_LF			;kollar efter vred-rot
	rcall	UPDATE_MENY			;uppdaterar menyval & LCD

	mov		r20,r24				;Skriver ut menyval
	rcall	SJUSEG_LOOKUP		;
	rcall	LEFT_8_WRITE		;

	rcall CHECK_ROT			//SEC om vred nedtryckt
	brcc MAIN				//Loopar om ej SEC

	rcall ROTLED_GREEN

	cpi r24,0
	breq RECORD_1
	cpi r24,1
	breq PLAY_1
	cpi r24,2
	breq RECORD_2
	cpi r24,3
	breq PLAY_2

	rjmp MAIN

RECORD_1:
	rcall RECORD_SONG_1
	rjmp MAIN
PLAY_1:
	rcall PLAY_SONG_1
	rjmp MAIN
RECORD_2:
	rcall RECORD_SONG_2
	rjmp MAIN
PLAY_2:
	rcall PLAY_SONG_2
	rjmp MAIN


RECORD_SONG_1:
	ldi XL,LOW(SONG1)
	ldi XH,HIGH(SONG1)
	rcall RECORD //Spelar in
	ret

RECORD_SONG_2:
	ldi XL,LOW(SONG2)
	ldi XH,HIGH(SONG2)
	rcall RECORD //Spelar in
	ret

RECORD:
	rcall ROTLED_RED
	rcall KEYBOARD_ON
	ldi ZH,HIGH(SPELAR_IN*2)
	ldi ZL,LOW(SPELAR_IN*2)
	rcall TWO_ROWS_TXT

	ldi r16,$F0
	st X+,r16				
	ldi r25,$FF				//Initerar med unik byte för första

WAIT_KEY:					;Väntar på input
	cpi r25,$F0				
	breq WAIT_KEY

	rcall TIMER1_ON

	ldi r20,30				//styr inspelningstid
RECORD_LOOP:				
	rcall delay
	rcall ROTLED_RED
	rcall delay
	rcall ROTLED_OFF
					
	cpi r25,$69
	breq MEMORY_FULL
	dec r20
	brne RECORD_LOOP 
MEMORY_FULL:

	clr r20
	cpi r25,$F0
	breq LAST_WAS_BREAK
	lds	r20, TCNT1L
	lds	r20, TCNT1H
LAST_WAS_BREAK:
	st X+,r20

	cli
	rcall SOUND_TIMER_OFF
	rcall TIMER1_OFF
	rcall KEYBOARD_OFF

	ldi r20,$FF //Sparar stoppet
	st X+,r20
	st X+,r20
	st X+,r20

	ret

PLAY_SONG_1:
	ldi XL,LOW(SONG1)
	ldi XH,HIGH(SONG1)
	rcall PLAY
	ret

PLAY_SONG_2:
	ldi XL,LOW(SONG2)
	ldi XH,HIGH(SONG2)
	rcall PLAY
	ret

PLAY:
	clr r25
	clr r16
	sts OCR1AH, r16
	sts OCR1AL, r16

	ldi ZH,HIGH(SPELAR_UPP*2)
	ldi ZL,LOW(SPELAR_UPP*2)
	rcall TWO_ROWS_TXT

	rcall KEYBOARD_OFF
	rcall ROTLED_GREEN

	sei
	rcall TIMER1_ON
LOOPEN:					
	cpi r25,$FF
	brne LOOPEN

	rcall SOUND_TIMER_OFF
	rcall TIMER1_OFF
	rcall KEYBOARD_ON

	ret

TIMER1_ISR:  
	push r16
	in r16,SREG
	push r16
	push r20
	push r19
	push r18

	cpi r24,1
	breq PLAYBACK
	cpi r24,3
	breq PLAYBACK
INSPELNING:			;om inspelning
	ldi r16,$F0
	ldi r20,$FF

	in r18,SREG
	cli
	st X+, r20 ; Spara tiden OCR1AH 
	st X+, r16 ; Spara prev MAKE-key eller F0

	clr	r20
	sts TCNT1H,	r20
	sts TCNT1L,	r20
	out SREG,	r18
		
	rjmp LEAVING	
PLAYBACK:			;om uppspelning
	ld r19,X+
	mov r25,r19

	rcall MAKE_TO_SOUND
	rcall PRINT_R25 ///print r25 till sjusegment

	ld r19,X+
	sts OCR1AH, r19
	sts OCR1AL, r19 ;
LEAVING:
	pop r18
	pop r19
	pop r20
	pop r16
	out SREG,r16
	pop r16

	reti

TIMER1_ON:
	push r16
	ldi r16,(1<<OCIE1A)	//Tillåt avbrott
	sts TIMSK1, r16
	pop r16
	ret

TIMER1_OFF:
	push r16
	ldi r16,(0<<OCIE1A)	//Tillåt inte avbrott
	sts TIMSK1, r16
	pop r16
	ret

MEMORY_TIMER_INIT:
	sbi DDRB,1 ; P1=OUTPUT
	ldi r16, (0<<COM1A1) | (0<<COM1A0) ; Toggle OC1A on compare match (för digitalanalysator)
	sts TCCR1A, r16

	ldi r16, (1<<CS12) | (0<<CS11) | (1<<CS10) | (1<<WGM12) ; Prescaler 1024 (långsamast), WGM12 väljer CTC för jämförelse med OCR1A. Avbrott på adress 0x0016. 
	sts TCCR1B, r16

	ldi r16, 255  ; Jämförelseregister
	sts OCR1AH, r16
	sts OCR1AL, r16

	ret

UPDATE_MENY: ; den tar in ett värde från 
	cpi		r23, 2
	breq	PREV	
	cpi		r23, 1
	breq	NEXT
	rjmp	MENY_DONE 
PREV:	
	cpi		r24, 0
	breq	MENY_DONE 		
	dec		r24
	rjmp	NEW_MENY
NEXT:
	cpi		r24, 3 
	breq	MENY_DONE 
	inc		r24
NEW_MENY:  ;; inte jättebra namn 
	rcall	MENY_CHOICE
MENY_DONE:
	ret

ROTART_LF: // r23=1 om höger, r23=2 om vänster
	in		r16,PIND
	andi	r16,$C0
	cpi		r16, $C0
	brne	L_OR_F
	clr		r23
	rjmp	ROT_DONE
L_OR_F: ;LEFT OR RIGHT 
	cpi		r16, $80
	brne	RIGHT
	ldi		r23, 2	
	rjmp	REPEAT
RIGHT:
	ldi		r23,1
REPEAT:
	in		r16, PIND
	andi	r16, $C0
	cpi		r16,$C0
	brne	REPEAT
ROT_DONE:
	ret

.include "keyboard.asm"
.include "sju_seg.asm"
.include "LCD.asm"
.include "Led&switch.asm"
.include "sound.asm"

