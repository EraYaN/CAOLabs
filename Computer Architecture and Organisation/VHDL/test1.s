move $s4, $zero
move $s5, $zero
addi $t1, $zero, 18
addi $s0, $zero, 4
addi $s2, $zero, 1
sll  $s2, $s2, 22
addi $s2, $s2, 44
addi $s6, $zero, -2
sllv $s0, $s0, $s6
jalr $s1, $s2
addi $s4, $s4, 8
addi $s5, $s5, 9
beq $s5, $t1, done
jr $s1
done: sllv $s4, $s4, $s4