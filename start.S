/*
 * Copyright 2018 Eiji Yoshiya
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#define	SP	254
#define	REG_STACK		0x80000000007f8000
#define	STACK_BOTTOM		0x8000000000800000

/*
 * stack setup.
 *	REG_STACK |             rL : 0             |
 *                |           g255 : -             |
 *                |             rB : -             |
 *                |             rD : -             |
 *        +32     |             rE : -             |
 *                |             rH : -             |
 *                |             rJ : -             |
 *                |             rM : -             |
 *        +64     |             rR : -             |
 *                |             rP : -             |
 *                |             rW : -             |
 *                |             rX : -             |
 *        +96     |             rY : -             |
 *                |             rZ : -             |
 *       +112     | 255 |     0    |    rA : 0     |
 */

	.text
	.globl	__start
__start:
	set 	$0, 0
	geta	$255, REG_STACK
	sto	$0, $255	/* rL */
	seth	$0, 0xff00	/* rg:255 | 0 | rA */
	add	$255, $255, 112
	sto	$0, $255 
	unsave	$255
	put	rG, 32
	geta	$SP, STACK_BOTTOM
	pushj	$0, main
loop:
	jmp	loop	
