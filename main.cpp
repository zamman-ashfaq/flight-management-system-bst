#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum RelationType { GREATER, LESS, EQUAL };

class ItemType
{
public:
    int id;
    string source, destination, airline;
    string departureTime, arrivalTime;
    string duration;        // stored as H:MM (example 1:45)
    float ticketPrice;
    string status;

    RelationType ComparedTo(ItemType item)
    {
        if (id > item.id)
            return GREATER;
        else if (id < item.id)
            return LESS;
        else
            return EQUAL;
    }

    void Print()
    {
        cout << "\nFlight ID: " << id;
        cout << "\nSource: " << source;
        cout << "\nDestination: " << destination;
        cout << "\nAirline: " << airline;
        cout << "\nDeparture Time: " << departureTime;
        cout << "\nArrival Time: " << arrivalTime;
        cout << "\nDuration: " << duration << " (H:MM)";
        cout << "\nTicket Price: " << ticketPrice;
        cout << "\nStatus: " << status;
        cout << "\n--------------------------";
    }
};

struct node
{
    ItemType data;
    node* left;
    node* right;
};

// FUNCTION TO MAKE TEXT LOWERCASE (used in airline search)

string ToLower(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        // capital letters A-Z are 32 less than small letters a-z
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = text[i] + 32;
    }

    return text;
}

// FUNCTION TO CALCULATE ETA
// ETA = departure time + duration (both given as hours and minutes)

string CalculateETA(string departure, string duration)
{
    int hour = (departure[0] - '0') * 10 +
        (departure[1] - '0');

    int minute = (departure[3] - '0') * 10 +
        (departure[4] - '0');

    // split duration like 1:45 into hours and minutes
    int colon = duration.find(':');

    int durHours = stoi(duration.substr(0, colon));
    int durMinutes = stoi(duration.substr(colon + 1));

    int total = hour * 60 + minute +
        durHours * 60 + durMinutes;

    hour = (total / 60) % 24;
    minute = total % 60;

    string result = "";

    if (hour < 10)
        result += "0";

    result += to_string(hour) + ":";

    if (minute < 10)
        result += "0";

    result += to_string(minute);

    return result;
}

class BST
{
public:

    node* root;

    BST()
    {
        root = NULL;
    }

    // INSERT FLIGHT

    void Insert(ItemType item)
    {
        node* newNode = new node;

        newNode->data = item;
        newNode->left = NULL;
        newNode->right = NULL;

        if (root == NULL)
        {
            root = newNode;
            cout << "\nFlight added successfully!";
            return;
        }

        node* temp = root;
        node* parent = NULL;

        while (temp != NULL)
        {
            parent = temp;

            if (item.ComparedTo(temp->data) == LESS)
                temp = temp->left;

            else if (item.ComparedTo(temp->data) == GREATER)
                temp = temp->right;

            else
            {
                cout << "\nFlight ID already exists!";
                delete newNode;
                return;
            }
        }

        if (item.ComparedTo(parent->data) == LESS)
            parent->left = newNode;
        else
            parent->right = newNode;

        cout << "\nFlight added successfully!";
    }

    // SEARCH FLIGHT

    node* Search(node* temp, int key)
    {
        if (temp == NULL || temp->data.id == key)
            return temp;

        if (key < temp->data.id)
            return Search(temp->left, key);

        return Search(temp->right, key);
    }

    void SearchFlight()
    {
        int id;

        cout << "\nEnter Flight ID: ";
        cin >> id;

        node* temp = Search(root, id);

        if (temp == NULL)
            cout << "\nFlight not found!";
        else
            temp->data.Print();
    }

    // DISPLAY FLIGHTS IN ASCENDING ORDER

    void Inorder(node* temp)
    {
        if (temp != NULL)
        {
            Inorder(temp->left);

            temp->data.Print();

            Inorder(temp->right);
        }
    }

    void Display()
    {
        if (root == NULL)
            cout << "\nNo flights available!";
        else
            Inorder(root);
    }

    // FIND MINIMUM NODE

