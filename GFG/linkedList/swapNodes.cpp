/*Swap nodes without changing data*/
/*Examples: 

Input : 10->15->12->13->20->14,  x = 12, y = 20
Output: 10->15->20->13->12->14

Input : 10->15->12->13->20->14,  x = 10, y = 20
Output: 20->15->12->13->10->14

Input : 10->15->12->13->20->14,  x = 12, y = 13
Output: 10->15->13->12->20->14

This may look like a simple problem, but is an interesting question as it has the following cases to be handled. 

  - x and y may or may not be adjacent.
  - Either x or y may be a head node.
  - Either x or y may be the last node.
  - x and/or y may not be present in the linked list.
*/