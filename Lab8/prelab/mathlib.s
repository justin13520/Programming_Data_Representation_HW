;Justin Liu, jl8wf	Date:10/19/2020		Filename: mathlib.s */


	global product
	global power
	section .data

	;; parameter 1: x is the base for power or the first term in product (rdi)
	;; parameter 2: y is the exponent for power or the second term in product (rsi)
	section .txt

product:
				;  prologue
	xor	r10, r10	;act as i
	xor	rax, rax	;zeroes out the return if anything was in it
start1:
	cmp 	r10, rsi	;compares i to second parameter
	je	done1		;done with the function, exit
	add	rax, rdi	;adds first parameter to return register
	inc	r10		;i++
	jmp	start1		;recursive call
done1:
	ret	
	
power:
	;; prologue
	xor	r10, r10	;zeroed so 'i' can compare to second parameter to stop
	inc	r10		;i = 1 for x^1 base case
start2:
	cmp	r10, rsi	;sees if power is equal to 1
	je	done2		;if so, return???
	dec	rsi		;power--
	call	power
	mov 	rsi, rax
done2:
	
	call product
	ret
