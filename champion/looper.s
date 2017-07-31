.name "LOOPER"
.comment "Looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooop"

sti r1, %:live, %1
ld  %0, r2 #carry = 1
live:	live  %1
fork	%:live
jump: zjmp	%:live


