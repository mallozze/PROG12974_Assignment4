/*
 * Name: Eric Mallozzi
 * Student Number: 991242826
 * Class: PROG10111 1209_24301, Fall 2020
 * Date: 11/27/2020
 * Program: Assignment4_Mallozzi.c
 * Description: A file (book.txt) conains information about books.
 * 				It will be uploaded to the program for the user to update
 *				the prices of the book by a percentage, and then save the 
 *				updated prices to the file.
 * Sheridan College: Trafalgar Campus
 */
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX 100

//Defining a struct for the book's information in the file
typedef struct{
	int id;
	char title[100];
	char author[100];
	int year;
	double price;
} Book;

//Defining functions to be used:

/*
 * readFromFile() Will read the information from the file as well as assigning 
 * each value to the related value in the struct. The function will run until 
 * the file has reached the end. 
 * Will return an integer of the amount of books that was processed
*/
int readFromFile();

/*
 * listBooks() will list the books from the file that was assigned to the 
 * Book structure. 
 * It will accept the count argument containing the amount
 * of books that were processed.
 */
void listBooks(int count);


/*
 * changePrices() will change the price of the books by a percentage that was
 * given by the user. 
 * It will accept the count argument containing the amount
 * of books that were processed, and the percentage that was entered by the 
 * user.
 */
void changePrices(int count, double percentage);


/*
 * writeToFile() will rewrite the information in the text-file with the 
 * updated information the user has implemented: the price.
 * Accepts the argument count for the amount of books that were processed.
 */
void writeToFile(int count);


//Defining the global variables to be used everywhere

//An array for the Book structure. Will be storing the books from the file.
//Will store up to 100 books 
Book books[MAX];

//A FILE variable to open the text-file to be processed
FILE *file;
 
 
 //Main function: where all the magic happens.
int main(){
	
	//A loop that will break once the user enters 0, signifying that no more
	//prices need to be changed.
	while(1){
	
		//initializing the count variable and running the 
		//readFromFile() function
		int count = readFromFile();
	
		//calls the listBooks function, passing the count
		listBooks(count);
		
		//initializing the percentage
		double percentage = 0.0;
		
		//prompting the user to enter the percentage change to the prices
		printf("Enter percent of price to increase: ");
		scanf("%lf", &percentage);
		
		//if the user enters 0, then the program exits
		if(percentage = 0.0 ){
			break;
		}
		
		//adding 1 to percentage to make it easier for calculations
		percentage = (percentage / 100) + 1;
	
		//Changing the prices in the struct 
		changePrices(count, percentage);
		
		//Writes the changes to the file
		writeToFile(count);

	}

	
	return 0;
}

int readFromFile(){
	
	//opens the file to be read and processed
	file = fopen("books.txt", "r");
	
	//initializing the counter
	int count = 0;
	
	//Error handling if the file has trouble reading
	if(file == NULL){
		printf("Error reading from the file");
		exit(1);
	} 
	
	puts("\nReading books from file completed.");
	
	//a loop that will read from a file and will continue until it has
	//reached the end of the file
	while(!feof(file)){
		
		//used to catch new lines
		char ch;
		
		//grabbing the ID for the book
		fscanf(file, "%d", &books[count].id);
		
		//grabbing the new line to not cause errors
		fscanf(file, "%c", &ch);
		
		//grabbing the title of the book
		fgets(&books[count].title, "%s", file);
		
		//grabbing the author of the book
		fgets(&books[count].author, "%s", file);
		
		//grabbing the year the book was published
		fscanf(file, "%d", &books[count].year);
		
		//grabbing the price of the book
		fscanf(file, "%lf", &books[count].price);
		
		//iterating the count of the amount of books processed
		++count;
		
	}
	
	//subtracting 1 from count because it counts the end of file read as a book
	count -= 1;
	
	//closing the file
	fclose(file);
	
	//returning the number of books
	return count;
}

void listBooks(int count){
	puts("==== Book List ====");
	
	//loop to print all the information grabbed from the file and 
	//stored in the Book structure
	for(int i = 0; i < count; i++){
		
		//print statement with formatting
		printf("%-8s%d\n%-8s%s%-8s%s%-8s%d\n%-8s%.2lf\n", 
		"ID:", books[i].id, "Title:", books[i].title, 
		"Author:", books[i].author, "Year:", books[i].year, 
		"Price:", round(books[i].price * 100) / 100);
		puts("---------------------");

	}
}

void changePrices(int count, double percentage){

	//adjusting the prices using the percentage the user gave
	for(int i = 0; i < count; i++){
		books[i].price *= percentage;
	}
	
	//letting the user knows the prices have changed
	puts("Prices changed");
}

void writeToFile(int count){
	
	//opens the file to write to it
	file = fopen("books.txt", "w");
	
	//overwriting the file with the updated information
	for(int i = 0; i < count; i++){
		
		//formatting how the file will be saved in the text file.
		fprintf(file, "%d\n%s%s%d\n%.2lf\n", books[i].id, books[i].title, 
		books[i].author, books[i].year, round(books[i].price * 100) / 100);
	}
	
	//closing the file
	fclose(file);
	
	//letting the user know the file writing is successful
	puts("Writing books to file completed");
}
