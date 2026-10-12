"""
Design Bus Seat Booking System
https://leetcode.com/problems/design-bus-seat-booking-system/

You are asked to design a seat booking system for a bus.

The bus has n rows. Each row has four seats labeled "A", "B", "C", and "D".

Seats "A" and "D" are window seats; seats "B" and "C" are middle seats. In
each row, seat "A" is adjacent to seat "B", and seat "D" is adjacent to seat
"C".

Booking rules:
    - Booking a middle seat ("B" or "C") always takes 1 second.
    - Booking a window seat ("A" or "D") takes 1 second if its adjacent middle
      seat is not booked, or 3 seconds (an extra delay of 2 seconds) if its
      adjacent middle seat is already booked.

A seat is identified by a string such as "A1" or "D20" (one letter from A to D
followed by its row number).

Implement the BusBooking class:
    - BusBooking(int n): Initializes the system with n empty rows.
    - void toggle(string seat): Books seat if it is free, or frees it if it is
      already booked.
    - int getTotalTime(): Returns the total time (in seconds) taken to book all
      currently booked seats, where the seats are booked in the order their
      toggle calls were made. If no seats are currently booked, return 0.
    - int getMinTime(): Returns the smallest possible total time (in seconds)
      to book all currently booked seats, over every possible order of booking
      them. If no seats are currently booked, return 0.

Note: The time cost of a seat is fixed at the moment it is booked, based on
the seats booked at that time. Booking or freeing other seats afterward does
not change the cost of a seat that is already booked.

Constraints:
    - 1 <= n <= 10^5
    - seat[0] is one of 'A', 'B', 'C', 'D'.
    - The remaining characters of seat form an integer row with 1 <= row <= n.
    - The total number of calls to toggle, getTotalTime, and getMinTime does
      not exceed 10^5.
"""
class BusBooking:

    def __init__(self, n: int):
        self.seats = [[0,0,0,0] for _ in range(n)]
        self.count = 0
        self.total = 0

    def toggle(self, seat: str) -> None:
        y = ord(seat[0]) - ord('A')
        x = int(seat[1]) - 1
        if self.seats[x][y] == 0:
            cost = 1
            if (y == 0 and self.seats[x][1]) or (y == 3 and self.seats[x][2]):
                cost = 3
            self.seats[x][y] = cost
            self.count += 1
            self.total += cost
        else:
            self.total -= self.seats[x][y]
            self.seats[x][y] = 0
            self.count -= 1

    def getTotalTime(self) -> int:
        return self.total

    def getMinTime(self) -> int:
        return self.count
