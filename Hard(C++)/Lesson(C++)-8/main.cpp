
#include "test_mod.h"

#ifdef ENABLE_GOOGLE_TEST_SECTION
TEST(Lesson_08, test_for_lesson7_Task3) {
  TestModule::lesson7_Task3();
}
#endif //ENABLE_GOOGLE_TEST_SECTION

// --------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  UNUSED(argc)
  UNUSED(argv)

  setlocale(LC_ALL, "Russian");

#ifdef ENABLE_GOOGLE_TEST_SECTION
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  return 0;
#endif
}
