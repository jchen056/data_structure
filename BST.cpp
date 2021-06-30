#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Node class definitions
class Node{
public:
   int key;
   Node* left;
   Node* right;

   Node(int nodeKey) {
      key = nodeKey;
      left = nullptr;
      right = nullptr;
   }
};
//BinarySearchTree class definitions
class BinarySearchTree {
private:
   Node* root;
   
   void DeleteTree(Node* treeRoot) {
      if (treeRoot)
      {
          DeleteTree(treeRoot->left);
          DeleteTree(treeRoot->right);
          delete treeRoot;
      }
   }

public:
   BinarySearchTree() {
      root = nullptr;
   }
   
   virtual ~BinarySearchTree() {
      DeleteTree(root);
   }
   
   Node* GetRoot() {
      return root;
   }
   //Binary search tree Search() function
   Node* Search(int desiredKey) {
      Node* currentNode = root;
      while (currentNode) {
         // Return the node if the key matches
         if (currentNode->key == desiredKey) {
            return currentNode;
         }
         
         // Navigate to the left if the search key is 
         // less than the node's key.
         else if (desiredKey < currentNode->key) {
            currentNode = currentNode->left;
         }
         
         // Navigate to the right if the search key is 
         // greater than the node's key.
         else {
            currentNode = currentNode->right;
         }
      }
      
      // The key was not found in the tree.
      return nullptr;
   }
   
   //Binary search tree Insert() function
   void Insert(Node* newNode) {
      // Check if tree is empty; If the tree is empty, then the root data member is assigned with the new node.
      if (root == nullptr) {
         root = newNode;
      }
      else {
         Node* currentNode = root;
         while (currentNode) {
            if (newNode->key < currentNode->key) {
               // If no left child exists, add the new node
               // here; otherwise repeat from the left child.
               if (currentNode->left == nullptr) {
                  currentNode->left = newNode;
                  currentNode = nullptr;
               }
               else {
                  currentNode = currentNode->left;
               }
            }
            else {
               // If no right child exists, add the new node
               // here; otherwise repeat from the right child.
               if (currentNode->right == nullptr) {
                  currentNode->right = newNode;
                  currentNode = nullptr;
               }
               else {
                  currentNode = currentNode->right;
               }
            }
         }
      }
   }
   //Binary search tree Remove() function
   bool Remove(int key) {
      Node* parent = nullptr;
      Node* currentNode = root;
      
      // Search for the node.
      while (currentNode) {
         // Check if currentNode has a matching key.
         if (currentNode->key == key) {
             //The node being removed is a leaf. The parent's left or right data member is assigned with null, depending on whether the node is the left or right child.
            if (currentNode->left == nullptr && currentNode->right == nullptr) { // Case 1
               if (parent == nullptr) { // Node is root
                  root = nullptr;
               }
               else if (parent->left == currentNode) { 
                  parent->left = nullptr;
               }
               else {
                  parent->right = nullptr;
               }
               delete currentNode;
               return true; // Node found and removed
            }
            //The node being removed has one child. The parent's left or right data member is assigned with the removed node's single child.
            else if (currentNode->left && currentNode->right == nullptr) { // Case 2
               if (parent == nullptr) { // Node is root
                  root = currentNode->left;
               }
               else if (parent->left == currentNode) {
                  parent->left = currentNode->left;
               }
               else {
                  parent->right = currentNode->left;
               }
               delete currentNode;
               return true; // Node found and removed
            }
            else if (currentNode->left == nullptr && currentNode->right) { // Case 2
               if (parent == nullptr) { // Node is root
                  root = currentNode->right;
               }
               else if (parent->left == currentNode) {
                  parent->left = currentNode->right;
               }
               else {
                  parent->right = currentNode->right;
               }
               delete currentNode;
               return true; // Node found and removed
            }
            //The node being removed has two children. First, the algorithm locates the node's successor (the leftmost child of the node's right subtree), and copies the successor's key to the node.
            else { // Case 3
               // Find successor (leftmost child of right subtree)
               Node* successor = currentNode->right;
               while (successor->left) {
                  successor = successor->left;
               }
               currentNode->key = successor->key; // Copy successor's key to current node
               parent = currentNode;
               
               // Reassigned currentNode and key so that loop continues with new key
               currentNode = currentNode->right;
               key = successor->key;
            }
         }
         else if (currentNode->key < key) { // Search right
            parent = currentNode;
            currentNode = currentNode->right;
         }
         else { // Search left
            parent = currentNode;
            currentNode = currentNode->left;
         }
      }
      return false; // Node not found
   }
};

