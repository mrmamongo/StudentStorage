//
// Created by MrMam on 08.05.2022.
//

#pragma once

#include "../enums/Enums.h"
#include <vector>

BETTER_ENUM(Group_t, uint16_t, first, second, third, fourth, fifth, UNDEFINED)
BETTER_ENUM(Mark, uint16_t, A = 6, B = 5, C = 4, D = 3, E = 2, F = 1)
BETTER_ENUM(Subject, uint16_t, Maths, Programming, Web)

class Student {
public:
    Student(): _group(Group_t::UNDEFINED) {};

    explicit Student(std::string name): _name(std::move(name)), _group(Group_t::UNDEFINED){};

    Student(std::string name, Group_t group, std::vector<std::pair<Subject, Mark>> marks = {})
        : _name(std::move(name)), _group(group), _marks(std::move(marks)){
        for (auto const& mark : _marks) {
            _average += (float)mark.second._to_integral();
        }
        _average /= (float)_marks.size();
    }
public:
    [[nodiscard]] std::string ToString() const;
    [[nodiscard]] static Student FromString(std::string);

    [[nodiscard]] const std::string& Name() const { return _name; }
    [[nodiscard]] Group_t Group() const { return _group; }
    [[nodiscard]] float Average() const { return _average; }
    std::vector<std::pair<Subject, Mark>>&  Marks() { return _marks; }

    void SetName(std::string name) { _name = std::move(name); }
    void SetGroup(Group_t group) { _group = group; }
    void SetAverage(float average) { _average = average; }
    void SetMarks(std::vector<std::pair<Subject, Mark>> marks) { _marks = std::move(marks); }

private:
    std::string _name;
    Group_t _group = Group_t::UNDEFINED;
    float _average = 0;
    std::vector<std::pair<Subject, Mark>> _marks;
};
