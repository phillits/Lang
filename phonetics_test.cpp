/*
Filename: phonetics_test.cpp

Test code for the phonetics portion of the lang library
*/

#include <gtest/gtest.h>

#include "phonetics.h"

using namespace lang;

TEST(ImpossibleArticulationTest, empty_constructor) {
  
  // Fields initialize as expected
  ImpossibleArticulation impossible_articulation1;
  EXPECT_EQ("", impossible_articulation1.message());
  
}

TEST(ImpossibleArticulationTest, standard_constructor) {
  
  // Fields initialize as expected
  ImpossibleArticulation impossible_articulation1("Voiced phonation paired with voiceless vot.");
  EXPECT_EQ("Voiced phonation paired with voiceless vot.", impossible_articulation1.message());
  
  ImpossibleArticulation impossible_articulation2("");
  EXPECT_EQ("", impossible_articulation2.message());
  
  ImpossibleArticulation impossible_articulation3("askdfjaklf");
  EXPECT_EQ("askdfjaklf", impossible_articulation4.message());
  
}

TEST(ImpossibleArticulationTest, copy_constructor) {
  
  // Fields initialize as expected
  ImpossibleArticulation impossible_articulation1("Unknown error");
  ImpossibleArticulation impossible_articulation2(impossible_articulation1);
  EXPECT_EQ(impossible_articulation1.message(), impossible_articulation2.message());
  
  ImpossibleArticulation impossible_articulation3("");
  ImpossibleArticulation impossible_articulation4(impossible_articulation1);
  EXPECT_EQ(impossible_articulation3.message(), impossible_articulation3.message());
  
}

TEST(ImpossibleArticulationTest, exception_conversion) {
  
  // Assignment
  expt::Exception exception1;
  ImpossibleArticulation impossible_articulation1("Voiced glottal stop");
  exception1 = impossible_articulation1;
  EXPECT_EQ(impossible_articulation1.message(), exception1.message());
  
  // Explicit cast
  ImpossibleArticulation impossible_articulation2("Impossible manner-place combination");
  expt::Exception exception2 = (expt::Exception) impossible_articulation2;
  
}

TEST(ImpossibleArticulationTest, value_error_conversion) {
  
  // Assignment
  expt::ValueError value_error1;
  ImpossibleArticulation impossible_articulation1("");
  value_error1 = impossible_articulation1;
  EXPECT_EQ(impossible_articulation1.message(), value_error1.message());
  
  // Explicit cast
  ImpossibleArticulation impossible_articulation2();
  expt::ValueError value_error2 = (expt::ValueError) impossible_articulation2;
  EXPECT_EQ(impossible_articulation2.message(), value_error2.message());
  
}

TEST(PhoneTest, nasalization) {
  
  Vowel vowel1;
  EXPECT_EQ(Phone::oral, vowel1.nasalization());
  
  Consonant consonant1;
  EXPECT_EQ(Phone::oral, consonant1.nasalization());
  
}

TEST(PhoneTest, set_nasalization) {
  
  Vowel vowel1;
  vowel1.set_nasalization(Phone::oral);
  EXPECT_EQ(Phone::oral, vowel1.nasalization());
  
  vowel1.set_nasalization(Phone::nasal);
  EXPECT_EQ(Phone::nasal, vowel1.nasalization());
  
  Consonant consonant;
  consonant1.set_nasalization(Phone::strongly_nasal);
  EXPECT_EQ(Phone::strongly_nasal, consonant1.nasalization());
  
}

TEST(PhoneTest, is_nasal) {
  
  Vowel vowel1;
  vowel1.set_nasalization(Phone::oral);
  EXPECT_FALSE(vowel1.is_nasal());
  
  vowel1.set_nasalization(Phone::nasal);
  EXPECT_TRUE(vowel1.is_nasal());
  
}

TEST(PhoneTest, phonation) {
  
  Vowel vowel1;
  vowel1.set_phonation(Phone::voiceless);
  EXPECT_EQ(Phone::voiceless, vowel1.phonation());
  
  vowel1.set_phonation(Phone::modal);
  EXPECT_EQ(Phone::modal, vowel1.phonation());
  
  Consonant consonant1;
  consonant1.set_phonation(Phone::strident);
  EXPECT_EQ(Phone::strident, consonant1.phonation());
  
}

TEST(PhoneTest, set_phonation) {
  
  Vowel vowel1;
  vowel1.set_phonation(Phone::voiceless);
  EXPECT_EQ(Phone::voiceless, vowel1.phonation());
  
  vowel1.set_phonation(Phone::breathy);
  EXPECT_EQ(Phone::breathy, vowel1.phonation());
  
  Consonant consonant1;
  consonant1.set_phonation(Phone::slack);
  EXPECT_EQ(Phone::slack, consonant1.phonation());
  
  // ImpossibleArticulation thrown when expected
  EXPECT_THROW(ImpossibleArticulation) {
    consonant1.set_vot(Consonant::completely_voiced);
    consonant1.set_phonation(Phone::voiceless);
  }
  
  EXPECT_THROW(ImpossibleArticulation) {
    consonant1.set_place(Consonant::glottal);
    consonant1.set_manner(Consonant::stop);
    consonant1.set_phonation(Phone::modal);
  }
  
}

