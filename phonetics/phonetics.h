nea/*
Filename: phonetics.h

This header file contains the definitions of the phonetics portion of the lang 
library.

Contents:

  Classes:
    
    class ImpossibleArticulation
    class DecodingFailed
    class Phone
      enum Phonation
      enum Nasalization
    class Vowel
      enum Height
      enum Backness
      enum Roundedness
    class Consonant
      enum Manner
      enum Place
      enum VOT
      enum Mechanism
    class Tone
    class Syllable
    typedef PhoneticSequence
*/

#include <string>
#include <vector>
#include <initializer_list>

#include "expt.h"

#ifndef PHONETICS_HEADER
#define PHONETICS_HEADER

namespace lang {
  
  // Classes
  
  class ImpossibleArticulation : public expt::Exception {
    
    /*
    This exception should be thrown whenever an attempt is made to create a 
    phone that is considered impossible or elsewhere in phonetics when 
    something that would be impossible to create is created.
    */
    
    public:
      
      ~ImpossibleArticulation();
        
        /*
        Destructor
        */
      
      ImpossibleArticulation();
        
        /*
        Empty constructor
        
        This will produce an ImpossibleArticulation with no message.
        */
      
      ImpossibleArticulation(std::string message);
        
        /*
        Standard constructor
        
        Parameters:
          message: An error message to provide information about what caused 
                    this exception to be thrown.
        */
      
      ImpossibleArticulation(const ImpossibleArticulation& original);
        
        /*
        Copy constructor
        
        Parameters:
          original: Other ImpossibleArticulation to be copied
        */
      
      operator expt::Exception();
        
        /*
        Returns a generic exception with the same message.
        */
      
      operator expt::ValueError();
        
        /*
        Returns a ValueError with the same message.
        */
    
  };
  
  class Phone {
    
    /*
    This is an abstract class for all phones.  It includes the functionality 
    for length, phonation, and nasalization, which are shared between 
    consonants and vowels.
    
    Pure virtual functions that child classes must implement:
    
      virtual std::string description() const
    */
    
    public:
      
      enum Phonation {voiceless       = 0, 
                      breathy         = 1, 
                      slack           = 2, 
                      modal           = 3, 
                      stiff           = 4, 
                      creaky          = 5, 
                      glottal_closure = 6, 
                      faucalized      = 7, 
                      harsh           = 8, 
                      strident        = 9};
        
        /*
        This enumeration provides the options for phonation that are supported 
        by this library.  It includes seven different states of pure glottal 
        phonation as well as three common states of supra-glottal phonation: 
        faucalized, harsh, and strident.
        */
      
      enum Nasalization {oral           = 0, 
                         nasal          = 1, 
                         strongly_nasal = 2};
        
        /*
        This enumeration provides three options for nasalization.  It is 
        included in the Phone class so that it can be used by both vowels and 
        voiced consonants.
        */
    
    protected:
      
            
      Nasalization _nasalization;
      
        /*
        Nasalization is represented in this library using the set of options 
        provided by the enumeration Nasalization.
        */
      
      Phonation _phonation;
        
        /*
        Phonation is represented using the set of options provided by the 
        enumeration Phonation.
        */
      
      float _length;
        
        /*
        This library regards adjacent similar phones as equivalent to 
        lengthened phones.  For simplicity's sake, the convention should be to 
        combine similar phones into a single lengthened phone.  
        
        To avoid the hassle of recording and tracking precise time values for 
        each phone, length is measured here relative to a standard length of 
        1.0.  This standard can be measured either as the standard length for 
        the language in question or the average length of the other phones in 
        the utterance.
        */
    
    public:
      
      ~Phone();
        
        /*
        Destructor
        */
      
      Nasalization nasalization() const;
      
        /*
        Returns the nasalization of the phone.
        */
    
      void set_nasalization(Nasalization new_nasalization);
      
        /*
        Sets the nasalization of the phone to the value given.
        
        Parameters:
          new_nasalization: The new nasalization value
        */
      
      bool is_nasal() const;
      
        /*
        Returns true if the vowel is nasal or strongly_nasal and false if it is 
        oral.
        */
      
      Phonation phonation() const;
      
        /*
        Returns the phonation of the phone.
        */
    
      void set_phonation(Phonation new_phonation);
        
        /*
        Sets the phonation of the phone.
        
        Parameters:
          new_phonation: The new phonation for the phone
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new phonation given would 
                                  result in an impossible articulation given 
                                  the current state of the other fields of the 
                                  phone.
        */
      
      void incr_phonation(int val = 1);
        
        /*
        Increments the phonation according to the order of the Phonation 
        enumeration, which roughly corresponds to moving towards a closed 
        glottis.  Will go around the horn.
        
        Parameters:
          val: The number of places to move in the Phonation enumeration
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new phonation value would 
                                  result in an impossible articulation given 
                                  the current state of the phone's other 
                                  fields.
        */
      
      void decr_phonation(int val = 1);
        
        /*
        Decrements the phonation according to the order of the Phonation 
        enumeration, which roughly corresponds to moving towards an open 
        glottis.  Will go around the horn.
        
        Parameters:
          val: The number of places to move in the Phonation enumeration
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new phonation value would 
                                  result in an impossible articulation given 
                                  the current state of the phone's other 
                                  fields.
        */
      
      float length() const;
        
        /*
        Returns the length of the phone.
        */
      
      void set_length(float new_length);
        
        /*
        Sets the length of the phone.
        
        Parameters:
          new_length: The new length for the phone.  Must be > 0.
        
        Exceptions:
          ImpossibleArticulation: Thrown if new_length is <= 0.
        */
      
      void lengthen(float val);
        
        /*
        Lengthens the phone by the amount given.
        
        Parameters:
          val: The amount that will be added to the length
        */
      
      void shorten(float val);
        
        /*
        Shortens the phone by the amount given.
        
        Parameters:
          val: The amount that will be subtracted from the length
        
        Exceptions:
          ImpossibleArticulation: Thrown if the value given would cause the 
                                  length of the phone to be <= 0.
        */
      
      void double_length();
        
        /*
        Doubles the length of the phone.
        */
      
      void halve_length();
        
        /*
        Halves the length of the phone.
        */
      
      virtual std::string description() const = 0;
        
        /*
        Returns a string description of the phone which describes all of its 
        defining characteristics.
        */
    
  };
  
  class Vowel : public Phone {
    
    /*
    This class can represent any articulable vowel.  No child classes should be
    needed.
    */
    
    public:
      
      enum Height {open       = 0, 
                   near_open  = 1, 
                   open_mid   = 2, 
                   mid        = 3, 
                   close_mid  = 4, 
                   near_close = 5, 
                   close      = 6};
        
        /*
        This enumeration provides an easy means of passing common values for 
        vowel height.  These enumeration values will be cast as floats when 
        passed as a height argument.  The enumeration is designed so that the 
        integer values of each item in the enumeration correspond to the 
        correct value when used as a height.
        */
      
      enum Backness {front      = 0, 
                     near_front = 1, 
                     central    = 2, 
                     near_back  = 3, 
                     back       = 4};
        
        /*
        This enumeration provides an easy means of passing common values for 
        vowel backness.  These enumeration values will be cast as floats when 
        passed as a backness argument.  The enumeration is designed so that the
        integer values of each item in the enumeration correspond to the 
        correct value when used as a backness.
        */
      
