.name "labels"
.comment "lmao"

main:
	live %:main

label1:
label2:
	add r1, r2, r3
	or :label1, %:label2, r4
