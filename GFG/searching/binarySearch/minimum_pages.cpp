// Allocate minimum number of pages
/*
Given the number of pages in n different books, and m students, the
books are arranged in ascending order of the number of pages, every
student is assigned to read some consecutive books, the task is to assign
the books in such a way that the maximum number of pages assigned
to student is minimum.
int books[n] = {b1,b2,b3...bn}
int students[m]={s1,s2,s3...sm} (let m<n)

return the minimum number of pages
*/

// Credits:- Aditya Verma
/*
input:
arr[]: 10 20 30 40 //num of pages
k: 2 //num of students
***the array need not be sorted

Output: minumum number of pages

Restriction:-
*each students reads atleast one book
*same book can't be read by multiple students
*books are assigned un continuous manner
*/

/*
max number of pages to be read by a student =
[10,10+20+30+40] = [10,100]
10---30-----60------100
we can start with max in array i.e. 40
*/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int max_in_array(int arr[], int length)
{
    int max = INT_MIN;
    for (int i = 0; i < length; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}
int sum_in_array(int arr[], int start, int end)
{
    int sum = 0;
    for (int i = start; i < end; i++)
    {
        sum += arr[i];
    }
    return sum;
}
bool isValid(int arr[], int K, int N, int max)
{
    // arr - array of books
    // K = num_books
    // N = number of students
    // max = upper limit
    bool result = false;
    if (N > K)
        result = false; // since by pigeonhole principle, aleast one student gets 0 books
    int num_students = 1;
    int sum = 0;
    for (int i = 0; i < K; i++)
    {
        sum = sum + arr[i];
        if (sum > max)
        {
            num_students++;
            sum = arr[i];
        }
    }
    if (num_students > K)
        result = false;

    return result;
}
int main()
{
    int num_books, num_students, temp;
    cout << "Enter the number of books: ";
    cin >> num_books;
    cout << "Enter the number of students: ";
    cin >> num_students;
    int books[num_books];
    for (int i = 0; i < num_books; i++)
    {
        cin >> temp;
        books[i] = temp;
    }
    int start = max_in_array(books, num_books);  // max pages in any book
    int end = sum_in_array(books, 0, num_books); // sum of pages
    int result = -1;
    while (start < end)
    {
        int mid = start + (end - start) / 2; // end is inclusive here
        if (isValid(books, num_books, num_students, mid) == true)
        {
            result = mid;
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    cout << result << "\n";
}