      enum Roundedness {unrounded   = 0, 
                        exolabial   = 1, 
                        endolabial  = 2};
        
        /*
        This enumeration provides the set of options for vowel roundedness.  It
        provides one option for unrounded and two different types of rounded: 
        exolabial and endolabial.
        */
    
    protected:
      
      float _height;
        
        /*
        Vowel height is represented in this library by a number between 0.0 and
        6.0, with 0.0 being open and 6.0 being close.  Each integer in this 
        range corresponds to one of the seven IPA-recognized vowel heights.  
        
        _height must always be between 0.0 and 6.0, inclusive.  Any function 
        that modifies this field should check to ensure that it does not exceed
        this range.
        */
      
      float _backness;
        
        /*
        Vowel backness is represented in this library by a number between 0.0 
        and 4.0, with 0.0 being front and 4.0 being back.  Each integer in this
        range corresponds to one of the five IPA-recognized vowel backnesses.  
        
        _backness must always be between 0.0 and 4.0, inclusive.  Any function 
        that modifies this field should check that it does not exceed this 
        range.
        */
      
      Roundedness _roundedness;
        
        /*
        Vowel roundedness is represented in this library using the set of 
        options provided by the enumeration Roundedness.
        */
      
      bool _r_colored;
        
        /*
        This library classifies all vowels as either r-colored or not r-
        colored.  If this field is true, the vowel is r-colored.
        */
    
    public:
      
      ~Vowel();
        
        /*
        Destructor
        */
      
      Vowel();
      
        /*
        Empty constructor
      
        The default vowel is a Schwa.
      
        Default values of fields: 
        
        height:                  mid
        backness:                central
        roundedness:             unrounded
        nasalization:            oral
        r-colored:               no
        phonation:               modal
        length:                  1.0
        */
      
      Vowel(float height, float backness, Roundedness roundedness);
      
        /*
        Simple constructor
      
        This constructor allows common vowels to be constructed without 
        worrying about other parameters.  This constructor does not allow for 
        the construction of nasal, r_colored, long, or short vowels.  
      
        Default values of other parameters:
      
        nasalization:            oral
        r-colored:               no
        phonation:               modal
        length:                  1.0
        
        Parameters:
          height:       Vowel height.  Must be between 0.0 and 6.0, inclusive.
          backness:     Vowel backness.  Must be between 0.0 and 4.0, 
                        inclusive.
          roundedness:  Vowel roundedness
        
        Exceptions:
          ImpossibleArticulation: Thrown if a value is passed for height or 
                                  backness that is out of the ranges specified 
                                  above.
        */
    
    Vowel(float height, float backness, Roundedness roundedness, 
          Nasalization nasalization, bool r_colored, 
          Phonation phonation = modal, float length = 1.0);
      
      /*
      Detailed constructor
      
      This constructor allows the user to specify all parameters and create any
      vowel within the limitations of this library.
      
      Parameters:
        height:       Vowel height.  Must be between 0.0 and 6.0, inclusive.
        backness:     Vowel backness.  Must be between 0.0 and 4.0, inclusive.
        roundedness:  Vowel roundedness
        nasalization: The presence and level of nasalization in this vowel
        r_colored:    Whether this vowel is r-colored
        phonation:    The phonation of this vowel.  Cannot be glottal_closure.
        length:       The length of the vowel.  Must be > 0.
      
      Exceptions:
        ImpossibleArticulation: Thrown if a value is passed for height or 
                                backness that is outside of the ranges 
                                specified above, if a value is passed for 
                                length that is <= 0, or if glottal_closure is 
                                passed for phonation.
      */
    
    Vowel(const Vowel& original);
      
      /*
      Copy constructor
      
      Parameters:
        original: Vowel from which to construct this vowel
      */
    
    Vowel& operator=(const Vowel& other);
      
      /*
      Standard field-wise assignment
      */
    
    bool operator==(const Vowel& other);
      
      /*
      Vowels are equal if all of their fields are equal.
      */
    
    bool operator!=(const Vowel& other);
      
      /*
      Vowels are equal if all of their fields are equal.
      */
    
    std::string description() const;
      
      /*
      Returns a description of the vowel which specifies all of its defining 
      characteristics using standard IPA terminology.
      */
    
    float height() const;
      
      /*
      Returns the height of the vowel.  Height is represented as a number 
      between 0.0 and 6.0, inclusive, with 0.0 being open and 6.0 being close. 
      Each integer in this range represents one of the standard IPA-recognized 
      vowel heights.
      */
    
    void set_height(float new_height);
      
      /*
      Sets the height of the vowel to the value given.
      
      Parameters:
        new_height: The new vowel height.  Must be between 0.0 and 6.0, 
                    inclusive.  0.0 represents open, and 6.0 represents close.
      
      Exceptions:
        ImpossibleArticulation: Thrown if a value is passed for new_height that
                                is outside of the range specified above.
      */
    
    void raise(float val = 1.0);
      
      /*
      Increases the height of the vowel by the amount given.  If no value is 
      given, the height will increase by one IPA-recognized height.
      
      Parameters:
        val: The amount by which the height will increase.
      
      Exceptions:
        ImpossibleArticulation: Thrown if the value passed for val would cause 
                                the height to exceed 6.0.
      */
    
    void lower(float val = 1.0);
      
      /*
      Decreases the height of the vowel by the amount given.  If no value is 
      given, the height will decrease by one IPA-recognized height.
      
      Parameters:
        val: The amount by which the height will decrease.
      
      Exceptions:
        ImpossibleArticulation: Thrown if the value passed for val would cause 
                                the height of the vowel to be negative.
      */
    
    float backness() const;
      
      /*
      Returns the backness of the vowel.  Backness is represented as a number 
      between 0.0 and 4.0, inclusive.  0.0 represents front, and 4.0 represents
      back.
      */
    
    void set_backness(float new_backness);
      
      /*
      Sets the backness of the vowel to the value given.
      
      Parameters:
        new_backness: The new backness of the vowel.  Must be between 0.0 and 
                      4.0.  0.0 represents front, and 4.0 represents back.
      
      Exceptions:
        ImpossibleArticulation: Thrown if a value is passed for new_backness 
                                that exceeds the range specified above.
      */
    
    void move_back(float val = 1.0);
      
      /*
      Increases the backness of the vowel by the amount given.  If no value is 
      given, the backness will increase by one IPA-recognized degree of 
      backness.  
      
      Parameters:
        val: The amount by which the vowel's backness will increase.
      
      Exceptions:
        ImpossibleArticulation: Thrown if the value passed for val would cause 
                                the vowel's backness to exceed 4.0.
      */
    
    void move_forward(float val = 1.0);
      
      /*
      Decreases the backness of the vowel by the amount given.  If no value is 
      given, the backness will decrease by one IPA-recognized degree of 
      backness.
      
      Parameters:
        val: The amount by which the vowel's backness will decrease.
      
      Exceptions:
        ImpossibleArticulation: Thrown if the value passed for val would cause 
                                the vowel's backness to be negative.
      */
    
    Roundedness roundedness() const;
      
      /*
      Returns the roundedness of the vowel.
      */
    
