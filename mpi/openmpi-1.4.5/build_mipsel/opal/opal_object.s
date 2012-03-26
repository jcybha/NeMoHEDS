	.file	1 "opal_object.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 1
	.abicalls
	.text
	.align	2
	.globl	opal_class_finalize
	.set	nomips16
	.ent	opal_class_finalize
	.type	opal_class_finalize, @function
opal_class_finalize:
	.frame	$sp,40,$31		# vars= 0, regs= 4/0, args= 16, gp= 8
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$18,32($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	.cprestore	16
	lw	$17,%got(classes)($28)
	nop
	lw	$4,%lo(classes)($17)
	nop
	beq	$4,$0,$L2
	nop

	lw	$18,%got(num_classes)($28)
	nop
	lw	$2,%lo(num_classes)($18)
	nop
	blez	$2,$L3
	move	$16,$0

	b	$L10
	sll	$2,$16,2

$L9:
	lw	$4,%lo(classes)($17)
	nop
$L10:
	addu	$4,$4,$2
	lw	$4,0($4)
	lw	$25,%call16(free)($28)
	beq	$4,$0,$L4
	addiu	$16,$16,1

	jalr	$25
	nop

	lw	$28,16($sp)
$L4:
	lw	$2,%lo(num_classes)($18)
	nop
	slt	$2,$16,$2
	bne	$2,$0,$L9
	sll	$2,$16,2

	lw	$4,%lo(classes)($17)
$L3:
	lw	$25,%call16(free)($28)
	nop
	jalr	$25
	nop

	lw	$28,16($sp)
	sw	$0,%lo(classes)($17)
	lw	$2,%got(max_classes)($28)
	sw	$0,%lo(num_classes)($18)
	sw	$0,%lo(max_classes)($2)
$L2:
	lw	$31,36($sp)
	move	$2,$0
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	opal_class_finalize
	.size	opal_class_finalize, .-opal_class_finalize
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"Out of memory\000"
	.align	2
$LC1:
	.ascii	"class malloc failed\000"
	.text
	.align	2
	.globl	opal_class_initialize
	.set	nomips16
	.ent	opal_class_initialize
	.type	opal_class_initialize, @function
opal_class_initialize:
	.frame	$sp,48,$31		# vars= 0, regs= 6/0, args= 16, gp= 8
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	reorder
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$20,40($sp)
	sw	$19,36($sp)
	sw	$18,32($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	.cprestore	16
	lw	$3,16($4)
	li	$2,1			# 0x1
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L28
	move	$17,$4
	.set	macro
	.set	reorder

	lw	$16,%got(class_lock)($28)
	move	$2,$0
	.set	noreorder
	.set	nomacro
	b	$L13
	li	$3,1			# 0x1
	.set	macro
	.set	reorder

$L30:
	lw	$4,%lo(class_lock)($16)
	#nop
	beq	$4,$3,$L30
$L13:
#APP
 # 104 "../../opal/include/opal/sys/mips/atomic.h" 1
		.set mips2         
	ll     $4, %lo(class_lock)($16)      
	bne    $4, $2, 2f  
	or     $2, $3, 0   
	sc     $2, %lo(class_lock)($16)      
	.set mips0         
	bne    $2, 1, 1b   
	nop                
2:                 
	.set reorder       

 # 0 "" 2
 # 79 "../../opal/include/opal/sys/mips/atomic.h" 1
	.set mips2; sync; .set mips0
 # 0 "" 2
#NO_APP
	bne	$4,$0,$L30
	lw	$3,16($17)
	li	$2,1			# 0x1
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L37
	move	$2,$17
	.set	macro
	.set	reorder

	sw	$0,20($17)
	li	$3,1			# 0x1
	move	$5,$0
	move	$18,$0
$L18:
	lw	$4,8($2)
	#nop
	beq	$4,$0,$L16
	addiu	$18,$18,1
$L16:
	lw	$4,12($2)
	#nop
	beq	$4,$0,$L17
	addiu	$5,$5,1
$L17:
	sw	$3,20($17)
	lw	$2,4($2)
	#nop
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L18
	addiu	$3,$3,1
	.set	macro
	.set	reorder

	addu	$5,$5,$18
	lw	$25,%call16(malloc)($28)
	addiu	$4,$5,2
	.set	noreorder
	.set	nomacro
	jalr	$25
	sll	$4,$4,2
	.set	macro
	.set	reorder

	lw	$28,16($sp)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L38
	sw	$2,24($17)
	.set	macro
	.set	reorder

	addiu	$3,$18,1
	sll	$3,$3,2
	sll	$18,$18,2
	lw	$6,20($17)
	addu	$18,$2,$18
	addu	$2,$2,$3
	sw	$2,28($17)
	.set	noreorder
	.set	nomacro
	blez	$6,$L20
	sw	$0,0($18)
	.set	macro
	.set	reorder

	move	$3,$17
	move	$4,$0
$L23:
	lw	$5,8($3)
	#nop
	beq	$5,$0,$L21
	addiu	$18,$18,-4
	sw	$5,0($18)
$L21:
	lw	$5,12($3)
	#nop
	beq	$5,$0,$L22
	sw	$5,0($2)
	addiu	$2,$2,4
$L22:
	addiu	$4,$4,1
	slt	$5,$4,$6
	lw	$3,4($3)
	bne	$5,$0,$L23
$L20:
	li	$3,1			# 0x1
	lw	$18,%got(num_classes)($28)
	lw	$19,%got(max_classes)($28)
	sw	$3,16($17)
	lw	$6,%lo(num_classes)($18)
	lw	$3,%lo(max_classes)($19)
	sw	$0,0($2)
	slt	$2,$6,$3
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L24
	sll	$8,$6,2
	.set	macro
	.set	reorder

	lw	$2,%got(classes)($28)
	#nop
	lw	$2,%lo(classes)($2)
$L25:
	lw	$3,24($17)
	addu	$2,$2,$8
	addiu	$6,$6,1
	sw	$3,0($2)
	sw	$6,%lo(num_classes)($18)
#APP
 # 86 "../../opal/include/opal/sys/mips/atomic.h" 1
	.set mips2; sync; .set mips0
 # 0 "" 2
#NO_APP
	sw	$0,%lo(class_lock)($16)
$L28:
	lw	$31,44($sp)
	lw	$20,40($sp)
	lw	$19,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,48
	.set	macro
	.set	reorder

$L24:
	lw	$20,%got(classes)($28)
	addiu	$3,$3,10
	lw	$25,%call16(realloc)($28)
	lw	$4,%lo(classes)($20)
	sw	$3,%lo(max_classes)($19)
	.set	noreorder
	.set	nomacro
	jalr	$25
	sll	$5,$3,2
	.set	macro
	.set	reorder

	lw	$28,16($sp)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L39
	sw	$2,%lo(classes)($20)
	.set	macro
	.set	reorder

	lw	$7,%lo(max_classes)($19)
	lw	$6,%lo(num_classes)($18)
	#nop
	slt	$3,$6,$7
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L40
	move	$3,$6
	.set	macro
	.set	reorder

	sll	$8,$6,2
	addu	$4,$2,$8
$L27:
	addiu	$3,$3,1
	slt	$5,$3,$7
	sw	$0,0($4)
	.set	noreorder
	.set	nomacro
	bne	$5,$0,$L27
	addiu	$4,$4,4
	.set	macro
	.set	reorder

	b	$L25
$L37:
#APP
 # 86 "../../opal/include/opal/sys/mips/atomic.h" 1
	.set mips2; sync; .set mips0
 # 0 "" 2
#NO_APP
	lw	$2,%got(class_lock)($28)
	lw	$31,44($sp)
	lw	$20,40($sp)
	lw	$19,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	sw	$0,%lo(class_lock)($2)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,48
	.set	macro
	.set	reorder

$L40:
	.set	noreorder
	.set	nomacro
	b	$L25
	sll	$8,$6,2
	.set	macro
	.set	reorder

$L39:
	lw	$4,%got($LC1)($28)
	lw	$25,%call16(perror)($28)
	addiu	$4,$4,%lo($LC1)
$L36:
	jalr	$25
	lw	$28,16($sp)
	#nop
	lw	$25,%call16(exit)($28)
	#nop
	.set	noreorder
	.set	nomacro
	jalr	$25
	li	$4,-1			# 0xffffffffffffffff
	.set	macro
	.set	reorder

$L38:
	lw	$4,%got($LC0)($28)
	lw	$25,%call16(perror)($28)
	.set	noreorder
	.set	nomacro
	b	$L36
	addiu	$4,$4,%lo($LC0)
	.set	macro
	.set	reorder

	.end	opal_class_initialize
	.size	opal_class_initialize, .-opal_class_initialize
	.globl	opal_object_t_class
	.section	.rodata.str1.4
	.align	2
$LC2:
	.ascii	"opal_object_t\000"
	.section	.data.rel.local,"aw",@progbits
	.align	2
	.type	opal_object_t_class, @object
	.size	opal_object_t_class, 36
opal_object_t_class:
	.word	$LC2
	.word	0
	.word	0
	.word	0
	.word	1
	.word	0
	.word	0
	.word	0
	.word	8
	.local	classes
	.comm	classes,4,4
	.local	num_classes
	.comm	num_classes,4,4
	.local	max_classes
	.comm	max_classes,4,4
	.local	class_lock
	.comm	class_lock,4,4
	.ident	"GCC: (Debian 4.4.5-8) 4.4.5"
