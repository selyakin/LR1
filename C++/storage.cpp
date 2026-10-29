#include "storage.h" 
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

static string escapeName(const string& name) {
    string res;
    for (char c : name) {
        if (c == '"') res += "\\\"";
        else if (c == '\\') res += "\\\\";
        else res += c;
    }
    return res;
}

void saveToFile(const string& filename) {
    ofstream out(filename);
    if (!out) throw runtime_error("Cannot open file for writing: " + filename);

    out << "{\n";

    // Arrays
    out << "  \"M\": {";
    bool first = true;
    for (const auto& [name, arr] : arrays) {
        if (!first) out << ", ";
        out << "\"" << escapeName(name) << "\": " << arr.toJson();
        first = false;
    }
    out << "},\n";

    // SLL
    out << "  \"F\": {";
    first = true;
    for (const auto& [name, s] : slls) {
        if (!first) out << ", ";
        out << "\"" << escapeName(name) << "\": " << s.toJson();
        first = false;
    }
    out << "},\n";

    // DLL
    out << "  \"L\": {";
    first = true;
    for (const auto& [name, d] : dlls) {
        if (!first) out << ", ";
        out << "\"" << escapeName(name) << "\": " << d.toJson();
        first = false;
    }
    out << "},\n";

    // Stack
    out << "  \"S\": {";
    first = true;
    for (const auto& [name, st] : stacks) {
        if (!first) out << ", ";
        out << "\"" << escapeName(name) << "\": " << st.toJson();
        first = false;
    }
    out << "},\n";

    // Queue
    out << "  \"Q\": {";
    first = true;
    for (const auto& [name, q] : queues) {
        if (!first) out << ", ";
        out << "\"" << escapeName(name) << "\": " << q.toJson();
        first = false;
    }
    out << "},\n";

    // Tree
    out << "  \"T\": {";
    first = true;
    for (const auto& [name, t] : trees) {
        if (!first) out << ", ";
        out << "\"" << escapeName(name) << "\": " << t.toJson();
        first = false;
    }
    out << "}\n";

    out << "}\n";
    out.close();
}


void loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) return;
    stringstream buffer;
    buffer << in.rdbuf();
    string json = buffer.str();
    in.close();


    const string keys[] = {"M", "F", "L", "S", "Q", "T"};
    for (const auto& key : keys) {
        size_t keyPos = json.find("\"" + key + "\"");
        if (keyPos == string::npos) continue;
        
        //  начало объекта
        size_t objStart = json.find('{', keyPos);
        if (objStart == string::npos) continue;
        
        //  пары "name": [...]
        size_t pos = objStart + 1;
        while (true) {
            // Имя
            size_t nameStart = json.find('"', pos);
            if (nameStart == string::npos) break;
            size_t nameEnd = json.find('"', nameStart + 1);
            if (nameEnd == string::npos) break;
            string name = json.substr(nameStart + 1, nameEnd - nameStart - 1);
            
            // Массив
            size_t arrStart = json.find('[', nameEnd);
            if (arrStart == string::npos) break;
            size_t arrEnd = json.find(']', arrStart);
            if (arrEnd == string::npos) break;
            
            string arrJson = json.substr(arrStart, arrEnd - arrStart + 1);
            
            if (key == "M") arrays[name].fromJson(arrJson);
            else if (key == "F") slls[name].fromJson(arrJson);
            else if (key == "L") dlls[name].fromJson(arrJson);
            else if (key == "S") stacks[name].fromJson(arrJson);
            else if (key == "Q") queues[name].fromJson(arrJson);
            else if (key == "T") trees[name].fromJson(arrJson);
            
            pos = arrEnd + 1;
            size_t nextComma = json.find(',', pos);
            size_t nextBrace = json.find('}', pos);
            if (nextBrace != string::npos && (nextComma == string::npos || nextBrace < nextComma)) break;
        }
    }
}