
#pragma once

#include <string>
#include <optional>
#include <vector>

namespace lesson_7 {

struct FullName;
struct Student;
class StudentsGroup;

// --------------------------------------------------------------------------------------
class IRepository {
public:
  IRepository() = default;
  virtual ~IRepository() = default;

  virtual void Open() = 0; 
  virtual void Save() = 0; 
};

// --------------------------------------------------------------------------------------
class IMethods {
public:
  IMethods() = default;
  virtual ~IMethods() = default;

  virtual double GetAverageScore(const FullName& name) const = 0;
  virtual std::string GetAllInfo(const FullName& name) const = 0;
  virtual std::string GetAllInfo() const = 0;
};

// --------------------------------------------------------------------------------------
struct FullName {
  std::string surname;
  std::string name;
  std::optional<std::string> patronymic;

  friend std::ostream& operator<<(std::ostream &output, const FullName &obj);
  friend std::istream& operator>>(std::istream &input, FullName &obj);
};

// --------------------------------------------------------------------------------------
struct Student {
  FullName full_name;
  std::vector<unsigned> scores;
  double average_score;

  friend std::ostream& operator<<(std::ostream &output, const Student &obj);
  friend std::istream& operator>>(std::istream &input, Student &obj);
};

// --------------------------------------------------------------------------------------
class StudentsGroup : public IRepository, public IMethods {
public:
  StudentsGroup(const std::vector<Student> &students);
  virtual ~StudentsGroup() = default;

  
  virtual void Open() override;
  virtual void Save() override;

  
  virtual double GetAverageScore(const FullName &name) const override;
  virtual std::string GetAllInfo(const FullName &name) const override;
  virtual std::string GetAllInfo() const override;

  
  void Clear();
  const Student *Find(const FullName &name) const;

private:
  std::vector<Student> m_students;
};

}  
