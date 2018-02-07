/*
Filename: expt.h

This file contains the definitions for the expt library.
*/

#include <string>

#ifndef EXPT_HEADER
#define EXPT_HEADER

namespace expt {

  // Classes

  class Exception {
    
    /*
    This class is a basic, all-purpose exception.  It should be used as a base 
    class for all other exceptions, and it can be used itself in situations 
    where no other exception seems to fit.  It includes an optional error 
    message with which to provide information about why the exception was 
    thrown.
    */
    
    protected:
      
      std::string _message;
       
        /*
        An error message to provide more information about what went wrong and 
        caused this exception to be thrown.
        */
    
    public:
      
      ~Exception();
         
        /*
        Destructor
        */
      
      Exception();
        
        /*
        Empty constructor
        
        This will create an Exception with no message.
        */
      
      Exception(std::string message);
        
        /*
        Standard constructor
        
        Parameters:
          message: An error message with which to provide more information 
                    about why the exception was thrown.
        */
      
      Exception(const Exception& original);
       
        /*
        Copy constructor
        
        Parameters:
          original: Exception to be copied
        */
      
      virtual Exception& operator=(const Exception& other);
       
        /*
        Standard field-wise assignment
        
        Parameters:
          other: Other Exception to be copied
        */
    
      virtual std::string message() const;
        
        /*
        Returns the error message associated with the exception.
        */
    
      virtual void set_message(std::string new_message);
       
        /*
        Replaces the Exception's error message with the one given.
        
        Parameters:
          new_message: The new error message
        */
    
  };
  
  class ValueError : public Exception {
    
    /*
    This exception should be thrown when a function is passed an argument that 
    is of the correct type but is not acceptable for some other reason.
    
    Examples of situations when this exception should be used:
      A negative number is passed when that wouldn't make sense.
      A zero is passed when that wouldn't make sense.
      Too large or small of a number is passed.
    */
    
    public:
      
      ~ValueError();
        
        /*
        Destructor
        */
      
      ValueError();
        
        /*
        Empty constructor
        
        Will have no error message.
        */
      
      ValueError(std::string message);
        
        /*
        Standard constructor
        
        Parameters:
          message: An error message to give the user some information about why
                    the exception was thrown
        */
      
      ValueError(const ValueError& original);
        
        /*
        Copy constructor
        
        Parameters:
          original: Other ValueError to be copied
        */
      
      ValueError& operator=(const ValueError& other);
        
        /*
        Standard field-wise assignment
        
        Parameters:
          other: Other ValueError to be copied
        */
      
      operator Exception();
        
        /*
        Creates a general exception with the same message as the ValueError.
        */
    
  };
  
  class IndexError : public ValueError {
    
    /*
    An exception to be used when a bounds check on an index fails.
    */
    
    public:
      
      ~IndexError();
        
        /*
        Destructor
        */
      
      IndexError();
        
        /*
        Empty constructor
        */
      
      IndexError& operator=(const IndexError& other);
        
        /*
        No actual assignment is needed because no data is stored in an 
        IndexError.  This operator is here just to allow the following line of 
        code:
        
          IndexError exception = IndexError();
        */
      
      operator ValueError();
        
        /*
        ValueError will have no message.
        */
      
      operator Exception();
        
        /*
        Exception will have no message.
        */
    
  };

};

#endif