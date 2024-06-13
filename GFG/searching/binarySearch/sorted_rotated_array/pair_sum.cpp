//    First find the largest element in an array which is the pivot point
//    also and the element just after the largest is the smallest element.
//    Once we have the indices of the largest and the smallest elements,
//    we use a similar meet-in-middle algorithm (as discussed here in method 1)
//    to find if there is a pair.
//
//    The only thing new here is indices are incremented and decremented
//    in a rotational manner using modular arithmetic.
//
//    Time Complexity: O(N). The step to find the pivot can be optimized
//    to O(Logn) using the Binary Search approach discussed here.

// Exercise:
// 1) Extend the above solution to work for arrays with duplicates allowed.