// ============================================================
// CODE OPTIMIZATIONS — Data Structures Overview
// ============================================================
// Open each subfolder sketch for the full working example:
//
//  linked_list/   — dynamic list, O(1) front insert/remove
//  binary_tree/   — sorted data, O(log n) search/insert
//  hash_table/    — key-value lookup, O(1) average
//  ring_buffer/   — circular FIFO, O(1) always, no heap alloc
//
// Quick comparison:
//
//  Structure     | Access | Search | Insert | Delete | Memory
//  --------------|--------|--------|--------|--------|-------
//  Array         | O(1)   | O(n)   | O(n)   | O(n)   | static
//  Linked List   | O(n)   | O(n)   | O(1)*  | O(1)*  | heap
//  Binary Tree   | O(n)   | O(logn)| O(logn)| O(logn)| heap
//  Hash Table    | O(1)** | O(1)** | O(1)** | O(1)** | heap
//  Ring Buffer   | O(1)   | O(n)   | O(1)   | O(1)   | static
//
//  * O(1) only at front/back; finding position is still O(n)
//  ** average case; O(n) worst case on hash collisions
//
// For embedded (tight RAM, no OS):
//   → Prefer Ring Buffer and arrays (no heap, no fragmentation)
//   → Use Hash Table / Linked List only on ESP32/Teensy+ (>32KB RAM)
//   → BST is great for config/lookup tables built at startup
// ============================================================

void setup() {
  Serial.begin(115200);
  Serial.println("See subfolders for each data structure example.");
}

void loop() {}