TEST(PhoneTest, incr_phonation) {
  
  Vowel vowel1;
  vowel1.set_phonation(Phone::voiceless);
  vowel1.incr_phonation();
  EXPECT_EQ(Phone::breathy, vowel1.phonation());
  
  vowel1.incr_phonation(2);
  EXPECT_EQ(Phone::modal, vowel1.phonation());
  
  // ImpossibleArticulation thrown when expected
  EXPECT_THROW(ImpossibleArticulation) {
    Consonant consonant1(Consonant::stop, 
                         Consonant::glottal, 
                         Phone::voiceless, 
                         Consonant::moderately_aspirated);
    consonant1.incr_phonation(1);
  }
  
}

TEST(PhoneTest, decr_phonation) {
  
  Consonant consonant1;
  consonant1.set_phonation(Phone::stiff);
  consonant1.decr_phonation();
  EXPECT_EQ(Phone::modal, consonant1.phonation());
  
  consonant1.decr_phonation(3);
  EXPECT_EQ(Phone::voiceless, consonant1.phonation());
  
}

TEST(PhoneTest, length) {
  
  Consonant consonant1;
  consonant1.set_length(1.0);
  EXPECT_EQ(1.0, consonant1.length());
  
  consonant1.set_length(2.0);
  EXPECT_EQ(2.0, consonant1.length());
  
  Vowel vowel1;
  vowel1.set_length(0.5);
  EXPECT_EQ(0.5, vowel1.length());
  
}

TEST(PhoneTest, set_length) {
  
  Vowel vowel1;
  vowel1.set_length(1.0);
  EXPECT_EQ(1.0, vowel1.length());
  
  vowel1.set_length(2.0);
  EXPECT_EQ(2.0, vowel1.length());
  
  Consonant consonant1;
  consonant1.set_length(0.01);
  EXPECT_EQ(0.01, consonant1.length());
  
}

TEST(PhoneTest, lengthen) {
  
  Vowel vowel1;
  vowel1.set_length(1.0);
  vowel1.lengthen(0.5);
  EXPECT_EQ(1.5, vowel1.length());
  
  vowel1.lengthen(0.4);
  EXPECT_EQ(1.9, vowel1.length());
  
}

TEST(PhoneTest, shorten) {
  
  Consonant consonant1;
  consonant1.set_length(1.0);
  consonant1.shorten(0.1);
  EXPECT_EQ(0.9, consonant1.length());
  
  consonant1.shorten(0.05);
  EXPECT_EQ(0.85, consonant1.length());
  
}

TEST(PhoneTest, double_length) {
  
  Vowel vowel1;
  vowel1.set_length(1.0);
  vowel1.double_length();
  EXPECT_EQ(2.0, vowel1.length());
  
  Consonant consonant1;
  consonant1.set_length(0.5);
  consonant1.double_length();
  EXPECT_EQ(1.0, consonant1.length());
  
}

TEST(PhoneTest, halve_length) {
  
  Vowel vowel1;
  vowel1.set_length(1.0);
  vowel1.halve_length();
  EXPECT_EQ(0.5, vowel1.length);
  
  Consonant consonant1;
  consonant1.set_length(2.0);
  consonant1.halve_length();
  EXPECT_EQ(1.0, consonant1.length());
  
}

TEST(VowelTest, empty_constructor) {
  
  Vowel vowel1;
  
  // Fields initialize as expected
  EXPECT_EQ(Vowel::mid, vowel1.height());
  EXPECT_EQ(Vowel::central, vowel1.backness());
  EXPECT_EQ(Vowel::unrounded, vowel1.roundedness());
  EXPECT_FALSE(vowel1.is_nasal());
  EXPECT_FALSE(vowel1.is_r-colored());
  EXPECT_EQ(Phone::modal, vowel1.phonation());
  EXPECT_EQ(1.0, vowel1.length());
  
}

TEST(VowelTest, simple_constructor) {
  
  Vowel vowel1(Vowel::open, Vowel::front, Vowel::exolabial);
  
  // Fields initialize as expected
  EXPECT_EQ(Vowel::open, vowel1.height());
  EXPECT_EQ(Vowel::front, vowel1.backness());
  EXPECT_EQ(Vowel::exolabial, vowel1.roundedness());
  EXPECT_FALSE(vowel1.is_nasal());
  EXPECT_FALSE(vowel1.is_r-colored());
  EXPECT_EQ(Phone::modal, vowel1.phonation());
  EXPECT_EQ(1.0, vowel1.length());
  
}



int main() {
  
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  
}