//---------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <iomanip>
#pragma hdrstop
#include <tchar.h>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const  char FILE_PATH[] = "I:\\iofile";

fstream MyFile( FILE_PATH, ios :: binary | ios :: in | ios :: out );
struct Deck
{
	int order;
	char name[ 20 ];
};

void printOptions();
void switchFunction();
void createFile();
void addRecord();
void printAllRecord();
int searchRecord( int );
int displayRecord();

//---------------------------------------------------------------------------
#pragma argsused
int main()
{
	if ( ! MyFile )
	{
		createFile();
	}
	cout << setw( 15) << right << "| Tarot card picking |" << endl;
	switchFunction();

	MyFile.close();
	return 0;
}
//---------------------------------------------------------------------------
//void printOptions()
//Purpose: print the menu of options to do in program
//Intput: NULL
//Output: NULL
//---------------------------------------------------------------------------
void printOptions()
{
  cout << endl << "Enter the choice to do" << endl << endl
		 << "ESC - exit the program" << endl
	//	 << "E - Edit a file." << endl
		 << "A - Print all record to screen." << endl
		 << "P - Pick a card." << endl;
}
//---------------------------------------------------------------------------
//switchFunction(  int choice )
//Purpose: switch options
//Intput: choice as integer
//Output: NULL
//---------------------------------------------------------------------------
void switchFunction()
{
	char choice;

	printOptions();
	choice = toupper ( getch() );


	while ( choice != 27 )
	{
		switch ( choice )
		{
		//	case 'E':
		//		addRecord();
		//		break;
			case 'A':
				printAllRecord();
				break;
			case 'P':
				displayRecord();
				break;
			default:
				cout << "Wrong option" << endl;
		}
//    clrscr();
		printOptions();
		choice = toupper ( getch() );
	}
}
//---------------------------------------------------------------------------
//void createFile()
//Purpose: Create a file of record.
//Intput: NULL
//Output: NULL
//---------------------------------------------------------------------------
void createFile()
{
	if ( ! MyFile )
	{
		fstream MyFile( FILE_PATH, ios :: binary | ios:: out );
	}

	MyFile.close();
}
//---------------------------------------------------------------------------
//void addRecord()
//Purpose: Add a record.
//Intput: NULL
//Output: NULL
//---------------------------------------------------------------------------
void addRecord()
{
	Deck temp;

	char opt;
	int counter = 0;
	
	cout << "--Add a record--" << endl << endl;
	while ( opt != 27 )
	{
		temp.order = counter;
	
		cout << "Enter name: ";
		cin >> temp.name;
	
		MyFile.open( FILE_PATH, ios :: binary | ios :: in | ios :: out );
		MyFile.clear();
		MyFile.seekp( 0, ios :: end );
		MyFile.write( ( const char* ) &temp, sizeof( Deck ) );
		MyFile.close();
		
		counter++;
		cout << endl <<"'Esc'- exite or any key to continue!!'" << endl;
		opt = getch(); 
	}
}
//---------------------------------------------------------------------------
//void printAllRecord()
//Purpose: Print all record to screen.
//Intput: NULL
//Output: NULL
//---------------------------------------------------------------------------
void printAllRecord()
{
	Deck temp;

	cout << "--Print all--" << endl << endl;

	MyFile.open( FILE_PATH, ios :: binary | ios :: in );
	MyFile.clear();
	MyFile.seekp ( 0 , ios :: beg );
	MyFile.read( ( char* ) &temp, sizeof ( Deck ) );

	while ( ! MyFile.eof() )
	{
		cout << left << setw( 4 ) << temp.order
           << setw ( 20  ) << temp.name;
		MyFile.read( ( char* ) &temp, sizeof ( Deck ) );
	}

	MyFile.close();
}
//---------------------------------------------------------------------------
//int searchRecord( char itemToFind[] )
//Purpose: Search for a record.
//Intput: itemToFind as integer
//Output: position as integer
//---------------------------------------------------------------------------
int searchRecord( int itemToFind )
{
	Deck temp;

	MyFile.open( FILE_PATH, ios :: binary | ios :: in );
	MyFile.clear();
	MyFile.seekp ( 0, ios :: beg );
	MyFile.read( ( char* ) &temp, sizeof ( Deck ) );

	int i = 0;
	while ( ! MyFile.eof() )
	{
		if (  temp.order == itemToFind  )
		{
			MyFile.close();
			return i;
		}
		MyFile.read( ( char* ) &temp, sizeof ( Deck ) );
		i++;
	}

	MyFile.close();
	return -1;
}
//---------------------------------------------------------------------------
//int displayRecord();
//Purpose: Display a record.
//Intput: NULL
//Output: position as integer
//---------------------------------------------------------------------------
int displayRecord()
{
	Deck temp;

	int position;
	int num;
	char choice;
	
	while ( choice != 27 )
	{	
		srand(time(0));
		int a = rand() % 553;
		cout << endl << "Enter the number you want ( < 10^10 ): ";
		cin >> num;
		temp.order = (num + a) % 79;
	  	position = searchRecord( temp.order);
		
		srand(time(0));
		int rev = rand() % 2;
	
		if ( position == -1 )
			cout << endl << "Record not found." << endl;
		else
		{
			MyFile.open( FILE_PATH, ios :: binary | ios :: in );
			MyFile.clear();
			MyFile.seekp ( position * sizeof( Deck ), ios :: beg );
			MyFile.read( ( char* ) &temp, sizeof ( Deck ) );
			MyFile.close();
	
			cout << endl <<"--------------------------" << endl
						 << setw(10) << right<< temp.name;
					
			if ( rev == 1 )
				cout << " rev" << endl;
				
			cout << endl <<"--------------------------" << endl;
		}
		
		cout << endl << "Continue ??? or Press 'Esc' to exit." << endl;
		choice= getch();
	}	
	return position;
}
//---------------------------------------------------------------------------

