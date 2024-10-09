#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100                 
#define MAX_STR_LEN 100         

typedef struct {
    char question[MAX_STR_LEN];
    char answer[MAX_STR_LEN];
} Flashcard;

typedef struct {
    Flashcard cards[MAX];       
    int top;                    
} Stack;

void initialize_stack(Stack *s) {
    s->top = -1;                
}

int is_full(Stack *s) {
    return s->top == MAX - 1;   
}

int is_empty(Stack *s) {
    return s->top == -1;        
}

void push(Stack *s, Flashcard card) {
    if (is_full(s)) {
        printf("Stack is full! Cannot add more flashcards.\n");
        return;
    }
    s->cards[++s->top] = card;  
}

Flashcard pop(Stack *s) {
    if (is_empty(s)) {
        Flashcard empty_card = {"", ""}; 
        return empty_card;
    }
    return s->cards[s->top--];  
}

void add_question(Stack *s) {
    if (is_full(s)) {
        printf("Stack is full! Cannot add more questions.\n");
        return;
    }
    Flashcard new_card;          
    printf("Enter a new question: ");
    scanf(" %[^\n]", new_card.question);  
    printf("Enter the answer: ");
    scanf(" %[^\n]", new_card.answer);    
    push(s, new_card);           
    printf("Question added successfully.\n");
}

void answer_questions(Stack *main_stack, Stack *skip_stack) {
    int score = 0;               
    char user_answer[MAX_STR_LEN]; 
    Flashcard current_card;      
    while (!is_empty(main_stack)) {
        current_card = pop(main_stack); 
        printf("\nQuestion: %s\n", current_card.question);
        printf("Do you want to (a) answer or (s) skip this question? ");
        char choice;
        scanf(" %c", &choice);  
        if (choice == 'a') {    
            printf("Your Answer: ");
            scanf(" %[^\n]", user_answer); 
            if (strcmp(current_card.answer, user_answer) == 0) {
                printf("Correct!\n");
                score++;
            } else {
                printf("Incorrect. The correct answer is: %s\n", current_card.answer);
            }
        } else if (choice == 's') { 
            printf("Question skipped.\n");
            push(skip_stack, current_card); 
        }
    }
    while (!is_empty(skip_stack)) {
        current_card = pop(skip_stack);
        printf("\nRevisiting Skipped Question: %s\n", current_card.question);
        printf("Your Answer: ");
        scanf(" %[^\n]", user_answer);

        if (strcmp(current_card.answer, user_answer) == 0) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. The correct answer is: %s\n", current_card.answer);
        }
    }
    printf("\nAll questions answered. Your final score is: %d\n", score);
}

int main() {
    Stack main_stack, skip_stack; 
    initialize_stack(&main_stack); 
    initialize_stack(&skip_stack);  
    int choice;                
    while (1) {
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
                add_question(&main_stack); 
                break;
            case 2:
                if (is_empty(&main_stack)) {
                    printf("No questions available. Please add some first.\n");
                } else {
                    printf("\n************************\n");
					printf("Starting the quiz...\n"); 
                    answer_questions(&main_stack, &skip_stack); 
                }
                break;
            case 3:
                printf("Exiting the game. Thank you for playing!\n");
                return 0; 
            default:
                printf("Invalid choice. Please try again.\n");
        }
}
    return 0; 
}

