#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>

class Array{
public:
    Array(std::initializer_list<std::string> list);
    Array();        
    Array(std::size_t size);
    Array(const Array& initialArr);
    Array& operator=(const Array& initialArr);
    ~Array();

    void reserve(std::size_t newCp);
    void push(const std::string& value);
    void insert(std::size_t index, const std::string& value);
    std::string get(std::size_t index) const;
    void remove(std::size_t index);
    void replace(std::size_t index, const std::string& value);
    std::size_t size() const;
    void print() const;

    std::string toJson() const;
    void fromJson(const std::string& json);

private:
    std::string* data;
    std::size_t sz;
    std::size_t cp;
};