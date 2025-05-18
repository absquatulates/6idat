
UPPDATE_TXT1:
	.db "Windows",0,"uppdateras ....       "

UPPDATE_TXT2:
	.db "Var God dr",$EF,"j.",0,"St", $E1 ,"ng ej av!    "

LEDTEXT_TXT:
	.db "Tryck in rot",0,"f",$EF ,"r att starta.  "

SPELA_IN1:
	.db "Spela in  #1",$A5,"  ",$7F ,0, "Spela upp #1",$A5,"    "

SPELA_UPP1:
	.db "Spela upp #1",$A5,"  ",$7F, 0, "Spela in  #2",$A5,"     ",0

SPELA_IN2:
	.db "Spela in  #2",$A5,"  ",$7F,0, "Spela upp #2",$A5,"    "

SPELA_UPP2:
	.db "Spela upp #2",$A5,"  ",$7F,0,"                 "


SPELAR_IN:
	.db "Spelar in     ", 0,"                        ",0

SPELAR_UPP:
	.db "Spelar upp      ", 0,"                      ",0



WAIT_ROT_ENC: // denna fastnar i sig sjäv tills användaren trycker in och släpper vredet 
	sbic	PIND,3
	rjmp	WAIT_ROT_ENC
	// här om intryckt vrede
VREDET_FAST:
	sbis	PIND,3
	rjmp	VREDET_FAST
	ret

CHECK_ROT: // sätter carry flaggan om rotarn är intryckt
	clc
	sbic	PIND,3
	rjmp LEAVE
LOOP:	
	sbis PIND,3
	rjmp LOOP
	sec
LEAVE:
	ret

ROTLED_GREEN:
	push r16
	push r19
	ldi		r16, ROTLED  
	ldi		r19, $02
	rcall	TWI_WRITE
	pop r19
	pop r16
	ret

ROTLED_RED:
	push r16
	push r19
	ldi		r16, ROTLED
	ldi		r19, $01
	rcall	TWI_WRITE
	pop r19
	pop r16
	ret

ROTLED_BOTH:
	push r16
	push r19
	ldi		r16, ROTLED
	ldi		r19, $00
	rcall	TWI_WRITE
	pop r19
	pop r16
	ret

ROTLED_OFF:
	push r16
	push r19

	ldi		r16, ROTLED 
	ldi		r19, $03
	rcall	TWI_WRITE

	pop r19
	pop r16
	ret




