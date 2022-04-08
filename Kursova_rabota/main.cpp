#include <iostream>
#include <fstream>
#include <iomanip> // For setprecision
#include <algorithm> // For erase/remove

using namespace std;

class ElectronicComponents {
private:
    string nomenclatureNum;
    string name;
    int value;
    string unit;
public:
    ElectronicComponents(string num, string n, int v, string u) {
        nomenclatureNum = num;
        name = n;
        value = v;
        unit = u;
    }
    string getName() {
        return name;
    }
    int getValue() {
        return value;
    }
    virtual void show() = 0;
    void showEc() {
        cout << "Nomenclature number: " << nomenclatureNum << "\n";
        cout << "Name: " << name << "\n";
        cout << "Value: " <<value << "" << unit << "\n";
    }
    ~ElectronicComponents() {
    }
};

class Resistor : public ElectronicComponents {
private:
    string country;
    double price;
public:
    Resistor(string c, double p, string num, string n, int v, string u) : ElectronicComponents(num, n, v, u) {
        country = c;
        price = p;
    }
    void show() {
        showEc();
        cout << "Made in: " << country << "\n";
        cout << fixed << setprecision(2) << "Price: " << price << "$\n";
    }
    ~Resistor() {
    }
};

class Capacitor : public ElectronicComponents {
private:
    string country;
    double price;
public:
    Capacitor(string c, double p, string num, string n, int v, string u) : ElectronicComponents(num, n, v, u) {
        country = c;
        price = p;
    }
    void show() {
        showEc();
        cout << "Made in: " << country << "\n";
        cout << fixed << setprecision(2) << "Price: " << price << "$\n";
    }
    ~Capacitor() {
    }
};

class LinkedList {
private:
    struct node {
        ElectronicComponents* compData;
        node* next;
        node(ElectronicComponents* newComp, node* newNext){
           compData = newComp;
           next = newNext;
        }
        ~node() {
        }
    };
    node *head, *tail;
public:
    LinkedList() {
        head = NULL;
        tail = NULL;
    }
    void addNode(ElectronicComponents* newComp) {
        node *tmp = new node(newComp, NULL);
        if(head == NULL) {
            head = tmp;
            tail = tmp;
        }
        else {
            tail->next = tmp;
            tail = tail->next;
        }
    }
    void removeNode(ElectronicComponents* removedComp) {
        node *tmp = head;
        node *prev = NULL;
        if (tmp != NULL && tmp->compData == removedComp) {
                head = tmp->next;
                delete tmp;
                return;
        }
        else {
            while (tmp != NULL && tmp->compData != removedComp) {
                prev = tmp;
                tmp = tmp->next;
            }
        }
        if (tmp == NULL) {
            return;
        }
        prev->next = tmp->next;
        delete tmp;
    }
    void search(string name, int minValue, int maxValue) {
        node *tmp = head;
        while (tmp != NULL) {
            if (tmp->compData->getName() == name && tmp->compData->getValue() >= minValue && tmp->compData->getValue() <= maxValue) {
                tmp->compData->show();
                cout << "\n";
            }
            tmp = tmp->next;
        }
    }
};

int main()
{
    string name;
    int minValue;
    int maxValue;

    cout << "Enter component type: ";
    cin >> name;
    name.erase(remove(name.begin(), name.end(), ' '), name.end());
    name[0] = toupper(name[0]);
    if (name != "Capacitor" && name != "Resistor") {
        cout << "Invalid component type!";
        return 0;
    }
    cout << "Enter minimum value: ";
    cin >> minValue;
    cout << "Enter maximum value: ";
    cin >> maxValue;

    streambuf *coutbuf = cout.rdbuf();
    ofstream Results("Results.txt");
    cout.rdbuf(Results.rdbuf());

    Capacitor *cap1 = new Capacitor("Germany", 1.20, "CG213", "Capacitor", 50, "pF");
    Capacitor *cap2 = new Capacitor("Italy", 1.00, "CI214", "Capacitor", 40, "pF");
    Capacitor *cap3 = new Capacitor("Germany", 2.00, "CG215", "Capacitor", 100, "pF");
    Resistor *res1 = new Resistor("France", 0.50, "RF118", "Resistor", 20, "oM");

    LinkedList list;
    list.addNode(cap1);
    list.addNode(cap2);
    list.addNode(cap3);
    list.addNode(res1);
    list.removeNode(cap3);
    list.search(name, minValue, maxValue);

    Results.close();
    cout.rdbuf(coutbuf);
    cout << "\nSaved to file Results.txt!\n";

    return 0;
}
