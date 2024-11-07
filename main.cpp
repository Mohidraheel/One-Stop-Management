#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <fstream>
int threshold = 10;
using namespace std;
using namespace std::chrono;
// tickets managements
class node
{
  string customer_name;
  int priority;
  string description;
  time_t creation_time;
  string status;
  time_t close_time;

public:
  node *next;
  int ticket_id;
  node()
  {
    ticket_id = 0;
    customer_name = "";
    priority = 0;
    description = "";
    creation_time = 0;
    status = "";
    close_time = 0;
    next = nullptr;
  }
  node(int t, string c, int p, string d)
  {
    ticket_id = t;
    customer_name = c;
    priority = p;
    description = d;
    creation_time = time(0) + 100;
    status = "open";
    close_time = 0;
    next = nullptr;
  }

  bool assigned()
  {
    if (status == "open" && status != "closed")
    {
      return true;
    }
    return false;
  }

  void closeticket()
  {
    status = "closed";
    close_time = time(0) + 10;
    cout << "Ticket Closed at:" << ctime(&close_time) << endl;
  }
  // 1 =high  2= medium and 3=low

  void display_ticket()
  {
    cout << "Ticket ID: " << ticket_id << endl;
    cout << "Customer Name: " << customer_name << endl;
    cout << "Priority: " << (priority == 1 ? "High" : priority == 2 ? "Medium"
                                                                    : "Low")
         << endl;
    cout << "Description: " << description << endl;
    cout << "Creation Time: " << ctime(&creation_time);
    if (status == "closed")
    {
      cout << "Close Time: " << ctime(&close_time);
    }
    cout << "Status: " << status << endl;
  }

  friend class linkedlist;
  friend class agentmanagement;
};
class myqueue
{
  // all the ids are here
  int *ticketid;
  int rear;
  int front;
  int size;
  int count;

public:
  myqueue()
  {
    this->size = 10;
    ticketid = new int[size];
    for (int i = 0; i < size; i++)
    {
      ticketid[i] = 0;
    }
    count = 0;
    rear = -1;
    front = -1;
  }
  bool isfull()
  {
    if (count < size)
    {
      return false;
    }
    return true;
  }
  void push(int id)
  {
    if (isfull())
    {
      return;
    }
    if (isempty())
    {
      front = 0;
    }

    rear = (rear + 1) % size;
    ticketid[rear] = id;
    count++;
  }
  bool isempty()
  {
    if (count == 0)
    {
      return true;
    }
    return false;
  }
  void pop()
  {
    if (isempty())
    {
      return;
    }
    front = (front + 1) % size;
    int x = ticketid[front];
    cout << "Ticket Removed:" << x << endl;
    count--;
  }
  void display()
  {
    if (isempty())
    {
      cout << "Queue is empty." << endl;
      return;
    }
    cout << "Tickets in Queue: ";
    for (int i = 0; i < count; i++)
    {
      cout << ticketid[(front + i) % 10] << " ";
    }
    cout << endl;
  }
  void addtoqueue(int id)
  {
    if (!isfull())
    {
      rear = (rear + 1) % size;
      ticketid[rear] = id;
      count++;
    }
  }
};

class linkedlist
{

public:
  node *head;
  int count = 0;
  linkedlist()
  {
    head = nullptr;
  }
  void addticket(int t, int p, string c, string d) // o(n)
  {
    node *newdata = new node(t, c, p, d);
    if (head == NULL)
    {
      newdata->next = head;
      head = newdata;
      count++;
      return;
    }
    node *temp = head;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    count++;
    temp->next = newdata;
    newdata->next = NULL;
  }

  void remove(int id) // o(n)
  {
    node *temp = head;
    node *prev = NULL;
    bool found = false;

    while (temp != NULL)
    {
      if (temp->ticket_id == id)
      {
        found = true;
        break;
      }
      prev = temp;
      temp = temp->next;
    }

    if (found)
    {
      temp->closeticket();

      if (prev == NULL)
      {
        head = temp->next;
      }
      else
      {
        prev->next = temp->next;
      }
      delete temp;
      count--;
    }
    else
    {
      cout << "Ticket ID not found." << endl;
    }
  }

