package main

type numberSet map[int]bool

func (st *numberSet) add(n int) {
	(*st)[n] = true
}
func (st *numberSet) remove(n int) {
	delete(*st, n)
}
func (st *numberSet) has(n int) bool {
	_, ok := (*st)[n]
	return ok
}

func containsDuplicate(nums []int) bool {
	st := make(numberSet)
	for _, elem := range nums {
		st.add(elem)
	}
	return len(st) != len(nums)
}

// alternative code
func containsDuplicate1(nums []int) bool {
	st := make(map[int]struct{})
	for _, n := range nums {
		if _, hashNum := st[n]; hashNum {
			return true
		}

	}
	return false
}
