.name "simple instructions"
.comment "sample text"

live 	%42						# 01 00 00 00 2a
add 	r1, r2, r3				# 04 01 02 03
zjmp	%254					# 09 00 00 00 fe
aff		r16						# 10 40 10
fork	%-100					# 0c ff 9c