    void set_roundedness(Roundedness new_roundedness);
      
      /*
      Sets the roundedness of the vowel to the value given.
      
      Parameters:
        new_roundedness: The new vowel roundedness
      */
    
    bool is_rounded() const;
      
      /*
      Returns true if roundedness is either exolabial or endolabial.  Returns 
      false if it is unrounded.
      */
    
    bool is_r_colored() const;
      
      /*
      Returns whether the vowel is r-colored.
      */
      
    void r_color();
      
      /*
      Makes the vowel r-colored.  If the vowel is already r-colored, nothing 
      will change.
      */
    
    void de_r_color();
      
      /*
      Makes the vowel not r-colored.  If the vowel is already not r-colored, 
      nothing will change.
      */
    
  };
  
  class Consonant : public Phone {
    
    /*
    This class can represent any articulable consonant, including non-pulmonic 
    consonants, within the limits of this library.  No child classes should be 
    needed.
    */
    
    public:
      
      enum Manner {lateral_flap         = 0, 
                   lateral_approximant  = 1, 
                   lateral_fricative    = 2, 
                   trill                = 3,
                   flap                 = 4, 
                   approximant          = 5, 
                   nsib_fricative       = 6, // non-sibilant fricative
                   sib_fricative        = 7, // sibilant fricative
                   stop                 = 8, 
                   nasal                = 9};
        
        /*
        This enumeration provides the set of options for manner of 
        articulation of consonants.
        */
      
      enum Place {bilabial                = 0, 
                  labiodental             = 1, 
                  dentolabial             = 2, 
                  bidental                = 3, 
                  apical_linguolabial     = 4, 
                  laminal_linguolabial    = 5, 
                  apical_lower_lip        = 6, 
                  laminal_lower_lip       = 7, 
                  interdental             = 8, 
                  apical_dental           = 9, 
                  laminal_dental          = 10, 
                  apical_alveolar         = 11, 
                  laminal_alveolar        = 12, 
                  apical_palato_alveolar  = 13, 
                  laminal_palato_alveolar = 14, 
                  apical_retroflex        = 15, 
                  laminal_retroflex       = 16, 
                  subapical_retroflex     = 17, 
                  alveolo_palatal         = 18, 
                  palatal                 = 19, 
                  velar                   = 20, 
                  uvular                  = 21, 
                  pharyngeal              = 22, 
                  epiglottal              = 23, 
                  glottal                 = 24};
        
        /*
        This enumeration provides the set of options for place of articulation 
        of consonants.
        */
      
      enum VOT {completely_voiced     = 0, 
                moderately_voiced     = 1, 
                weakly_voiced         = 2, 
                not_aspirated         = 3, 
                weakly_aspirated      = 4, 
                moderately_aspirated  = 5, 
                strongly_aspirated    = 6};
        
        /*
        This enumeration provides the set of options for voice-onset time of 
        consonants.
        */
      
      enum Mechanism {pul_eg      = 0, // pulmonic egressive
                      ejective    = 1, 
                      click       = 2, 
                      implosive   = 3};
        
        /*
        This enumeration provides the set of options for mechanism of 
        consonants.
        */
    
    protected:
      
      Manner _manner;
      
      Place _place;
      
      Place _secondary_articulation;
        
        /*
        If a consonant doesn't have a secondary articulation, this field should
        be set equal to the primary place of articulation.
        */
      
      VOT _vot;
        
        /*
        Voice-onset time
        */
      
      Mechanism _mechanism;
    
    public:
      
      ~Consonant();
        
        /*
        Destructor
        */
      
      Consonant();
        
        /*
        Empty constructor
        
        Default values of fields:
        
          manner of articulation:   stop
          place of articulation:    apical alveolar
          secondary articulation:   none
          phonation:                voiceless
          voice-onset time:         moderate aspiration
          airstream mechanism:      pulmonic egressive
          length:                   1.0
          nasalization:             oral
        */
      
      Consonant(Manner manner, Place place, Phonation phonation, VOT vot, 
                Nasalization nasalization = oral, Mechanism mechanism = pul_eg, 
                float length = 1.0);
        
        /*
        Standard constructor
        
        Parameters:
          manner:       Manner of articulation
          place:        Place of articulation
          phonation:    The phonation of this consonant
          vot:          Voice-onset time
          nasalization: Specifying this consonant as nasal or oral
          mechanism:    Airstream mechanism
          length:       The length of this consonant
        
        Exceptions:
          ImpossibleArticulation: Thrown if the arguments passed result in an 
                                  impossible consonant.
        */
      
      Consonant(const Consonant& original);
        
        /*
        Copy constructor
        
        Parameters:
          original: Consonant to be copied
        */
      
      Consonant& operator=(const Consonant& other);
        
        /*
        Standard field-wise assignment
        */
      
      bool operator==(const Consonant& other) const;
        
        /*
        Consonants are equal whose fields are equal.
        */
      
      bool operator!=(const Consonant& other) const;
        
        /*
        Consonants are equal whose fields are equal.
        */
      
      std::string description() const;
        
        /*
        Returns a string description of the consonant which specifies all of 
        its defining features.
        */
      
      Manner manner() const;
      
        /*
        Returns the manner of articulation of this consonant.
        */
      
      void set_manner(Manner new_manner);
        
        /*
        Sets the manner of articulation of this consonant to the value given.
        
        Parameters:
          new_manner: The new manner of articulation
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new manner of articulation 
                                  given would result in an impossible 
                                  consonant.
        */
      
      void incr_manner(int val = 1);
        
        /*
        Increments this consonant's manner of articulation upwards according to
        the order of the standard IPA table of pulmonic consonants, which also 
        corresponds to the order of the Manner enumeration.
        
        Parameters:
          val: The number of manners to increment
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new manner of articulation 
                                  would result in an impossible consonant.
        */
        
      void decr_manner(int val = 1);
        
        /*
        Decrements this consonant's manner of articulation downwards according 
        to the order of the standard IPA table of pulmonic consonants, which 
        also corresponds to the order of the Manner enumeration.
        
        Parameters:
          val: The number of manners to decrement
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new manner of articulation 
                                  would result in an impossible consonant.
        */
      
      Place place() const;
        
        /*
        Returns the place of articulation of this consonant.
        */
      
      void set_place(Place new_place);
        
        /*
        Sets the place of articulation of this consonant to the value given.
        
        Parameters:
          new_place: The new place of articulation
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new place of articulation given
                                  would result in an impossible consonant.
        */
      
      void incr_place(int val = 1);
        
        /*
        Increments this consonant's place of articulation rightwards according 
        to the order of the standard IPA table of pulmonic consonants, which also 
        corresponds to the order of the Place enumeration.
        
        Parameters:
          val: The number of places to increment
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new place of articulation would
                                  result in an impossible consonant.
        */
      
      void decr_place(int val = 1);
        
        /*
        Decrements this consonant's place of articulation leftwards according 
        to the order of the standard IPA table of pulmonic consonants, which also 
        corresponds to the order of the Place enumeration.
        
        Parameters:
          val: The number of places to decrement
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new place of articulation would
                                  result in an impossible consonant.
        */
      
      bool has_secondary_articulation() const;
        
        /*
        Returns whether this consonant has a secondary articulation.
        */
      
