// ============================================================
// DATA STRUCTURE: Singly Linked List
// ============================================================
// Operations:
//   append()   O(n) — walk to end, then insert
//   prepend()  O(1) — insert at front instantly
//   dequeue()  O(1) — remove from front instantly
//   search()   O(n) — must traverse
//   remove()   O(n) — must find the node first
//
// Best for: dynamic queues, task lists, unknown item counts
// Avoid when: you need random access by index (use array instead)
// ============================================================

struct Node {
  int value;
  Node* next;
};

// Insert at FRONT — O(1)
void prepend(Node*& head, int value) {
  Node* newNode = new Node{ value, head };
  head = newNode;
}

// Insert at END — O(n)
void append(Node*& head, int value) {
  Node* newNode = new Node{ value, nullptr };
  if (head == nullptr) { head = newNode; return; }
  Node* cur = head;
  while (cur->next) cur = cur->next;
  cur->next = newNode;
}

// Remove from FRONT and return value — O(1)
int dequeue(Node*& head) {
  if (!head) return -1;
  int val = head->value;
  Node* old = head;
  head = head->next;
  delete old;
  return val;
}

// Remove a specific value — O(n)
bool removeValue(Node*& head, int value) {
  if (!head) return false;
  if (head->value == value) { dequeue(head); return true; }
  Node* cur = head;
  while (cur->next) {
    if (cur->next->value == value) {
      Node* toDelete = cur->next;
      cur->next = toDelete->next;
      delete toDelete;
      return true;
    }
    cur = cur->next;
  }
  return false;
}

// Search — O(n)
bool search(Node* head, int value) {
  while (head) {
    if (head->value == value) return true;
    head = head->next;
  }
  return false;
}

void printList(Node* head) {
  while (head) {
    Serial.print(head->value);
    Serial.print(" -> ");
    head = head->next;
  }
  Serial.println("NULL");
}

void freeList(Node*& head) {
  while (head) dequeue(head);
}

// ---

void setup() {
  Serial.begin(115200);

  Node* list = nullptr;

  // O(1) — insert at front
  prepend(list, 10);
  prepend(list, 20);
  prepend(list, 30);
  Serial.print("After prepend 10,20,30: ");
  printList(list);  // 30 -> 20 -> 10 -> NULL

  // O(n) — insert at end
  append(list, 99);
  Serial.print("After append 99:        ");
  printList(list);  // 30 -> 20 -> 10 -> 99 -> NULL

  // O(n) — remove middle value
  removeValue(list, 20);
  Serial.print("After remove 20:        ");
  printList(list);  // 30 -> 10 -> 99 -> NULL

  // O(1) — dequeue front
  int val = dequeue(list);
  Serial.print("Dequeued: ");
  Serial.println(val);  // 30
  printList(list);      // 10 -> 99 -> NULL

  // O(n) — search
  Serial.print("Search 99: ");
  Serial.println(search(list, 99) ? "found" : "not found");

  freeList(list);
}

void loop() {}