  bool search(int id) // O(n)
  {
    node *temp = head;
    while (temp != NULL)
    {
      if (temp->ticket_id == id)
      {
        return true;
      }
      temp = temp->next;
    }
    return false;
  }

  void swap1(node *&current, node *&previous) // O(1)
  {
    node *nextptr = current->next;
    current->next = nextptr->next;
    nextptr->next = current;
    if (previous != NULL)
    {
      previous->next = nextptr;
    }
    else
    {
      head = nextptr;
    }
    previous = nextptr;
  }

  void sort(int choice) // o(n ^2)
  {

    bool swapped = false;
    if (choice == 1)
    {

      if (head == NULL || head->next == NULL)
      {
        return;
      }
      do
      {
        swapped = false;
        node *temp = head;
        node *prev = NULL;

        while (temp->next != NULL)
        {
          if (temp->priority > temp->next->priority)
          {
            swap1(temp, prev);
            swapped = true;
            // prev=temp->next;
          }
          else
          {
            prev = temp;
            temp = temp->next;
          }
        }

      } while (swapped);
    }
    else
    {
      if (choice == 2)
      {
        do
        {
          swapped = false;
          node *temp = head;
          node *prev = NULL;

          while (temp->next != NULL)
          {
            if (temp->customer_name > temp->next->customer_name)
            {
              swap1(temp, prev);
              swapped = true;
              // prev=temp->next;
            }
            else
            {
              prev = temp;
              temp = temp->next;
            }
          }

        } while (swapped);
      }
      else
      {
        do
        {
          swapped = false;
          node *temp = head;
          node *prev = NULL;

          while (temp->next != NULL)
          {
            if (temp->creation_time > temp->next->creation_time)
            {
              swap1(temp, prev);
              swapped = true;
              // prev=temp->next;
            }
            else
            {
              prev = temp;
              temp = temp->next;
            }
          }

        } while (swapped);
      }
    }
  }
  void swapdata(node *a, node *b) // O(1)
  {
    swap(a->ticket_id, b->ticket_id);
    swap(a->customer_name, b->customer_name);
    swap(a->priority, b->priority);
    swap(a->description, b->description);
    swap(a->creation_time, b->creation_time);
    swap(a->status, b->status);
    swap(a->close_time, b->close_time);
  }

  void selectionsort(int choice) // O(N^2)
  {
    node *temp = head;
    node *nextptr = NULL;
    node *min;
    for (; temp != NULL; temp = temp->next)
    {
      min = temp;
      for (nextptr = temp->next; nextptr != NULL; nextptr = nextptr->next)
      {
        if (choice == 1)
        {
          if (min->priority > nextptr->priority)
          {
            min = nextptr;
          }
        }
        else
        {
          if (choice == 3)
          {
            if (min->creation_time > nextptr->creation_time)
            {
              min = nextptr;
            }
          }
          else
          {
            if (choice == 2)
            {
              if (min->customer_name > nextptr->customer_name)
              {
                min = nextptr;
              }
            }
          }
        }
      }
      if (min != temp)
      {
        swapdata(temp, min);
      }
    }
  }
  void sortedd(node **sorted, node *current, int choice) // O(N)
  {
    node *temp = *sorted;

    if (choice == 1)
    {
      if ((*sorted == NULL) || ((*sorted)->priority > current->priority))
      {
        current->next = (*sorted);
        (*sorted) = current;
      }
      else
      {
        while (temp->next != NULL && temp->next->priority < current->priority)
        {
          temp = temp->next;
        }
        current->next = temp->next;
        temp->next = current;
      }
    }
    else if (choice == 2)
    {
      if ((*sorted == NULL) || ((*sorted)->customer_name > current->customer_name))
      {
        current->next = (*sorted);
        (*sorted) = current;
      }
      else
      {
        while (temp->next != NULL && temp->next->customer_name < current->customer_name)
        {
          temp = temp->next;
        }
        current->next = temp->next;
        temp->next = current;
      }
    }
    else if (choice == 3)
    {
      if ((*sorted == NULL) || ((*sorted)->creation_time > current->creation_time))
      {
        current->next = (*sorted);
        (*sorted) = current;
      }
      else
      {
        while (temp->next != NULL && temp->next->creation_time < current->creation_time)
        {
          temp = temp->next;
        }
        current->next = temp->next;
        temp->next = current;
      }
    }
  }