class BSTPrint {
private:
   static std::string GetRepeated(char toRepeat, int numberOfTimes) {
      if (numberOfTimes <= 0) {
         return std::string();
      }

      char* chars = new char[numberOfTimes + 1];
      for (int i = 0; i < numberOfTimes; i++) {
         chars[i] = toRepeat;
      }
      chars[numberOfTimes] = '\0';
      std::string result(chars);
      delete[] chars;
      return result;
   }
   
   static std::string GetSpaces(int numberOfSpaces) {
      return GetRepeated(' ', numberOfSpaces);
   }
   
   static void IndentLines(std::vector<std::string>& lines, int numberOfSpaces) {
      if (numberOfSpaces > 0) {
         // Prepend indentation to each line
         std::string indent = GetSpaces(numberOfSpaces);
         for (int i = 0; i < lines.size(); i++) {
            lines[i] = indent + lines[i];
         }
      }
   }

   static std::vector<std::string> TreeToLines(Node* subtreeRoot) {
      using namespace std;
      
      if (subtreeRoot == nullptr) {
         return vector<string>();
      }
      
      // Make a string with the subtreeRoot's key enclosed in brackets
      string rootString = string("[") + to_string(subtreeRoot->key) + string("]");
      int rootStrLen = rootString.length();
      
      // Case 1: subtreeRoot is a leaf
      if (subtreeRoot->left == nullptr && subtreeRoot->right == nullptr) {
         vector<string> lines;
         lines.push_back(rootString);
         return lines;
      }
      
      // Recursively make line strings for each child
      vector<string> leftLines = TreeToLines(subtreeRoot->left);
      vector<string> rightLines = TreeToLines(subtreeRoot->right);
      
      int lineCount = max(leftLines.size(), rightLines.size());
      vector<string> allLines;
      allLines.resize(lineCount + 2);
      
      // Case 2: subtreeRoot has no left child
      if (subtreeRoot->left == nullptr) {
         // Create the first 2 lines, not yet indented
         allLines[0] = rootString;
         allLines[1] = GetSpaces(rootStrLen) + "\\";
         
         // Find where the right child starts
         int rightChildIndent = (int)rightLines[0].find('[');
         
         // Goal: Indent lines appropriately so that the parent's right branch 
         // character ('\') matches up with the right child's '['.
         
         if (rightChildIndent <= rootStrLen) {
            // Indent all lines below
            IndentLines(rightLines, rootStrLen - rightChildIndent);
         }
         else {
            // Indent first 2 lines
            string indent = GetSpaces(rightChildIndent - rootStrLen);
            allLines[0] = indent + allLines[0];
            allLines[1] = indent + allLines[1];
         }
         
         // Copy rightLines into allLines starting at index 2
         for (size_t i = 0; i < rightLines.size(); i++) {
            allLines[i + 2] = rightLines[i];
         }
         
         return allLines;
      }
      
      // Case 3: subtreeRoot has no right child
      if (subtreeRoot->right == nullptr) {
         // Goal: Indent lines appropriately so that the parent's left branch 
         // character ('/') matches up with the left child's ']'.
         
         // Create the first 2 lines
         string indent = GetSpaces(leftLines[0].find(']'));
         allLines[0] = indent + " " + rootString;
         allLines[1] = indent + "/";
         
         // Copy leftLines into allLines starting at index 2
         for (size_t i = 0; i < leftLines.size(); i++) {
            allLines[i + 2] = leftLines[i];
         }
         
         return allLines;
      }
      
      // Case 4: subtreeRoot has both a left and right child
      
      // The goal is to have the two child nodes as close to the parent as 
      // possible without overlap on any level.
      
      // Compute absolute indentation, in number of spaces, needed for right lines
      int indentNeeded = 0;
      if (rightLines.size() > 0) {
         // Indent should at least get the immediate right child to be to the 
         // right of the root
         int left0Len = (int)leftLines[0].length();
         indentNeeded = max(0, 
            left0Len + (int)rootString.length() - (int)rightLines[0].find('['));
      }
      for (int i = 0; i < leftLines.size() && i < rightLines.size(); i += 2) {
         // Lines with branches are skipped, so the line of interest has only 
         // nodes. The difference between where the left line ends and the 
         // right line begins should be at least 3 spaces for clarity.
         int rightBegin = (int)rightLines[i].find('[');
         
         int forThisLine = (int)leftLines[i].length() + 3 - rightBegin;
         indentNeeded = max(indentNeeded, forThisLine);
      }
      
      // Build final lines in allLines starting at index 2
      string absoluteIndent = GetSpaces(indentNeeded);
      for (size_t i = 0; i < leftLines.size() || i < rightLines.size(); i++) {
         // If no right line, just take the left
         if (i >= rightLines.size()) {
            allLines[2 + i] = leftLines[i];
         }
         else {
            string left = "";
            if (i < leftLines.size()) {
               left = leftLines[i];
            }
            string right = absoluteIndent + rightLines[i];
            allLines[2 + i] = left + right.substr(left.length());
         }
      }
      
      // The first 2 lines remain. allLines[2] has the proper string for the 
      // 2 child nodes, and thus can be used to create branches in allLines[1].
      int leftIndex = (int)allLines[2].find(']');
      int rightIndex = (int)allLines[2].rfind('[');
      allLines[1] = GetSpaces(leftIndex) + "/" + 
         GetSpaces(rightIndex - leftIndex - 1) + "\\";
      
      // The space between leftIndex and rightIndex is the space that 
      // subtreeRoot's string should occupy. If rootString is too short, put 
      // underscores on the sides.
      rootStrLen = rightIndex - leftIndex - 1;
      if (rootString.length() < rootStrLen) {
         int difference = rootStrLen - (int)rootString.length();
         string underscores = GetRepeated('_', difference / 2);
         if (difference % 2 == 0) {
            rootString = underscores + rootString + underscores;
         }
         else {
            rootString = underscores + rootString + underscores + "_";
         }
      }
      allLines[0] = GetSpaces(leftIndex + 1) + rootString;
      
      return allLines;
   }

public:
   static std::string TreeToString(Node* subtreeRoot) {
      if (subtreeRoot == nullptr) {
         return "(empty tree)";
      }
      
      // First convert the tree to an array of line strings
      std::vector<std::string> lines = BSTPrint::TreeToLines(subtreeRoot);
      
      // Combine all lines into 1 string
      std::string treeString = lines[0];
      for (int i = 1; i < lines.size(); i++) {
         treeString += ("\n" + lines[i]);
      }
      return treeString;
   }
};

