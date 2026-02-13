/*
 * DSA Project: EE Calculator
 * VERSION: Final Rainbow Edition (Full Color UI)
 * FEATURES: 
 * - Distinct Color Themes for Every Module
 * - Vertical ANSI Schematics
 * - Dynamic Circuit Simulator
 * - Full Base Conversion
 * COMPATIBILITY: Dev-C++ Safe (Windows 11)
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cctype> 

using namespace std;

// ==========================================
// COLOR CODES (ANSI)
// ==========================================
#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"       

// ==========================================
// HELPERS
// ==========================================

template <typename T>
string numToStr(T val) {
    stringstream ss;
    ss << val;
    return ss.str();
}

int strToNum(string str) {
    int x;
    stringstream ss(str);
    ss >> x;
    return x;
}

// ==========================================
// DATA STRUCTURES
// ==========================================

struct Node {
    string data;
    int value; 
    Node* next;
    Node* prev; 

    Node(string d, int v = 0) : data(d), value(v), next(NULL), prev(NULL) {}
};

struct TreeNode {
    string key; 
    double value;
    TreeNode *left, *right;

    TreeNode(string k, double v) : key(k), value(v), left(NULL), right(NULL) {}
};

// --- 1. Stack ---
class Stack {
private:
    Node* top;
public:
    Stack() : top(NULL) {}
    
    void push(int val) { 
        Node* newNode = new Node(numToStr(val), val);
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (!top) return -1;
        int val = top->value;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    bool isEmpty() { return top == NULL; }
};

// --- 2. Singly Linked List ---
class SinglyLinkedList {
public:
    Node* head;
    SinglyLinkedList() : head(NULL) {}

    void insert(string group) {
        Node* newNode = new Node(group);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// --- 3. Doubly Linked List ---
class DoublyLinkedList {
public:
    Node* head;
    Node* tail;
    
    DoublyLinkedList() : head(NULL), tail(NULL) {}

    void append(string op, int result) {
        Node* newNode = new Node(op, result);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    vector<pair<string, int> > toVector() {
        vector<pair<string, int> > v;
        Node* temp = head;
        while (temp) {
            v.push_back(make_pair(temp->data, temp->value));
            temp = temp->next;
        }
        return v;
    }
};

// --- 4. Circular Linked List ---
class CircularLinkedList {
    Node* head;
public:
    CircularLinkedList() : head(NULL) {}

    void addLog(string log) {
        Node* newNode = new Node(log);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
            newNode->next = head;
        }
    }
};

// --- 5. Binary Search Tree (BST) ---
class BST {
    TreeNode* root;
    
    TreeNode* insert(TreeNode* node, string key, double val) {
        if (!node) return new TreeNode(key, val);
        if (key < node->key) node->left = insert(node->left, key, val);
        else if (key > node->key) node->right = insert(node->right, key, val);
        return node;
    }

    TreeNode* search(TreeNode* node, string key) {
        if (!node || node->key == key) return node;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

public:
    BST() : root(NULL) {}
    void addVariable(string key, double val) { root = insert(root, key, val); }
    double getVariable(string key) {
        TreeNode* res = search(root, key);
        if (res) return res->value;
        cout << "Var not found!" << endl;
        return 0.0;
    }
};

// --- 6. Graph (ANSI Schematics) ---
class Graph {
    int V;
    vector<vector<int> > adj; 
    vector<string> nodeTypes; 

    // Helper to print BIG ASCII Art
    void printGateBlock(string type) {
        if (type == "AND") {
            cout << "      |``````\\\n";
            cout << "      | AND   ) \n";
            cout << "      |......'  \n";
        }
        else if (type == "OR") {
            cout << "      \\``````\\\n";
            cout << "       )  OR  ) \n";
            cout << "      /....../  \n";
        }
        else if (type == "NOT") {
            cout << "      |\\````|\n";
            cout << "      | NOT >o\n";
            cout << "      |/....| \n";
        }
        else if (type == "NAND") {
            cout << "      |``````\\\n";
            cout << "      | NAND  )o\n";
            cout << "      |......'  \n";
        }
        else if (type == "NOR") {
            cout << "      \\``````\\\n";
            cout << "       ) NOR  )o\n";
            cout << "      /....../  \n";
        }
        else if (type == "XOR") {
            cout << "      ))`````\\\n";
            cout << "      )) XOR  )\n";
            cout << "      ))...../ \n";
        }
        else if (type.find("In_") != string::npos) {
            cout << "   [" << type << "]\n";
        }
    }

public:
    Graph(int V) : V(V) {
        adj.resize(V);
        nodeTypes.resize(V);
    }

    void setNodeType(int i, string type) { nodeTypes[i] = type; }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v); 
    }

    void traceCircuit() {
        vector<bool> visited(V, false);
        vector<int> q; 
        q.push_back(0); 
        visited[0] = true;

        cout << "\n    === LARGE ANSI SCHEMATIC (Vertical Flow) ===\n\n";
        
        int head = 0;
        while(head < q.size()){
            int u = q[head++];
            
            // Print the Component
            printGateBlock(nodeTypes[u]);
            
            // Check for connections
            bool hasNeighbors = false;
            for(size_t i = 0; i < adj[u].size(); i++){
                int v = adj[u][i];
                if(!visited[v]){
                    visited[v] = true;
                    q.push_back(v);
                    hasNeighbors = true;
                }
            }
            
            // Print Wires going DOWN
            if(hasNeighbors) {
                cout << "          ||\n";
                cout << "          ||\n";
                cout << "          \\/\n";
            } else if (u != V-1) {
                 cout << "          ||\n";
                 cout << "          \\/ (combines with next)\n";
            }
        }
        cout << "\n    [ FINAL OUTPUT ]\n";
        cout << "-------------------------------------\n";
    }
};

// --- 7. Hashing ---
class HashTable {
    static const int SIZE = 20; 
    struct HashNode {
        string key;
        string desc;
        HashNode* next;
    };
    HashNode* table[SIZE];

    int hashFunc(string key) {
        int sum = 0;
        for(size_t i = 0; i < key.length(); i++) sum += key[i];
        return sum % SIZE;
    }

public:
    HashTable() {
        for(int i=0; i<SIZE; i++) table[i] = NULL;
    }

    void insert(string key, string desc) {
        int idx = hashFunc(key);
        HashNode* newNode = new HashNode;
        newNode->key = key;
        newNode->desc = desc;
        newNode->next = table[idx];
        table[idx] = newNode;
    }

    string get(string key) {
        int idx = hashFunc(key);
        HashNode* temp = table[idx];
        while(temp) {
            if(temp->key == key) return temp->desc;
            temp = temp->next;
        }
        return "Unknown Option";
    }
};

// ==========================================
// SORTING ALGORITHMS
// ==========================================

class SortingAlgorithms {
public:
    static void bubbleSort(vector<pair<string, int> >& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - i - 1; j++)
                if (arr[j].second > arr[j + 1].second)
                    swap(arr[j], arr[j + 1]);
    }

    static void insertionSort(vector<pair<string, int> >& arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            pair<string, int> key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j].second > key.second) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    static void merge(vector<pair<string, int> >& arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        vector<pair<string, int> > L(n1), R(n2);
        for (int i = 0; i < n1; i++) L[i] = arr[l + i];
        for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i].second <= R[j].second) arr[k++] = L[i++];
            else arr[k++] = R[j++];
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    static void mergeSort(vector<pair<string, int> >& arr, int l, int r) {
        if (l >= r) return;
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }

    static void heapify(vector<pair<string, int> >& arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[l].second > arr[largest].second) largest = l;
        if (r < n && arr[r].second > arr[largest].second) largest = r;
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    static void heapSort(vector<pair<string, int> >& arr) {
        int n = arr.size();
        for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
};

// ==========================================
// CALCULATOR LOGIC
// ==========================================

class Calculator {
    Stack conversionStack;
    DoublyLinkedList history;
    CircularLinkedList sessionLog;
    BST variableStore;
    HashTable commandHelp;

public:
    Calculator() {
        commandHelp.insert("1", "Arithmetic: Performs +, -, *, / on two decimal inputs.");
        commandHelp.insert("2", "Base Conversion: Converts between Bin, Oct, and Dec.");
        commandHelp.insert("3", "BCD: Splits long binary strings into 4-bit nodes.");
        commandHelp.insert("4", "Truth Tables: Shows full logic tables for AND, OR, NAND, NOT.");
        commandHelp.insert("5", "Variables: Stores/Retrieves values using a BST.");
        commandHelp.insert("6", "Circuit Model: Builds a custom circuit and Truth Table.");
        commandHelp.insert("7", "Sort History: Sorts past results using 4 algorithms.");
    }

    // --- 1. Arithmetic (CYAN) ---
    void arithmetic() {
        double a, b;
        char op;
        cout << CYAN << "Enter expression (e.g., 5 + 3): " << RESET;
        cin >> a >> op >> b;
        double res = 0;
        if (op == '+') res = a + b;
        else if (op == '-') res = a - b;
        else if (op == '*') res = a * b;
        else if (op == '/') res = (b != 0) ? a / b : 0;
        
        cout << CYAN << "\n Result Table \n";
        cout << " Input A | Op | Input B | Result \n";
        cout << "---------|----|---------|--------\n";
        cout << " " << setw(7) << a << " | " << op << "  | " << setw(7) << b << " | " << res << endl << RESET;
        
        history.append(numToStr(a) + op + numToStr(b), (int)res);
        sessionLog.addLog("Arith");
    }

    // --- 2. Base Conversion (YELLOW) ---
    int toDecimal(string valStr, int base) {
        int power = 1;
        int num = 0;
        for (int i = valStr.length() - 1; i >= 0; i--) {
            int digit = valStr[i] - '0';
            num += digit * power;
            power = power * base;
        }
        return num;
    }

    string fromDecimal(int dec, int base) {
        if (dec == 0) return "0";
        Stack s;
        while (dec > 0) {
            s.push(dec % base);
            dec /= base;
        }
        string res = "";
        while (!s.isEmpty()) {
            res += numToStr(s.pop());
        }
        return res;
    }

    void baseConversion() {
        cout << YELLOW << "\n--- Base Conversion ---\n";
        cout << "1. Decimal -> Binary\n";
        cout << "2. Decimal -> Octal\n";
        cout << "3. Binary -> Decimal\n";
        cout << "4. Binary -> Octal\n";
        cout << "5. Octal -> Decimal\n";
        cout << "6. Octal -> Binary\n";
        cout << "Select mode: " << RESET;
        int mode;
        cin >> mode;

        string inputStr;
        cout << YELLOW << "Enter Value: " << RESET;
        cin >> inputStr;

        string result = "";
        
        switch(mode) {
            case 1: result = fromDecimal(strToNum(inputStr), 2); break;
            case 2: result = fromDecimal(strToNum(inputStr), 8); break;
            case 3: result = numToStr(toDecimal(inputStr, 2)); break;
            case 4: result = fromDecimal(toDecimal(inputStr, 2), 8); break;
            case 5: result = numToStr(toDecimal(inputStr, 8)); break;
            case 6: result = fromDecimal(toDecimal(inputStr, 8), 2); break;
            default: cout << "Invalid mode."; return;
        }

        cout << YELLOW << "\n Conversion Result \n";
        cout << " Input      | Mode  | Output \n";
        cout << "------------|-------|--------\n";
        cout << " " << setw(10) << inputStr << " | " << mode << "     | " << result << endl << RESET;

        history.append("BaseConv", strToNum(result));
    }

    // --- 3. BCD Conversion (MAGENTA) ---
    void bcdConversion() {
        string bin;
        cout << MAGENTA << "Enter Binary String (length multiple of 4): " << RESET;
        cin >> bin;
        SinglyLinkedList bcdList;
        for(size_t i=0; i<bin.length(); i+=4) {
            string group = bin.substr(i, 4);
            bcdList.insert(group);
        }
        cout << MAGENTA << "BCD Groups stored in Linked List: ";
        bcdList.display();
        cout << RESET;
    }

    // --- 4. Truth Table (GREEN) ---
    void generateTruthTable() {
        cout << GREEN << "\n--- Logic Truth Table ---\n";
        cout << "Select Gate: 1.AND  2.OR  3.NAND  4.NOT\n> " << RESET;
        int gate; cin >> gate;

        int inputs[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
        
        cout << GREEN << "\n Truth Table Result \n";
        if(gate == 4) { // NOT
            cout << " Input | Output \n";
            cout << "-------|--------\n";
            cout << " 0     | 1      \n";
            cout << " 1     | 0      \n";
        } else {
            cout << " A | B | Output \n";
            cout << "---|---|--------\n";
            for(int i=0; i<4; i++) {
                int out = 0;
                if (gate == 1) out = inputs[i][0] & inputs[i][1];
                else if (gate == 2) out = inputs[i][0] | inputs[i][1];
                else if (gate == 3) out = !(inputs[i][0] & inputs[i][1]);
                cout << " " << inputs[i][0] << " | " << inputs[i][1] << " |   " << out << endl;
            }
        }
        cout << RESET;
    }

    // --- 5. Variable Manager (BLUE) ---
    void variableManager() {
        string name;
        double val;
        cout << BLUE << "Enter Variable Name: " << RESET; cin >> name;
        cout << BLUE << "Enter Value: " << RESET; cin >> val;
        variableStore.addVariable(name, val);
        cout << BLUE << "Saved. Retrieve " << name << ": " << variableStore.getVariable(name) << endl << RESET;
    }

    // --- 6. Circuit Model (RED) ---
    int evalGate(int a, int b, string type) {
        if(type == "AND") return a & b;
        if(type == "OR") return a | b;
        if(type == "NAND") return !(a & b);
        if(type == "NOR") return !(a | b);
        if(type == "XOR") return a ^ b;
        return 0;
    }

    void showCircuit() {
        int numInputs;
        cout << RED << "\n--- Dynamic Circuit Builder ---\n";
        cout << "How many input variables? (e.g., 3 for A, B, C): " << RESET;
        cin >> numInputs;

        if (numInputs < 2) {
            cout << RED << "Need at least 2 inputs for a circuit.\n" << RESET;
            return;
        }

        int numGates = numInputs - 1; 
        vector<string> gateTypes(numGates);
        
        cout << RED << "We need " << numGates << " gates to combine these inputs.\n";
        cout << "Available Gates: AND, OR, NAND, NOR, XOR, NOT\n" << RESET;

        Graph circuit(numInputs + numGates); 
        
        for(int i=0; i<numGates; i++) {
            cout << RED << "Select Logic for Gate " << (i+1) << ": " << RESET;
            cin >> gateTypes[i];
            // Uppercase conversion
            for (size_t k = 0; k < gateTypes[i].length(); ++k)
                gateTypes[i][k] = toupper(gateTypes[i][k]);
        }

        // Build Schematic
        for(int i=0; i<numInputs; i++) {
            string name = "In_";
            name += (char)('A' + i);
            circuit.setNodeType(i, name);
        }
        
        // Input A -> Gate 1
        circuit.setNodeType(numInputs, gateTypes[0]);
        circuit.addEdge(0, numInputs); 
        circuit.addEdge(1, numInputs);

        for(int i=1; i<numGates; i++) {
             circuit.setNodeType(numInputs + i, gateTypes[i]);
             circuit.addEdge(numInputs + i - 1, numInputs + i);
             circuit.addEdge(i + 1, numInputs + i);
        }
        
        cout << RED;
        circuit.traceCircuit();
        cout << RESET;

        // Generate Custom Truth Table
        cout << RED << "\n--- Calculated Truth Table ---\n";
        
        for(int i=0; i<numInputs; i++) {
            cout << " " << (char)('A'+i) << " |";
        }
        cout << " Final Output\n";
        
        for(int i=0; i<numInputs; i++) cout << "---|";
        cout << "--------------\n";

        int totalRows = pow(2, numInputs);
        
        for(int i=0; i<totalRows; i++) {
            vector<int> currentInputs(numInputs);
            int temp = i;
            for(int j=numInputs-1; j>=0; j--) {
                currentInputs[j] = temp % 2;
                temp /= 2;
            }

            for(int j=0; j<numInputs; j++) {
                cout << " " << currentInputs[j] << " |";
            }

            int currentVal = currentInputs[0];
            for(int k=0; k<numGates; k++) {
                currentVal = evalGate(currentVal, currentInputs[k+1], gateTypes[k]);
                if(currentVal != 0) currentVal = 1; 
            }

            cout << "      " << currentVal << endl;
        }
        cout << RESET;
    }

    // --- 7. Sorting (BOLD WHITE) ---
    void sortHistory() {
        vector<pair<string, int> > vec = history.toVector();
        if(vec.empty()) { cout << WHITE << "No history to sort.\n" << RESET; return; }

        cout << WHITE << BOLD << "Choose Sort: 1.Bubble 2.Insert 3.Merge 4.Heap\n> " << RESET;
        int choice; cin >> choice;

        if (choice == 1) SortingAlgorithms::bubbleSort(vec);else if (choice == 2) SortingAlgorithms::insertionSort(vec);
        else if (choice == 3) SortingAlgorithms::mergeSort(vec, 0, vec.size()-1);
        else if (choice == 4) SortingAlgorithms::heapSort(vec);

        cout << WHITE << BOLD << "\n Sorted History (by Result) \n";
        cout << " Operation          | Result \n";
        cout << "--------------------|--------\n";
        for(size_t i = 0; i < vec.size(); ++i) {
            cout << " " << setw(18) << left << vec[i].first << " | " << vec[i].second << endl;
        }
        cout << RESET;
    }
    
    // --- 8. Help (YELLOW) ---
    void help() {
        string cmd;
        cout << YELLOW << "\nEnter Module Number (1-7) to get help: " << RESET;
        cin >> cmd;
        cout << YELLOW << "\n[Module " << cmd << "]: " << commandHelp.get(cmd) << endl << RESET;
    }
};

// ==========================================
// MAIN
// ==========================================

int main() {
    // ----------------------------------------------------
    // ASCII ART HEADER (With Colors)
    // ----------------------------------------------------
    cout << CYAN << "*********************************************************************************************************" << RESET << endl;
    cout << CYAN << "* " << YELLOW << "****** ****** ****** * * * *    *******" << CYAN << " *" << endl;
    cout << CYAN << "* " << YELLOW << "*      *      *      *   * *    *      " << CYAN << " *" << endl;
    cout << CYAN << "* " << YELLOW << "*****  ****** *      * * * *    *      " << CYAN << " *" << endl;
    cout << CYAN << "* " << YELLOW << "*      *      *      *   * *    *      " << CYAN << " *" << endl;
    cout << CYAN << "* " << YELLOW << "****** ****** ****** *   * ***** ****** " << CYAN << "*" << endl;
    cout << CYAN << "*********************************************************************************************************" << RESET << endl;
    cout << GREEN << "                                  E L E C T R I C A L   E N G I N E E R I N G                             " << RESET << endl;
    
    Calculator calc;
    int choice;

    do {
        cout << "\n=== DSA PROJECT CALCULATOR ===\n";
        cout << CYAN << "1. Arithmetic (+,-,*,/)\n" << RESET;
        cout << YELLOW << "2. Base Conversion (Bin/Oct/Dec)\n" << RESET;
        cout << MAGENTA << "3. BCD Grouping (Singly LL)\n" << RESET;
        cout << GREEN << "4. Logic Truth Table (Single Gate)\n" << RESET;
        cout << BLUE << "5. Manage Variables (BST)\n" << RESET;
        cout << RED << "6. Circuit Model (Dynamic + Custom Truth Table)\n" << RESET;
        cout << WHITE << "7. Sort History (Bubble/Merge/Heap/Insert)\n" << RESET;
        cout << YELLOW << "8. Module Help (Hashing)\n" << RESET;
        cout << "0. Exit\n";
        cout << "Select: ";
        cin >> choice;

        switch(choice) {
            case 1: calc.arithmetic(); break;
            case 2: calc.baseConversion(); break;
            case 3: calc.bcdConversion(); break;
            case 4: calc.generateTruthTable(); break;
            case 5: calc.variableManager(); break;
            case 6: calc.showCircuit(); break;
            case 7: calc.sortHistory(); break;
            case 8: calc.help(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
