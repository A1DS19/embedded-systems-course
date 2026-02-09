.global asm_add
.global asm_mul
.global asm_iterate_numbers

; ============================================================
; uint16_t asm_add(uint16_t a, uint16_t b)
; Adds two 16-bit numbers.
; args: r25:r24 = a, r23:r22 = b
; returns: r25:r24 = a + b
; ============================================================
.func
asm_add:
  add r24, r22        ; add low bytes (may set carry flag)
  adc r25, r23        ; add high bytes + carry from low byte addition
  ret
.endfunc

; ============================================================
; uint16_t asm_mul(uint16_t a, uint16_t b)
; Multiplies two 8-bit values (low bytes of a and b).
; args: r25:r24 = a, r23:r22 = b
; returns: r25:r24 = a * b
; note: mul is 8-bit only, so a and b must be <= 255
; ============================================================
.func
asm_mul:
  mul r24, r22        ; multiply low bytes, result in r1:r0 (hardware fixed)
  mov r24, r0         ; copy low byte of result to return register
  mov r25, r1         ; copy high byte of result to return register
  clr r1              ; clear r1 (AVR ABI requires r1 = 0 at all times)
  ret
.endfunc

; ============================================================
; void asm_iterate_numbers(uint8_t* numbers)
; Iterates over a 10-element array, increments each element
; by 1, then multiplies it by 10.
; Formula: numbers[i] = (numbers[i] + 1) * 10
; args: r25:r24 = pointer to array in SRAM
; ============================================================
.func
asm_iterate_numbers:
  mov XL, r24         ; load array pointer into X register (low byte)
  mov XH, r25         ; load array pointer into X register (high byte)
  ldi r18, 10         ; loop counter (10 elements)
  ldi r19, 10         ; multiplier constant (stored in register for mul)

loop:
  ld r24, X           ; read current element from SRAM at address X
  inc r24             ; increment element by 1
  mul r24, r19        ; multiply by 10, result in r1:r0
  st X+, r0           ; store low byte of result back, advance X to next element
  dec r18             ; decrement loop counter
  brne loop           ; if counter != 0, repeat loop

  clr r1              ; restore r1 to zero (AVR ABI requirement)
  ret
.endfunc
