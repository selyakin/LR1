#include <iostream>
#include <sstream>

#include "array.h"

using namespace std;

Array::Array() : data(nullptr), sz(0), cp(0) {}

Array::Array(size_t size) 
    :data(size ? new string[size]() : nullptr),
    sz(size),
    cp(size) {}

Array::Array(initializer_list<string> list)
    :data(new string[list.size()]),
    sz(list.size()),
    cp(list.size()) {
    size_t i = 0;
    for(string el: list)
        data[i++] = el;
}

Array::Array(const Array& initialArr)
    : data(initialArr.sz ? new string[initialArr.sz] : nullptr),
    sz(initialArr.sz),
    cp(initialArr.sz){
    for(size_t i = 0; i < sz; ++i)
        data[i] = initialArr.data[i];
}

Array& Array::operator=(const Array& initialArr) {
    if (this == &initialArr) return *this;
    string* tempData = initialArr.sz ? new string[initialArr.sz] : nullptr;
    for (size_t i = 0; i < initialArr.sz; ++i) 
        tempData[i] = initialArr.data[i];
    delete[] data;
    data = tempData; sz = initialArr.sz; cp = initialArr.sz;
    return *this;
}

Array::~Array(){
    delete [] data;
};

void Array::reserve(size_t newCp){
    if(newCp <= cp) return;
    string* tempData = new string[newCp];
    for(size_t i = 0; i < sz; ++i)
        tempData[i] = data[i];
    delete [] data;
    data = tempData;
    cp = newCp;
}

void Array::push(const string& value){
    if(sz == cp){
        reserve(sz == 0 ? 1 : cp * 2);
    }
    data[sz++] = value;
};

void Array::insert(size_t index, const string& value){
    if(index > sz) throw out_of_range("insert: index > size");
    if(sz == cp) reserve(sz == 0 ? 1 : cp * 2);
    for(size_t i = sz; i > index; --i)
            data[i] = data[i - 1];
    data[index] = value;
    ++sz;
}

string Array::get(size_t index) const{
    if(index >= sz) throw out_of_range("get: index >= size");
    return data[index];
}
void Array::remove(size_t index){
    if(index >= sz) throw out_of_range("remove: index >= size");
    for(size_t i = index; i + 1 < sz; ++i)
        data[i] = data[i + 1];
    --sz; 
}

void Array::replace(size_t index, const string& value){
    if(index >= sz) throw out_of_range("replace: index >= size");
    data[index] = value;
}
size_t Array::size() const{
    return sz;
}

void Array::print() const{
    cout << "Array: \n";
    for(size_t i = 0; i < sz; ++i){
        cout << "array["<< i << "] = " << data[i] << '\n';
    }
    cout << '\n';
}

string Array::toJson() const {
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < sz; ++i) {
        if (i > 0) ss << ", ";
        ss << "\"" << data[i] << "\""; 
    }
    ss << "]";
    return ss.str();
}

void Array::fromJson(const string& json) {
    *this = Array(); // очищение
    size_t pos = 0;
    while ((pos = json.find('"', pos)) != string::npos) {
        size_t endQuote = json.find('"', pos + 1);
        if (endQuote == string::npos) break;
        string val = json.substr(pos + 1, endQuote - pos - 1);
        push(val);
        pos = endQuote + 1;
    }
}