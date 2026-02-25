// ============================================================
// DATA STRUCTURE: Binary Search Tree (BST)
// ============================================================
// Operations (balanced tree):
//   insert()   O(log n) — halves the search space each step
//   search()   O(log n)
//   remove()   O(log n)
//   inOrder()  O(n)     — prints sorted output!
//
// Key property: left child < parent < right child
// Best for: sorted data, fast lookup, range queries
// Avoid when: data arrives already sorted (degrades to O(n))
//             → use AVL or Red-Black tree for self-balancing
// ============================================================

struct Node {
  int value;
  Node* left;
  Node* right;
};

Node* newNode(int value) {
  return new Node{ value, nullptr, nullptr };
}

// Insert — O(log n) average
Node* insert(Node* root, int value) {
  if (!root) return newNode(value);
  if (value < root->value)
    root->left  = insert(root->left,  value);
  else if (value > root->value)
    root->right = insert(root->right, value);
  // equal values are ignored (set behavior)
  return root;
}

// Search — O(log n) average
bool search(Node* root, int value) {
  if (!root) return false;
  if (value == root->value) return true;
  if (value < root->value) return search(root->left,  value);
  else                     return search(root->right, value);
}

// Find the minimum node (used for deletion)
Node* findMin(Node* root) {
  while (root->left) root = root->left;
  return root;
}

// Remove a value — O(log n) average
Node* remove(Node* root, int value) {
  if (!root) return nullptr;
  if (value < root->value) {
    root->left  = remove(root->left,  value);
  } else if (value > root->value) {
    root->right = remove(root->right, value);
  } else {
    // Found the node to delete
    if (!root->left) {          // no left child
      Node* temp = root->right;
      delete root;
      return temp;
    } else if (!root->right) {  // no right child
      Node* temp = root->left;
      delete root;
      return temp;
    }
    // Two children: replace with in-order successor
    Node* successor = findMin(root->right);
    root->value = successor->value;
    root->right = remove(root->right, successor->value);
  }
  return root;
}

// In-order traversal: LEFT → ROOT → RIGHT → always prints sorted!
void inOrder(Node* root) {
  if (!root) return;
  inOrder(root->left);
  Serial.print(root->value);
  Serial.print(" ");
  inOrder(root->right);
}

// Tree height (useful to check if it's becoming unbalanced)
int height(Node* root) {
  if (!root) return 0;
  int l = height(root->left);
  int r = height(root->right);
  return 1 + (l > r ? l : r);
}

void freeTree(Node* root) {
  if (!root) return;
  freeTree(root->left);
  freeTree(root->right);
  delete root;
}

// ---

void setup() {
  Serial.begin(115200);

  Node* root = nullptr;

  // Insert values in random order
  int values[] = { 50, 30, 70, 20, 40, 60, 80 };
  for (int v : values) root = insert(root, v);

  //        50
  //       /  \
  //      30   70
  //     / \  / \
  //    20 40 60 80

  Serial.print("In-order (sorted): ");
  inOrder(root);  // 20 30 40 50 60 70 80
  Serial.println();

  Serial.print("Tree height: ");
  Serial.println(height(root));  // 3

  Serial.print("Search 40: ");
  Serial.println(search(root, 40) ? "found" : "not found");  // found

  Serial.print("Search 99: ");
  Serial.println(search(root, 99) ? "found" : "not found");  // not found

  // Remove a node with two children
  root = remove(root, 30);
  Serial.print("After removing 30: ");
  inOrder(root);  // 20 40 50 60 70 80
  Serial.println();

  freeTree(root);
}

void loop() {}