  void insertion(int choice) // O(N^2)
  {
    if (head == NULL || head->next == NULL)
    {
      return;
    }
    node *current = head;
    node *sorted = NULL;

    while (current != NULL)
    {
      node *nextNode = current->next;
      sortedd(&sorted, current, choice);
      current = nextNode;
    }

    head = sorted;
  }

  void split(node *source, node **front, node **back) // O(N)
  {
    node *fast;
    node *slow;
    fast = source->next;
    slow = source;
    while (fast != NULL && fast->next != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
  }

  node *merge(node *a, node *b, int choice) // O(N)
  {
    node *result = NULL;
    if (a == NULL)
    {
      return b;
    }
    else
    {
      if (b == NULL)
      {
        return a;
      }
    }

    if (choice == 1)
    {
      if (a->priority < b->priority)
      {
        result = a;
        result->next = merge(a->next, b, choice);
      }
      else
      {
        result = b;
        result->next = merge(a, b->next, choice);
      }
    }
    else
    {
      if (choice == 2)
      {
        if (a->customer_name < b->customer_name)
        {
          result = a;
          result->next = merge(a->next, b, choice);
        }
        else
        {
          result = b;
          result->next = merge(a, b->next, choice);
        }
      }
      else
      {
        if (choice == 3)
        {
          if (a->creation_time <= b->creation_time)
          {
            result = a;
            result->next = merge(a->next, b, choice);
          }
          else
          {
            result = b;
            result->next = merge(a, b->next, choice);
          }
        }
      }
    }
    return result;
  }

  void mergesort(node **temp, int choice) // O(NLOG N)
  {
    if (*temp == NULL || (*temp)->next == NULL)
    {
      return;
    }
    node *current = *temp;

    node *a;
    node *b;

    split(current, &a, &b);

    mergesort(&a, choice);
    mergesort(&b, choice);

    *temp = merge(a, b, choice);
  }
  node *partition(node *start, node *end, int choice) // O(N)
  {
    node *pivot = end;
    node *pIndex = start;

    for (node *current = start; current != end; current = current->next)
    {
      bool condition = false;

      // Adjust the condition based on sorting choice
      if (choice == 1)
      { // Sort by priority
        condition = current->priority < pivot->priority;
      }
      else if (choice == 2)
      { // Sort by customer name
        condition = current->customer_name < pivot->customer_name;
      }
      else if (choice == 3)
      { // Sort by creation time
        condition = current->creation_time < pivot->creation_time;
      }

      if (condition)
      {
        swapdata(pIndex, current);
        pIndex = pIndex->next;
      }
    }
    swapdata(pIndex, end); // Finally, swap the pivot to its correct position
    return pIndex;
  }

  void quicksort(node *start, node *end, int choice) // O(N^2)
  {
    if (!start || start == end || start == end->next)
    {
      return; // Base case: stop recursion
    }

    // Partition the list and get the pivot node
    node *pIndex = partition(start, end, choice);

    // Recurse for the left and right sub-lists
    if (pIndex != start)
    {
      // Find the node before pIndex to recurse on the left part
      node *temp = start;
      while (temp->next != pIndex)
      {
        temp = temp->next;
      }
      quicksort(start, temp, choice); // Left part
    }

    quicksort(pIndex->next, end, choice); // Right part
  }

  void sort1(int choice) // O(N^2)
  {
    node *end = head;
    while (end && end->next)
    {
      end = end->next;
    }
    quicksort(head, end, choice);
  }
  // Partition for quicksort

  void display() // O(N)
  {
    node *temp = head;

    while (temp != NULL)
    {
      temp->display_ticket();
      temp = temp->next;
      cout << endl;
    }
    cout << endl;
  }
};

class agent
{
  string name;
  int id;
  int assignedtickets[5]; // assume max 5
  int ticketcount;
  bool available;

public:
  agent()
  {
    name = "";
    id = 0;
    ticketcount = 0;
    available = true;
    for (int j = 0; j < 5; j++)
    {

      assignedtickets[j] = -1;
    }
  }
  agent(string n, int i)
  {
    name = n;
    id = i;
    ticketcount = 0;
    available = true;
    for (int j = 0; j < 5; j++)
    {
      assignedtickets[j] = -1;
    }
  }
  void assignedticket1(int ticket_id) // O(1)
  {
    if (ticketcount < 5)
    {
      assignedtickets[ticketcount++] = ticket_id;
      // Check if the agent has reached their maximum ticket count
      if (ticketcount == 5)
      {
        available = false;
      }
    }
    else
    {
      available = false;
    }
  }
  bool isTicketAssigned(int ticket_id) // O(5)
  {
    for (int i = 0; i < ticketcount; i++)
    {
      if (assignedtickets[i] == ticket_id)
      {
        return true; // The ticket is already assigned to this agent
      }
    }
    return false;
  }

