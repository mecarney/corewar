.name "PickleRick!"
.comment "I turned myself into a pickle. I'm Pickle Riiiiick"

	ld %0, r15
	ld %5, r8
part1:
	zjmp %:part3

part2:
	live %1
	live %1
	live %1
	live %1
	sub r7, r8, r9
	zjmp %:part4

part3:
	sti r1, %:part2, %1
	sti r1, %:part2, %6
	sti r1, %:part2, %11
	sti r1, %:part2, %16
	sti r1, %:part5, %1
	sti r1, %:part5, %6
	sti r1, %:part5, %11
	sti r1, %:part5, %16
	sti r1, %:part5, %21
	sti r1, %:part5, %26
	sti r1, %:part5, %31
	sti r1, %:part5, %36
	fork %:part2

part4:
	ld %5, r7
	add r6, r4, r5
	fork %:part2
	add r15, r15, r15
	zjmp %:part5

part5:
	live %1
	live %1
	live %1
	live %1
	live %1
	live %1
	live %1
	live %1
	zjmp %:part5
