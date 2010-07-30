/*
 * =====================================================================================
 *
 *       Filename:  StringHashMap.hpp
 *
 *    Description:  A specialisation of the hash template supporting string objects, enabling their use in hash_maps
 *
 *        Version:  1.0
 *        Created:  22/05/10 21:41:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  James Smaldon (JS), jqs@cs.nott.ac.uk
 *        Company:  University of Nottingham
 *
 * =====================================================================================
 */

#ifndef __STRINGHASH_HPP__
#define __STRINGHASH_HPP__

#include <string>

namespace std
{                                                                                             
  template<> struct hash< std::string >                                                       
  {                                                                                           
    size_t operator()( const std::string& x ) const                                           
    {                                                                                         
      return hash< const char* >()( x.c_str() );                                              
    }                                                                                         
  };                                                                                          
} 

#endif
