#include <iostream>

using namespace std;

class Element
{
public:
    int value;
    Element *next;
    Element *prev;

    Element (int x)
    {
        value = x;
        next = NULL;
        prev = NULL;
    }
};

class List
{
private:
    int amount;
public:
    Element *head;
    Element *tail;

    List()
    {
        head = NULL;
        tail = NULL;
        amount = 0;
    }

    void addFirst(int x)
    {
        Element *newElement = new Element(x);

        if ((head == NULL) && (tail == NULL))
        {
            head = newElement;
            tail = newElement;
            amount++;
        }
        else
        {
            head->prev = newElement;
            newElement->next = head;
            head = newElement;
            amount++;
        }
    }

    void addBetween(int x, int pos)
    {
        if ((pos >= 1) && (pos <= amount+1))
        {
            if (pos == 1)
                addFirst(x);
            else if (pos == amount+1)
                addLast(x);
            else
            {
                Element *newElement = new Element(x);
                Element *temp = head;

                for (int i=2; i<pos; i++)
                    temp = temp->next;

                newElement->prev = temp;
                newElement->next = temp->next;
                temp->next->prev = newElement;
                temp->next = newElement;
                amount++;
            }
        }
        else
            cout << "Nie mozna dodac elementu na pozycje: " << pos << "." << endl;
    }

    void addLast(int x)
    {
        Element *newElement = new Element (x);

        if ((head == NULL) && (tail == NULL))
        {
            head = newElement;
            tail = newElement;
            amount++;
        }
        else
        {
            Element *temp = tail;

            tail->next = newElement;
            newElement->prev = tail;
            tail = newElement;
            amount++;
        }
    }

    void deleteFirst()
    {
        if ((head == NULL) && (tail == NULL))
            cout << "Lista jest pusta, nie mam co usuwac!" << endl;
        else if (head->next == NULL)
        {
            delete(head);
            head = NULL;
            tail = NULL;
            amount--;
        }
        else
        {
            Element *toDelete = head;
            head = head->next;
            delete(toDelete);
            head->prev = NULL;
            amount--;
        }
    }


    void deleteBetween(int pos)
    {
        if ((pos >= 1) && (pos <= amount))
        {
            if (pos == 1)
                deleteFirst();
            else if (pos == amount)
                deleteLast();
            else
            {
                Element *temp = head;

                for (int i=2; i<pos; i++)
                    temp = temp->next;

                Element *toDelete = temp->next;
                temp->next = temp->next->next;
                temp->next->prev = temp;
                delete(toDelete);
                amount--;
            }
        }
        else
            cout << "Nie mozna usunac elementu z pozycji: " << pos << "." << endl;

    }


    void deleteLast()
    {
        if ((head == NULL) && (tail == NULL))
            cout << "Lista jest pusta, nie mam co usuwac!" << endl;
        else if (tail->prev == NULL)
        {
            delete(tail);
            head = NULL;
            tail = NULL;
            amount--;
        }
        else
        {
            Element *toDelete = tail;
            tail = tail->prev;
            delete(toDelete);
            tail->next = NULL;
            amount--;
        }
    }


    void find(int x)
    {
        Element *temp = head;
        int i = 1;
        cout << "Wartosc " << x << " znajduje sie na pozycjach: ";

        while (temp)
        {
            if (temp->value == x)
                cout << i << " ";

            temp = temp->next;
            i++;
        }
    }


    void show()
    {
        Element *temp = head;
        int i = 1;

        while (temp)
        {
            cout << i << ": " << temp->value << endl;
            temp = temp->next;
            i++;
        }
    }
};


List connect(List lista1, List lista2)
{
    List lista3;
    Element *temp1 = lista1.head;
    Element *temp2 = lista2.head;

    while(temp1)
    {
        lista3.addLast(temp1->value);
        temp1 = temp1->next;
    }
    while(temp2)
    {
        lista3.addLast(temp2->value);
        temp2 = temp2->next;
    }
    return lista3;
}


List deleteFromFirstSecondValues(List lista1, List lista2)
{
    Element *temp1 = lista1.head;
    Element *temp2 = lista2.head;
    int i;

    while(temp2)
    {
        temp1 = lista1.head;
        i = 1;
        while(temp1)
        {
            if(temp2->value == temp1->value)
            {
                temp1 = temp1->next;
                lista1.deleteBetween(i);
            }
            else
            {
                temp1 = temp1->next;
                i++;
            }
        }
    temp2 = temp2->next;
    }
    return lista1;
}



int main()
{
    List mojaLista1;
    List mojaLista2;
    List mojaLista3;

    cout << "Lista 1:" << endl;
    mojaLista1.addLast(4);
    mojaLista1.addLast(2);
    mojaLista1.addLast(6);
    mojaLista1.addLast(4);
    mojaLista1.addLast(6);
    mojaLista1.addLast(8);
    mojaLista1.addFirst(15);
    mojaLista1.show();

    cout << "Lista 2:" << endl;
    mojaLista2.addLast(6);
    mojaLista2.addLast(2);
    mojaLista2.show();

    cout << "Lista po polaczeniu Listy 1 oraz Listy 2:" << endl;
    mojaLista3 = connect(mojaLista1, mojaLista2);
    mojaLista3.show();

    cout << "Lista 1 po usunieciu elementow Listy 2:" << endl;
    mojaLista1 = deleteFromFirstSecondValues(mojaLista1, mojaLista2);
    mojaLista1.show();



    return 0;
}
