
SOUND_TIMER_ON:
	push r16
	ldi r16, (1<<CS02)|(0<<CS01)|(0<<CS00)
	out TCCR0B, r16		;Prescaler 256
	pop r16
	ret

SOUND_TIMER_OFF:
	push r16
	ldi r16, (0<<CS02)|(0<<CS01)|(0<<CS00)
	out TCCR0B, r16		;Timer avstängd
	pop r16
	ret

SOUND_TIMER_INIT:
	push r16
	ldi r16, (1<<COM0B0)|(1<<WGM01)
	out TCCR0A, r16
	pop r16
	ret

SOUND_INIT:
	sbi DDRD,5
	rcall SOUND_TIMER_INIT
	ret

MAKE_TO_SOUND:
	push ZL
	push ZH
	push r16

	ldi  ZL,LOW(MAKE_SOUND_MAP*2)
	ldi  ZH,HIGH(MAKE_SOUND_MAP*2)
	
	cpi r19,$F0
	breq NO_SOUND
	cpi r19,$FF
	breq NO_SOUND
	rcall SOUND_TIMER_ON

AGAIN:
	lpm r16, Z+
	cp r16,r19
	breq MAKE_FOUND
	cpi r16,$FF
	breq NO_SOUND
	adiw Z,1	
	rjmp AGAIN
MAKE_FOUND:
	lpm r16,Z
	out OCR0A,r16
	rjmp SOUND_CHANGED

NO_SOUND:
	rcall SOUND_TIMER_OFF
	;rcall rotled_both
	;rcall delay

SOUND_CHANGED:

	pop r16
	pop ZH
	pop ZL

	ret

	MAKE_SOUND_MAP:
		.db $1C, 142, $1D, 134, $1B, 127, $24, 119, $23, 113, $2B, 106, $2C, 100, $34, 94, $35, 89, $33, 84, $3C, 79, $3B, 75, $42, 70, $FF, $FF

		;0 = spela in 1
		;1 = spela upp 1
		;2 = spela in 2
		;3 = speila upp 2