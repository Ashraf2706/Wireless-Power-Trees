// UMBC - CMSC 341 - Spring 2024 - Proj2
#include "wpower.h"
WirelessPower::WirelessPower(TREETYPE type){
  m_type = type;
  m_root = nullptr;
}
WirelessPower::~WirelessPower(){
  clear();
}
void WirelessPower::clear(){
  clearHelper(m_root);
  m_root = nullptr;
}

//Helper function for clearing nodes
void WirelessPower::clearHelper(Customer*& aNode){
  if(aNode != nullptr){
    clearHelper(aNode->m_left);
    clearHelper(aNode->m_right);
    delete aNode;
    aNode = nullptr;
  }
}

void WirelessPower::insert(const Customer& customer) {
  if (m_type == AVL) {
    m_root = insertHelper(customer, m_root);
    m_root = avlBalance(m_root);  // Balance only if AVL tree
  } else if (m_type == BST) {
      m_root = insertHelper(customer, m_root);  // Insert without balancing for BST
  } else if (m_type == SPLAY) {
      // For SPLAY, insert and then splay
      m_root = insertHelper(customer, m_root);
      m_root = splayHelper(m_root, customer.getID());  // Splay the inserted node
  }
}

// Helper function for inserting nodes
Customer* WirelessPower::insertHelper(const Customer& customer, Customer* aNode) {
  if (aNode == nullptr) {
    return new Customer(customer);
  }
  if (customer.getID() < aNode->getID()) {
    aNode->setLeft(insertHelper(customer, aNode->getLeft()));
  } else if (customer.getID() > aNode->getID()) {
    aNode->setRight(insertHelper(customer, aNode->getRight()));
  }
  // Update height
  aNode->setHeight(1 + max(getHeightHelper(aNode->getLeft()), getHeightHelper(aNode->getRight())));
  if (m_type == AVL) {
    aNode = avlBalance(aNode);
  }
  return aNode;
}


void WirelessPower::remove(int id) {
  if (m_type == BST || m_type == AVL) {
    m_root = removeHelper(id, m_root);
    if (m_type == AVL) {
      m_root = avlBalance(m_root);  // Only balance if it's an AVL tree
    }
  }
}

Customer* WirelessPower::removeHelper(int id, Customer* aNode) {
    if (aNode == nullptr) {
        return nullptr;
    }
    if (id < aNode->getID()) {
        aNode->setLeft(removeHelper(id, aNode->getLeft()));
    } else if (id > aNode->getID()) {
        aNode->setRight(removeHelper(id, aNode->getRight()));
    } else {
        if (aNode->getLeft() == nullptr || aNode->getRight() == nullptr) {
            Customer* temp = aNode->getLeft() ? aNode->getLeft() : aNode->getRight();
            if (temp == nullptr) {
                temp = aNode;
                aNode = nullptr;
            } else {
                *aNode = *temp;
            }
            delete temp;
        } else {
            Customer* temp = findMinHelper(aNode->getRight());
            aNode->setID(temp->getID());
            aNode->setLatitude(temp->getLatitude());
            aNode->setLongitude(temp->getLongitude());
            aNode->setRight(removeHelper(temp->getID(), aNode->getRight()));
        }
    }
    if (aNode == nullptr) {
        return nullptr;
    }
    // Update height
    aNode->setHeight(1 + max(getHeightHelper(aNode->getLeft()), getHeightHelper(aNode->getRight())));
    if (m_type == AVL) {
        aNode = avlBalance(aNode);
    }
    return aNode;
}


TREETYPE WirelessPower::getType() const{
    return m_type;
}

void WirelessPower::setType(TREETYPE type) {
    if (m_type != type) {
        // If changing to AVL, make sure entire tree is balanced 
        if (type == AVL) {
            m_root = convertToAVL(m_root);
        }
        m_type = type;
    }
}

const WirelessPower & WirelessPower::operator=(const WirelessPower & rhs){
    if(this != &rhs) {
        clear();
        if (rhs.m_root != nullptr) {
            m_root = copyHelper(rhs.m_root);
        } else {
            m_root = nullptr;
        }
        m_type = rhs.m_type;
    }

    return *this;
}

//Helper function for carrying out a deep copy
Customer* WirelessPower::copyHelper(Customer *aNode) {
    if(aNode == nullptr){
        return nullptr;
    }
    //create a new node with same data
    Customer* newNode = new Customer(aNode->getID(), aNode->getLatitude(), aNode->getLongitude());
    newNode->setHeight(aNode->getHeight());
    newNode->setLeft(copyHelper(aNode->getLeft()));
    newNode->setRight(copyHelper(aNode->getRight()));

    return newNode;
}

void WirelessPower::dumpTree() const {dump(m_root);}

void WirelessPower::dump(Customer* customer) const{
    if (customer != nullptr){
        cout << "(";
        dump(customer->m_left); //first visit the left child
        cout << customer->m_id << ":" << customer->m_height;//second visit the node itself
        dump(customer->m_right);//third visit the right child
        cout << ")";
    }
}
ostream& operator<<(ostream& sout, const Customer & x ) {
    sout << x.m_id << " (" << x.getLatStr() << ", " << x.getLongStr() << ")" << endl;
    return sout;
}

