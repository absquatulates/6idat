;
; sju_seg.asm
;
; Created: 2024-01
; Author : grupp 5
;


.equ ROTLED = $26
.equ ADDR_LEFT8 = $24
.equ ADDR_RIGHT8 = $25

.include "TWI.asm"



RIGHT_8_WRITE: // 
	push r16
	ldi		r16, ADDR_RIGHT8
	rcall	TWI_WRITE
	pop r16
	ret


LEFT_8_WRITE:
	push r16
	ldi		r16, ADDR_LEFT8
	rcall	TWI_WRITE
	pop r16
	ret


SJUSEG_LOOKUP: // denna tar in ett värde från r20 och skickar ut dess lookup värde i r19
	push	ZH
	push	ZL

	ldi		ZL,LOW(BCD7*2)
	ldi		ZH,HIGH(BCD7*2)
	add		ZL,r20
	adc		ZH,zero
	lpm		r19, Z

	pop		ZL
	pop		ZH
	ret

PRINT_R25:
	cpi r25,$F0
	brne NO_F0
	ldi r19,$80
	rjmp ROTLED_DONE
NO_F0:
	rcall HEX_VAL_LOOKUP
	rcall SJUSEG_LOOKUP
ROTLED_DONE:
	rcall RIGHT_8_WRITE
	ret



BCD7:
	.db $3f, $06, $5b, $4f, $66, $6d, $7d, $07, $7f, $6f, $77, $7C, $39, $5E, $79, $71,$00,$00


