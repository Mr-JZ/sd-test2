/**
 *  \brief     cout definition.
 *  \details   This file defines a global reference to a singleton object cout \n
 *  of type \ref Platform::BSP::TermColor
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      14.06.2016
 *  \copyright HS Osnabrueck
 */

/** @file */

#include "TermColor.h"

namespace Platform
{
namespace BSP
{
TermColor& cout = TermColor::getInstance();  ///< reference to TermColor object, can be used for C++ like output
                                             ///< without iostream / newlib nano memory overhead.


const TermColor& TermColor::operator<<(Manipulators c) const
   {
       switch(c)
       {
       case  endl:
          fputc('\n', stdout);
          break;
       case  hex:
          m_isHex   = true;
          m_isOctal = false;
          break;
       case oct:
           m_isHex   = false;
           m_isOctal = true;
           break;
       case dec:
           m_isHex   = false;
           m_isOctal = false;
           break;
       case fixed:
           m_isFixed      = true;
           m_isScientific = false;
           break;
       case scientific:
           m_isFixed      = false;
           m_isScientific = true;
           break;
       case left:
           m_isLeft  = true;
           break;
       case right:
           m_isLeft  = false;
       };
       setFlags();
       return *this;
   }

}
}
