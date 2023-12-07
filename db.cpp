#include<unordered_map>
#include <string>
#include <iostream>
using namespace std;

class InMemoryDb {
    private:
        unordered_map<string, int> db;
        unordered_map<string, int> transactionDb;
        bool transactionInProgress;
    public:
        InMemoryDb() : transactionInProgress(false) {};

        int get(const string &key) {
            if (!transactionInProgress && db.count(key))
                return db[key];
            return -1;
        }

        void put(const string &key, int val) {
            if (!transactionInProgress)
                throw runtime_error("Transaction already in progress");

            if (transactionInProgress)
                transactionDb[key] = val;
        }

        void begin_transaction() {
            if (transactionInProgress)
                throw runtime_error("Transaction already in progress");
            transactionDb = db;
            transactionInProgress = true;
        }

        void commit() {
            if (!transactionInProgress)
                throw runtime_error("No transaction in progress to commit");
            db = transactionDb;
            transactionDb.clear();
            transactionInProgress = false;
        }

        void rollback() {
            if (!transactionInProgress)
                throw runtime_error("No transaction in progress to rollback");
            transactionDb.clear();
            transactionInProgress = false;
        }
};

int main() {
    InMemoryDb db = InMemoryDb();

    // Should return -1 since A doesn't exist in db yet
    cout << "Should return -1: " << db.get("A") << endl;

    // Should throw an error because a transaction is not in progress
    try {
        db.put("A", 5);
    } catch (exception ex) {
        cerr << ex.what() << endl;
    }

    // Can now use put since transaction has started
    db.begin_transaction();
    // Sets transactionDb value of A to 5
    db.put("A", 5);
    // Should return -1
    cout << "Should return -1: " << db.get("A") << endl;
    // Sets transactionDb value of A to 6
    db.put("A", 6);
    // Update db
    db.commit();
    // Should return 6
    cout << "Should return 6: " << db.get("A") << endl;
    // Should throw an error
    try {
        db.commit();
    } catch (exception ex) {
        cerr << ex.what() << endl;
    }
    // Should throw an error
    try {
        db.rollback();
    } catch (exception ex) {
        cerr << ex.what() << endl;
    }
    // Should return -1
    cout << "Should return -1: " << db.get("B") << endl;
    // New transaction
    db.begin_transaction();
    db.put("B", 10);
    db.rollback();
    // Should be -1
    cout << "Should return -1: " << db.get("B") << endl;

    return 0;
}