    node* Minimum(node* temp)
    {
        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    // DELETE FLIGHT

    node* DeleteNode(node* temp, int key)
    {
        if (temp == NULL)
            return temp;

        if (key < temp->data.id)
            temp->left = DeleteNode(temp->left, key);

        else if (key > temp->data.id)
            temp->right = DeleteNode(temp->right, key);

        else
        {
            if (temp->left == NULL)
            {
                node* child = temp->right;
                delete temp;
                return child;
            }

            else if (temp->right == NULL)
            {
                node* child = temp->left;
                delete temp;
                return child;
            }

            node* child = Minimum(temp->right);

            temp->data = child->data;

            temp->right = DeleteNode(temp->right,
                child->data.id);
        }

        return temp;
    }

    void DeleteFlight()
    {
        int id;

        cout << "\nEnter Flight ID to delete: ";
        cin >> id;

        if (Search(root, id) == NULL)
            cout << "\nFlight not found!";
        else
        {
            root = DeleteNode(root, id);
            cout << "\nFlight deleted successfully!";
        }
    }

    // SHOW ETA OF ALL FLIGHTS

    void ShowETA(node* temp)
    {
        if (temp == NULL)
            return;

        ShowETA(temp->left);

        string eta = CalculateETA(temp->data.departureTime,
            temp->data.duration);

        cout << "\nFlight ID: " << temp->data.id;
        cout << "\nFlight Duration: " << temp->data.duration;
        cout << "\nCalculated ETA: " << eta;

        if (eta == temp->data.arrivalTime)
            cout << "\nStatus: On-Time";

        else if (eta < temp->data.arrivalTime)
            cout << "\nStatus: Early";

        else
            cout << "\nStatus: Delayed";

        cout << "\n--------------------------";

        ShowETA(temp->right);
    }

    // SURPRISE FEATURE: SEARCH BY AIRLINE

    void SearchAirline(node* temp, string name, int& count)
    {
        if (temp != NULL)
        {
            SearchAirline(temp->left, name, count);

            if (ToLower(temp->data.airline) == name)
            {
                temp->data.Print();
                count++;
            }

            SearchAirline(temp->right, name, count);
        }
    }

    void AirlineFeature()
    {
        string name;
        int count = 0;

        cout << "\nEnter Airline Name: ";
        cin.ignore();
        getline(cin, name);

        SearchAirline(root, ToLower(name), count);

        if (count == 0)
            cout << "\nNo flights found for this airline!";

        else
            cout << "\nTotal Flights Found: " << count;
    }

    // WRITE FLIGHTS INTO FILE (PREORDER: node, left, right)

    void WriteToFile(node* temp, ofstream& file)
    {
        if (temp != NULL)
        {
            file << temp->data.id << ","
                << temp->data.source << ","
                << temp->data.destination << ","
                << temp->data.airline << ","
                << temp->data.departureTime << ","
                << temp->data.arrivalTime << ","
                << temp->data.duration << ","
                << temp->data.ticketPrice << ","
                << temp->data.status << endl;

            WriteToFile(temp->left, file);

            WriteToFile(temp->right, file);
        }
    }

    // SAVE FLIGHTS TO FILE

    void SaveToFile()
    {
        ofstream file("flights.txt");

        if (!file)
        {
            cout << "\nFile could not be opened!";
            return;
        }

        WriteToFile(root, file);

        file.close();

        cout << "\nFlights saved successfully!";
    }

    // LOAD FLIGHTS FROM FILE

    void LoadFromFile()
    {
        ifstream file("flights.txt");

        if (!file)
        {
            cout << "\nFile not found!";
            return;
        }

        string idText, priceText;
        ItemType item;

        while (getline(file, idText, ','))
        {
            if (!getline(file, item.source, ','))
                break;

            if (!getline(file, item.destination, ','))
                break;

            if (!getline(file, item.airline, ','))
                break;

            if (!getline(file, item.departureTime, ','))
                break;

            if (!getline(file, item.arrivalTime, ','))
                break;

            if (!getline(file, item.duration, ','))
                break;

            if (!getline(file, priceText, ','))
                break;

            if (!getline(file, item.status))
                break;

            item.id = stoi(idText);
            item.ticketPrice = stof(priceText);

            Insert(item);
        }

        file.close();

        cout << "\nFile loaded successfully!";
    }
};

// MAIN FUNCTION

int main()
{
    BST tree;

    // LOAD FILE WHEN PROGRAM STARTS

    tree.LoadFromFile();

    int choice;

    do
    {
        cout << "\n\n========== FLIGHT MANAGEMENT SYSTEM ==========";
        cout << "\n1. Add New Flight";
        cout << "\n2. Search Flight by ID";
        cout << "\n3. Delete Flight by ID";
        cout << "\n4. Display All Flights (Ascending Flight ID)";
        cout << "\n5. Calculate Flight Duration and ETA";
        cout << "\n6. Surprise Feature";
        cout << "\n7. Save Flights to File";
        cout << "\n8. Load Flights from File";
        cout << "\n0. Exit";
        cout << "\n==============================================";

        cout << "\nEnter your choice: ";

        // if the user types a letter, clear the error
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        if (choice == 1)
        {
            ItemType item;

            cout << "\nEnter Flight ID: ";
            cin >> item.id;

            cin.ignore();

            cout << "Enter Source: ";
            getline(cin, item.source);

            cout << "Enter Destination: ";
            getline(cin, item.destination);

            cout << "Enter Airline: ";
            getline(cin, item.airline);

            cout << "Enter Departure Time (HH:MM): ";
            getline(cin, item.departureTime);

            cout << "Enter Arrival Time (HH:MM): ";
            getline(cin, item.arrivalTime);

            cout << "Enter Duration (H:MM, example 1:45): ";
            getline(cin, item.duration);

            cout << "Enter Ticket Price: ";
            cin >> item.ticketPrice;

            cin.ignore();

            cout << "Enter Status: ";
            getline(cin, item.status);

            tree.Insert(item);
        }

        else if (choice == 2)
            tree.SearchFlight();

        else if (choice == 3)
            tree.DeleteFlight();

        else if (choice == 4)
            tree.Display();

        else if (choice == 5)
        {
            if (tree.root == NULL)
                cout << "\nNo flights available!";
            else
                tree.ShowETA(tree.root);
        }

        else if (choice == 6)
            tree.AirlineFeature();

        else if (choice == 7)
            tree.SaveToFile();

        else if (choice == 8)
            tree.LoadFromFile();

        else if (choice == 0)
            cout << "\nExiting Program...";

        else
            cout << "\nInvalid Choice!";

    } while (choice != 0);

    return 0;
}