//Helper function to update heights
void WirelessPower::updateHeightsHelper(Customer *aNode) {
    if(aNode == nullptr){
        return;
    }
    //Update heights for left and right trees
    updateHeightsHelper(aNode->getLeft());
    updateHeightsHelper(aNode->getRight());
    //Update height of current node
    aNode->setHeight(max(getHeightHelper(aNode->getLeft()), getHeightHelper(aNode->getRight())) +1);
}

//Helper function for AVL tree
Customer* WirelessPower::avlBalance(Customer* node) {
    if (node == nullptr){
        return nullptr;
    }
    // Update height for the current node
    node->setHeight(1 + max(getHeightHelper(node->getLeft()), getHeightHelper(node->getRight())));
    int balance = getBalanceHelper(node);
    // Left heavy
    if (balance > 1) {
        if (getBalanceHelper(node->getLeft()) < 0) {
            node->setLeft(rotateLeft(node->getLeft()));
        }
        return rotateRight(node);
    }
    // Right heavy
    if (balance < -1) {
        if (getBalanceHelper(node->getRight()) > 0) {
            node->setRight(rotateRight(node->getRight()));
        }
        return rotateLeft(node);
    }
    return node;
}


//Helper function for right rotation
Customer* WirelessPower::rotateRight(Customer* aNode) {
    if(aNode == nullptr){
        return nullptr;
    }
    Customer* newRoot = aNode->getLeft();
    aNode->setLeft(newRoot->getRight());
    newRoot->setRight(aNode);
    aNode->setHeight(max(getHeightHelper(aNode->getLeft()), getHeightHelper(aNode->getRight())) + 1);
    newRoot->setHeight(max(getHeightHelper(newRoot->getLeft()), getHeightHelper(newRoot->getRight())) + 1);
    return newRoot;
}

//Helper function for left rotation
Customer* WirelessPower::rotateLeft(Customer* aNode) {
    if(aNode == nullptr){
        return nullptr;
    }
    Customer* newRoot = aNode->getRight();
    aNode->setRight(newRoot->getLeft());
    newRoot->setLeft(aNode);
    // Update heights
    aNode->setHeight(max(getHeightHelper(aNode->getLeft()), getHeightHelper(aNode->getRight())) + 1);
    newRoot->setHeight(max(getHeightHelper(newRoot->getLeft()), getHeightHelper(newRoot->getRight())) + 1);
    // Return new root
    return newRoot;
}

//Helper functions to get height of tree
int WirelessPower::getHeightHelper(Customer *aNode) {
    if(aNode == nullptr){
        return -1;
    }
    return aNode->getHeight();
}

//Helper function to get balance of tree
int WirelessPower::getBalanceHelper(Customer *aNode) {
    if(aNode == nullptr){
        return 0;
    }
    return getHeightHelper(aNode->getLeft()) - getHeightHelper(aNode->getRight());
}

//Helper function for splay node to the root
Customer* WirelessPower::splayHelper(Customer* root, int key) {
  if(root == nullptr || root->getID() == key) {
    return root;
  }
  // Go left
  if(key < root->getID()) {
    if (root->getLeft() == nullptr) {
      return root;
    }
    // Left Left
    if (key <= root->getLeft()->getID()) {
      root->getLeft()->setLeft(splayHelper(root->getLeft()->getLeft(), key));
      root = rotateRight(root);
    }
    //Left Right
    else if (key >= root->getLeft()->getID()) {
      root->getLeft()->setRight(splayHelper(root->getLeft()->getRight(), key));
      if (root->getLeft()->getRight() != nullptr) {
        root->setLeft(rotateLeft(root->getLeft()));
      }
    }
    // Do the second rotation for the root
    if (root->getLeft() == nullptr) {
      return root;
    } else {
      root = rotateRight(root);
      return root;
    }
  }
  //Go right 
  else {
    if (root->getRight() == nullptr) {
      return root;
    }
    //Right Right
    if (key >= root->getRight()->getID()) {
      root->getRight()->setRight(splayHelper(root->getRight()->getRight(), key));
      root = rotateLeft(root);
    }
    //Right Left
    else if (key <= root->getRight()->getID()) {
      root->getRight()->setLeft(splayHelper(root->getRight()->getLeft(), key));
      if (root->getRight()->getLeft() != nullptr) {
          root->setRight(rotateRight(root->getRight()));
      }
    }
    // Do the second rotation for the root
    if (root->getRight() == nullptr){
      return root;
    }else{
      root = rotateLeft(root);
      return root;
    }  
  }
}

Customer* WirelessPower::findMinHelper(Customer *aNode) {
  if(aNode == nullptr || aNode->getLeft() == nullptr){
    return aNode;
  }else{
    return findMinHelper(aNode->getLeft());
  }
}

Customer* WirelessPower::convertToAVL(Customer* node) {
  if (node == nullptr) return nullptr;

  // Recursively convert left and right subtrees
  node->setLeft(convertToAVL(node->getLeft()));
  node->setRight(convertToAVL(node->getRight()));

  // Balance the current node
  return avlBalance(node);
}

Customer* WirelessPower::getRoot() const{
  return m_root;
}

bool WirelessPower::emptyHelper() const {
  return m_root == nullptr;
}