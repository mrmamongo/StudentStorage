//
// Created by MrMam on 09.05.2022.
//
#pragma once
#include <list>

#include "../Student/Student.h"

class Where {
public:
    virtual ~Where() = 0;
    virtual bool exec(const Student& s) = 0;
};

class IDB {
public:
    IDB() = default;

    virtual ~IDB() = default;

    IDB(const IDB &other) = delete;

    IDB &operator=(const IDB &other) = delete;

public:
    virtual bool Empty() = 0;

    virtual const std::list<Student>& Select() = 0;

    virtual std::list<const Student*> Select(Where *where) = 0;

    virtual bool Insert(Student const& s) = 0;
    virtual bool Insert(Student && s) = 0;

    virtual void Insert(std::list<Student> const&) = 0;
    virtual void Insert(std::list<Student> &&) = 0;

    virtual bool Delete(std::pair<std::string, Group_t> student) = 0;

    virtual void DropAll() = 0;
};

class Container {
public:
    Container() = default;
    Container(IDB* db): _db(db) {}

    void changeDatabase(IDB* db) {
        if (!db) return;
        if (!_db) { _db = db; return;}
        db->Insert(std::move(_db->Select()));
        delete _db;
        _db = db;
    }

    IDB*& operator->() {
        return _db;
    }

    ~Container() {
        delete _db;
    }
private:
    IDB* _db = nullptr;
};