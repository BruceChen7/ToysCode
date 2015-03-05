event = 0
odd = 0
while i < 10 {
	if i % 2 == 0 {
		even = event + i
	} else {
		odd = odd + 1	
	}
	i = i + 1	
}
even + odd
