
#include "test.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <cstring>
#include <fstream>
#include <iomanip>
#include <tuple>
#include <deque>
#include <forward_list>
#include <random>
#include <map>
#include <thread>
#include <future>



#include "lesson-С-7-8.h"

#ifdef ENABLE_PROTOBUF_SECTION
#include "protobuf/data.pb.h"
#endif // ENABLE_PROTOBUF_SECTION

using namespace std;

// --------------------------------------------------------------------------------------
void TestModule::lesson7_Task2() {
#ifdef ENABLE_PROTOBUF_SECTION
  using namespace lesson_7;
  cout << "--- TASK 2 ---" << endl;

  // инициализируем данные
  pb::StudentGroup group;
  pb::FullName full_name;
  full_name.set_name("Petr");
  full_name.set_surname("Ivanov");

  auto student = group.add_students();
  student->add_scores(75);
  student->add_scores(25);
  student->add_scores(45);
  student->mutable_fullname()->Swap(&full_name);
  const auto &scores_ref{student->scores()};
  const auto average{
    accumulate(scores_ref.cbegin(), scores_ref.cend(), 0) / scores_ref.size()};
  student->set_average_score(average);

  cout << "Before serialization: " << endl;
  cout << group.DebugString() << endl;

  // выполняем сериализацию
  string data;
  group.SerializeToString(&data);

  // выполняем десериализацию
  group.Clear();
  group.ParseFromString(data);
  cout << "After deserialization: " << endl;
  cout << group.DebugString() << endl << endl;
#endif // ENABLE_PROTOBUF_SECTION
}

// --------------------------------------------------------------------------------------
void TestModule::lesson7_Task3() {
  using namespace lesson_7;
#ifndef ENABLE_GOOGLE_TEST_SECTION
  cout << "--- TASK 3 ---" << endl;
#endif //ENABLE_GOOGLE_TEST_SECTION

  auto getAverageScore = [](const auto &v) {
    return double(accumulate(v.cbegin(), v.cend(), 0)) / v.size();
  };

  // инициализируем данные
  FullName full_name_st1;
  full_name_st1.name = string{"Petr"};
  full_name_st1.surname = string{"Ivanov"};
  FullName full_name_st2;
  full_name_st2.name = string{"Nastya"};
  full_name_st2.surname = string{"Semenova"};
  full_name_st2.patronymic = string{"Sergeevna"};

  Student student_st1;
  student_st1.full_name = full_name_st1;
  student_st1.scores = {75, 25, 45};
  student_st1.average_score = getAverageScore(student_st1.scores);
  Student student_st2;
  student_st2.full_name = full_name_st2;
  student_st2.scores = {35, 50, 95};
  student_st2.average_score = getAverageScore(student_st2.scores);

  StudentsGroup group_A{{student_st1, student_st2}};
#ifndef ENABLE_GOOGLE_TEST_SECTION
  cout << "Before serialization: " << endl;
  cout << group_A.GetAllInfo() << endl;
#endif //ENABLE_GOOGLE_TEST_SECTION
  group_A.Save();

  StudentsGroup group_B{};
  group_B.Open();
#ifndef ENABLE_GOOGLE_TEST_SECTION
  cout << "After deserialization: " << endl;
  cout << group_B.GetAllInfo() << endl;
#else
  ASSERT_EQ(group_A.Size(), group_B.Size());
  const auto student_res_1 = group_B.Find(student_st1.full_name);
  ASSERT_TRUE(nullptr != student_res_1);
  const auto student_res_2 = group_B.Find(student_st2.full_name);
  ASSERT_TRUE(nullptr != student_res_2);
  
  for (size_t n{0u}; n < student_st1.scores.size(); ++n) {
    SCOPED_TRACE(n);
    ASSERT_EQ(student_st1.scores[n], student_res_1->scores[n]);
  }
  ASSERT_NEAR(student_st1.average_score,
              student_res_1->average_score,
              numeric_limits<double>::epsilon());
 
  for (size_t n{0u}; n < student_st2.scores.size(); ++n) {
    SCOPED_TRACE(n);
    ASSERT_EQ(student_st2.scores[n], student_res_2->scores[n]);
  }
  ASSERT_NEAR(student_st2.average_score,
              student_res_2->average_score,
              numeric_limits<double>::epsilon());
#endif //ENABLE_GOOGLE_TEST_SECTION
}
