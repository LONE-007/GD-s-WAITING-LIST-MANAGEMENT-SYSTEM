# Seat Booking System with Waiting List Management

## Overview
This project implements a seat booking system in C, allowing users to manage seat reservations, check availability, cancel bookings, edit reservations, and view the seating chart. It also includes a waiting list feature for when seats are fully booked.

## Features
- **Check Seat Availability**: Users can check if a specific seat is available.
- **Book a Seat**: Users can reserve a seat for a passenger. If the seat is booked, the passenger is added to a waiting list.
- **Cancel Booking**: Users can cancel their booking for a specific seat.
- **Edit Booking**: Users can change the passenger name associated with a booked seat.
- **Display Seating Chart**: Users can view the current status of all seats.

## Data Structures
- **SeatNode**: Represents a seat in the linked list, containing the seat number, booking status, and passenger name.
- **QueueNode**: Represents a node in the booking queue for handling waiting list requests.
- **SeatList**: Manages the linked list of seats.
- **BookingQueue**: Manages the queue for handling waiting list bookings.

## Getting Started

### Prerequisites
- A C compiler (e.g., GCC)
- Basic knowledge of C programming

### Compilation
To compile the program, use the following command:

```bash
gcc -o seat_booking_system seat_booking_system.c
```

### Running the Program
After compilation, run the program:

```bash
./seat_booking_system
```

### User Interface
The program will present a menu with the following options:
1. Check seat availability
2. Book a seat
3. Cancel booking
4. Edit booking
5. Display seating chart
6. Exit

### Example Workflow
1. Select an option from the menu.
2. Follow the prompts to enter the required information.
3. View messages confirming your actions.

## Code Structure
- The main logic is implemented in the `main` function.
- Functions are defined for each feature to keep the code organized and modular.
