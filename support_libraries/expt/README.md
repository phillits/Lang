## Expt {#top}

This is a small library of basic general-purpose exceptions for use throughout 
the project.  

##### Contents {#contents}

[`class Exception`](#exception)
[`class ValueError`](#value_error)
[`class IndexError`](#index_error)

### Exception {#exception}

This class is an all-purpose exception.  It is the base class for all other 
exceptions in this project.  It should be used directly in any situation in 
which no other exception would make sense, although that should be pretty rare.

##### Constructors {#exception/constructors}
  
`Exception()`                           empty constructor
`Exception(std::string message)`        standard constructor
`Exception(const Exception& original)`  copy constructor

##### Member functions {#exception/member_functions}
  
`std::string message()`
  Returns the error message associated with the exception.
  
`void set_message(std::string new_message)`
  Replaces the `Exception`'s error message with the one given.

##### Operators implemented {#exception/operators}

`=` assignment

### ValueError {#value_error}

`ValueError` should be thrown when a function is passed an argument that is of 
the proper type but has a value is not acceptable.  For example, it could be 
used to prevent the passing of negative values or of inputs that are too large.

##### Constructors {#value_error/constructors}

`ValueError()`                           empty constructor
`ValueError(std::string message)`        standard constructor
`ValueError(const ValueError& original)` copy constructor

##### Member functions {#value_error/member_functions}

See [Exception](#exception/member_functions) for inherited functions.

##### Operators implemented {#value_error/operators}

`=` assignment

### IndexError {#index_error}

`IndexError` is a specific type of ValueError to be used for bounds-checking 
bracket operators or any other function that takes an index within a container 
as an argument.  `IndexError` should be thrown when an index is passed that is 
out of bounds.  Because this usage is so specific, `IndexError` does not use the 
`_message` field provided by the `Exception` class, from which it inherits.  

##### Constructors {#index_error/constructors}

`IndexError()`  empty constructor

##### Member functions {#index_error/member_functions}

See [ValueError](#value_error/member_functions) for inherited functions.

##### Operators implemented {#index_error/operators}

`=` assignment