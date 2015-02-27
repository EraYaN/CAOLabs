# sortByCounting function
#  $a0 = a[];
#  $a1 = length
sortByCounting:	subi $sp, $sp, 4
		sw $s0 ($sp) # i
		subi $sp, $sp, 4
		sw $s1 ($sp) # lessThan
		subi $sp, $sp, 4
		sw $s2 ($sp) # b (base address)
		
		move $s0, $zero # set $s0 to zero (i)
		move $s1, $zero # set $s1 to zero (lessThan)
		
		sll $t0, $a1, 2
		li $v0, 9 # sbrk (C++ new)
        	move $a0, $t0 # set the number of bytes to alloc
        	syscall                 # DYNAMICALLY ALLOCATING MEMORY OF SIZE 4 BYTES AT ADDRESS OF VAR
        	move $s2, $v0 # get address
		
		
		
for_sort:	move $a2, $s0 # pass i as thrid argument
		jal countLessThen # call result is in $v0
		
		sll $t0, $v0, 2 # get lessThan address result
		add $t0, $t0, $s2 # $t0 now holds the current target element's address in b (b[lessThan])
		
		sll $t1, $s0, 2 # get i address result
		add $t1, $t1, $a0 # $t1 now holds the current source element's address in a (a[i])
		
		lw $t2, ($t1) # load source element
		sw $t2, ($t0) # store source to target
		
		addi $s0,$s0,1 # increase counter
		bne $a1,$s0,for_sort # if i is not equal to length rerun loop
		
for_copy:	move $s0, $zero # set $s0 to zero (i)
		sll $t0, $s0, 2 # get i address result
		
		add $t0, $t0, $s2 # $t0 now holds the current target element's address in b (b[lessThan])
		add $t1, $t0, $a0 # $t1 now holds the current source element's address in a (a[i])
		
		lw $t2, ($t1) # load source element
		sw $t2, ($t0) # store source to target
		
		addi $s0,$s0,1 # increase counter
		bne $a1,$s0,for_copy # if i is not equal to length rerun loop

		lw $s0 ($sp) # i
		subi $sp, $sp, 2		
		lw $s1 ($sp) # i
		subi $sp, $sp, 4
		lw $s2 ($sp) # i
		subi $sp, $sp, 4
		
		jr $ra