  void removetickets(int ticket_id) // O(5)
  {
    for (int i = 0; i < ticketcount; i++)
    {
      if (assignedtickets[i] == ticket_id)
      {
        assignedtickets[i] = assignedtickets[ticketcount - 1];
        assignedtickets[--ticketcount] = -1;
        // If there are fewer than 5 tickets assigned, mark the agent as available
        if (ticketcount < 5)
        {
          available = true;
        }
        break;
      }
    }
  }

  void display() // O(5)
  {
    cout << "Agent ID: " << id
         << ", Name: " << name
         << ", Availability: " << (available ? "Available" : "Unavailable")
         << ", Assigned Tickets: ";
    for (int i = 0; i < ticketcount; ++i)
    {
      cout << assignedtickets[i] << " ";

      cout << endl;
    }
  }
  friend class agentmanagement;
};

class mystack
{
  int *data;
  int top;
  int size;

public:
  mystack()
  {
    this->size = 10;
    data = new int[size];
    for (int i = 0; i < size; i++)
    {
      data[i] = 0;
    }
    top = -1;
  }

  int peek() // O(1)
  {
    return data[top];
  }
  bool isfull() // O(1)
  {
    if (top == size - 1)
    {
      return true;
    }
    return false;
  }

  void push(int d) // O(1)
  {
    if (!isfull())
    {
      data[++top] = d;
    }
  }

  bool empty() // O(1)
  {
    if (top == -1)
    {
      return true;
    }
    return false;
  }

  void pop() // O(1)
  {
    if (!empty())
    {
      top--;
    }
    return;
  }

  ~mystack()
  {
    delete[] data; // Free allocated memory
  }
};

class resolutionlog
{

  struct LogNode
  {
    int ticketID;
    string resolutionInfo;
    LogNode *next;

    LogNode(int id, const string &info) : ticketID(id), resolutionInfo(info), next(nullptr) {}
  };
  LogNode *top;

public:
  resolutionlog()
  {

    top = nullptr;
  }

  ~resolutionlog()
  {
  }

  void closedlog(int id, string &name) // O(1)
  {
    LogNode *newNode = new LogNode(id, name);
    newNode->next = top;
    top = newNode;
  }

  void viewlog() // O(N)
  {
    LogNode *current = top;
    cout << "\nTicket Resolution Log (Most recent first):\n";
    while (current)
    {
      cout << "Ticket ID: " << current->ticketID << ", Resolution: " << current->resolutionInfo << endl;
      current = current->next;
    }
  }
};

class agentmanagement
{
  resolutionlog *l1;
  agent *agents;
  int size;
  int capacity;
  linkedlist *tm;
  myqueue *mq;
  agent *selected;
  node *n;

public:
  agentmanagement(int s, linkedlist *t, resolutionlog *r1, myqueue *q1)
  {
    size = s;
    tm = t;
    agents = new agent[size];
    capacity = 0;
    l1 = r1;
    mq = q1;
  }

