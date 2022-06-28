//
// Created by MrMam on 09.05.2022.
//

#include "RAM_DB.h"

const std::list<Student>& RAM_DB::Select() {
    return _data;
}
std::list<const Student*> RAM_DB::Select(Where* where) {
    std::list<const Student*> out;
    for (const auto& student : _data) {
        if (where->exec(student)) {
            out.emplace_back(&student);
        }
    }
    return out;
}

bool RAM_DB::Insert(Student const& s) {
    if (std::find_if(_data.begin(), _data.end(), [&s](const auto rhs) {
        return rhs.Name() == s.Name() && rhs.Group() == s.Group();
    }) != _data.end()) {
        return false;
    }

    _data.emplace_back(std::move(s));
    return true;
}
bool RAM_DB::Insert(Student && s) {
    if (std::find_if(_data.begin(), _data.end(), [&s](const auto rhs) {
        return rhs.Name() == s.Name() && rhs.Group() == s.Group();
    }) != _data.end()) {
        return false;
    }

    _data.emplace_back(std::move(s));
    return true;
}

void RAM_DB::Insert(std::list<Student> const& s) {
    for (const auto& stud: s) {
        Insert(stud);
    }
}
void RAM_DB::Insert(std::list<Student> && s) {
    for (const auto& stud: s) {
        Insert(stud);
    }
}

bool RAM_DB::Delete(std::pair<std::string, Group_t> student) {
    const auto found = std::find_if(_data.begin(), _data.end(), [&student](const auto rhs) {
        return rhs.Name() == student.first && rhs.Group() == student.second;
    });
    if (found == _data.end()) {
        return false;
    }
    _data.erase(found);
    return true;
}

void RAM_DB::DropAll() {
    _data.clear();
}
