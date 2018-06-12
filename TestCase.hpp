#pragma once
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class TestCase {
    
    public:
    
    int passed, failed, count;
    ostream* os;
    string name;
    
    TestCase(string name, ostream& os) {
        passed = failed = count = 0;
        this->name = name;
        this->os = &os;
    }
    
    template<typename T>
    TestCase check_equal(T left, T right) {
        count++;
        if (!(left == right)){
            *os << name << ": Failure in test #" << count << ": " << left << " should equal " << right << endl;
            failed++;
        }
        else {
            passed++;    
        }
        return *this;
    }
    
    template<typename T>
    TestCase check_different(T left, T right) {
        count++;
        if (left == right) {
            *os << name << ": Failure in test #" << count << ": " << left << " shouldn't equal " << right << endl;
            failed++;
        }
        else {
           passed++; 
        }
        return *this;
    }
    
    template<typename T>
    TestCase check_output(T left, string right) {
        count++;
        stringstream buffer;
        buffer << left;
        if (buffer.str() != right) {
            *os << name << ": Failure in test #" << count << ": string value should be " << left << " but is " << right << endl;
            failed++;
        }
        else {
            passed++;
        }
        return *this;
    }
    
    template<typename F, typename T1, typename T2>
    TestCase check_function(F func, T1 input, T2 expected) {
        count++;
        if (func(input) != expected) {
            *os << name << ": Failure in test #" << count << ": Function should return " << expected << " but returned " << func(input) << endl;
            failed++;
        }
        else {
            passed++;
        }
        return *this;
    }

    void print() {
        *os << name << ": " << failed << " failed, " << passed << " passed, " << count << " total." << endl;
        *os << "---" << endl;
    }
    
};