  void addagent(string n, int id) // O(1)
  {
    if (capacity < size)
    {
      agents[capacity++] = agent(n, id);
    }
    else
    {
      cout << "Agent array is full!" << endl;
    }
  }

  void addticket(myqueue &q1) // O(N *M )
  {
    node *t = NULL;
    node *temp = tm->head;

    // Find the ticket with the highest priority (lowest number is highest priority)
    while (temp != NULL)
    {
      if (temp->status == "open")
      {
        if (t == NULL || temp->priority < t->priority)
        {
          t = temp; // Select ticket with highest priority
        }
      }
      temp = temp->next;
    }

    if (t == nullptr)
    {
      cout << "No open tickets available for assignment." << endl;
      return;
    }

    int min = 6;
    selected = NULL;

    // Reset selected agent to avoid assigning the same ticket multiple times
    for (int i = 0; i < capacity; i++)
    {
      // Select the agent who is available and has the least assigned tickets
      if (agents[i].available == true && agents[i].ticketcount < min)
      {
        min = agents[i].ticketcount;
        selected = &agents[i];
      }
    }

    if (selected == nullptr)
    {
      cout << "No available agents to assign ticket " << t->ticket_id << endl;
      return;
    }

    // Assign the ticket to the selected agent
    selected->assignedticket1(t->ticket_id);

    // Ensure that once the ticket is assigned, it is not available for other agents
    t->status = "assigned";
    // Mark ticket status as assigned
    q1.pop();
    cout << "Ticket " << t->ticket_id << " assigned to Agent " << selected->name << endl;
    cout << endl;
  }

  void closeticket(int ticket_id) // O(N+M)
  {
    node *t = NULL;
    node *temp = tm->head;

    // Find the ticket by ticket_id and check if it's still open
    while (temp != NULL)
    {
      if (temp->ticket_id == ticket_id)
      {
        if (temp->status == "assigned")
        {
          t = temp;
          break;
        }
        else
        {
          cout << endl;
          cout << "Ticket " << ticket_id << " is already closed!" << endl;
          return;
        }
      }
      temp = temp->next;
    }

    if (t == NULL)
    {
      cout << "Ticket " << ticket_id << " not found!" << endl;
      return;
    }

    // Remove the ticket from the assigned agent
    l1->closedlog(t->ticket_id, t->customer_name); // Log the ticket closure
    t->closeticket();
    for (int i = 0; i < capacity; i++)
    {
      if (agents[i].isTicketAssigned(ticket_id))
      {
        agents[i].removetickets(ticket_id);
        break;
      }
    }

    cout << "Ticket " << t->ticket_id << " has been closed." << endl;
  }

  ~agentmanagement()
  {
    delete[] agents;
  }