      Place secondary_articulation() const;
        
        /*
        Returns this consonant's secondary place of articulation.
        
        If the consonant has no secondary articulation, this function will 
        return the primary place of articulation.
        */
      
      void set_secondary_articulation(Place new_place);
        
        /*
        Sets the consonant's secondary articulation to new_place.  If the 
        consonant doesn't already have a secondary articulation, one will be 
        added at new_place.  If new_place == the primary place of articulation,
        no secondary articulation will be added.
        
        Parameters:
          new_place: The new secondary place of articulation
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new secondary articulation 
                                  would result in an impossible consonant.
        */
      
      void remove_secondary_articulation();
        
        /*
        Removes the consonant's secondary articulation.  If the consonant has 
        no secondary articulation, nothing will happen.
        */
      
      void incr_secondary_articulation(int val = 1);
        
        /*
        Increments the place of secondary articulation rightwards according to 
        the order of the standard IPA table of pulmonic consonants, which is 
        also the order of the Place enumeration.
        
        Parameters:
          val: The number of places of articulation to move
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new secondary articulation 
                                  would result in an impossible articulation.
        */
      
      void decr_secondary_articulation(int val = 1);
        
        /*
        Decrements the place of secondary articulation leftwards according to 
        the order of the standard IPA table of pulmonic consonants, which is 
        also the order of the Place enumeration.
        
        Parameters:
          val: The number of places of articulation to move
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new secondary articulation 
                                  would result in an impossible articulation.
        */
        
      VOT vot() const;
        
        /*
        Returns the voice-onset time of the consonant.
        */
      
      void set_vot(VOT new_vot);
        
        /*
        Sets the voice-onset time of the consonant to the value given.
        
        Parameters:
          new_vot: The new voice-onset time
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new voice-onset time given 
                                  would result in an impossible consonant.
        */
        
      void later_vot(int val = 1);
        
        /*
        Gives the consonant a later voice-onset time by moving val places 
        higher in the VOT enumeration.
        
        Parameters:
          val: The number of places to move in the VOT enumeration
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new voice-onset time would 
                                  result in an impossible consonant.
        */
      
      void earlier_vot(int val = 1);
        
        /*
        Give the consonant an earlier voice-onset time by moving val places 
        lower in the VOT enumeration.
        
        Parameters:
          val: The number of places to move in the VOT enumeration
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new voice-onset time would 
                                  result in an impossible consonant.
        */
      
      Mechanism mechanism() const;
        
        /*
        Returns the consonant's airstream mechanism.
        */
      
      void set_mechanism(Mechanism new_mechanism);
        
        /*
        Sets the consonant's airstream mechanism to the value given.
        
        Parameters:
          new_mechanism: The new airstream mechanism
        
        Exceptions:
          ImpossibleArticulation: Thrown if the new airstream mechanism given 
                                  would result in an impossible consonant.
        */
      
      void incr_mechanism(int val = 1);
        
        /*
        Increments this consonant's mechanism of articulation according to the 
        order of the Mechanism enumeration.  Will go around the horn.
        
        Parameters:
          val: The number of mechanisms to increment
        */
      
      void decr_mechanism(int val = 1);
        
        /*
        Decrements this consonant's mechanism of articulation according to the 
        order of the Mechanism enumeration.  Will go around the horn.
        
        Parameters:
          val: The number of mechanisms to decrement
        */
    
  };
  
  class Tone {
    
    /*
    This class represents one tone pattern to be applied to a syllable.  It is 
    essentially a wrapper around an array of three integers.  These integers 
    must be between -2 and 2, with negative numbers representing low pitches 
    and positive numbers representing high pitches.
    */
    
    protected:
        
      int _array[3];
        
        /*
        This array represents a chronological pattern of pitch across a 
        syllable.  Each integer in the array must be between -2 and 2, with 
        negative numbers representing low pitches and positive numbers 
        representing high pitches.  Any function that modifies this field 
        should ensure that no integer value exceeds this valid range.
        */
    
    public:
      
      class iterator {
        
        protected:
          
          Tone* _tone;
            
            /*
            The Tone through which this iterator is iterating
            */
          
          int _position;
            
            /*
            The iterator's position in the Tone, defined as an index in the 
            internal array of integers.  
            
            Any function that moves the iterator should be bounds checked to 
            ensure that this value is always a valid index.
            */
        
        public:
          
          ~iterator();
            
            /*
            Destructor
            */
          
          iterator(Tone& tone, int position = 0);
            
            /*
            Standard constructor
            
            Parameters:
              tone:     The Tone through which this iterator is iterating
              position: The index in the Tone where this iterator will 
                        start.  Negative indices are allowed.  Bounds checked.
            
            Exceptions:
              expt::IndexError: Thrown if a value is passed for position that is out 
                                of bounds.
            */
          
          iterator(const iterator& original);
            
            /*
            Copy constructor
            
            Parameters:
              original: Other iterator to be copied
            */
          
          iterator& operator=(const iterator& other);
            
            /*
            Standard field-wise assignment
            */
          
          iterator& operator++();
            
          iterator& operator++(int);
          
          iterator& operator--();
          
          iterator& operator--(int);
          
          bool operator==(const iterator& other) const;
            
            /*
            Iterators are equal that are at the same position in the same 
            Tone.
            */
          
          bool operator!=(const iterator& other) const;
            
            /*
            Iterators are equal that are at the same position in the same
            Tone.
            */
          
