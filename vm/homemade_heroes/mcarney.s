.name "couerwar"
.comment "beep beep boop Max smells"

label1:
	live		%0
	sti			r1, %:label1, %1
	fork		%:label2
	sub			r16, r16, r16
	zjmp		%:label1
