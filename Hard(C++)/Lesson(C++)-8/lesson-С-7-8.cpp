
#include "lesson-Ñ-7-8.h"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>

using namespace std;

static const auto FILEPATH{"./data.bin"};
static const auto STRING_SEP{'\0'};

// --------------------------------------------------------------------------------------


template <typename T>
void value2Bin(ostream &output, T const &value) {
  output.write(reinterpret_cast<const char*>(&value), streamsize(sizeof(value)));
}
void value2Bin(ostream &output, const std::string &value) {
  output.write(reinterpret_cast<const char*>(value.c_str()),
               streamsize(sizeof(char) * value.size() + 1u));
}

// --------------------------------------------------------------------------------------

template <typename T>
void bin2Value(istream &input, T &value) {
  input.read(reinterpret_cast<char*>(&value), streamsize(sizeof(value)));
}
void bin2Value(istream &input, string &value) {
  getline(input, value, STRING_SEP);
}

namespace lesson_7 {

// --------------------------------------------------------------------------------------
ostream &operator<<(ostream &output, const FullName &obj) {
  
  value2Bin(output, obj.surname);
  value2Bin(output, obj.name);
  if (obj.patronymic.has_value()) {
    value2Bin(output, obj.patronymic.value());
  }
  else { 
    output << STRING_SEP;
  }
  return output;
}

// --------------------------------------------------------------------------------------
std::istream &operator>>(std::istream &input, FullName &obj) {

  bin2Value(input, obj.surname);
  bin2Value(input, obj.name);
  string patronymic;
  bin2Value(input, patronymic);
  if (patronymic.empty()) {
    obj.patronymic = nullopt;
  }
  else {
    obj.patronymic = patronymic;
  }
  return input;
}

// --------------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &output, const Student &obj) {
  output << obj.full_name;
  
  value2Bin(output, obj.scores.size());
 
  for_each(obj.scores.cbegin(), obj.scores.cend(),
           [&output](const auto &value) { value2Bin(output, value); }
  );
  value2Bin(output, obj.average_score);
  return output;
}

// --------------------------------------------------------------------------------------
std::istream &operator>>(std::istream &input, Student &obj) {
  input >> obj.full_name;
  size_t scores_size;

  bin2Value(input, scores_size);

  obj.scores.resize(scores_size);
  for_each(obj.scores.begin(), obj.scores.end(),
           [&input](auto &value) { bin2Value(input, value); }
  );
  bin2Value(input, obj.average_score);
  return input;
}

// --------------------------------------------------------------------------------------
StudentsGroup::StudentsGroup(const std::vector<Student> &students) : m_students(students)
{}

// --------------------------------------------------------------------------------------
void StudentsGroup::Open() {
  ifstream input(FILEPATH, ios::binary);
  Clear();
  if (input.is_open()) {

    size_t students_size;
    bin2Value(input, students_size);
   
    m_students.resize(students_size);
    for_each(m_students.begin(), m_students.end(), [&input](auto &element) {
      input >> element;
    });
    input.close();
  }
}

// --------------------------------------------------------------------------------------
void StudentsGroup::Save() {
  ofstream output(FILEPATH, ios::binary);
  if (output.is_open()) {
    
    value2Bin(output, m_students.size());

    copy(m_students.cbegin(), m_students.cend(),
         ostream_iterator<Student>(output, ""));
    output.close();
  }
}

// --------------------------------------------------------------------------------------
double StudentsGroup::GetAverageScore(const FullName &name) const {
  auto student{Find(name)};
  return (nullptr == student ? 0. : student->average_score);
}

// --------------------------------------------------------------------------------------
string StudentsGroup::GetAllInfo(const FullName &name) const {
  auto student{Find(name)};
  ostringstream oss;
  if (student) {
    oss << "Surname: " << student->full_name.surname << endl;
    oss << "Name: " << student->full_name.name << endl;
    if (student->full_name.patronymic.has_value()) {
      oss << "Patronymic: " << student->full_name.patronymic.value() << endl;
    }
    oss << "Scores: ";
    copy(student->scores.cbegin(), student->scores.cend(),
         ostream_iterator<unsigned>{oss, ","});
    oss.seekp(-1, ios_base::end);
    oss << endl;
    oss << "Average score: " << student->average_score << endl;
  }
  return oss.str();
}

// --------------------------------------------------------------------------------------
string StudentsGroup::GetAllInfo() const {
  ostringstream oss;
  for_each(m_students.cbegin(), m_students.cend(), [this, &oss](const auto &element) {
    oss << "-----------------" << endl;
    oss << GetAllInfo(element.full_name);
  });
  return oss.str();
}

// --------------------------------------------------------------------------------------
void StudentsGroup::Clear() {
  m_students.clear();
}

// --------------------------------------------------------------------------------------
const Student *StudentsGroup::Find(const FullName &name) const {
  auto res = find_if(m_students.cbegin(), m_students.cend(),
                     [&name](const auto &element) -> bool {
    return (element.full_name.surname == name.surname) &&
           (element.full_name.name == name.name) &&
           (element.full_name.patronymic == name.patronymic);
  });
  return (res != m_students.cend() ? res.operator->() : nullptr);
}

} 
