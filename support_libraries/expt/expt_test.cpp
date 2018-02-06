/*
Filename: expt_test.cpp
Author:   Tyler Phillips
Date:     11/29/17

Test code for the expt library
*/

#include "expt.h"
#include <gtest/gtest.h>

using namespace expt;

TEST(ExceptionTest, empty_constructor) {
  
  // Fields initialize as expected
  Exception exception1;
  EXPECT_EQ("", exception1.message());
  
}

TEST(ExceptionTest, standard_constructor) {
  
  // Fields initialize as expected
  Exception exception1("Error");
  EXPECT_EQ("Error", exception1.message());
  
  Exception exception2("");
  EXPECT_EQ("", exception2.message());
  
  Exception exception3(" ");
  EXPECT_EQ(" ", exception3.message());
  
}

TEST(ExceptionTest, copy_constructor) {
  
  // Fields initialize as expected
  Exception exception1("Stop iteration");
  Exception exception2(exception1);
  EXPECT_EQ("Stop iteration", exception2.message());
  
  Exception exception3("-&\n1");
  Exception exception4(exception3);
  EXPECT_EQ("-&\n1", exception4.message());
  
}

TEST(ExceptionTest, assignment_operator) {
  
  // Fields transfer as expected
  Exception exception1("Keyboard interrupt");
  Exception exception2;
  exception2 = exception1;
  EXPECT_EQ("Keyboard interrupt", exception2.message());
  
  Exception exception3("Dog");
  exception1 = exception3;
  EXPECT_EQ("Dog", exception1.message());
  
}

TEST(ExceptionTest, get_message) {
  
  Exception exception1;
  exception1.set_message("cat");
  EXPECT_EQ("cat", exception1.message());
  
  exception1.set_message("Error");
  EXPECT_EQ("Error", exception1.message());
  
}

TEST(ExceptionTest, set_message) {
  
  Exception exception1;
  
  // Common cases
  exception1.set_message("Keyboard Interrupt");
  EXPECT_EQ("Keyboard Interrupt", exception1.message());
  
  exception1.set_message("Error");
  EXPECT_EQ("Error", exception1.message());
  
  // Empty string
  exception1.set_message("");
  EXPECT_EQ("", exception1.message());
  
  // White space
  exception1.set_message(" \n");
  EXPECT_EQ(" \n", exception1.message());
  
  // Nonalphabetic characters
  exception1.set_message("123#$%\0 --");
  EXPECT_EQ("123#$%\0 --", exception1.message());
  
  // Single character
  exception1.set_message("a");
  EXPECT_EQ("a", exception1.message());
  
  // Mixed case
  exception1.set_message("AaA");
  EXPECT_EQ("AaA", exception1.message());
  
  // Weird characters
  exception1.set_message("\n\t\0");
  EXPECT_EQ("\n\t\0", exception1.message());
  
  // Multiple words
  exception1.set_message("Hi, Conner!");
  EXPECT_EQ("Hi, Conner!", exception1.message());
  
}

TEST(ExceptionTest, overall) {
  
  bool exception_caught(false);
  
  try {
    throw Exception("Unknown Exception");
  }
  
  catch(Exception exception) {
    exception_caught = true;
    EXPECT_EQ("Unknown Exception", exception.message());
  }
  
  EXPECT_TRUE(exception_caught);
  
}

TEST(ValueErrorTest, empty_constructor) {
  
  // Fields initialize as expected
  ValueError value_error1;
  EXPECT_EQ("", value_error1.message());
  
}

TEST(ValueErrorTest, standard_constructor) {
  
  // Fields initialize as expected
  ValueError value_error1("Negative value passed.");
  EXPECT_EQ("Negative value passed.", value_error1.message());
  
  ValueError value_error2("Zero passed.");
  EXPECT_EQ("Zero passed.", value_error2.message());
  
}

TEST(ValueErrorTest, copy_constructor) {
  
  // Fields initialize as expected
  ValueError value_error1("");
  ValueError value_error2(value_error1);
  EXPECT_EQ(value_error1.message(), value_error2.message());
  
  ValueError value_error3("AaA");
  ValueError value_error4(value_error3);
  EXPECT_EQ(value_error3.message(), value_error4.message());
  
}

TEST(ValueErrorTest, assignment_operator) {
  
  // Fields transfer as expected
  ValueError value_error1("abc");
  ValueError value_error2;
  value_error2 = value_error1;
  EXPECT_EQ(value_error1.message(), value_error2.message());
  
  ValueError value_error3(" \t\n");
  ValueError value_error4;
  value_error4 = value_error3;
  EXPECT_EQ(value_error3.message(), value_error4.message());
  
}

TEST(ValueErrorTest, exception_cast) {
  
  // Message transfers as expected
  ValueError value_error1("123");
  Exception exception1;
  exception1 = value_error1;
  EXPECT_EQ(value_error1.message(), exception1.message());
  
  ValueError value_error2("~!@");
  Exception exception2;
  exception2 = (Exception) value_error2;
  EXPECT_EQ(value_error2.message(), exception2.message());
  
}

TEST(ValueErrorTest, overall) {
  
  bool exception_caught(false);
  try {
    throw ValueError("Value too large.");
  }
  catch(ValueError error) {
    exception_caught = true;
    EXPECT_EQ("Value too large.", error.message());
  }
  EXPECT_TRUE(exception_caught);
  
}

TEST(IndexErrorTest, empty_constructor) {
  
  // Fields initialize as expected
  IndexError index_error1;
  EXPECT_EQ("", index_error1.message());
  
}

TEST(IndexErrorTest, assignment_operator) {
  
  IndexError index_error1 = IndexError();
  
}

TEST(IndexErrorTest, value_error_cast) {
  
  IndexError index_error1;
  ValueError value_error1;
  value_error1 = index_error1;
  EXPECT_EQ("", value_error1.message());
  
  IndexError index_error2;
  ValueError value_error2;
  value_error2 = (ValueError) index_error2;
  EXPECT_EQ("", value_error2.message());
  
}

TEST(IndexErrorTest, exception_cast) {
  
  IndexError index_error1;
  Exception exception1;
  exception1 = index_error1;
  EXPECT_EQ("", exception1.message());
  
  IndexError index_error2;
  Exception exception2;
  exception2 = (Exception) index_error2;
  EXPECT_EQ("", exception2.message());
  
}

int main() {
  
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  
}