          bool operator>(const iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator>(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator<(const iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator<(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator>=(const iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator>=(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator<=(const iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator<=(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          iterator& operator+=(int val);
          
          iterator& operator-=(int val);
          
          int operator[](int index);
            
            /*
            Allows the iterator to be de-referenced with an offset.  Returns 
            the int index places away from the iterator's current position.
            */
          
          int operator*();
            
            /*
            Returns the int at the iterator's current position in the 
            Tone.
            */
          
          Tone& tone() const;
            
            /*
            Returns a reference to the Tone this iterator is operating on.
            */
          
          void set_tone(Tone& new_tone);
            
            /*
            Moves this iterator to a different Tone.  Position is 
            unchanged.
            
            Parameters:
              new_tone: New Tone
            */
          
          int position() const;
            
            /*
            Returns the current position of the iterator.
            */
          
          int inverse_position() const;
            
            /*
            Returns the position of the iterator as a negative int measured 
            from the end of the Tone.
            */
          
          void set_position(int position);
            
            /*
            Moves the iterator to the position give.
            
            Parameters:
              position: The new position as an index in the Tone.  Negative
                        indices allowed.  Bounds checked.
            
            Exceptions:
              expt::IndexError: Thrown if the bounds check fails.
            */
      
      };
      
      class const_iterator {
        
        protected:
          
          const Tone* _tone;
            
            /*
            The Tone through which this iterator is iterating
            */
          
          int _position;
            
            /*
            The iterator's position in the Tone, defined as an index in the 
            internal array of integers.
            
            Any function that moves the iterator should be bounds checked to 
            ensure that this value is always a valid index.
            */
        
        public:
          
          ~const_iterator();
            
            /*
            Destructor
            */
          
          const_iterator(const Tone& tone, int position = 0);
            
            /*
            Standard constructor
            
            Parameters:
              tone:     The Tone through which this iterator is iterating
              position: The index in the Tone where this iterator will 
                        start.  Negative indices are allowed.  Bounds checked.
            
            Exceptions:
              expt::IndexError: Thrown if a value is passed for position that 
                                is out of bounds.
            */
          
          const_iterator(const const_iterator& original);
            
            /*
            Copy constructor
            
            Parameters:
              original: Other const_iterator to be copied.
            */
          
          const_iterator& operator=(const const_iterator& other);
            
            /*
            Standard field-wise assignment
            */
          
          const_iterator& operator++();
            
          const_iterator& operator++(int);
          
          const_iterator& operator--();
          
          const_iterator& operator--(int);
          
          bool operator==(const const_iterator& other) const;
            
            /*
            Iterators are equal that are at the same position in the same 
            Tone.
            */
          
          bool operator!=(const const_iterator& other) const;
            
            /*
            Iterators are equal that are at the same position in the same
            Tone.
            */
          
          bool operator>(const const_iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator>(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator<(const const_iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator<(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator>=(const const_iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator>=(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator<=(const const_iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator<=(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          const_iterator& operator+=(int val);
          
          const_iterator& operator-=(int val);
          
          int operator[](int index) const;
            
            /*
            Allows the iterator to be de-referenced with an offset.  Returns 
            the integer index places away from the iterator's current position.
            */
          
          int operator*() const;
            
            /*
            Returns the integer at the iterator's current position in the 
            Tone.
            */
          
          const Tone& tone() const;
            
            /*
            Returns a reference to the Tone this iterator is operating on.
            */
          
          void set_tone(const Tone& new_tone);
            
            /*
            Moves this iterator to a different Tone.  Position is 
            unchanged.
            
            Parameters:
              new_tone: New Tone
            */
          
          int position() const;
            
            /*
            Returns the current position of the iterator.
            */
          
          int inverse_position() const;
            
            /*
            Returns the position of the iterator as a negative int measured 
            from the end of the Tone.
            */
          
          void set_position(int position);
            
            /*
            Moves the iterator to the position give.
            
            Parameters:
              position: The new position as an index in the Tone.  Negative
                        indices allowed.  Bounds checked.
            
            Exceptions:
              expt::IndexError: Thrown if the bounds check fails.
            */
        
      };
      
      ~Tone();
        
        /*
        Destructor
        */
      
      Tone();
        
        /*
        Empty constructor
        
        Defaults to {0, 0, 0}.
        */
      
      Tone(int tone1, int tone2, int tone3);
        
        /*
        Standard constructor
        
        Parameters:
          The three parameters represent the tone pattern in chronological 
          sequence.  Each integer must be between -2 and 2, with negative 
          numbers representing low pitches and positive numbers representing 
          high pitches.
        
        Exceptions:
          ImpossibleArticulation: Thrown if an argument is passed that is < -2 
                                  or > 2.
        */
      
      Tone(std::initializer_list<int> list);
        
        /*
        Initializer-list constructor
        
        Parameters:
          list: An initializer list of exactly three integers.  The value of 
                each integer must be between -2 and 2, inclusive.
        
        Exceptions:
          expt::ValueError: Thrown if an initializer list is passed that does 
                            not have exactly three items.
          ImpossibleArticulation: Thrown if any of the integers is < -2 or > 2.
        */
      
      Tone(const Tone& original);
        
        /*
        Copy constructor
        
        Parameters:
          original: Other Tone to be copied
        */
      
      Tone& operator=(const Tone& other);
        
        /*
        Standard field-wise assignment
        */
    
      Tone& operator=(std::initializer_list<int> list);
        
        /*
        list must contain exactly three items, and each item must be between -2
        and 3, inclusive.
        
        Exceptions:
          expt::ValueError: Thrown if an initializer list is passed that does 
                            not have exactly three items.
          ImpossibleArticulation: Thrown if any of the integers is < -2 or > 2.
        */
      
      Tone& operator++();
        
        /*
        Iterates the Tone through the entire set of possible tones in a pre-
        defined order.
        */
      
      Tone& operator++(int);
        
        /*
        Iterates the Tone through the entire set of possible tones in a pre-
        defined order.
        */
      
      Tone& operator--();
        
        /*
        Iterates the Tone through the entire set of possible tones in a pre-
        defined order.
        */
      
      Tone& operator--(int);
        
        /*
        Iterates the Tone through the entire set of possible tones in a pre-
        defined order.
        */
      
      bool operator==(const Tone& other) const;
        
        /*
        Tones are equal if all three integer values are equal.
        */
      
      bool operator!=(const Tone& other) const;
        
        /*
        Tones are equal if all three integer values are equal.
        */
      
      int& operator[](int index);
        
        /*
        Returns the integer representing the pitch at the given index.  In 
        other words, allows indexing of the internal array of integers.
        
        Bounds checked
        
        Exceptions:
          expt::IndexError: Thrown if the bounds check fails.
        */
      
      const int& operator[](int index) const;
        
        /*
        Returns the integer representing the pitch at the given index.  In 
        other words, allows indexing of the internal array of integers.
        
        Bounds checked
        
        Exceptions:
          expt::IndexError: Thrown if the bounds check fails.
        */
      
      operator int();
        
        /*
        Returns the internal array.
        */
      
      iterator begin();
      
      const_iterator begin() const;
      
      iterator end();
      
      const_iterator end() const;
      
      int array() const;
        
        /*
        Returns a copy of the internal array of integers.
        */
    
  };
  
  class Syllable {
    
    /*
    This class represents a phonetic syllable.
    */
    
    protected:
      
      std::vector<Phone*> _onset;
      
      std::vector<Phone*> _nucleus;
      
      std::vector<Phone*> _coda;
      
      Tone _tone;
      
      std::vector<Vowel> _vowels;
        
        /*
        This vector contains all of the vowels used in the syllable so that 
        they can be pointed to from the onset, nucleus, and coda vectors.
        */
      
      std::vector<Consonant> _consonants;
        
        /*
        This vector contains all of the consonants used in the syllable so that
        they can be pointed to from the onset, nucleus, and coda vectors.
        */
    
    public:
      
      class iterator {
        
        protected:
          
          Syllable* _syllable;
            
            /*
            The Syllable through which this iterator is iterating
            */
          
          int _position;
            
            /*
            The iterator's position in the Syllable, defined as an index as if 
            the entire Syllable were one vector.  
            
            Any function that moves the iterator should be bounds checked to 
            ensure that this value is always a valid index.
            */
        
        public:
          
          ~iterator();
            
            /*
            Destructor
            */
          
          iterator(Syllable& syllable, int position = 0);
            
            /*
            Standard constructor
            
            Parameters:
              syllable: The Syllable through which this iterator is iterating
              position: The index in the Syllable where this iterator will 
                        start.  Negative indices are allowed.  Bounds checked.
            
            Exceptions:
              expt::IndexError: Thrown if a value is passed for position that 
                                is out of bounds.
            */
          
          iterator(const iterator& original);
            
            /*
            Copy constructor
            
            Parameters:
              original: Other iterator to be copied
            */
          
          iterator& operator=(const iterator& other);
            
            /*
            Standard field-wise assignment
            */
          
          iterator& operator++();
            
          iterator& operator++(int);
          
          iterator& operator--();
          
          iterator& operator--(int);
          
          bool operator==(const iterator& other) const;
            
            /*
            Iterators are equal that are at the same position in the same 
            Syllable.
            */
          
          bool operator!=(const iterator& other) const;
            
            /*
            Iterators are equal that are at the same position in the same
            Syllable.
            */
          
          bool operator>(const iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator>(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator<(const iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator<(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator>=(const iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator>=(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator<=(const iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator<=(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          iterator& operator+=(int val);
          
          iterator& operator-=(int val);
          
          Phone* operator[](int index);
            
            /*
            Allows the iterator to be de-referenced with an offset.  Returns 
            the Phone* index places away from the iterator's current position.
            */
          
          Phone* operator*();
            
            /*
            Returns the Phone* at the iterator's current position in the 
            Syllable.
            */
          
          Phone* operator->();
          
          Syllable& syllable() const;
            
            /*
            Returns a reference to the Syllable this iterator is operating on.
            */
          
          void set_syllable(Syllable& new_syllable);
            
            /*
            Moves this iterator to a different Syllable.  Position is 
            unchanged.
            
            Parameters:
              new_syllable: New syllable
            */
          
          int position() const;
            
            /*
            Returns the current position of the iterator.
            */
          
          int inverse_position() const;
            
            /*
            Returns the position of the iterator as a negative int measured 
            from the end of the Syllable.
            */
          
          void set_position(int position);
            
            /*
            Moves the iterator to the position give.
            
            Parameters:
              position: The new position as an index in the Syllable.  Negative
                        indices allowed.  Bounds checked.
            
            Exceptions:
              expt::IndexError: Thrown if the bounds check fails.
            */
      
      };
      
      class const_iterator {
        
        protected:
          
          const Syllable* _syllable;
            
            /*
            The Syllable through which this iterator is iterating
            */
          
          int _position;
            
            /*
            The iterator's position in the Syllable, defined as an index as if 
            the entire Syllable were one vector.  
            
            Any function that moves the iterator should be bounds checked to 
            ensure that this value is always a valid index.
            */
        
        public:
          
          ~const_iterator();
            
            /*
            Destructor
            */
          
          const_iterator(const Syllable& syllable, int position = 0);
            
            /*
            Standard constructor
            
            Parameters:
              syllable: The Syllable through which this iterator is iterating
              position: The index in the Syllable where this iterator will 
                        start.  Negative indices are allowed.  Bounds checked.
            
            Exceptions:
              expt::IndexError: Thrown if a value is passed for position that 
                                is out of bounds.
            */
          
          const_iterator(const const_iterator& original);
            
            /*
            Copy constructor
            
            Parameters:
              original: Other const_iterator to be copied.
            */
          
          const_iterator& operator=(const const_iterator& other);
            
            /*
            Standard field-wise assignment
            */
          
          const_iterator& operator++();
            
          const_iterator& operator++(int);
          
          const_iterator& operator--();
          
          const_iterator& operator--(int);
          
          bool operator==(const const_iterator& other) const;
            
            /*
            Iterators are equal that are at the same position in the same 
            Syllable.
            */
          
          bool operator!=(const const_iterator& other) const;
            
            /*
            Iterators are equal that are at the same position in the same
            Syllable.
            */
          
          bool operator>(const const_iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator>(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator<(const const_iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator<(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator>=(const const_iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator>=(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          bool operator<=(const const_iterator& other) const;
            
            /*
            Compares the positions of the two iterators.
            */
          
          bool operator<=(int position) const;
            
            /*
            Compares the position of this iterator to an integer position.
            */
          
          const_iterator& operator+=(int val);
          
          const_iterator& operator-=(int val);
          
          const Phone* operator[](int index) const;
            
            /*
            Allows the iterator to be de-referenced with an offset.  Returns 
            the Phone* index places away from the iterator's current position.
            */
          
          const Phone* operator*() const;
            
            /*
            Returns the Phone* at the iterator's current position in the 
            Syllable.
            */
          
          const Phone* operator->() const;
          
          const Syllable& syllable() const;
            
            /*
            Returns a reference to the Syllable this iterator is operating on.
            */
          
          void set_syllable(const Syllable& new_syllable);
            
            /*
            Moves this iterator to a different Syllable.  Position is 
            unchanged.
            
            Parameters:
              new_syllable: New syllable
            */
          
          int position() const;
            
            /*
            Returns the current position of the iterator.
            */
          
          int inverse_position() const;
            
            /*
            Returns the position of the iterator as a negative int measured 
            from the end of the Syllable.
            */
          
          void set_position(int position);
            
            /*
            Moves the iterator to the position give.
            
            Parameters:
              position: The new position as an index in the Syllable.  Negative
                        indices allowed.  Bounds checked.
            
            Exceptions:
              expt::IndexError: Thrown if the bounds check fails.
            */
        
      };
      
      ~Syllable();
        
        /*
        Destructor
        */
      
      Syllable();
        
        /*
        Empty constructor
        
        The default syllable is just a Schwa.
        */
      
      Syllable(const std::vector<const Phone*> onset, 
               const std::vector<const Phone*> nucleus, 
               const std::vector<const Phone*> coda, 
               const Tone tone = {0, 0, 0});
        
        /*
        Detailed constructor
        
        Parameters:
          onset:    A vector of pointers to the phones representing the 
                    syllable onset
          nucleus:  A vector of pointers to the phones representing the 
                    syllable nucleus.  Cannot be empty.
          coda:     A vector of pointers to the phones representing the 
                    syllable coda
          tone:     The tone of the syllable.
        
        Exceptions:
          ImpossibleArticulation: Thrown if nucleus is an empty vector.
        */
      
      Syllable(std::string transcription, PhoneticEncoding encoding = x-sampa);
      
        /*
        Transcription constructor

        Constructs a syllable from a string containing a phonetic transcription
        representing a single syllable.  See the enumeration PhoneticEncoding 
        for a list of supported transcription systems.

        Parameters:
          transcription:  A phonetic transcription representing a single 
                          syllable.  The transcription may be enclosed in 
                          square brackets or not enclosed.  It may not be 
                          enclosed in any other type of bracket.
          encoding:       This parameter specifies which transcription system 
                          the transcription is encoded in using the set of 
                          options provided by the PhoneticEncoding enumeration.

        Exceptions:
          DecodingFailed: Thrown if transcription cannot be recognized as a 
                          single valid syllable in the specified transcription 
                          system.
        */
      
      Syllable(const Syllable& original);
        
        /*
        Copy constructor
        
        Parameters:
          original: The other Syllable to be copied
        */
      
      Syllable& operator=(const Syllable& other);
        
        /*
        Standard field-wise assignment
        */
      
      bool operator==(const Syllable& other) const;
      
      bool operator!=(const Syllable& other) const;
      
      Phone& operator[](int index);
      
      const Phone& operator[](int index) const;
      
      iterator begin();
      
      iterator end();
      
      iterator onset_begin();
        
        /*
        Returns an iterator at the start of the syllable onset.
        */
      
      iterator onset_end();
        
        /*
        Returns an iterator at the end of the syllable onset.
        */
      
      iterator nucleus_begin();
        
        /*
        Returns an iterator at the start of the syllable nucleus.
        */
      
      iterator nucleus_end();
        
        /*
        Returns an iterator at the end of the syllable nucleus.
        */
      
      iterator coda_begin();
        
        /*
        Returns an iterator at the start of the syllable coda.
        */
      
      iterator coda_end();
        
        /*
        Returns an iterator at the end of the syllable coda.
        */
      
      const_iterator begin() const;
      
      const_iterator end() const;
      
      const_iterator onset_begin() const;
        
        /*
        Returns an iterator at the start of the syllable onset.
        */
      
      const_iterator onset_end() const;
        
        /*
        Returns an iterator at the end of the syllable onset.
        */
      
      const_iterator nucleus_begin() const;
        
        /*
        Returns an iterator at the start of the syllable nucleus.
        */
      
      const_iterator nucleus_end() const;
        
        /*
        Returns an iterator at the end of the syllable nucleus.
        */
      
      const_iterator coda_begin() const;
        
        /*
        Returns an iterator at the start of the syllable coda.
        */
      
      const_iterator coda_end() const;
        
        /*
        Returns an iterator at the end of the syllable coda.
        */
      
      const std::vector<Phone*>& onset() const;
        
        /*
        Returns a const reference to the internal vector of Phone pointers 
        representing the syllable onset.
        */
      
      const std::vector<Phone*>& nucleus() const;
        
        /*
        Returns a const reference to the internal vector of Phone pointers 
        representing the syllable nucleus.
        */
      
      const std::vector<Phone*>& coda() const;
        
        /*
        Returns a const reference to the internal vector of Phone pointers 
        representing the syllable coda.
        */
      
      const std::vector<Phone*> phones() const;
        
        /*
        Returns a const vector containing pointers to all of the Phones in the 
        syllable, in order.
        */
      
      std::vector<Vowel>& vowels();
        
        /*
        Returns a reference to the internal vector containing all of the 
        syllable's vowels.  This allows operations to be performed on all 
        vowels in the syllable.
        */
      
      const std::vector<Vowel>& vowels() const;
        
        /*
        Returns a const reference to the internal vector containing all of the 
        syllable's vowels.
        */
      
      std::vector<Consonant>& consonants();
        
        /*
        Returns a reference to the internal vector containing all of the 
        syllable's consonants.  This allows operations to be performed on all
        consonants in the syllable.
        */
      
      const std::vector<Consonant>& consonants() const;
        
        /*
        Returns a const reference to the internal vector containing all of the 
        syllable's consonants.
        */
      
      Tone tone() const;
        
        /*
        Returns the syllable's tone.
        */
      
      void insert_onset(Phone new_phone, int position);
        
        /*
        Inserts a new phone into the syllable onset.
        
        Parameters:
          new_phone:  The new phone to be inserted
          position:   An index in the syllable onset.  Bounds checked.  
                      Negative indices allowed.
        
        Exceptions:
          expt::IndexError: Thrown if the bounds check fails.
        */
      
      void insert_nucleus(Phone new_phone, int position);
        
        /*
        Inserts a new phone into the syllable nucleus.
        
        Parameters:
          new_phone:  The new phone to be inserted
          position:   An index in the syllable nucleus.  Bounds checked.  
                      Negative indices allowed.
        
        Exceptions:
          expt::IndexError: Thrown if the bounds check fails.
        */
      
      void insert_coda(Phone new_phone, int position);
        
        /*
        Inserts a new phone into the syllable coda.
        
        Parameters:
          new_phone:  The new phone to be inserted
          position:   An index in the syllable coda.  Bounds checked.  
                      Negative indices allowed.
        
        Exceptions:
          expt::IndexError: Thrown if the bounds check fails.
        */
      
      void remove_onset(int index);
        
        /*
        Removes the phone at the given index.
        
        Parameters:
          index: An index in the syllable onset.  Bounds checked.  Negative 
                  indices allowed.
        
        Exceptions:
          expt::IndexError: Thrown if the bounds check fails.
        */
      
      void remove_nucleus(int index);
        
        /*
        Removes the phone at the given index.
        
        Parameters:
          index: An index in the syllable nucleus.  Bounds checked.  Negative
                  indices allowed.
        
        Exceptions:
          expt::IndexError: Thrown if the bounds check fails.
        */
      
      void remove_coda(int index);
        
        /*
        Removes the phone at the given index.
        
        Parameters:
          index: An index in the syllable coda.  Bounds checked.  Negative 
                  indices allowed.
        
        Exceptions:
          expt::IndexError: Thrown if the bounds check fails.
        */
      
      std::string unicode() const;
        
        /*
        Returns the IPA representation of the syllable, using Unicode 
        characters where necessary.  Will be enclosed in square brackets.
        */

      std::string kirschenbaum() const;

        /*
        Returns the IPA representation of the syllable using Kirschenbaum 
        encoding.  Will be enclosed in square brackets.
        */

      std::string x-sampa() const;

        /*
        Returns the IPA representation of the syllable using X-SAMPA encoding. 
        Will be enclosed in square brackets.
        */
    
  };
  
  typedef std::vector<Syllable> PhoneticSequence;
  
  // Functions
  
  Phone::Phonation& operator++(Phone::Phonation& start_val);
    
    /*
    Iterates through the Phonation enumeration in numerical order.  Will 
    go around the horn.
    */
  
  Phone::Phonation& operator++(Phone::Phonation& start_val, int);
    
    /*
    Iterates through the Phonation enumeration in numerical order.  Will 
    go around the horn.
    */
  
  Phone::Phonation& operator--(Phone::Phonation& start_val);
    
    /*
    Iterates through the Phonation enumeration in numerical order.  Will 
    go around the horn.
    */
  
  Phone::Phonation& operator--(Phone::Phonation& start_val, int);
    
    /*
    Iterates through the Phonation enumeration in numerical order.  Will 
    go around the horn.
    */
    
  Phone::Phonation& operator+=(Phone::Phonation& start_val, int val);
    
    /*
    Iterates through the Phonation enumeration in numerical order.  Will 
    go around the horn.
    */
  
  Phone::Phonation& operator-=(Phone::Phonation& start_val, int val);
    
    /*
    Iterates through the Phonation enumeration in numerical order.  Will 
    go around the horn.
    */
  
  std::string string(Phone::Phonation& phonation);
    
    /*
    Returns the name of the Phonation value in string form.
    
    Parameters:
      phonation: Phonation to convert
    */
  
  Phone::Nasalization& operator++(Phone::Nasalization& start_val);
    
    /*
    Iterates through the Nasalization enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Phone::Nasalization& operator++(Phone::Nasalization& start_val, int);
    
    /*
    Iterates through the Nasalization enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Phone::Nasalization& operator--(Phone::Nasalization& start_val);
    
    /*
    Iterates through the Nasalization enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Phone::Nasalization& operator--(Phone::Nasalization& start_val, int);
    
    /*
    Iterates through the Phonation enumeration in numerical order.  Will go 
    around the horn.
    */
    
  Phone::Nasalization& operator+=(Phone::Nasalization& start_val, int val);
    
    /*
    Iterates through the Nasalization enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Phone::Nasalization& operator-=(Phone::Nasalization& start_val, int val);
    
    /*
    Iterates through the Nasalization enumeration in numerical order.  Will go 
    around the horn.
    */
  
  std::string string(Phone::Nasalization& nasalization);
    
    /*
    Returns the name of the Nasalization value in string form.
    
    Parameters:
      nasalization: Nasalization to be converted
    */
  
  Vowel::Height& operator++(Vowel::Height& start_val);
    
    /*
    Iterates through the Height enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Height& operator++(Vowel::Height& start_val, int);
    
    /*
    Iterates through the Height enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Height& operator--(Vowel::Height& start_val);
    
    /*
    Iterates through the Height enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Height& operator--(Vowel::Height& start_val, int);
    
    /*
    Iterates through the Height enumeration in numerical order.  Will go 
    around the horn.
    */
    
  Vowel::Height& operator+=(Vowel::Height& start_val, int val);
    
    /*
    Iterates through the Height enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Height& operator-=(Vowel::Height& start_val, int val);
    
    /*
    Iterates through the Height enumeration in numerical order.  Will go 
    around the horn.
    */
  
  std::string string(Vowel::Height& height);
    
    /*
    Returns the name of the Height value in string form.
    
    Parameters:
      height: Height to be converted
    */
  
  Vowel::Backness& operator++(Vowel::Backness& start_val);
    
    /*
    Iterates through the Backness enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Backness& operator++(Vowel::Backness& start_val, int);
    
    /*
    Iterates through the Backness enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Backness& operator--(Vowel::Backness& start_val);
    
    /*
    Iterates through the Backness enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Backness& operator--(Vowel::Backness& start_val, int);
    
    /*
    Iterates through the Backness enumeration in numerical order.  Will go 
    around the horn.
    */
    
  Vowel::Backness& operator+=(Vowel::Backness& start_val, int val);
    
    /*
    Iterates through the Backness enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Backness& operator-=(Vowel::Backness& start_val, int val);
    
    /*
    Iterates through the Backness enumeration in numerical order.  Will go 
    around the horn.
    */
  
  std::string string(Vowel::Backness& backness);
    
    /*
    Returns the name of the Backness value in string form.
    
    Parameters:
      backness: Backness to be converted
    */
  
  Vowel::Roundedness& operator++(Vowel::Roundedness& start_val);
    
    /*
    Iterates through the Roundedness enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Roundedness& operator++(Vowel::Roundedness& start_val, int);
    
    /*
    Iterates through the Roundedness enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Roundedness& operator--(Vowel::Roundedness& start_val);
    
    /*
    Iterates through the Roundedness enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Roundedness& operator--(Vowel::Roundedness& start_val, int);
    
    /*
    Iterates through the Roundedness enumeration in numerical order.  Will go 
    around the horn.
    */
    
  Vowel::Roundedness& operator+=(Vowel::Roundedness& start_val, int val);
    
    /*
    Iterates through the Roundedness enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Vowel::Roundedness& operator-=(Vowel::Roundedness& start_val, int val);
    
    /*
    Iterates through the Roundedness enumeration in numerical order.  Will go 
    around the horn.
    */
  
  std::string string(Vowel::Roundedness& roundedness);
    
    /*
    Returns the name of the Roundedness value in string form.
    
    Parameters:
      roundedness: Roundedness to be converted
    */
  
  Consonant::Manner& operator++(Consonant::Manner& start_val);
    
    /*
    Iterates through the Manner enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Manner& operator++(Consonant::Manner& start_val, int);
    
    /*
    Iterates through the Manner enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Manner& operator--(Consonant::Manner& start_val);
    
    /*
    Iterates through the Manner enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Manner& operator--(Consonant::Manner& start_val, int);
    
    /*
    Iterates through the Manner enumeration in numerical order.  Will go 
    around the horn.
    */
    
  Consonant::Manner& operator+=(Consonant::Manner& start_val, int val);
    
    /*
    Iterates through the Manner enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Manner& operator-=(Consonant::Manner& start_val, int val);
    
    /*
    Iterates through the Manner enumeration in numerical order.  Will go 
    around the horn.
    */
  
  std::string string(Consonant::Manner& manner);
    
    /*
    Returns the name of the Manner value in string form.
    
    Parameters:
      manner: Manner to be converted
    */
  Consonant::Place& operator++(Consonant::Place& start_val);
    
    /*
    Iterates through the Place enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Place& operator++(Consonant::Place& start_val, int);
    
    /*
    Iterates through the Place enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Place& operator--(Consonant::Place& start_val);
    
    /*
    Iterates through the Place enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Place& operator--(Consonant::Place& start_val, int);
    
    /*
    Iterates through the Place enumeration in numerical order.  Will go 
    around the horn.
    */
    
  Consonant::Place& operator+=(Consonant::Place& start_val, int val);
    
    /*
    Iterates through the Place enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Place& operator-=(Consonant::Place& start_val, int val);
    
    /*
    Iterates through the Place enumeration in numerical order.  Will go 
    around the horn.
    */
  
  std::string string(Consonant::Place& place);
    
    /*
    Returns the name of the Place value in string form.
    
    Parameters:
      place: Place to be converted
    */
  
  Consonant::VOT& operator++(Consonant::VOT& start_val);
    
    /*
    Iterates through the VOT enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::VOT& operator++(Consonant::VOT& start_val, int);
    
    /*
    Iterates through the VOT enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::VOT& operator--(Consonant::VOT& start_val);
    
    /*
    Iterates through the VOT enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::VOT& operator--(Consonant::VOT& start_val, int);
    
    /*
    Iterates through the VOT enumeration in numerical order.  Will go 
    around the horn.
    */
    
  Consonant::VOT& operator+=(Consonant::VOT& start_val, int val);
    
    /*
    Iterates through the VOT enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::VOT& operator-=(Consonant::VOT& start_val, int val);
    
    /*
    Iterates through the VOT enumeration in numerical order.  Will go 
    around the horn.
    */
  
  std::string string(Consonant::VOT& vot);
    
    /*
    Returns the name of the VOT value in string form.
    
    Parameters:
      vot: VOT to be converted
    */
  
  Consonant::Mechanism& operator++(Consonant::Mechanism& start_val);
    
    /*
    Iterates through the Mechanism enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Mechanism& operator++(Consonant::Mechanism& start_val, int);
    
    /*
    Iterates through the Mechanism enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Mechanism& operator--(Consonant::Mechanism& start_val);
    
    /*
    Iterates through the Mechanism enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Mechanism& operator--(Consonant::Mechanism& start_val, int);
    
    /*
    Iterates through the Mechanism enumeration in numerical order.  Will go 
    around the horn.
    */
    
  Consonant::Mechanism& operator+=(Consonant::Mechanism& start_val, int val);
    
    /*
    Iterates through the Mechanism enumeration in numerical order.  Will go 
    around the horn.
    */
  
  Consonant::Mechanism& operator-=(Consonant::Mechanism& start_val, int val);
    
    /*
    Iterates through the Mechanism enumeration in numerical order.  Will go 
    around the horn.
    */
  
  std::string string(Consonant::Mechanism& mechanism);
    
    /*
    Returns the name of the Mechanism value in string form.
    
    Parameters:
      mechanism: Mechanism to be converted
    */
  
};

#endif // PHONETICS_HEADER