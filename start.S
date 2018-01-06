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
