/**
 * https://codeforces.com/blog/entry/73558
 * Problem:-
 * There are N <= 5000 workers in a factory.Each is available during some days of each month of every year. Find two workers with
 * maximum intersection of their schedules.
 *
 * Appraoch:-
 * Convert each schedule to a 30-bit bitset or number and then calculate the pairwise
 * and value of two workers
 * -count the number of on-bits in the result, the number with most on-bits is the answer
 */
