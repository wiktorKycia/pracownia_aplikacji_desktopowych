#include<iostream>
using namespace std;
/*
Zadanie polega na implementacji w czystym języku C 
i przetestowaniu następujących funkcji realizujących operacje 
na przedmiotowych na tych zajęciach strukturach danych: 
tworzenie dynamicznej listy jednokierunkowej, 
dopisanie/usunięcie elementu (na początku listy, na końcu listy, wewnątrz listy (przed/po ustalonym elementem/cie)), 
wydrukowanie całej listy, 
wyszukanie konkretnego elementu w liście. 
Analogiczne operacje należy zaimplementować dla stosu i kolejki z uwzględnieniemich ograniczeń konstrukcyjnych. 
Rozwiązanie powinno zawierać podział kodu na pliki nagłowkowe i implementacyjne. 
*/

struct Node
{
    int value;
    Node* next;
};
void display_list(Node *start);
void create_first_node(Node *start, int starting_value);
void insert_at_end(Node *start, Node *new_node);
void insert_at_beginning(Node *start, Node *new_node);
Node* start = nullptr;

int main()
{
    create_first_node(start, 1);
    insert_at_beginning(start, new Node({2, nullptr}));
    insert_at_end(start, new Node({3, nullptr}));

    display_list(start);
}

void display_list(Node *start)
{
    Node *temp = start;
    while(temp->next != nullptr)
    {
        cout << (*temp).value << endl; // (*temp).value to to samo co temp->value
    }
    delete temp;
}

void create_first_node(Node *start, int starting_value)
{
    start = new Node({starting_value, nullptr});
}

void insert_at_end(Node *start, Node *new_node)
{
    Node *temp = start;
    while(temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = new_node;
    new_node->next = nullptr;
    delete temp;
}

void insert_at_beginning(Node **start, Node *new_node) 
{
    if (new_node == NULL) return;  // Safety check
    
    new_node->next = *start;  // Point new node to current first node
    *start = new_node;        // Update start to point to new node
}