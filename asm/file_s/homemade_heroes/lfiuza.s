.name "FreddyMercury"
.comment "get it?"

verse1:
	live %3
	live %1
	live %2
	live %4
	fork %:verse2
	zjmp %:chorus

chorus:
	add r4, r5, r4
	ldi %:bridge, r4, r2
	live %0
	live %42
	live %42
	live %42
	st r14, -131
	zjmp %:verse1

interlude:
	ld %0, r1
	ld %0, r3
	ld %0, r4
	ld %42, r5

verse2:
	live %2
	live %42
	fork %:bridge
	zjmp %:chorus

bridge:
	sti r2, %:verse1, %1
	sti r2, %:chorus, %1
	sti r2, %:interlude, %1
	sti r2, %:verse2, %1
	zjmp %:chorus	
