#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100                 // Maximum number of flashcards
#define MAX_STR_LEN 100         // Maximum string length for questions and answers

// Structure to represent a flashcard
typedef struct {
    char question[MAX_STR_LEN];
    char answer[MAX_STR_LEN];
} Flashcard;

// Stack structure to hold flashcards
typedef struct {
    Flashcard cards[MAX];       // Array to store flashcards
    int top;                    // Index of the top card
} Stack;

// Function to initialize a stack
void initialize_stack(Stack *s) {
    s->top = -1;                // Set top index to -1 (empty stack)
}

// Function to check if the stack is full
int is_full(Stack *s) {
    return s->top == MAX - 1;   // Returns 1 if full, else 0
}

// Function to check if the stack is empty
int is_empty(Stack *s) {
    return s->top == -1;        // Returns 1 if empty, else 0
}

// Function to push a flashcard onto the stack
void push(Stack *s, Flashcard card) {
    if (is_full(s)) {
        printf("Stack is full! Cannot add more flashcards.\n");
        return;
    }
    s->cards[++s->top] = card;  // Add card to stack and increment top index
}

// Function to pop a flashcard off the stack
Flashcard pop(Stack *s) {
    if (is_empty(s)) {
        Flashcard empty_card = {"", ""}; // Return an empty card if stack is empty
        return empty_card;
    }
    return s->cards[s->top--];  // Return top card and decrement top index
}

// Function to allow players to add questions
void add_question(Stack *s) {
    if (is_full(s)) {
        printf("Stack is full! Cannot add more questions.\n");
        return;
    }

    Flashcard new_card;          // Create a new flashcard
    printf("Enter a new question: ");
    scanf(" %[^\n]", new_card.question);  // Read the question
    printf("Enter the answer: ");
    scanf(" %[^\n]", new_card.answer);    // Read the answer

    push(s, new_card);           // Push the new flashcard onto the stack
    printf("Question added successfully.\n");
}

// Function to play the quiz game
void answer_questions(Stack *main_stack, Stack *skip_stack) {
    int score = 0;               // Variable to keep track of score
    char user_answer[MAX_STR_LEN]; // Buffer for user answers
    Flashcard current_card;      // Variable to hold current flashcard

    while (!is_empty(main_stack)) {
        current_card = pop(main_stack); // Get the top flashcard
        
        printf("\nQuestion: %s\n", current_card.question);
        printf("Do you want to (a) answer or (s) skip this question? ");
        char choice;
        scanf(" %c", &choice);  // Read user choice

        if (choice == 'a') {    // If the user chooses to answer
            printf("Your Answer: ");
            scanf(" %[^\n]", user_answer); // Read user answer

            // Check if the answer is correct
            if (strcmp(current_card.answer, user_answer) == 0) {
                printf("Correct!\n");
                score++;
            } else {
                printf("Incorrect. The correct answer is: %s\n", current_card.answer);
            }
        } else if (choice == 's') { // If the user chooses to skip
            printf("Question skipped.\n");
            push(skip_stack, current_card); // Move current card to skip stack
        }
    }

    // Revisit skipped questions
    while (!is_empty(skip_stack)) {
        current_card = pop(skip_stack);
        
        printf("\nRevisiting Skipped Question: %s\n", current_card.question);
        printf("Your Answer: ");
        scanf(" %[^\n]", user_answer);

        // Check the user's answer for the skipped question
        if (strcmp(current_card.answer, user_answer) == 0) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. The correct answer is: %s\n", current_card.answer);
        }
    }

    // End game and display final score
    printf("\nAll questions answered. Your final score is: %d\n", score);
}

// Main function to run the quiz game
int main() {
    Stack main_stack, skip_stack; // Declare stacks for main questions and skipped questions
    initialize_stack(&main_stack); // Initialize main stack
    initialize_stack(&skip_stack);  // Initialize skip stack

    int choice;                   // Variable for menu choice

    while (1) {
        // Display menu options
        printf("\n---------------------------\n");        
        printf("\nFlashcard Quiz Game\n");
        printf("\n---------------------------\n");
        printf("\nMENU\n");
        printf("1. Add a Question\n");
        printf("2. Start the Quiz\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_question(&main_stack); // Call function to add questions
                break;
            case 2:
                if (is_empty(&main_stack)) {
                    printf("No questions available. Please add some first.\n");
                } else {
                    printf("\n************************\n");
					printf("Starting the quiz...\n"); // Indicate quiz is starting
                    answer_questions(&main_stack, &skip_stack); // Call function to start quiz
                }
                break;
            case 3:
                printf("Exiting the game. Thank you for playing!\n");
                return 0; // Exit the program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0; // Program should never reach here
}

