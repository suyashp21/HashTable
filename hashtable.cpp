#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>

using namespace std;


struct Student {
  char first[20];
  char last[20];
  int id;
  float gpa;
};

struct Node {
  Student* student;
  Node* next;
};

void addstudent(Node* hashtable[], int size, Student* s);
void printstudent(Student* s);
void print(Node* hashtable[], int size);
bool check(Node* hashtable[], int size);
void remove(Node* hashtable[], int size, int id);
Node** rehash(Node* hashtable[], int size);

int main() {
  int size = 100;
  char action[20];
  int deleteid;
  Node* hashtable [1600];
  for (int i=0; i<size; i++) {
    // create a dummy student as each head... makes this so much easier
    Student* s = new Student();
    s->id = i;
    Node* n = new Node();
    n->student = s;
    n->next = NULL;
    hashtable[i] = n;
  }

  while (true) {
    cout << "What would you like to do? (ADD, RANDOM, PRINT, DELETE, QUIT)" << endl;
    cin >> action;
    if (strcmp(action, "ADD") == 0) {
      Student* s = new Student();
      cout << "First name: "; cin >> s->first;
      cout << "Last name: "; cin >> s->last;
      cout << "ID: "; cin >> s->id;
      cout << "GPA: "; cin >> s->gpa;
      cout << "\n";
      addstudent(hashtable, size, s);
    }
    else if (strcmp(action, "PRINT") == 0) {
      print(hashtable, size);
    }
    else if (strcmp(action, "DELETE") == 0) {
      cout << "Enter the ID number of the student you are deleting: ";
      cin >> deleteid;
      remove(hashtable, size, deleteid);
    }
    else if (strcmp(action, "QUIT") == 0) {
      break;
    }
    else {
      cout << "I don't recognize that input." << endl;
    }
    /*
    while (check(hashtable, size) == true) {
      int newsize = 2*size;
      Node* newtable [newsize];
      for (int i=0; i<size; i++) {
	Node* current = hashtable[i]->next;
	while (current != NULL) {
	  addstudent(newtable, newsize, hashtable[i]->student);
	  current = current->next;
	}
      }
    }
    */
    
  }


  // addstudent(hashtable, size);

  // cout << hashtable[42]->next->student->first;

  return 0;
}

void addstudent(Node* hashtable[], int size, Student* s) {
  /* Student* s = new Student();
  cout << "First Name: "; cin >> s->first;
  cout << "Last Name: "; cin >> s->last;
  cout << "ID: "; cin >> s->id;
  cout << "GPA: "; cin >> s->gpa;
  cout << "\n"; */
  Node* n = new Node();
  n->student = s;
  n->next = NULL;
  int hash = (s->id)%size;
  Node* temp = new Node();
  temp = hashtable[hash];
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = n;
}

void printstudent(Student* s) {
  cout << s->first << " " << s->last << endl;
  cout << s->id << endl;
  cout << "GPA: " << fixed << setprecision(2) << s->gpa << endl;
  cout << "\n";
}

void print(Node* hashtable[], int size) {
  cout << "\n";
  Node* n = new Node();
  for (int i=0; i<size; i++) {
    n = hashtable[i];
    n = n->next;
    while (n != NULL) {
      printstudent(n->student);
      n = n->next;
    }
  }
}

bool check(Node* hashtable[], int size) {
  // check if table should be rehashed
  bool b = false;
  int numfull = 0;
  int count = 0;
  Node* n = new Node();
  for (int i=0; i<size; i++) {
    numfull = 0;
    n = hashtable[i];
    if (n->next == NULL) {
      continue;
    }
    n = n->next;
    while (n != NULL) {
      numfull = numfull+1;
      n = n->next;
    }
    if (numfull > 3) {
      b = true;
    }
  }
  if (count > size/2) {
    b = true;
  }
  return b;
}

void remove(Node* hashtable[], int size, int id) {
  // remove a student
  int i = id % size;
  Node* previous = hashtable[i];
  Node* current = hashtable[i]->next;
  bool found = false;
  char confirm;
  while (current != NULL) {
    if (current->student->id == id) {
      cout << "I'm about to delete " << current->student->first << " " << current->student->last << ". Is this what you want to do? (y/n)" << endl;
      cin >> confirm;
      if (confirm == 'y' || confirm == 'Y') {
	cout << "Deleting student." << endl;
	previous->next = current->next;
	delete current->student;
	delete current;
      }
      else {
	cout << "Ok. No student deleted." << endl;
      }
      found = true;
      break;
    }
    else {
      previous = current;
      current = current->next;
    }
  }
  if (found == false) {
    cout << "No student has that ID number. Nothing has been deleted." << endl;
  }
}

Node** rehash(Node* hashtable[], int size) {
  // rehash the table!!!
  int newsize = 2*size;
  Node* newtable [newsize];
  for (int i=0; i<size; i++) {
    Node* current = hashtable[i]->next;
    while (current != NULL) {
      addstudent(newtable, newsize, hashtable[i]->student);
      current = current->next;
    }
  }
  Node** returntable = newtable;
  return returntable;
}
