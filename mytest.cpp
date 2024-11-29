// UMBC - CMSC 341 - Spring 2024 - Proj2
#include "wpower.h"
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL, SHUFFLE};
class Random {
public:
  Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
  {
      if (type == NORMAL){
          //the case of NORMAL to generate integer numbers with normal distribution
          m_generator = std::mt19937(m_device());
          //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
          //the mean and standard deviation can change by passing new values to constructor
          m_normdist = std::normal_distribution<>(mean,stdev);
      }
      else if (type == UNIFORMINT) {
          //the case of UNIFORMINT to generate integer numbers
          // Using a fixed seed value generates always the same sequence
          // of pseudorandom numbers, e.g. reproducing scientific experiments
          // here it helps us with testing since the same sequence repeats
          m_generator = std::mt19937(10);// 10 is the fixed seed value
          m_unidist = std::uniform_int_distribution<>(min,max);
      }
      else if (type == UNIFORMREAL) { //the case of UNIFORMREAL to generate real numbers
          m_generator = std::mt19937(10);// 10 is the fixed seed value
          m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
      }
      else { //the case of SHUFFLE to generate every number only once
          m_generator = std::mt19937(m_device());
      }
  }
  void setSeed(int seedNum){
      // we have set a default value for seed in constructor
      // we can change the seed by calling this function after constructor call
      // this gives us more randomness
      m_generator = std::mt19937(seedNum);
  }

  void getShuffle(vector<int> & array){
      // the user program creates the vector param and passes here
      // here we populate the vector using m_min and m_max
      for (int i = m_min; i<=m_max; i++){
          array.push_back(i);
      }
      shuffle(array.begin(),array.end(),m_generator);
  }

  void getShuffle(int array[]){
      // the param array must be of the size (m_max-m_min+1)
      // the user program creates the array and pass it here
      vector<int> temp;
      for (int i = m_min; i<=m_max; i++){
          temp.push_back(i);
      }
      std::shuffle(temp.begin(), temp.end(), m_generator);
      vector<int>::iterator it;
      int i = 0;
      for (it=temp.begin(); it != temp.end(); it++){
          array[i] = *it;
          i++;
      }
  }

  int getRandNum(){
      // this function returns integer numbers
      // the object must have been initialized to generate integers
      int result = 0;
      if(m_type == NORMAL){
          //returns a random number in a set with normal distribution
          //we limit random numbers by the min and max values
          result = m_min - 1;
          while(result < m_min || result > m_max)
              result = m_normdist(m_generator);
      }
      else if (m_type == UNIFORMINT){
          //this will generate a random number between min and max values
          result = m_unidist(m_generator);
      }
      return result;
  }

  double getRealRandNum(){
      // this function returns real numbers
      // the object must have been initialized to generate real numbers
      double result = m_uniReal(m_generator);
      // a trick to return numbers only with two deciaml points
      // for example if result is 15.0378, function returns 15.03
      // to round up we can use ceil function instead of floor
      result = std::floor(result*100.0)/100.0;
      return result;
  }

private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution
};

class Tester{
public:
  bool testAVLTreeBalanceAfterInsertions(int numInsertions);
  bool testBSTPropertyAfterInsertions(const WirelessPower& tree);
  bool testSplayTreeOperation(const WirelessPower& tree);
  bool testHeightInSplayTreeAfterInsertion(const WirelessPower& tree, int numInsertions);
  bool testRemoveNormalCaseForBST();
  bool testRemoveEdgeCaseForBST();
  bool testAVLBalanceAfterMultipleRemovals();
  bool testBSTPropertyAfterMultipleRemovals();
  bool testHeightValuesAfterRemovalsForBST();
  bool testAssignmentOperatorNormalCase();
  bool testAssignmentOperatorErrorCase();

private:
  bool isBSTPropertyPreserved(Customer* aNode);
  bool isAVLPropertyPreserved(Customer* aNode);
  int getHeight(Customer* aNode);
  bool isSameTree(Customer* node1, Customer* node2);
};

