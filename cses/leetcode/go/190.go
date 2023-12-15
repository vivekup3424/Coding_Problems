func reverseBits(num uint32) uint32 {
	var totalBits := 32
	var ans uint32 := 0
	for i := 0; i < totalBits; i++ {
		ans = (ans<<1) | (num&1)
		num >>= 1
	}
	return ans
}