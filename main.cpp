#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cstdlib> 
#include <ctime>   
#include <cmath>

using namespace std;

struct ReviewNode {
    double rating;
    string comment;
    ReviewNode* next;
};
class Movie {
private:
    string title;
    ReviewNode* head;

    void cleanup() {
        ReviewNode* current = head;
        while (current != nullptr) {
            ReviewNode* nextNode = current->next; 
            delete current;                       
            current = nextNode;                   
        }
        head = nullptr; // set head to null to indicate the list is empty
    }

public:
    // constructor initializes the movie with a title
    Movie(const string& movieTitle) : title(movieTitle), head(nullptr) {}

    // destructor automatically calls the cleanup function to prevent memory leaks
    ~Movie() {
        cleanup();
    }

    // adds a new review with a randomly generated rating to the head of the list
    void addReview(const string& comment) {
        // generate a random rating between 1.0 and 5.0
        double rating = 1.0 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (5.0 - 1.0)));
        rating = floor(rating * 10) / 10; // Round down to one decimal place

        // create the new review node
        ReviewNode* newNode = new ReviewNode{rating, comment, nullptr};
        
        // add the new node to the head of the list
        if (head != nullptr) {
            newNode->next = head;
        }
        head = newNode;
    }

    // prints all reviews for the movie and calculates the average rating
    void printReviews() const {
        if (head == nullptr) {
            cout << "\nNo reviews for \"" << title << "\"." << endl;
            return;
        }

        cout << "\n--- Reviews for \"" << title << "\" ---" << endl;
        ReviewNode* current = head;
        double totalRating = 0.0;
        int count = 0;

        while (current != nullptr) {
            count++;
            cout << "> Rating: " << fixed << setprecision(1) << current->rating
                 << " | Comment: " << current->comment << endl;
            totalRating += current->rating;
            current = current->next;
        }

        if (count > 0) {
            double average = totalRating / count;
            cout << "> Average Rating: " << fixed << setprecision(2) << average << endl;
        }
    }
};




int main() {
    srand(static_cast<unsigned int>(time(0)));

    // read review comments from an external file into a vector
    ifstream commentFile("comments.txt");
    vector<string> comments;
    string line;

    //pointer settings
    ReviewNode* head = nullptr;
    ReviewNode* tail = nullptr;

    int choice = 0;
    cout << "Which linked list method should we use?" << endl;
    cout << "[1] New nodes are added at the head of the linked list" << endl;
    cout << "[2] New nodes are added at the tail of the linked list" << endl;
    cout << "Choice: ";
    cin >> choice;
    // input verification
    while (cin.fail() || (choice != 1 && choice != 2)){
        cout << "Invalid input. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choice;    
    }
    char another = 'y';
    do {
        double rating = -1.0;
        string comment;

        // get the review rating from the user with validation
        cout << "Enter review rating 0-5: ";
        cin >> rating;
        while (cin.fail() || rating < 0 || rating > 5) {
             cout << "Invalid rating. Please enter a number between 0 and 5: ";
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             cin >> rating;
        }

        // get the review comment
        cout << "Enter review comments: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the newline character left by cin
        getline(cin, comment);

        // add the new node based on the user's initial choice
        if (choice == 1) {
            addNodeToHead(head, tail, rating, comment);
        } else { 
            addNodeToTail(head, tail, rating, comment);
        }

        // ask if the user wants to enter another review
        cout << "Enter another review? Y/N: ";
        cin >> another;

    } while (another == 'y' || another == 'Y');

    
    printListAndAverage(head);

    
    cleanup(head);

    return 0;
}


void addNodeToTail(ReviewNode*& head, ReviewNode*& tail, double rating, const string& comment) {
    ReviewNode* newNode = new ReviewNode{rating, comment, nullptr};
    if (head == nullptr) {
        // if the list is empty, the new node is both the head and the tail
        head = newNode;
        tail = newNode;
    } else {
        // else link the current tail to the new node and update tail
        tail->next = newNode;
        tail = newNode;
    }
}

void addNodeToHead(ReviewNode*& head, ReviewNode*& tail, double rating, const string& comment) {
    ReviewNode* newNode = new ReviewNode{rating, comment, nullptr};
    if (head == nullptr) {
        // If the list is empty, the new node is both the head and the tail
        head = newNode;
        tail = newNode;
    } else {
        // Otherwise, link the new node to the current head and update head
        newNode->next = head;
        head = newNode;
    }
}

void printListAndAverage(ReviewNode* head) {
    if (head == nullptr) {
        cout << "\nNo reviews to display." << endl;
        return;
    }

    cout << "\nOutputting all reviews:" << endl;
    ReviewNode* current = head;
    double totalRating = 0.0;
    int count = 0;

    while (current != nullptr) {
        count++;
        cout << "> Review #" << count << ": " << current->rating << ": " << current->comment << endl;
        totalRating += current->rating;
        current = current->next;
    }

    if (count > 0) {
        double average = totalRating / count;
        cout << "> Average: " << fixed << setprecision(6) << average << endl;
    }
}

void cleanup(ReviewNode*& head) {
    ReviewNode* current = head;
    while (current != nullptr) {
        ReviewNode* nextNode = current->next; 
        delete current;                       
        current = nextNode;                   
    head = nullptr; 
    }
}