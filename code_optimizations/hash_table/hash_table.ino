// ============================================================
// DATA STRUCTURE: Hash Table (with chaining for collisions)
// ============================================================
// Operations:
//   set()    O(1) average — hash key → go directly to bucket
//   get()    O(1) average
//   remove() O(1) average
//   (worst case O(n) if all keys collide into same bucket)
//
// Best for: key-value lookup (config, sensor IDs, name→value)
// Avoid when: you need ordered data (BST is better)
//             keys are unknown at design time on tiny MCUs
// ============================================================

const int TABLE_SIZE = 16;  // must be power of 2 for fast modulo

struct Entry {
  const char* key;
  int value;
  Entry* next;  // chaining: multiple entries per bucket
};

struct HashTable {
  Entry* buckets[TABLE_SIZE] = { nullptr };
};

// djb2 hash — fast, good distribution for small tables
unsigned int hashKey(const char* key) {
  unsigned int hash = 5381;
  while (*key) hash = ((hash << 5) + hash) + (unsigned char)*key++;
  return hash % TABLE_SIZE;
}

// Insert or update — O(1) average
void set(HashTable& table, const char* key, int value) {
  unsigned int idx = hashKey(key);
  Entry* cur = table.buckets[idx];

  // Update existing key
  while (cur) {
    if (strcmp(cur->key, key) == 0) { cur->value = value; return; }
    cur = cur->next;
  }

  // New entry — insert at front of chain
  Entry* entry = new Entry{ key, value, table.buckets[idx] };
  table.buckets[idx] = entry;
}

// Lookup — O(1) average
// Returns pointer to value, or nullptr if not found
int* get(HashTable& table, const char* key) {
  unsigned int idx = hashKey(key);
  Entry* cur = table.buckets[idx];
  while (cur) {
    if (strcmp(cur->key, key) == 0) return &cur->value;
    cur = cur->next;
  }
  return nullptr;
}

// Remove a key — O(1) average
bool removeKey(HashTable& table, const char* key) {
  unsigned int idx = hashKey(key);
  Entry* cur  = table.buckets[idx];
  Entry* prev = nullptr;
  while (cur) {
    if (strcmp(cur->key, key) == 0) {
      if (prev) prev->next = cur->next;
      else       table.buckets[idx] = cur->next;
      delete cur;
      return true;
    }
    prev = cur;
    cur  = cur->next;
  }
  return false;
}

// Print all entries (unordered — hash tables don't preserve order!)
void printTable(HashTable& table) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Entry* cur = table.buckets[i];
    while (cur) {
      Serial.print("  [");
      Serial.print(i);
      Serial.print("] ");
      Serial.print(cur->key);
      Serial.print(" = ");
      Serial.println(cur->value);
      cur = cur->next;
    }
  }
}

void freeTable(HashTable& table) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Entry* cur = table.buckets[i];
    while (cur) {
      Entry* next = cur->next;
      delete cur;
      cur = next;
    }
    table.buckets[i] = nullptr;
  }
}

// ---

void setup() {
  Serial.begin(115200);

  HashTable config;

  // O(1) — set sensor config values by name
  set(config, "temp_pin",    A0);
  set(config, "pressure_pin", A1);
  set(config, "threshold",   75);
  set(config, "sample_rate", 100);

  // O(1) — lookup directly by name, no looping needed!
  int* pin = get(config, "temp_pin");
  Serial.print("temp_pin = ");
  Serial.println(pin ? *pin : -1);  // A0

  int* rate = get(config, "sample_rate");
  Serial.print("sample_rate = ");
  Serial.println(rate ? *rate : -1);  // 100

  // O(1) — update existing key
  set(config, "threshold", 80);
  int* thresh = get(config, "threshold");
  Serial.print("threshold (updated) = ");
  Serial.println(thresh ? *thresh : -1);  // 80

  // O(1) — remove
  removeKey(config, "pressure_pin");
  Serial.print("pressure_pin after remove: ");
  Serial.println(get(config, "pressure_pin") ? "found" : "not found");

  Serial.println("All entries:");
  printTable(config);

  freeTable(config);
}

void loop() {}
