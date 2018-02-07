/*
Filename: expt.cpp

Implementation of the expt library of general-purpose exceptions.
*/

#include <string>

#include "expt.h"

using namespace expt;

// Classes

// Exception
  
  Exception::~Exception() {}
  
  Exception::Exception() {
    
    // Initialize essential fields
    _message = "";
    
  }
  
  Exception::Exception(std::string message) {
    
    // Initialize essential fields
    _message = message;
    
  }
  
  Exception::Exception(const Exception& original) {
    
    // Initialize essential fields
    _message = original._message;
    
  }
  
  Exception& Exception::operator=(const Exception& other) {
    
    // Field assignment
    _message = other._message;
    
    return *this;
    
  }
  
  std::string Exception::message() const {
    
    return _message;
    
  }
  
  void Exception::set_message(std::string new_message) {
    
    _message = new_message;
    
  }

// ValueError
  
  ValueError::~ValueError() {}
  
  ValueError::ValueError() {
    
    // Initialize essential fields
    _message = "";
    
  }
  
  ValueError::ValueError(std::string message) {
    
    // Initialize essential fields
    _message = message;
    
  }
  
  ValueError::ValueError(const ValueError& original) {
    
    // Initialize essential fields
    _message = original._message;
    
  }
  
  ValueError& ValueError::operator=(const ValueError& other) {
    
    // Transfer fields
    _message = other._message;
    
    return *this;
    
  }
  
  ValueError::operator Exception() {
    
    return Exception(_message);
    
  }

// IndexError
  
  IndexError::~IndexError() {}
  
  IndexError::IndexError() {
    
    // Initialize essential fields
    _message = "";
    
  }
  
  IndexError& IndexError::operator=(const IndexError& other) {
    
    return *this;
    
  }
  
  IndexError::operator ValueError() {
    
    return ValueError();
    
  }
  
  IndexError::operator Exception() {
    
    return Exception();
    
  }