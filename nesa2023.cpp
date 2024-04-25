#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

string toLowercase(string str){
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

//itemadd
void itemAdd(){
	int item_id;
	float item_quantity;
	string item_name, item_date;
	string user_input;
	
	cout << "Enter the item data separated by comma: ";
	getline(cin, user_input);
	
	//stringstream for parsing 
	stringstream ss(user_input);
	
	//parse input
	char comma = ',';
	ss >> item_id >> comma;
	getline(ss, item_name, ',');
	ss >> item_quantity >> comma;
	getline(ss, item_date, ',');
	
	//open file
	ofstream file("itemdata.csv", ios::app);
	if(!file.is_open()){
		cout << "Failed opening the specified file." << endl;
		return;
	}else{
		file << item_id << " " << item_name << " " << item_quantity << " " << item_date << endl;
		file.close();
		cout << "The data added to the file successfully." << endl;
	
	}
	
}

//listItems
void listItems(){
	//read data 
	ifstream file("itemdata.csv");
	if(!file.is_open()){
		cout << "Failed opening the specified file.";
		return;
	}else{
		string line;
		int item_id;
		float item_quantity;
		string item_name, item_date;
		while(getline(file, line)){
			//read data from a string
			//default - data separated by spaces
			stringstream ss(line);
			ss >> item_id ;
			ss >> item_name;
			ss >> item_quantity;
			ss >> item_date;
			
			//print data 
			cout << "Item ID: " << item_id << "\t" 
			<< "Item Name: " << item_name << "\t"
			<< "Item Quantity: " << item_quantity << "\t"
			<< "Item Date: " << item_date << "\t" << endl;
		}
		file.close();
	}	
	
}

//commands
void commands(){
	string command;
	string lowercaseCommand;
	
	command_loop:
	while(true){
		cout << "\nEnter command/ help for more info: ";
		getline(cin, command);
		lowercaseCommand = toLowercase(command);
		
		if(lowercaseCommand == "itemadd"){
			itemAdd();
			goto command_loop;
		}else if(lowercaseCommand == "listitems"){
			listItems();
			goto command_loop;
		}else if(lowercaseCommand == "help"){
			cout << "Command syntaxes: itemadd, listitems, exit, help" << endl;
			goto command_loop;
		}else if(lowercaseCommand == "exit"){
			break;
		}else{
			cout<< "This command doesn't exist"<< endl;
			goto command_loop;
		}
	}
	
}

int main(){
	cout << "=================ITEM REGISTRATION===================\n";
	 commands();
	return 0;
}