void SpaceSplit(const string& str, vector<string>& output) {
   size_t startIndex = 0;
   size_t endIndex = str.find(' ', startIndex);
   while (endIndex != string::npos) {
      // Only push non-empty strings
      if (endIndex > startIndex) {
         output.push_back(str.substr(startIndex, endIndex - startIndex));
      }
      
      // Get the next start and end indices
      startIndex = endIndex + 1;
      endIndex = str.find(' ', startIndex);
   }
   output.push_back(str.substr(startIndex));
}

int main() {
   BinarySearchTree tree;
      
   // Ask user for values to insert
   cout << "Enter values to insert with spaces between: ";
   string userValuesString;
   getline(cin, userValuesString);
   cout << endl;
      
   // Add each value to the tree
   vector<string> userValues;
   SpaceSplit(userValuesString, userValues);
   for (string value : userValues) {
      int key = stoi(value);
      tree.Insert(new Node(key));
   }
      
   // Show the tree
   cout << "Initial tree:" << endl;
   cout << BSTPrint::TreeToString(tree.GetRoot()) << endl;
   cout << endl;
      
   // Ask the user for a value to remove
   cout << "Enter value to remove: ";
   string removeValueString;
   getline(cin, removeValueString);
   int removeValue = stoi(removeValueString);
   cout << endl;
      
   cout << "Tree after removing " << removeValue << ":" << endl;
   tree.Remove(removeValue);
   cout << BSTPrint::TreeToString(tree.GetRoot()) << endl;
}
