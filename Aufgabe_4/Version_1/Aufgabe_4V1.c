           org 100h
            cpu 8086

            jmp start

; Variable
status      db 0000000b ; Statusbyte
;                    x
;                    |
;                    +--------> Lichtschranke hat ausgeloest (1)

position    db 0        ; Weichenposition
tcount      db 0        ; Impulszaehler
anzahl      db 0        ; Anzahl der Teile

; Konstanten



LS_aktiv    equ 0000001b; Lichtschranke hat ausgeloest
intab0      equ 20h     ; Adresse Interrupttabelle PIT
intab7      equ 3ch     ; Adresse Interrupttabelle Lichtschranke
eoi         equ 20h     ; End Of Interrupt (EOI)
clrscr      equ 0       ; Clear Screen
getkey      equ 1       ; Funktion auf Tastatureingabe warten
ascii       equ 2       ; Funktion ASCII-Zeichenausgabe
hexbyte     equ 4       ; HEX-Byte Ausgabe
conin       equ 5       ; Console IN
conout      equ 6       ; Console OUT
pitc        equ 0a6h    ; Steuerkanal PIT
pit1        equ 0a2h    ; Counter 1 PIT
ppi_ctl     equ 0b6h    ; Steuerkanal PPI (Parallelinterface)
ppi_a       equ 0b0h    ; Kanal A PPI
ppi_pa0     equ 1       ; LED 0
ppi_pa1     equ 2       ; LED 1
ppi_pa2     equ 4       ; LED 2
ppi_pa3     equ 8       ; Lautsprecher
ppi_pa6     equ 1<<6    ; Servo
ppi_b       equ 0b2h    ; Kanal B PPI
ppi_c       equ 0b4h    ; Kanal C PPI
ocw_2_3     equ 0c0h    ; PIC (Interruptcontroller), OCW2,3
ocw_1       equ 0c2h    ; PIC (Interruptcontroller), OCW1
icw_1       equ 0c0h    ; PIC (Interruptcontroller), ICW1
icw_2_4     equ 0c2h    ; PIC (Interruptcontroller), ICW2,4
leds        equ 0       ; LED Port
schalter    equ 0       ; Schalterport
keybd       equ 80h     ; SBC-86 Tastatur
gokey       equ 11h     ; Taste "GO"
outkey      equ 15h     ; Taste "OUT"
sseg7       equ 9eh     ; Segmentanzeige 7
tc          equ 185     ; 1843200 Hz / 185 = ca. 10000 Hz = 0.1 ms
                        ; Taktzyklus
tperiode    equ 200     ; Periodendauer des PWM-Signals
trechts     equ 10      ; Dauer fuer Rechts
tlinks      equ 20      ; Dauer fuer Links




;------------------------------------------------------------------------------------------------------



start:

; Initialisierung

    call init                   ; Controller und Interruptsystem scharfmachen

    mov ah, clrscr              ; Anzeige aus
    int conout
    
    mov byte [status], 0        ; Init. Statusbyte und alle LEDs
    mov al, 0
    out ppi_a, al
    out leds, al
    mov byte [position], trechts    ; initial Position rechts
    mov byte [anzahl], 0

; Hintergrundprogramm




again:

; Der hier einzufügende Programmcode wird immer dann ausgeführt, wenn die
; Interruptserviceroutinen nicht laufen (Hintergrundprogramm). Das wäre z.B. 
; die Manipulation des Statusbits und die Ausgabe auf das Display.

	;Die Lichtschranke 
	mov al, [status]
	out leds, al
	and al, ~1
	mov [status], al
	
	


	jmp again




;------------------------------------------------------------------------------------------------------


        
; Initialisierung Controller und Interruptsystem
init:
    cli                         ; Interrupts aus

; PIT-Init.
    mov al, 01110110b           ; Kanal 1, Mode 3, 16-Bit ZK
    out pitc, al                ; Steuerkanal
    mov al, tc & 0ffh           ; Low-Teil Zeitkonstante
    out pit1, al
    mov al, tc >> 8             ; High-Teil Zeitkonstante
    out pit1, al

; PPI-Init.
    mov al, 10001011b           ; PPI A/B/C Mode0, A Output, sonst Input
    out ppi_ctl, al
    jmp short $+2               ; I/O-Delay
    mov al, 0                   ; LED's aus (high aktiv)
    out ppi_a, al
    
; PIC-Init.
    mov al, 00010011b           ; ICW1, ICW4 benoetigt, Bit 2 egal, 
                                ; Flankentriggerung
    out icw_1, al
    jmp short $+2               ; I/O-Delay
    mov al, 00001000b           ; ICW2, auf INT 8 gemapped
    out icw_2_4, al
    jmp short $+2               ; I/O-Delay
    mov al, 00010001b           ; ICW4, MCS-86, EOI, non-buffered,
                                ; fully nested
    out icw_2_4, al
    jmp short $+2               ; I/O-Delay
    mov al, 01111110b           ; Kanal 0 + 7 am PIC demaskieren
                                ; PIT K1 und Lichttaster
    out ocw_1, al
    
; Interrupttabelle init.    
    mov word [intab7], isr_1    ; Interrupttabelle (Lichttaster) 
                                ; initialisieren (Offset)
    mov [intab7 + 2], cs        ; (Segmentadresse)
    mov word [intab0], isr_2    ; Interrupttabelle (Timer) 
                                ; initialisieren (Offset)
    mov [intab0 + 2], cs        ; (Segmentadresse)
    
    sti                         ; ab jetzt Interrupts
    ret


;------------------------------------------------------------------------------------------------------






isr_1:
    push ax

; Interruptservice Reflexlichttaster:
; Hier ist z.B. der Programmcode einzufügen, um Statusbits zu manipulieren.
; Der gemeinsame Ausgang aus der ISR ist "isr1".

    mov al, [status]
    or al, 1
    mov [status], al


isr1:
    mov al, eoi                 ; EOI an PIC
    out ocw_2_3, al
    pop ax
    iret
    
    
    
    
    
    
isr_2:
    push ax

; Interruptservice Timer Kanal 1:
; Hier ist z.B. der Programmcode einzufügen, um die entsprechende Position
; anzufahren. Ausgänge sind auch lesbar! Der gemeinsame Ausgang aus der ISR
; ist "isr2".





isr2:
    mov al, eoi                 ; EOI an PIC
    out ocw_2_3, al
    pop ax
    iret
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
