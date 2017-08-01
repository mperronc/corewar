.name "demo zjmp"
.comment ""

ld %42, r8			#carry = 0
zjmp %42			#nojump
sub r5, r6, r7		#carry = 0
zjmp %42			#jump
