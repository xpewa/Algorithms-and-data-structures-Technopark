/*
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. 
 * Хранимые строки непустые и состоят из строчных латинских букв. Хеш-функция строки должна быть реализована 
 * с помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми. 
 * Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4. 
 * Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества 
 * и проверки принадлежности данной строки множеству.
 * 1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
 * g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
 */

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <sstream>
#include <cstring>

#define BUFFER_SIZE 8

size_t str_hash(const std::string& data) {
    size_t hash = 0;
    for (char i : data) {
        hash = hash * 13 + i;
    }
    return hash;
}

template <class T> struct Hasher {
    size_t operator() (const T& key) const {
        return key;
    }
};

template <> struct Hasher<std::string> {
    size_t operator() (const std::string& key) const {
        return str_hash(key);
    }
};

template <class T>
struct DefaultEqual {
    bool operator() (const T& l, const T& r) const {
        return l == r;
    }
};


template <class Key>
class HashTableNode {
public:
    HashTableNode(): deleted(false), empty(true) {}
    HashTableNode(Key key): key(key), deleted(false), empty(false) {}
    ~HashTableNode() = default;
    Key key;
    bool deleted;
    bool empty;
};

template <class Key, class Equal = DefaultEqual<Key>, class Hash = Hasher<Key>>
class HashTable {
public:
    HashTable(Hash hash = Hash(), Equal equal = Equal()): 
        table(BUFFER_SIZE), 
        realSize(0), 
        hash(hash), 
        equal(equal) {}
    ~HashTable() = default;

    bool has(const Key& key);
    bool add(const Key& key);
    bool remove(const Key& key);
private:
    std::vector<HashTableNode<Key>> table;
    size_t realSize;

    Hash hash;
    Equal equal;

    void rehash();
};

template <class Key, class Equal, class Hash>
bool HashTable<Key, Equal, Hash>::has(const Key& key) {
    size_t hash_ = hash(key) % table.capacity();

    for (size_t i = 0; i < table.capacity(); ++i) {
        if (table[hash_].empty)
            break;
        if (equal(table[hash_].key, key) && !table[hash_].deleted)
            return true;

        hash_ = (hash_ + i) % table.capacity();
    }

    return false;
}

template <class Key, class Equal, class Hash>
bool HashTable<Key, Equal, Hash>::add(const Key& key) {
    if (((double)realSize / (double)table.capacity()) >= 3.0/4.0) {
        rehash();
    }

    size_t hash_ = hash(key) % table.capacity();
    int firstDeleted = -1;
    for (size_t i = 0; i < table.capacity(); ++i) {
        if (table[hash_].empty)
            break;
        if (equal(table[hash_].key, key) && !table[hash_].deleted)
            return false;
        if (table[hash_].deleted && firstDeleted < 0)
            firstDeleted = hash_;

        hash_ = (hash_ + i) % table.capacity();
    }

    if (firstDeleted < 0) {
        table[hash_] = HashTableNode<Key>(key);
    }
    else {
        table[firstDeleted].key = key;
        table[firstDeleted].deleted = false;
        table[firstDeleted].empty = false;
    }

    ++realSize;
    return true;
}

template <class Key, class Equal, class Hash>
bool HashTable<Key, Equal, Hash>::remove(const Key& key) {
    size_t hash_ = hash(key) % table.capacity();

    for (size_t i = 0; i < table.capacity(); ++i) {
        if (table[hash_].empty)
            break;
        if (equal(table[hash_].key, key) && !table[hash_].deleted) {
            table[hash_].deleted = true;
            --realSize;
            return true;
        }

        hash_ = (hash_ + i) % table.capacity();
    }

    return false;
}

template <class Key, class Equal, class Hash>
void HashTable<Key, Equal, Hash>::rehash() {
    size_t oldSize = table.capacity();

    std::vector<HashTableNode<Key>> oldTable(oldSize);
    for (int i = 0; i < oldSize; ++i) {
        oldTable[i] = table[i];
    }

    table.resize(oldSize*2);
    table.clear();
    realSize = 0;

	for (int i = 0; i < oldSize; ++i) {
		if (!oldTable[i].empty && !oldTable[i].deleted) {
			add(oldTable[i].key);
		}
	}
}

void run(std::istream &is, std::ostream &os) {
    HashTable<std::string> table;

    while (!is.eof()) {
        std::string str;
        getline(is, str);
        if (str != "\0") {
            char command = str[0];
            std::string key;
            key.append(str, 2, str.size()-2);
            bool res = false;
            switch(command) {
                case '+':
                    res = table.add(key);
                    break;
                case '?':
                    res = table.has(key);
                    break;
                case '-':
                    res = table.remove(key);
                    break;
            }
            os << (res ? "OK" : "FAIL") << std::endl;
        }
        else
            break;
    }     
}

void tests() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "+ hello" << std::endl;
        input << "+ bye" << std::endl;
        input << "? bye" << std::endl;
        input << "+ bye" << std::endl;
        input << "- bye" << std::endl;
        input << "? bye" << std::endl;
        input << "? hello" << std::endl;

        run(input, output);

        assert(output.str() == "OK\nOK\nOK\nFAIL\nOK\nFAIL\nOK\n");
    }
}

int main() {
    run(std::cin, std::cout);
    //tests();
    return 0;
}