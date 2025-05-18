

.equ SCL = PC5
.equ SDA = PC4

TWI_INIT:
	push r16
	// set twi scale
	ldi		r16, 8 // går sönder under 4
	sts		TWBR, r16

	ldi r16, (1 << TWEN)   ; Enable TWI, enable TWI interrupt, enable acknowledge bit
    sts TWCR, r16  ; Write control register
	pop r16
	ret

TWI_WRITE: // har r16 som "adress-argument" och r19 som datan som ska skickas ut 
	lsl		r16 
	rcall	START

	rcall	DATA_SEND ; skickar ut adressen
	mov		r16, r19 // denna är viktig 
	rcall	DATA_SEND ; skickar ut datan
	rcall	STOP

	ret

TWINT_FLAG_WAIT:	
	push	r16
WAIT_EINZ:	
	lds		r16, TWCR
	sbrs	r16, TWINT
	rjmp	WAIT_EINZ

	pop		r16
	ret


DATA_SEND: // skickar ut r16s inehåll genom TWI
	push	r16
	sts		TWDR, r16
	rcall	TX
	pop		r16
	ret 

TX:
	ldi		r16, (1<<TWINT) | (1<<TWEN)
	sts		TWCR, r16
	rcall	TWINT_FLAG_WAIT
	ret 

START:
	push	r16
	ldi		r16, (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
	sts		TWCR,	r16
	rcall	TWINT_FLAG_WAIT
	pop		r16
	ret

STOP:
	push	r16
	ldi		r16,(1<<TWINT)|(1<<TWEN)|(1<<TWSTO)
	sts		TWCR, r16
	pop		r16
	ret



WAIT: 
	push	r16
	ldi		r16,  $FF
WAIT_INNRE:
	dec		r16
	brne	WAIT_INNRE
	ldi		r16, $FF
WAIT_2:
	dec		r16
	brne	WAIT_2
	pop		r16
	ret

DELAY: ;denna är väldigt lång 
	push r16
	push r17
	push r18

	ldi r18, $10
DELAYSTART:
	ldi r16,$FF
DELAY_YTTRE:
	ldi r17, $FF
DELAY_INNRE:
	dec r17
	brne DELAY_INNRE
	dec r16 
	brne DELAY_YTTRE
	dec r18
	brne DELAYSTART

	pop r18
	pop r17
	pop r16
	ret

