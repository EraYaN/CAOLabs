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
		