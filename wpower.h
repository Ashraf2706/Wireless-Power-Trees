// UMBC - CMSC 341 - Spring 2024 - Proj2
#ifndef WPOWER_H
#define WPOWER_H
#include <iostream>
using namespace std;
class Grader;//this class is for grading purposes, no need to do anything
class Tester;//this is your tester class, you add your test functions in this class
class WirelessPower;
const int MINID = 10000;
const int MAXID = 99999;
const int MINLAT = -90;
const int MAXLAT = 90;
const int MINLONG = -180;
const int MAXLONG = 180;
#define DEFAULT_HEIGHT 0
#define DEFAULT_ID 0
enum TREETYPE {BST, AVL, SPLAY};
class Customer{
public:
    friend class WirelessPower;
    friend class Grader;
    friend class Tester;
    Customer(int id, double lat, double longitude){
        m_id = id; m_latitude = lat; m_longitude = longitude;
        m_left = nullptr; m_right = nullptr; m_height = DEFAULT_HEIGHT;
    }
    int getHeight() const {return m_height;}
    Customer* getLeft() const {return m_left;}
    Customer* getRight() const {return m_right;}
    int getID() const {return m_id;}
    double getLatitude() const {return m_latitude;}
    double getLongitude() const {return m_longitude;}
    void setID(const int id){m_id=id;}
    void setLatitude(double lat) {m_latitude=lat;}
    void setLongitude(double longitude) {m_longitude=longitude;}
    void setHeight(int height){m_height=height;}
    void setLeft(Customer* left){m_left=left;}
    void setRight(Customer* right){m_right=right;}
    string getLatStr() const{
        string text = "";
        int latSeconds = (int)(abs(m_latitude * 3600));
        int latDegrees = latSeconds / 3600;
        latSeconds = latSeconds % 3600;
        int latMinutes = latSeconds / 60;
        latSeconds %= 60;
        char latDirection = (m_latitude >= 0) ? 'N' : 'S';
        text = to_string(latDegrees) + "\u00B0 " + to_string(latMinutes) + "' " +
               to_string(latSeconds) + "\" " + latDirection;
        return text;
    }
    string getLongStr() const{
        string text = "";
        int longSeconds = (int)(abs(m_longitude * 3600));
        int longDegrees = longSeconds / 3600;
        longSeconds = longSeconds % 3600;
        int longMinutes = longSeconds / 60;
        longSeconds %= 60;
        char longDirection = (m_longitude >= 0) ? 'E' : 'W';
        text = to_string(longDegrees) + "\u00B0 " + to_string(longMinutes) + "' " +
               to_string(longSeconds) + "\" " + longDirection;
        return text;
    }
    // Overloaded insertion operator
    friend ostream& operator<<(ostream& sout, const Customer & x );
private:
    int m_id;
    double m_latitude;
    double m_longitude;
    Customer* m_left;    //the pointer to the left child in the BST
    Customer* m_right;   //the pointer to the right child in the BST
    int m_height;        //the height of node in the BST
};
class WirelessPower{
public:
    friend class Grader;
    friend class Tester;

    WirelessPower(TREETYPE type);
    ~WirelessPower();
    void dumpTree() const;// for debugging purposes
    const WirelessPower & operator=(const WirelessPower & rhs);
    void clear();
    TREETYPE getType() const;
    void insert(const Customer& customer);//inserts into BST, AVL, or SPLAY
    void remove(int id);//only removes from AVL and BST, not from SPLAY
    //changing type from BST or SPLAY to AVL should transfer all nodes to an AVL tree
    void setType(TREETYPE type);
private:
    Customer* m_root;       //the root of the BST
    TREETYPE m_type;        // the type of tree, BST, AVL or SPLAY
    //helper for recursive traversal
    void dump(Customer* customer) const;
    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************
    void clearHelper(Customer*& aNode);
    Customer* copyHelper(Customer* aNode);
    Customer* insertHelper(const Customer& customer, Customer* aNode);
    Customer* removeHelper(int id, Customer* aNode);
    void updateHeightsHelper(Customer* aNode);
    Customer* avlBalance(Customer* aNode);
    Customer* splayHelper(Customer* root, int key);
    Customer* rotateRight(Customer* aNode);
    Customer* rotateLeft(Customer* aNode);
    int getHeightHelper(Customer* aNode);
    int getBalanceHelper(Customer* aNode);
    Customer* findMinHelper(Customer* aNode);
    Customer* convertToAVL(Customer* node);
    Customer* getRoot()const;
    bool emptyHelper()const;
};
#endif