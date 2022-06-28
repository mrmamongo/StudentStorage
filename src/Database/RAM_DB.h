//
// Created by MrMam on 09.05.2022.
//
#pragma once
#include "IDB.h"

class RAM_DB : public IDB {
private:
public:
    RAM_DB() = default;
public:
    bool Empty() override { return _data.empty(); }

    const std::list<Student>& Select() override;
    std::list<const Student*> Select(Where* where) override;

    bool Insert(Student const& s) override;
    bool Insert(Student && s) override;
    void Insert(std::list<Student> const& s) override;
    void Insert(std::list<Student>&& s) override;
    bool Delete(std::pair<std::string, Group_t> student) override;
    void DropAll() override;
private:
    std::list<Student> _data;
};
