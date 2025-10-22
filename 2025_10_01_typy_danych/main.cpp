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
    Node *next = nullptr;
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

void insert_at_end(Node *start, Node *new_node)
{
    Node *temp = start;

    while(temp->next != nullptr) // temp->next, bo chcemy się zatrzymać na ostatnim elemencie, a nie wyjść poza i tym samym przypisywać nullptr do temp-a
    {
        temp = temp->next;
    }

    temp->next = new_node;
    temp = nullptr;// reset wskaźnika, aby nie było wyspu pamięci
    // delete - usuwa obiekt pod wskaźnikiem
    // = nullptr - resetuje wskaźnik
}

void insert_after(Node *start, Node *new_node, int index)
{
    int i {0};
    Node *temp = start;
    while(i != index)
    {
        temp = temp->next;
        i++;
    }
    new_node->next = temp->next;
    temp->next = new_node;
    temp = nullptr; // reset wskaźnika
}

Node remove_at_end(Node *start)
{
    if (start->next != nullptr) // jeśli lista jest 2 lub więcej elementowa
    {
        Node *temp = start;
        while(temp->next->next != nullptr)
        {
            temp = temp->next;
        }
        Node *result = temp->next;
        temp->next = nullptr;
        return *result;
    }
    else // kiedy lista ma jeden element
    {
        Node *result = start;
        start = nullptr;
        return *result;
    }
}

Node remove_at_start(Node *&start) // oryginalny wskaźnik
{
    Node *temp = start->next;
    Node *result = start;
    start = temp;
    result->next = nullptr;
    temp = nullptr;
    return *result;
}

Node remove_after(Node *start, int index)
{
    Node *temp = start;
    int i = 0;

    while (i < index - 1 && temp != nullptr && temp->next != nullptr)
    {
        temp = temp->next;
        i++;
    }

    if (temp == nullptr || temp->next == nullptr)
    {
        throw std::out_of_range("Index out of range or invalid operation.");
    }

    Node *result = temp->next;
    temp->next = temp->next->next;
    result->next = nullptr;
    return *result;
}

Node* get_node_ptr_at(Node *start, int index)
{
    Node *temp = start;
    int i = 0;
    while (i != index)
    {
        i++;
        temp = temp->next;
    }
    return temp;
}

Node get_node_at(Node *start, int index)
{
    Node *temp = start;
    int i = 0;
    while (i != index)
    {
        i++;
        temp = temp->next;
    }
    return *temp;
}

int get_value_at(Node *start, int index)
{
    Node *temp = start;
    int i = 0;
    while (i != index)
    {
        temp = temp->next;
        i++;
    }
    return temp->value;
}

void print_list(Node *start)
{
    Node *temp = start; // wskaźnikowy temp przypisz adres obiektu, na który wskazuje start
    int i = 0;
    while(temp != nullptr)
    {
        cout << i << ": \v\tAddress: "<< temp << "  <Value=" << temp->value << ", Next=" << temp->next << "> \n";
        temp = temp->next; // do wskaźnika temp zapisz adres obiektu pod temp->next
        i++;
    }
    //delete temp;//*to nic nie robi, bo delete usuwa obiekt, a temp wskazuje teraz na nullptr
}

void print_list_simpler(Node *start)
{
    Node *temp = start;
    while(temp != nullptr)
    {
        cout << temp->value << " ";
        temp = temp->next;
    }
}

int main()
{
    setlocale(LC_ALL, "pl_PL.UTF-8");
    Node *start = create_list();
    bool running = true;
    do
    {
        cout << endl;
        print_list_simpler(start);
        cout << endl << endl;
        cout << "===== Wybierz opcję =====" << endl;
        cout << "1. Dodaj na początek" << endl;
        cout << "2. Dodaj na koniec" << endl;
        cout << "3. Dodaj po ..." << endl;

        cout << "4. Usuń z początku" << endl;
        cout << "5. Usuń z końca" << endl;
        cout << "6. Usuń po ..." << endl;

        cout << "7. Pobierz wartość z indeksu ..." << endl;
        cout << "8. wyjdź" << endl;
        cout << "=========================" << endl;
        int choice;
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                int value;
                cout << "Wpisz wartość: ";
                cin >> value;

                insert_at_start(start, new Node{value});
                break;
            }
            case 2:
            {
                int value;
                cout << "Wpisz wartość: ";
                cin >> value;

                insert_at_end(start, new Node{value});
                break;
            }
            case 3:
            {
                int value, index;
                cout << "Podaj numer indeksu: ";
                cin >> index;

                cout << "Wpisz wartość: ";
                cin >> value;

                insert_after(start, new Node{value}, index);
                break;
            }
            case 4:
            {
                remove_at_start(start);
                break;
            }
            case 5:
            {
                remove_at_end(start);
                break;
            }
            case 6:
            {
                int index;
                cout << "Podaj indeks: ";
                cin >> index;

                remove_after(start, index);
                break;
            }
            case 7:
            {
                int index;
                cout << "Podaj indeks: ";
                cin >> index;

                int value = get_value_at(start, index);
                cout << "Wartość pod indeksem " << index << " to " << value << endl;
                getchar();
                break;
            }
            case 8:
            {
                exit(0);
            }
            default:
            {
                cout << "Nie ma takiej opcji! spróbuj ponownie!" << endl;
                getchar();
                break;
            }
        }
        system("clear");
    } while (running);
    
    /*
    Node *start = create_list(10);
    Node *new_node = new Node({12, nullptr});
    // cout << "pointer start: " << &start << endl;
    // cout << "object start: " << start << endl;
    // cout << "pointer new_node: " << &new_node << endl;
    // cout << "object new_node: "<< new_node << endl;
    insert_at_start(start, new_node);
    insert_at_end(start, new Node({15, nullptr}));
    insert_after(start, new Node({-5, nullptr}), 1);
    // cout << "in main: "<<endl;
    // cout << "pointer start: " << &start << endl;
    // cout << "object start: " << start << endl;
    // cout << "pointer new_node: " << &new_node << endl;
    // cout << "object new_node: "<< new_node << endl;


    insert_at_end(start, new Node({20}));
    insert_at_start(start, new Node({7}));
    insert_after(start, new Node({14}), 2);

    print_list(start); // 7 12 10 14 -5 15 20

    Node node1 = get_node_at(start, 4);
    cout << endl << endl << node1.value << endl; // -5
    
    Node *node2_ptr = get_node_ptr_at(start, 2);
    cout << endl << node2_ptr->value << endl; // 10

    int node3 = get_value_at(start, 3);
    cout << endl << node3 << endl; // 14

    Node rm1 = remove_at_start(start);
    cout << endl << rm1.value << endl; // 7

    Node rm2 = remove_at_end(start);
    cout << endl << rm2.value << endl; // 20

    Node rm3 = remove_after(start, 2); // 14
    cout << endl << rm3.value << endl;

    */

    return 0;
}


