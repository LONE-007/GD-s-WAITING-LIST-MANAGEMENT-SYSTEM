#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define a structure for a seat node in the linked list
typedef struct SeatNode {
    int seatNumber;
    bool isBooked;
    char passengerName[50];
    struct SeatNode* next;
} SeatNode;

// Define a structure for a queue node
typedef struct QueueNode {
    int seatNumber;
    char passengerName[50];
    struct QueueNode* next;
} QueueNode;

// Define a structure for the seat linked list
typedef struct {
    SeatNode* head;
} SeatList;

// Define a structure for the booking queue
typedef struct {
    QueueNode* front;
    QueueNode* rear;
} BookingQueue;

// Function prototypes
SeatNode* createSeatNode(int seatNumber);
QueueNode* createQueueNode(int seatNumber, const char* passengerName);
void initializeSeatList(SeatList* seatList, int totalSeats);
bool isSeatAvailable(SeatList* seatList, int seatNumber);
bool bookSeat(SeatList* seatList, int seatNumber, const char* passengerName);
void enqueueBooking(BookingQueue* queue, int seatNumber, const char* passengerName);
QueueNode* dequeueBooking(BookingQueue* queue);
void processBookingQueue(SeatList* seatList, BookingQueue* queue);
void displaySeatingChart(SeatList* seatList);
void cancelBooking(SeatList* seatList, int seatNumber);
void editBooking(SeatList* seatList, int seatNumber, const char* passengerName);

SeatNode* createSeatNode(int seatNumber) {
    SeatNode* newNode = (SeatNode*)malloc(sizeof(SeatNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->seatNumber = seatNumber;
    newNode->isBooked = false;
    strcpy(newNode->passengerName, "");
    newNode->next = NULL;
    return newNode;
}

QueueNode* createQueueNode(int seatNumber, const char* passengerName) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->seatNumber = seatNumber;
    strcpy(newNode->passengerName, passengerName);
    newNode->next = NULL;
    return newNode;
}

void initializeSeatList(SeatList* seatList, int totalSeats) {
    seatList->head = NULL;
    for (int i = 1; i <= totalSeats; i++) {
        SeatNode* newNode = createSeatNode(i);
        newNode->next = seatList->head;
        seatList->head = newNode;
    }
}

bool isSeatAvailable(SeatList* seatList, int seatNumber) {
    SeatNode* current = seatList->head;
    while (current != NULL) {
        if (current->seatNumber == seatNumber) {
            return !current->isBooked;
        }
        current = current->next;
    }
    return false; // Seat not found
}

bool bookSeat(SeatList* seatList, int seatNumber, const char* passengerName) {
    SeatNode* current = seatList->head;
    while (current != NULL) {
        if (current->seatNumber == seatNumber) {
            if (current->isBooked) {
                return false; // Seat already booked
            }
            current->isBooked = true;
            strcpy(current->passengerName, passengerName);
            return true;
        }
        current = current->next;
    }
    return false; // Seat not found
}

void enqueueBooking(BookingQueue* queue, int seatNumber, const char* passengerName) {
    QueueNode* newNode = createQueueNode(seatNumber, passengerName);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("Added %s to the waiting list for seat %d.\n", passengerName, seatNumber);
}

QueueNode* dequeueBooking(BookingQueue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return temp;
}

void processBookingQueue(SeatList* seatList, BookingQueue* queue) {
    QueueNode* temp;
    while ((temp = dequeueBooking(queue)) != NULL) {
        if (bookSeat(seatList, temp->seatNumber, temp->passengerName)) {
            printf("Booked %s to seat %d.\n", temp->passengerName, temp->seatNumber);
            free(temp);
        } else {
            enqueueBooking(queue, temp->seatNumber, temp->passengerName);
            printf("Seat %d is already booked for %s. Added back to waiting list.\n", temp->seatNumber, temp->passengerName);
            free(temp);
            break; // Stop processing when a request cannot be fulfilled
        }
    }
}

void cancelBooking(SeatList* seatList, int seatNumber) {
    SeatNode* current = seatList->head;
    while (current != NULL) {
        if (current->seatNumber == seatNumber && current->isBooked) {
            current->isBooked = false;
            strcpy(current->passengerName, "");
            printf("Booking for seat %d has been cancelled.\n", seatNumber);
            return;
        }
        current = current->next;
    }
    printf("No booking found for seat %d.\n", seatNumber);
}

void editBooking(SeatList* seatList, int seatNumber, const char* passengerName) {
    SeatNode* current = seatList->head;
    while (current != NULL) {
        if (current->seatNumber == seatNumber && current->isBooked) {
            strcpy(current->passengerName, passengerName);
            printf("Booking for seat %d has been updated to %s.\n", seatNumber, passengerName);
            return;
        }
        current = current->next;
    }
    printf("No booking found for seat %d.\n", seatNumber);
}

void displaySeatingChart(SeatList* seatList) {
    SeatNode* current = seatList->head;
    printf("Seating Chart:\n");
    while (current != NULL) {
        printf("Seat %d: %s\n", current->seatNumber, current->isBooked ? current->passengerName : "Available");
        current = current->next;
    }
}

int main() {
    SeatList seatList;
    BookingQueue bookingQueue = {NULL, NULL};
    int totalSeats = 10; // Example: 10 total seats
    initializeSeatList(&seatList, totalSeats);
    
    int choice, seatNumber;
    char passengerName[50];

    while (1) {
        printf("\n----- WAITING LIST MANAGEMENT SYSTEM -----\n");
        printf("1. Check seat availability\n");
        printf("2. Book a seat\n");
        printf("3. Cancel booking\n");
        printf("4. Edit booking\n");
        printf("5. Display seating chart\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter seat number to check availability: ");
                scanf("%d", &seatNumber);
                if (isSeatAvailable(&seatList, seatNumber)) {
                    printf("Seat %d is available.\n", seatNumber);
                } else {
                    printf("Seat %d is already booked.\n", seatNumber);
                }
                break;
            case 2:
                printf("Enter seat number to book: ");
                scanf("%d", &seatNumber);
                if (seatNumber < 1 || seatNumber > totalSeats) {
                    printf("Invalid seat number.\n");
                } else {
                    printf("Enter passenger name: ");
                    scanf("%s", passengerName);
                    if (!bookSeat(&seatList, seatNumber, passengerName)) {
                        enqueueBooking(&bookingQueue, seatNumber, passengerName);
                        processBookingQueue(&seatList, &bookingQueue);
                    }
                }
                break;
            case 3:
                printf("Enter seat number to cancel booking: ");
                scanf("%d", &seatNumber);
                if (seatNumber < 1 || seatNumber > totalSeats) {
                    printf("Invalid seat number.\n");
                } else {
                    cancelBooking(&seatList, seatNumber);
                }
                break;
            case 4:
                printf("Enter seat number to edit booking: ");
                scanf("%d", &seatNumber);
                if (seatNumber < 1 || seatNumber > totalSeats) {
                    printf("Invalid seat number.\n");
                } else {
                    printf("Enter new passenger name: ");
                    scanf("%s", passengerName);
                    editBooking(&seatList, seatNumber, passengerName);
                }
                break;
            case 5:
                displaySeatingChart(&seatList);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