int main() {
  Tester tester;
  {
    cout << "Testing AVL Tree balances after a decent number of insertions: ";
    if (tester.testAVLTreeBalanceAfterInsertions(300)) {
        cout << "PASSED!" << endl;
    } else {
        cout << "FAILED!" << endl;
    }

    cout << "Testing BST property is preserved after all insertions: ";
    if(tester.testBSTPropertyAfterInsertions(WirelessPower(BST))){
        cout << "PASSED!" << endl;
    }else{
        cout << "FAILED!" << endl;
    }

    cout << "Testing SPLAY Tree performs splay operations: ";
    if(tester.testSplayTreeOperation(WirelessPower(SPLAY))){
        cout << "PASSED!" << endl;
    }else{
        cout << "FAILED!" << endl;
    }

    cout << "Testing heights are correct after multiple insertions in SPLAY tree: ";
    if(tester.testHeightInSplayTreeAfterInsertion(WirelessPower(SPLAY), 20)){
        cout << "PASSED!" << endl;
    }else{
        cout << "FAILED!" << endl;
    }

    cout << "Testing remove function for a normal case in BST tree: ";
    if(tester.testRemoveNormalCaseForBST()){
        cout << "PASSED!" << endl;
    }else{
        cout << "FAILED!" << endl;
    }

    cout << "Testing remove function for a edge case in the BST tree: ";
    if(tester.testRemoveEdgeCaseForBST()){
        cout << "PASSED!" << endl;
    }else{
        cout << "FAILED!" << endl;
    }

    cout << "Testing AVL Tree balances after multiple removals: ";
    if(tester.testAVLBalanceAfterMultipleRemovals()){
        cout << "PASSED!" << endl;
    }else{
        cout << "FAILED!" << endl;
    }

    cout << "Testing BST property is preserved after multiple removals: ";
    if(tester.testBSTPropertyAfterMultipleRemovals()){
        cout << "PASSED!" << endl;
    }else{
        cout << "FAILED!" << endl;
    }

    cout << "Testing height values are correct in a BST tree after multiple removals: ";
    if(tester.testHeightValuesAfterRemovalsForBST()){
        cout << "PASSED!" << endl;
    }else{
        cout << "FAILED!" << endl;
    }

    cout << "Testing assignment operator for a Normal Case: ";
    if(tester.testAssignmentOperatorNormalCase()){
        cout << "PASSED!" << endl;
    }else{
        cout << "FAILED!" << endl;
    }

    cout << "Testing Assignment Operator for an Error Case: ";
    if(tester.testAssignmentOperatorErrorCase()){
        cout << "PASSED!" << endl;
    }else{
        cout << "FAILED!" << endl;
    }
  } 
  return 0;
}

bool Tester::testAVLTreeBalanceAfterInsertions(int numInsertions) {
  WirelessPower tree(AVL);
  Random idGen(1, 1000);
  for (int i = 0; i < numInsertions; i++) {
      int id = idGen.getRandNum();
      tree.insert(Customer(id, 0, 0));
  }
  return isAVLPropertyPreserved(tree.getRoot());
}

bool Tester::isAVLPropertyPreserved(Customer* node) {
  if (node == nullptr) {
      return true; // An empty subtree always satisfies AVL property
  }
  // Calculate the height of the left and right subtrees
  int leftHeight = getHeight(node->getLeft());
  int rightHeight = getHeight(node->getRight());

  // Check if the balance factor of the current node is violated
  if (leftHeight - rightHeight > 1 || rightHeight - leftHeight > 1) {
      return false;
  }
  return isAVLPropertyPreserved(node->getLeft()) && isAVLPropertyPreserved(node->getRight());
}

int Tester::getHeight(Customer* node) {
  if (node == nullptr) {
      return -1;
  }
  // Calculate the height of the left and right subtrees
  int leftHeight = getHeight(node->getLeft());
  int rightHeight = getHeight(node->getRight());
  return max(leftHeight, rightHeight) + 1;
}

bool Tester::testBSTPropertyAfterInsertions(const WirelessPower& tree){
    return isBSTPropertyPreserved(tree.getRoot());
}

bool Tester::isBSTPropertyPreserved(Customer *aNode) {
    if(aNode == nullptr){
        return true;
    }
    if((aNode->getLeft() != nullptr && aNode->getLeft()->getID() >= aNode->getID()) ||
       (aNode->getRight() != nullptr && aNode->getRight()->getID() <= aNode->getID())){
        return false;
    }
    return isBSTPropertyPreserved(aNode->getLeft()) && isBSTPropertyPreserved(aNode->getRight());

}
bool Tester::testSplayTreeOperation(const WirelessPower& tree) {
  WirelessPower splayTree = tree;
  vector<int> nodeIDs = {1,2,3};

  for (unsigned int i = 0; i < nodeIDs.size(); i++) {
      int id = nodeIDs[i];
      splayTree.insert(Customer(id, 0, 0));
      // Check if the inserted node becomes the root
      if (splayTree.getRoot()->getID() != id) {
          cout << "Root not at top" << endl;
          return false; 
      }
      // Check if the tree preserves the BST property
      if (!isBSTPropertyPreserved(splayTree.getRoot())) {
          cout << "Bst not preserved" << endl;
          return false; 
      }
  }
  return true;
}

