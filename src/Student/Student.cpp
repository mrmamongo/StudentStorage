//
// Created by MrMam on 08.05.2022.
//

#include "Student.h"
#include <sstream>
#include <regex>

std::string Student::ToString() const {
    std::stringstream ss;
    ss << "Name: " << _name << " Group: " << _group._to_string() << " Average: " << _average << " Marks: ";
    for (const auto& mark_pair : _marks) {
        ss << mark_pair.first << ":" << mark_pair.second << " ";
    }
    return ss.str();
}

Student Student::FromString(std::string str) {
    static std::stringstream subjects;
    if (subjects.str().empty()) {
        subjects << "((";
        for (auto const &sub: Subject::_names()) {
            subjects << sub << "|";
        }
        subjects << ")\\:\\d+)";
    }
    static std::regex subject_regex(subjects.str(), std::regex_constants::ECMAScript);
    std::string name;
    std::vector<std::pair<Subject, Mark>> marks;
    name.assign(str.substr(0, str.find_first_of(' ')));
    str = str.substr(name.size() + 1);
    auto group_p = str.find_first_of(' ');
    Group_t group = Group_t::_from_string(str.substr(0, group_p).data());
    str = str.substr(group_p + 1);
    for (auto subject_start = std::sregex_iterator(str.begin(), str.end(), subject_regex);
         subject_start != std::sregex_iterator(); ++subject_start) {
        auto sub_string = subject_start->str();
        Subject s = Subject::_from_string(sub_string.substr(0, sub_string.find_first_of(':')).data());
        Mark m = Mark::_from_integral(atoi(sub_string.substr(sub_string.find_first_of(':') + 1).data()));
        marks.emplace_back(std::make_pair(s, m));
    }

    return {name, group, std::move(marks)};
}