  void displayAgents() // O(M)
  {
    for (int i = 0; i < capacity; ++i)
    {
      agents[i].display();
      cout << endl;
    }
  }
};

void fetchConfig()
{
  cout << "*** Configuration ***" << endl;
  cout << endl;
  ifstream inputFile("config.txt");
  string l1;
  string l2;
  int sorting;
  int searching;

  if (inputFile.is_open())
  {
    if (getline(inputFile, l1))
    {
      cout << "Your Sorting Choice: " << l1 << endl;
      if (l1 == "Bubble Sort")
      {
        sorting = 1;
      }
      else if (l1 == "Insertion Sort")
      {
        sorting = 2;
      }
      else if (l1 == "Selection Sort")
      {
        sorting = 3;
      }
      else if (l1 == "Quick Sort")
      {
        sorting = 4;
      }
      else if (l1 == "Merge Sort")
      {
        sorting = 5;
      }
      else
      {
        cout << endl;
        cout << "Invalid sorting choice" << endl;
        cout << "Setting sorting to Bubble Sort as Default" << endl;
        cout << endl;
        sorting = 1;
      }
    }
    cout << endl;
    if (getline(inputFile, l2))
    {
      cout << "Your Searching Choice: " << l2 << endl;
      if (l2 == "Linear Search")
      {
        searching = 1;
      }
      else
      {
        cout << endl;
        cout << "Invalid searching choice" << endl;
        cout << "Setting searching to Binary Search as Default" << endl;
        searching = 1;
        cout << endl;
      }
    }
    inputFile.close();
  }
  else
  {
    cout << "Unable to open the file" << endl;
    cout << "Setting searching to Linear Search as Default" << endl;
    searching = 1;
    cout << "Setting sorting to Bubble Sort as Default" << endl;
    sorting = 1;
  }
  cout << endl;
}

class commandline
{
public:
  void start()
  {

    int num = 0;

    myqueue q1;
    linkedlist ll;
    char ans;
    int id = 15;
    int priority;
    string name;
    string queury;

    do
    {
      cout << endl;
      cout << "Do you want to add a ticket (Y/N): ";
      cin >> ans;

      // If the user enters 'n', exit the loop
      if (ans == 'n' || ans == 'N')
        break;

      // Increment ID and take input
      id++;

      cout << "Enter Customer Name: ";
      cin.ignore();
      getline(cin, name);

      cout << "Enter Priority (1 = High, 2 = Medium, 3 = Low): ";
      cin >> priority;

      cout << "Enter Query: ";
      cin.ignore();
      getline(cin, queury); // Use 'queury' instead of 'name'

      // Add ticket and push ID to queue
      ll.addticket(id, priority, name, queury);
      cout << id;
      q1.push(id);
      num++;

    } while (true);

    int choice;
    // higher the priority the data will be first
    cout << "Enter Your Choice You want to sort the data:" << endl;
    cout << "1-Priority" << endl;
    cout << "2-Name" << endl;
    cout << "3-Creation-Time" << endl;
    cin >> choice;
    int choice2;

    if (ll.count < 10)
    {
      cout << "You Have 3 choices for sorting:bubble,selection and insertion" << endl;
      cout << "1-Bubblesort" << endl;
      cout << "2-Insertionsort" << endl;
      cout << "3-Selectionsort" << endl;
      cin >> choice2;

      switch (choice2)
      {
      case 1:
        ll.sort(choice);
        break;

      case 3:
        ll.selectionsort(choice);
        break;

      case 2:
        ll.insertion(choice);
        break;

      default:
        cout << "Invalid choice" << endl;
        break;
      }
    }
    else
    {

      cout << "1-MergeSort" << endl;
      cout << "2-Quicksort" << endl;
      cin >> choice2;
      switch (choice2)
      {
      case 1:
        ll.mergesort(&ll.head, choice);
        break;

      case 2:
        ll.sort1(choice);
        break;

      default:
        break;
      }
    }
    cout << endl;
    ll.display();

    system("cls");
    int sid;
    cout << "Enter id you want to search:";
    cin >> sid;
    if (ll.search(sid))
    {
      cout << "Data Found" << endl;
    }
    else
    {
      cout << "Data Not Found" << endl;
      cout << "______________" << endl;
    }

    resolutionlog r1;
    agentmanagement a(10, &ll, &r1, &q1);

    a.addagent("Sarah", 101);
    a.addagent("Miraan", 102);
    while (num != 0)
    {
      a.addticket(q1);
      num--;
    }
    a.displayAgents();
    a.closeticket(16);
    r1.viewlog();
  }
};

int main()
{

  cout << "23K-3000-Mohid Raheel Khan" << endl;
  cout << endl;
  cout << "\033[1;34m" << "\t\t==========================================" << "\033[0m" << endl;
  cout << "\033[1;32m" << "\t\t\033[4m" << "            Welcome to the            " << "\033[0m" << endl;
  cout << "\033[1;31m" << "\t\t        One-Stop Management System        " << "\033[0m" << endl;
  cout << "\033[1;34m" << "\t\t==========================================" << "\033[0m" << endl;


  cout << "\033[1;36m" << "\t\t     Manage your tickets efficiently!" << "\033[0m" << endl;
  cout << "\033[1;34m" << "\t\t==========================================" <<endl;
  cout << "\033[0m";
  commandline c1;
  c1.start();

  return 0;
}
