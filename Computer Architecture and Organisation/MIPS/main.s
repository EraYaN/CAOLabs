		.text
		j	main			# Jump to main-routine

		.data
str1:		.asciiz "Insert the array size \n"
str2:		.asciiz "Insert the array elements,one per line  \n"
str3:		.asciiz "The sorted array is : \n"
str5:		.asciiz "\n"

		.text
		.globl	main
main: 
		la	$a0, str1		# Print of str1
		li	$v0, 4			#
		syscall				#

		li	$v0, 5			# Get the array size(n) and
		syscall				# and put it in $v0
		move	$s2, $v0		# $s2=n
		sll	$s0, $v0, 2		# $s0=n*4
		sub	$sp, $sp, $s0		# This instruction creates a stack
						# frame large enough to contain
						# the array
		la	$a0, str2		#
		li	$v0, 4			# Print of str2
		syscall				#
            
		move	$s1, $zero		# i=0
for_get:	bge	$s1, $s2, exit_get	# if i>=n go to exit_for_get
		sll	$t0, $s1, 2		# $t0=i*4
		add	$t1, $t0, $sp		# $t1=$sp+i*4
		li	$v0, 5			# Get one element of the array
		syscall				#
		sw	$v0, 0($t1)		# The element is stored
						# at the address $t1
		la	$a0, str5
		li	$v0, 4
		syscall
		addi	$s1, $s1, 1		# i=i+1
		j	for_get
exit_get:	move	$a0, $sp		# $a0=base address af the array
		move	$a1, $s2		# $a1=size of the array
		jal	sortByCounting		# isort(a,n)
						# In this moment the array has been 
						# sorted and is in the stack frame 
		la	$a0, str3		# Print of str3
		li	$v0, 4
		syscall

		move	$s1, $zero		# i=0
for_print:	bge	$s1, $s2, exit_print	# if i>=n go to exit_print
		sll	$t0, $s1, 2		# $t0=i*4
		add	$t1, $sp, $t0		# $t1=address of a[i]
		lw	$a0, 0($t1)		#
		li	$v0, 1			# print of the element a[i]
		syscall				#

		la	$a0, str5
		li	$v0, 4
		syscall
		addi	$s1, $s1, 1		# i=i+1
		j	for_print
exit_print:	add	$sp, $sp, $s0		# elimination of the stack frame 
              
		li	$v0, 10			# EXIT
		syscall				#
		
# sortByCounting function
#  $a0 = a[];
#  $a1 = length
sortByCounting:	subi $sp, $sp, 4
		sw $s0 ($sp) # i
		subi $sp, $sp, 4
		sw $s1 ($sp) # lessThan
		subi $sp, $sp, 4
		sw $s2 ($sp) # b (base address)
		subi $sp, $sp, 4
		sw $s3 ($sp) # a (base address) and $ra
		
		
		move $s0, $zero # set $s0 to zero (i)
		move $s1, $zero # set $s1 to zero (lessThan)
		move $s3, $a0 # save a base address
		sll $t0, $a1, 2
		li $v0, 9 # sbrk (C++ new)
        	move $a0, $t0 # set the number of bytes to alloc
        	syscall                 # DYNAMICALLY ALLOCATING MEMORY OF SIZE 4 BYTES AT ADDRESS OF VAR
        	move $s2, $v0 # get address
		move $a0, $s3 # restore A base address
		move $s3, $ra # save $ra
		
for_sort:	move $a2, $s0 # pass i as thrid argument
		
		jal countLessThan # call result is in $v0
		
		sll $t0, $v0, 2 # get lessThan address result
		add $t0, $t0, $s2 # $t0 now holds the current target element's address in b (b[lessThan])
		
		sll $t1, $s0, 2 # get i address result
		add $t1, $t1, $a0 # $t1 now holds the current source element's address in a (a[i])
		
		lw $t2, ($t1) # load source element
		sw $t2, ($t0) # store source to target
		
		addi $s0,$s0,1 # increase counter
		bne $a1,$s0,for_sort # if i is not equal to length rerun loop
		
		move $s0, $zero # set $s0 to zero (i)
for_copy:	sll $t2, $s0, 2 # get i address result
		
		add $t0, $t2, $s2 # $t0 now holds the current target element's address in b (b[lessThan])
		add $t1, $t2, $a0 # $t1 now holds the current source element's address in a (a[i])
		
		lw $t3, ($t0) # load source element
		sw $t3, ($t1) # store source to target
		
		addi $s0,$s0,1 # increase counter
		bne $a1,$s0,for_copy # if i is not equal to length rerun loop
		
		move $ra, $s3 # restore $ra
		
		lw $s0 ($sp) # i
		addi $sp, $sp, 4		
		lw $s1 ($sp) # i
		addi $sp, $sp, 4
		lw $s2 ($sp) # i
		addi $sp, $sp, 4
		lw $s3 ($sp) # i
		addi $sp, $sp, 4
		
		jr $ra
		
# countLessThan function
countLessThan: 	move	$t0, $zero		#count=0
		move 	$t1, $zero 		#j=0
		move	$t2, $a0
		sll	$t4, $a2, 2		#i*4
		add	$t4, $a0, $t4		#t4= address of a[i}
		lw	$t4, ($t4)		#load a[i] to $t4
for_clt:	bge  	$t1, $a1, exit_clt	#if j>=length exit for loop
		lw	$t3, ($t2)		#load a[j]
		blt	$t3, $t4, count_clt	#if a[j]<a[i] jump to count++
		bne	$t3, $t4, loopprepare	#if a[j]!=a[i], no count++ will be necessary
		ble	$t1, $a2, loopprepare	#if j<=i, no count++ will be necessary
count_clt:	addi	$t0, $t0, 1		#count++
loopprepare:	addi	$t1, $t1, 1		#j++
		addi	$t2, $t2, 4		#next address in array
		j	for_clt			#loop
exit_clt:	move	$v0, $t0		#return
		jr	$ra			#return
