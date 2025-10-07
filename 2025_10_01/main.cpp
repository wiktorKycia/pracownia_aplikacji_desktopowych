#include <iostream>

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
    Node *next;
};

Node* create_list(int initial_first_value = 0)
{
    return new Node({initial_first_value, nullptr});
}

void insert_at_start(Node *&start, Node *new_node) // do funkcji jako parametr start przekazujemy oryginalny wskaźnik
{
    // cout << "in function" <<endl;
    // cout << "pointer start: " << &start << endl;
    // cout << "object start: " << start << endl;
    // cout << "pointer new_node: " << &new_node << endl;
    // cout << "object new_node: "<< new_node << endl;
    new_node->next = start; // obiektowi new_node do właściwości next przypisza adres obiektu na który wskazuje start
    start = new_node; // do wskaźnika start przypisujemy adres obiektu new_node
    // cout << "pointer start: " << &start << endl;
    // cout << "object start: " << start << endl;
    // cout << "pointer new_node: " << &new_node << endl;
    // cout << "object new_node: "<< new_node << endl;
}

void print_list(Node *start)
{
    Node *temp = start; // wskaźnikowy temp przypisz adres obiektu, na który wskazuje start
    while(temp != nullptr)
    {
        cout << "<Value=" << temp->value << ", Next=" << temp->next << "> \n";
        temp = temp->next; // do wskaźnika temp zapisz adres obiektu pod temp->next
    }
    delete temp;
}

int main()
{
    Node *start = create_list(10);
    Node *new_node = new Node({12, nullptr});
    // cout << "pointer start: " << &start << endl;
    // cout << "object start: " << start << endl;
    // cout << "pointer new_node: " << &new_node << endl;
    // cout << "object new_node: "<< new_node << endl;
    insert_at_start(start, new_node);
    // cout << "in main: "<<endl;
    // cout << "pointer start: " << &start << endl;
    // cout << "object start: " << start << endl;
    // cout << "pointer new_node: " << &new_node << endl;
    // cout << "object new_node: "<< new_node << endl;

    print_list(start);
    return 0;
}