bool Tester::testHeightInSplayTreeAfterInsertion(const WirelessPower& tree, int numInsertions){
  WirelessPower splayTree = tree; // Copy of original tree 

  Random idGen(1, 1000);
  for (int i = 0; i < numInsertions; i++) {
      int id = idGen.getRandNum();
      splayTree.insert(Customer(id, 0, 0));
  }

  int calcHeight = getHeight(splayTree.getRoot());
  int expectedHeight = log2(numInsertions);
  bool splayHeight = calcHeight <= 2 * expectedHeight;
  return splayHeight;
}

bool Tester::testRemoveNormalCaseForBST(){
  WirelessPower bstTree(BST);
  bstTree.insert(Customer(10, 0, 0));
  bstTree.insert(Customer(5, 0, 0));
  bstTree.insert(Customer(15, 0, 0));
  bstTree.insert(Customer(3, 0, 0));
  bstTree.insert(Customer(7, 0, 0));
  bstTree.insert(Customer(12, 0, 0));
  bstTree.insert(Customer(17, 0, 0));

  // Remove a node from the BST
  bstTree.remove(15);
  // Verify that the removed node is no longer present in the BST
  Customer* removedNode = bstTree.getRoot();
  while (removedNode != nullptr) {
    if (removedNode->getID() == 15) {// Node with ID 15 should not be found in the tree after removal
      return false;
    }
    removedNode = removedNode->getRight();
  }

  // Verify that BST properties are preserved after the removal operation
  return isBSTPropertyPreserved(bstTree.getRoot());
}
bool Tester::testRemoveEdgeCaseForBST(){
  WirelessPower bstTree(BST);
  bstTree.insert(Customer(10,0,0));
  bstTree.remove(10);
  return bstTree.emptyHelper();
}
bool Tester::testAVLBalanceAfterMultipleRemovals(){
  WirelessPower avlTree(AVL);
  for(int i = 0; i < 300; i++){
      avlTree.insert(Customer(i,0,0));
  }
  for(int i = 0; i < 150; i++){
      avlTree.remove(i);
  }
  return isAVLPropertyPreserved(avlTree.getRoot());
}
bool Tester::testBSTPropertyAfterMultipleRemovals(){
  WirelessPower bstTree(BST);
  for(int i = 0; i < 300; i++){
      bstTree.insert(Customer(i, 0,0));
  }
  for(int i = 0; i < 200; i++){
      bstTree.remove(i);
  }
  return isBSTPropertyPreserved(bstTree.getRoot());
}
bool Tester::testHeightValuesAfterRemovalsForBST(){
  WirelessPower bstTree(BST);
  int insertedNodes = 7;
  int removedNodes = 3;
  bstTree.insert(Customer(10, 0, 0));
  bstTree.insert(Customer(5, 0, 0));
  bstTree.insert(Customer(15, 0, 0));
  bstTree.insert(Customer(3, 0, 0));
  bstTree.insert(Customer(7, 0, 0));
  bstTree.insert(Customer(12, 0, 0));
  bstTree.insert(Customer(17, 0, 0));
  bstTree.remove(3);
  bstTree.remove(12);
  bstTree.remove(5);
  int treeHeight = getHeight(bstTree.getRoot());
  int remainder = insertedNodes - removedNodes;
  int expectedHeight = log2(remainder);
  expectedHeight = max(0, expectedHeight);
  return treeHeight == expectedHeight;
}
bool Tester::testAssignmentOperatorNormalCase(){
  WirelessPower tree1(BST);
  WirelessPower tree2(BST);

  tree1.insert(Customer(1,0,0));
  tree1.insert(Customer(2,0,0));
  tree1.insert(Customer(3,0,0));

  tree2 = tree1;
  return isSameTree(tree1.getRoot(), tree2.getRoot());
}

bool Tester::isSameTree(Customer *node1, Customer *node2) {
    if(node1 == nullptr && node2 == nullptr){
      return true;
  }
  if (node1 == nullptr || node2 == nullptr){
      return false;
  }
  bool idCheck = node1->getID() == node2->getID();
  Customer* leftCheck1 = node1->getLeft();
  Customer* leftCheck2 = node2->getLeft();
  Customer* rightCheck1 = node1->getRight();
  Customer* rightCheck2 = node2->getRight();

  return idCheck && isSameTree(leftCheck1, leftCheck2) && isSameTree(rightCheck1, rightCheck2);
}
bool Tester::testAssignmentOperatorErrorCase(){
  WirelessPower tree1(BST);
  WirelessPower tree2(BST);

  tree2 = tree1;
  return tree1.emptyHelper() && tree2.emptyHelper();
}

