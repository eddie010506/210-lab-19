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

    if (!commentFile) {
        cerr << "Error: Could not open comments.txt. Please ensure the file exists in the same directory." << endl;
        return 1;
    }

    while (getline(commentFile, line)) {
        if (!line.empty()) {
            comments.push_back(line);
        }
    }
    commentFile.close();

   

    // create a container of Movie objects
    vector<Movie> movies;
    movies.emplace_back("Inception");
    movies.emplace_back("The Matrix");
    movies.emplace_back("Parasite");
    movies.emplace_back("The Grand Budapest Hotel");

    // add at least three reviews to each movie object
    int commentIndex = 0;
    for (auto& movie : movies) {
        for (int i = 0; i < 3; ++i) {
            if(commentIndex < comments.size()){
                movie.addReview(comments[commentIndex]);
                commentIndex++;
            }
        }
    }

    // print all the reviews for each movie
    for (const auto& movie : movies) {
        movie.printReviews();
    }

    return 0;
}