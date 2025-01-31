// *****************************************************************************
//
// Copyright (C) SAAB AB
//
// All rights, including the copyright, to the computer program(s)
// herein belong to SAAB AB. The program(s) may be used and/or
// copied only with the written permission of SAAB AB, or in
// accordance with the terms and conditions stipulated in the
// agreement/contract under which the program(s) have been
// supplied.
//
//
// Information Class:	COMPANY UNCLASSIFIED
// Defence Secrecy:		NOT CLASSIFIED
// Export Control:		NOT EXPORT CONTROLLED
//
//
// File			: gzBase.h
// Module		: gzBase
// Description	: Class definition of basic classes such as strings etc.
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.211
//		
//
//			
// NOTE:	GizmoBase is a platform abstraction utility layer for C++. It contains 
//			design patterns and C++ solutions for the advanced programmer.
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980819	Created file 
// AMO	990602	Added support for file traversal	
// AMO	120904	Changed the PRNG to a Mersenne Twister							(2.6.16)
// AMO	120904	Added Normal, Exponential and Weibull random numnber gen		(2.6.16)
// AMO	130205	Added gzString::substitute										(2.6.24)
// AMO	140821	Added upper/lower case for gzYesNo								(2.8.0)
// AMO	180426	Added some safe STDC routines									(2.9.1)
//
// ******************************************************************************

#ifndef __GZ_BASE_H__
#define __GZ_BASE_H__

/*!	\file 
	\brief Basic utilites like string and time management

Gizmo3D provides platform independant functionality for string management, time and date management,
directory and file management etc. These features can be used without using the Gizmo3D graphical api.
	
*/

#include "gzBasicTypes.h"
#include "gzMemory.h"
#include "gzDebug.h"
#include "gzMutex.h"

#include <string.h>

#if defined GZ_UNIX

#include <dirent.h>

typedef DIR * gzDirHandle;
typedef struct dirent * gzDirEntry;

#else	// non unix

#include "windows.h"
typedef HANDLE gzDirHandle;
typedef WIN32_FIND_DATAW gzDirEntry;

#endif

// ----------------------- UNICODE macros for gzString arguments -----------------------

#if defined UNICODE
	#define GZ_T_UNICODE(x)			(x)##.getWideString()
	#define GZ_T_UNICODE_LEN(x)		(x)##.getWideStringLength()
#else
	#define GZ_T_UNICODE(x)			(const char *)(x)
	#define GZ_T_UNICODE_LEN(x)		(x)##.length()
#endif

#define MAX_GZSTRING_LEN			(0xFFFF)

// ******************** class definitions ***************************************

//******************************************************************************
// Class	: gzString
//									
// Purpose  : String objects
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	980820	Created 
//									
//******************************************************************************

/*! \brief Provides a generic string management class

The gzString class is Gizmo3D generic class for string management. It encapsulates
C strings (null terminated) and provides methods for comparing, sub string search etc.

*/

class  GZ_BASE_EXPORT gzString   
{

public:		

	// Type info
	GZ_DECLARE_TYPE_INTERFACE_;

	// Constructors	

	//! Default constructor of a gzString
	/*! Creates an empty string. No allocation of "string" memory is done. However a (cast) to a const char * returns
	a pointer to a zero terminated empty C string. */
	gzString():m_string(NULL),m_len(0),m_uniqueID(0),m_hash(0){}

	//! Create a gzString from a C string
	/*! Creates a gzString from a C string pointer. Remember to have a zero terminated string as input !! 
	\param str A null terminated C string */
	gzString(const char *str):m_string(NULL),m_len(0),m_uniqueID(0),m_hash(0){ *this = str; }

	gzString(const char *str, gzUInt16 len);
    
	gzString(const gzString &str);
    
	virtual ~gzString();

	/*! Creates a gzString from a WIDE string pointer. The gzString will be encoded into UTF8 if the character values
	are greater than 0x7f 
	\param widestr A NULL terminated WIDE string 
	\sa getWideString */
    gzString(const gzWideChar *widestr);

    gzString(const gzWideChar *widestr , gzUInt16 len,gzBool isPlain=FALSE);


	/*! Creates a string representation of the number. Use radix=10 to create normal decimal number, Use radix=16 to create Hex.
	\param number The number to be converted into a string representation.
	\param radix The base radix of the number conversion.
	\param minLen The minimum length. */
	gzString(gzInt64 number,gzUByte radix,gzUInt16 minLen=0);
	
	/*! creates a string representation of the gzDouble number. You can provide formatting (printf) sequence to customize output
	\param number The number (gzDouble) to be converted
	\param format A (printf) formatting sequence. Defaults to "%f" */
	gzString(gzDouble number,const gzString & format=""); 
	

	/*! Returns the number of UTF8 characters in the string. Remember to use getWideStringLength for WIDE strings.*/
    gzUInt16		length() const		{ return m_len; }

    /*! Clears the contents of the string */
    gzVoid			clear();

	/*! Returns a C string representation of the gzString. The buffer is terminated by a ZERO */
    const char *	getString() const;

	/*! Return a gzInt64 representation of the string */
	gzInt64			num() const;

	/*! Return a gzInt64 representation of the string */
	gzInt32			num32() const { return (gzInt32)num(); }

	/*! Return a gzDouble representation of the string */
	gzDouble		real(gzUInt16 decimalToken='.') const;

	/*! Return a gzDouble representation of the string */
	gzFloat			realf(gzUInt16 decimalToken = '.') const { return (gzFloat)real(decimalToken); }

	gzDouble		sortval() const;

	//! Search for substring
	/*! Returns TRUE if substr is found withing the string. FALSE if not.
	\param substr The string to search for
	\param startindex The character position to start searching for the substr.
	\param caseSensitive Set to TRUE if the search should be case sensitive
	\param index A pointer to a gzUInt32 to get the actual position of the substr */
	gzBool			contains(const gzString & substr, gzUInt16 startindex=0 , gzBool caseSensitive = TRUE , gzUInt16 *index=nullptr) const;
	
	//! Extract substring
	/*! Extracts the contents of the gzString on the right side of the substr.
	\param substr The substring to mark the start where to find the right side substring
	\param searchFromEnd TRUE if the search for the substr is to be done from the end
	\param caseSensitive TRUE if the substring match is case sensitive */
	gzString		rightOf(const gzString & substr, gzBool searchFromEnd = TRUE, gzBool caseSensitive = TRUE ) const;
	
	//! Extract substring
	/*! Extracts the contents of the gzString on the left side of the substr.
	\param substr The substring to mark the end where to find the left side substring
	\param searchFromStart TRUE if the search for the substr is to be done from the start
	\param caseSensitive TRUE if the substring match is case sensitive */
	gzString		leftOf(const gzString & substr, gzBool searchFromStart = TRUE , gzBool caseSensitive = TRUE ) const;
	
	//! Convert to lower ascii representation. Does not work with WIDE strings
	gzString		toLower() const;
	
	//! Convert to upper ascii representation. Does not work with WIDE strings
	gzString		toUpper() const;

	//! Get (count) left most characters. If (inverse) you get the others
	gzString		left(gzUInt16 count,gzBool inverse=FALSE)	const;

	//! Get (count) right most characters. If (inverse) you get the others
	gzString		right(gzUInt16 count,gzBool inverse=FALSE)	const;

	gzUInt32		find(gzUByte token,gzUInt16 start=0)		const;


	/*! Remove characters from start and end of string.
	\param c the character number to strip
	\param left TRUE if to strip from the left
	\param right TRUE if to strip from the right */
	gzString		strip(char c , gzBool left=TRUE , gzBool right=TRUE) const;

	gzString		stripWhiteSpace(gzBool left=TRUE , gzBool right=TRUE) const;

	//! Reverse the string contents. Does not work with WIDE strings.
	gzVoid			reverse();

	//! Return a rather unique number that represents the string
	gzUInt32		hash()	const	{ return m_hash; }

	//! Check for empty string
	gzBool			isEmpty() const { return m_len==0; }

	//! Check prefix character
	gzBool			isFirst( const gzString &str , gzBool caseSensitive = TRUE) const;

	//! Check prefix character
	gzBool			isFirst( const char ch , gzBool caseSensitive = TRUE) const;

	//! Check postfix character
	gzBool			isLast( const gzString &str , gzBool caseSensitive = TRUE) const;

	//! Check postfix character
	gzBool			isLast( const char ch , gzBool caseSensitive = TRUE) const;

	gzBool			compare( const gzString &str , gzBool caseSensitive = TRUE , gzUInt16 *count=nullptr) const;

	//! Recreate the string based on a formatting sequence
	/*! The method works like a sprintf method to create a string out of a format sequence. 
	The ARG_DECL_LIST is a type specified ecliptic argument that can hold 10 values 
	e.g. \code
	
	gzString a;

	a.format("%f",10.27);
	
	\endcode
	
	Creates a string "10.27" 
	
	\code

	formats: %<pos><flags><width><precision><size><type>

	<pos>
	number$	uses number to get argument at position 1 to 16. Number is ended by $
	*$		takes argument and uses that value as argument position 1-16

	<flags>
	-		left align within width field. Default is to right align
	+		prefix width sign if output is number type
	0		insert 0 if number value and no + prefix
	' ' (blank)	prefix with a space, ignore if + prefix	

	<precision>
	.number	for type 's' or 'S' number specifies the number of characters in string.
			for type 'f' number specifies the number of decimals
			

	<type>
	c		takes a number n and insert wide char token with value n in string
	s		takes pointer to null terminated ansi string or ansii gzString and inserts ansii string
	S		takes pointer to null terminated unicode string or utf8 gzString and inserts unicode string
	f		takes number and inserts plain number [-]ddd.ddd in string
	e		takes number and insert exponential number [-]d.dddd e [sign]dd in string
	E		takes number and insert exponential number [-]d.dddd E [sign]dd in string
	g		takes number and insers most compact format of f or e
	G		takes number and insers most compact format of f or E
	d		takes signed integer and inserts integer value in string
	u		takes unsigned integer and inserts unsigned integer value in string
	x		takes unsigned integer and inserts hex lower case value in string 
	X		takes unsigned integer and inserts hex upper case value in string
	b		takes unsigned integer and inserts binary lower case value in string
	B		takes unsigned integer and inserts binary upper case value in string
	o		takes unsigned integer and inserts octal lower case value in string
	O		takes unsigned integer and inserts octal upper case value in string

	\endcode */
	gzString &		format( const gzString &format, ARG_DECL_LIST );

	static gzString	formatString(const gzString &format, ARG_DECL_LIST);

	//! Generates a unique string identifier from a number
	static gzString identifier(gzUInt64 number);

	//! Get The length of the wide string representation
	gzUInt16		getWideStringLength() const;

	//! Get the wide string data into a buffer
	/*! The buffer need to have the appropriate size so the buffer doesn't get overflowed. Use the getWideStringLength()
	to create a buffer and remember to append a zero slot at the end of you want a NULL terminated wide string */
	gzUInt16		getWideString(gzWideChar *buffer, gzBool appendZero=TRUE) const;

	//! Tell you if the string has possible escaped UTF8 chars
	gzBool			hasEscapedUTF8Chars() const;

	//! Tell you if you have a ascii sequence that is no UTF8 valid sequence
	gzBool			isAsciiString() const;

	//! Tell you if you have a ascii sequence that is an Int64 or Int32
	gzBool			isNum() const;

	//! Tell you if you have a ascii sequence that is a integer or float or double
	gzBool			isReal() const;

	//! Convert from Ascii to UTF8
	/*! Sometimes you have ascii data with e.g. åäö characters that are not valid UTF8 characters
	and therefor you can not convert between UTF8 and gzWideChar. This method casts Ascii to UTF8 */
	gzString		convertAsciiToUTF8() const;

	//! Convert from UTF8 to Ascii
	/*! Sometimes you want tp have have ascii data with e.g. åäö characters that are not valid UTF8 characters
	and therefor you can not convert between UTF8 and Ascii. This method casts UTF8 to Ascii*/
	gzString		convertUTF8ToAscii() const;

	gzString		convertUTF8ToNumList(const gzString &format="0x%02x",const gzString &separator=",") const;

	gzString		convertNumListToUTF8() const;

	gzString		convertTextToCtrl() const;

	gzString		convertCtrlToText(gzBool changeSpace=FALSE,gzBool escapeSingleQuote=TRUE) const;

	//! Get a pointer to a null terminated gzWideChar buffer
	const gzWideChar *	getWideString(gzUInt16 knownLength=0) const;
	
	//! Get a BSTR that contains the length in the first byte. No appended zero in the end
	/* Remember that BSTR strings can contain zero characters but they are limited to max 255 characters */
	gzArray<gzUByte>	getBSTR() const;
	
	//! Get a Wide BSTR that contains the length in the first gzWideChar. No appended zero in the end
	/* Remember that WideBSTR strings can contain zero characters but they are limited to max 65535 characters */
	gzArray<gzWideChar>	getWideBSTR() const;

	//! Scrambles the string with the code value
	gzString &		scramble(gzUInt32 code);

	//! Get the dot value e.g. "255.234.245.23"
	/*! Use this to convert Ip adresses etc into a large number */
	gzInt64		dotValue(gzUInt32 base=256,gzUInt32 *groups=nullptr) const; // e.g. "255.234.245.23"

	//! Changes character from into a to character
	gzUInt16		substitute(char from,char to);

	//! Changes character from into a to character
	gzString		substitute(const gzString &subString,const gzString &replacement) const;

	//! returns True if string contains "yes"
	gzBool			yesNo() const;

	gzUInt64		wrapHash() const;

	//! Calcualtes the hash value of the buffer s with size.
	/* param size Set to zero if string length shall be calculated. */
    static gzUInt32	hash(const char *s , gzUInt32 size=0); 
	
	// Unique string management
	gzBool		isUnique() const;
	gzUInt16	getUniqueID() const;
	gzBool		makeUnique(gzUInt16 uniqueID=0);
	gzBool		checkUnique() const;

	static gzString checkUnique(const char* str);

	// ----- Class Operators ------------------------------

	operator gzInt64 ()		const { return num(); }

	operator gzDouble ()	const { return real(); }

	operator gzFloat ()		const { return realf(); }

    gzString &	operator =(const char *str);

	// Default cast of string to char * (UTF8 or ASCII)
	operator const char *() const;	

    gzString &	operator =(const gzString &str);

    gzString &	operator +=(const char *str);

	gzString 	operator +(const char *str) const;
	
	gzString	operator +(const gzString &str) const;

	gzString &	operator +=(const gzString &str);

    gzString &	operator +=(const char c);
	
	gzString &	operator +=(const gzWideChar wc);

	gzString 	operator +(const char c) const;
	
	gzString 	operator +(const gzWideChar wc) const;

    gzBool		operator !() const { return (m_string == NULL) ? TRUE : (m_string[0] == '\0'); }
	
	char 		operator ()(const gzUInt16 index) const;

	gzString	operator ()(const gzUInt16 index , const gzUInt16 len) const;

	// ---- Global operators --------------------------------

    GZ_BASE_EXPORT friend gzBool	operator ==(const gzString &str, const char *s);
 
    GZ_BASE_EXPORT friend gzBool	operator ==(const char *s, const gzString &str);
    
    GZ_BASE_EXPORT friend gzBool	operator ==(const gzString &str1, const gzString &str2);

    GZ_BASE_EXPORT friend gzBool	operator !=(const gzString &str, const char *s);
    
    GZ_BASE_EXPORT friend gzBool	operator !=(const char *s, const gzString &str);

    GZ_BASE_EXPORT friend gzBool	operator !=(const gzString &str1, const gzString &str2);

	GZ_BASE_EXPORT friend gzBool	operator <(const gzString &str, const char *s);
    
    GZ_BASE_EXPORT friend gzBool	operator <(const char *s, const gzString &str);

    GZ_BASE_EXPORT friend gzBool	operator <(const gzString &str1, const gzString &str2);

	GZ_BASE_EXPORT friend gzBool	operator >(const gzString &str, const char *s);
    
    GZ_BASE_EXPORT friend gzBool	operator >(const char *s, const gzString &str);

    GZ_BASE_EXPORT friend gzBool	operator >(const gzString &str1, const gzString &str2);

	GZ_BASE_EXPORT friend gzBool	operator <=(const gzString &str, const char *s);
 
    GZ_BASE_EXPORT friend gzBool	operator <=(const char *s, const gzString &str);
    
    GZ_BASE_EXPORT friend gzBool	operator <=(const gzString &str1, const gzString &str2);

	GZ_BASE_EXPORT friend gzBool	operator >=(const gzString &str, const char *s);
 
    GZ_BASE_EXPORT friend gzBool	operator >=(const char *s, const gzString &str);
    
    GZ_BASE_EXPORT friend gzBool	operator >=(const gzString &str1, const gzString &str2);

	// -------------------- static utils ------------------------------

	static gzString	spaces(gzUInt16 count,const char fillChar=' ');

private:

	gzChar		mutable	*m_string;
	gzUInt16			m_len;
	gzUInt16	mutable	m_uniqueID;
	gzUInt32			m_hash;
    
};


//! Default empty string to be used for empty string argument passing
const gzString GZ_EMPTY_STRING;

//! Max unique ID for gzString in system
const gzUInt16 GZ_MAX_SYSTEM_UNIQUE_ID=65535;

//! Max unique ID for gzString used by base software
const gzUInt16 GZ_MAX_BASE_UNIQUE_ID=500;

//! String constants
const gzString	GZ_STRING_DOT_SLASH			= "./";
const gzString	GZ_STRING_DOT_BACKSLASH		= ".\\";

const gzString	GZ_STRING_SPACE				= " ";

const gzString	GZ_LOG_IDENTIFIER		= "Gizmo3D";
const gzString	GZ_SYSTEM_IDENTIFIER	= "GizmoSDK";

const gzString	GZ_ATTRIBUTE_LF			= "lf";
const gzString	GZ_ATTRIBUTE_ECHO		= "echo";
const gzString	GZ_ATTRIBUTE_APPEND		= "append";
const gzString	GZ_ATTRIBUTE_CHUNK		= "chunk";
const gzString	GZ_ATTRIBUTE_GLOBAL		= "global";
const gzString	GZ_ATTRIBUTE_PATH		= "path";

const gzString	GZ_STRING_COLON_SEP		= ":";
const gzString	GZ_STRING_SEMI_SEP		= ";";
const gzString	GZ_STRING_SLASH			= "/";
const gzString	GZ_STRING_DOT			= ".";
const gzString	GZ_STRING_D_DOT			= "..";
const gzString	GZ_STRING_COMMA			= ",";
const gzString	GZ_STRING_BACKSLASH		= "\\";
const gzString	GZ_STRING_DSLASH		= "//";
const gzString	GZ_STRING_QUESTION_MARK	= "?";
const gzString	GZ_STRING_AMPERSAND		= "&";
const gzString	GZ_STRING_LEFT_BRACKET	= "[";
const gzString	GZ_STRING_RIGHT_BRACKET	= "]";
const gzString	GZ_STRING_YES			= "yes";
const gzString	GZ_STRING_NO			= "no";
const gzString	GZ_STRING_TRUE			= "true";
const gzString	GZ_STRING_FALSE			= "false";
const gzString	GZ_STRING_NULL			= "null";
const gzString	GZ_STRING_C_YES			= "Yes";
const gzString	GZ_STRING_C_NO			= "No";
const gzString	GZ_STRING_C_TRUE		= "TRUE";
const gzString	GZ_STRING_DOLLAR		= "$";
const gzString	GZ_STRING_PERCENT		= "%";
const gzString	GZ_STRING_DBL_QUOTE		= "\"";
const gzString	GZ_STRING_SGL_QUOTE		= "'";
const gzString	GZ_STRING_NEWLINE		= "\n";
const gzString	GZ_STRING_RETURN		= "\r";
const gzString	GZ_STRING_STAR			= "*";


class GZ_BASE_EXPORT gzUniqueString : public gzString
{
public:
	gzUniqueString(const gzString &copy,gzUInt16 uniqueID=0);
	gzUniqueString(gzUInt16 uniqueID);

	static gzUInt16			getNextFreeId();
	static gzBool			isFreeId(gzUInt16 uniqueID);
	static gzVoid			cleanAllUniqueId();
	static gzUniqueString	getString(gzUInt16 uniqueID);
	static gzVoid			dumpAllUniqueId(gzMessageLevel level = GZ_MESSAGE_DEBUG,gzBool showOnlyAllocated=TRUE);
};

//! Possible values for gzBeep()
enum gzBeepType
{
	GZ_BEEP_DEFAULT,
	GZ_BEEP_ASTERISK,
	GZ_BEEP_EXCLAMATION,
	GZ_BEEP_HAND,
	GZ_BEEP_QUESTION,
	GZ_BEEP_OK
};

//******************************************************************************
// Generic Utilities
//******************************************************************************

//! Initialises the random number sequqnce
GZ_BASE_EXPORT gzVoid gzRandomInit(gzUInt32 seed);

//! Gives random double value between [0.0 and 1.0[ 
GZ_BASE_EXPORT gzDouble gzRandom();

//! Gives random float value between [0.0 and 1.0[ 
GZ_BASE_EXPORT gzFloat gzRandomf();

GZ_BASE_EXPORT gzUInt32 gzRandomUInt32();

//! Gives random normal distributed double value between with mean m and stdev s
GZ_BASE_EXPORT gzDouble gzRandomNormal(const gzDouble &m=0.0,const gzDouble &s=1.0);

//! Gives random weibull distributed double value with sclae factor and shape factor
GZ_BASE_EXPORT gzDouble gzRandomWeibull(const gzDouble &scale=1.0,const gzDouble &shape=1.0);

//! Gives random exponential distributed double value with rate factor 
GZ_BASE_EXPORT gzDouble gzRandomExponential(const gzDouble &rate=1.0);

//! Gives random double value between [0.0 and 1.0[
GZ_BASE_EXPORT const gzDouble &gzRandom(gzUInt32 seqIndex);

//! Checks if unsigned int value is power of two
GZ_BASE_EXPORT gzBool gzIsPowerOfTwo(const gzUInt64 & v);

//! Checks if value is power of two
GZ_BASE_EXPORT gzBool gzIsDoublePowerOfTwo(gzDouble number);

//! Gets value that is power of two and that is larger or equal to number
GZ_BASE_EXPORT gzDouble gzGetUpperPowerOfTwo(gzDouble number);

//! Gets the exponent for the value that is a power of two
GZ_BASE_EXPORT gzInt32 gzGetUpperPowerOfTwoExponent(gzDouble number);

//! Generates an ascii representation of the long integer number with radix 
GZ_BASE_EXPORT gzVoid gzLtoA( char * buffer , gzInt64 number , gzUByte radix , gzInt16 precision=0 , gzUInt16 *len=nullptr , gzBool upper=FALSE);

//! Generates an unicode representation of the long integer number with radix 
GZ_BASE_EXPORT gzVoid gzLtoA( gzWideChar * buffer , gzInt64 number , gzUByte radix , gzInt16 precision=0 , gzUInt16 *len=nullptr , gzBool upper=FALSE);

//! Generates an ascii representation of the long integer number with radix 
GZ_BASE_EXPORT gzVoid gzULtoA( char * buffer , gzUInt64 number , gzUByte radix , gzInt16 precision=0 , gzUInt16 *len=nullptr , gzBool upper=FALSE);

//! Generates an unicode representation of the long integer number with radix 
GZ_BASE_EXPORT gzVoid gzULtoA( gzWideChar * buffer , gzUInt64 number , gzUByte radix , gzInt16 precision=0 , gzUInt16 *len=nullptr , gzBool upper=FALSE);

//! Generates an ascii identifier representation of the unsigned long integer number
GZ_BASE_EXPORT gzVoid gzULtoIdent( char * buffer , gzUInt32 maxlen, gzUInt64 number , gzInt16 precision=0 , gzUInt16 *len=nullptr );

//! Generates an ascii representation of the double precision number
GZ_BASE_EXPORT gzVoid gzDtoA( char * buffer , gzDouble number , gzInt16 precision=6 , gzUInt16 *len=nullptr , gzInt32 digits=15);

//! Generates an unicode representation of the double precision number
GZ_BASE_EXPORT gzVoid gzDtoA( gzWideChar * buffer , gzDouble number , gzInt16 precision=6 , gzUInt16 *len=nullptr , gzInt32 digits=15);

//! Calculated the faculty of a number
GZ_BASE_EXPORT gzDouble gzFaculty( gzUInt32 num);

//! Calculated the combination C of two numbers
GZ_BASE_EXPORT gzDouble gzCombination( gzUInt32 n , gzUInt32 p);

GZ_BASE_EXPORT gzDouble gzPow10(gzInt16 power);

//! Rounding of double to x digits precision
GZ_BASE_EXPORT gzDouble gzPrecision( gzDouble number , gzUInt16 digits , gzBool round=TRUE);

//! Encode UTF8 to ULong
GZ_BASE_EXPORT gzUInt32 gzUTF8ToULong(const char *adress,gzUByte *size=nullptr);

//! Decode ULong to UTF8
GZ_BASE_EXPORT gzUByte gzUInt32ToUTF8(char *adress,gzUInt32 data);

//! Return size of UTF8 encoding for data
GZ_BASE_EXPORT gzUByte gzUTF8Size(gzUInt32 data);

//! Return size of UTF8 encoding for adress
GZ_BASE_EXPORT gzUByte gzUTF8Size(const char *adress);

GZ_BASE_EXPORT gzInt32 gzGetLastSysError();

GZ_BASE_EXPORT gzVoid gzSetLastSysError(gzInt32 error=0);

GZ_BASE_EXPORT	gzString gzGetSysErrorDescription(gzInt32 error);

//! Returns yes/no/YES/NO depending on value
GZ_BASE_EXPORT gzString gzYesNo(gzBool value,gzBool upperCase=FALSE);

GZ_BASE_EXPORT	gzBool gzBigEndian();

GZ_BASE_EXPORT	gzVoid gzBeep(gzBeepType beepType = GZ_BEEP_DEFAULT);

GZ_BASE_EXPORT	gzBool gzIsValidIpAddress(const gzString& ipAddress, gzUInt32 groups = 4);

GZ_BASE_EXPORT	gzBool gzAttachConsole();

//! Expands $(xxx) to reg key xxx values in a new string
//! Expands ${yyy} to inet iface yyy ip a.b.c.d
GZ_BASE_EXPORT	gzString gzRegKeyExpandedString(const gzString &compressed);

GZ_BASE_EXPORT gzVoid flipEndian(gzUInt64 &a);

GZ_BASE_EXPORT gzInt32 gzwcslen(const gzWideChar *string);

//! Return current working dir as gzString
GZ_BASE_EXPORT gzString gzGetCWD();

GZ_BASE_EXPORT gzString gzGetProcessName();

//! Simplifies path to remove .. and . except options ?
GZ_BASE_EXPORT gzString gzSimplifyPath(const gzString& path);

GZ_BASE_EXPORT gzString gzGetEnv(const gzString& env);
GZ_BASE_EXPORT gzVoid gzPutEnv(const gzString& env, const gzString& key);

//******************************************************************************
// Struct	: gzTranslation
//
// Purpose  : Data item for a translation
//
// Notes	: -
//
// Revision History...
//
// Who	Date	Description
//
// AMO	000531	Created 
//									
//******************************************************************************
struct gzTranslation
{
	gzString	language;
	gzString	context;
	gzString	message;
	gzString	translation;
};

GZ_BASE_EXPORT gzArray<gzTranslation> getDefaultTranslations();

// ------------------------ gzSerializeAdapterError ---------------------------

//! gzSerializeAdapterError is used to inform a user of an adapter if anything went wrong in reading data from an adapter

enum gzSerializeAdapterError
{
	GZ_SERIALIZE_ADAPTER_ERROR_NO_ERROR,

	GZ_SERIALIZE_ADAPTER_ERROR_MISSING_URL,
	GZ_SERIALIZE_ADAPTER_ERROR_ACCESS_DENIED,
	GZ_SERIALIZE_ADAPTER_ERROR_WRITE_NOT_ALLOWED,
	GZ_SERIALIZE_ADAPTER_ERROR_FAILED_TO_CONNECT,
	GZ_SERIALIZE_ADAPTER_ERROR_BROKEN_ACCESS,
	GZ_SERIALIZE_ADAPTER_ERROR_URL_SYNTAX,
	GZ_SERIALIZE_ADAPTER_ERROR_MISSING_URL_PROVIDER,
	GZ_SERIALIZE_ADAPTER_ERROR_FORMAT_ERROR,
	GZ_SERIALIZE_ADAPTER_ERROR_TIMEOUT,
	GZ_SERIALIZE_ADAPTER_ERROR_OTHER,
};

//! Possible root values for your registry entries
enum gzRegKeyHeader
{
	GZ_KEY_LOCAL_MACHINE,
	GZ_KEY_CURRENT_USER,
	GZ_KEY_CLASSES_ROOT,
};

//! Default registry location prefix
const gzString GIZMOSDK_END				=	"/GizmoSDK";							// Defines deafult key ending for GizmoSDK
const gzString GZ_DEFAULT_KEY_HEADER	=	"software/Saab"  "/GizmoSDK";			// Defines default key registry and adds ending
const gzString GZ_DEFAULT_REGISTRY		=	"/usr/local/gizmosdk/gizmosdk.reg";


//******************************************************************************
// Class	: gzKeyDatabase
//									
// Purpose  : Management of key data
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990518	Created 
//									
//******************************************************************************
/*! \brief Provides a generic user and global environment access

The gzKeyDatabase handles symbolic values in a global or user context. There are also
support for password protected values etc.

*/
class  GZ_BASE_EXPORT gzKeyDatabase
{
public:
	
	// ------------ global used keys ------------------
	static gzBool  	existGlobalKey(gzString key, const gzString & password="", gzBool useEnv = TRUE);

	static gzBool  	setGlobalKey(gzString key , gzString value, const gzString & password="",gzBool useEnv=TRUE);
	static gzString getGlobalKey(gzString key, const gzString & password="", gzBool useEnv = TRUE);
	static gzString getDefaultGlobalKey(gzString key, const gzString &defaultValue , const gzString & password="", gzBool useEnv = TRUE);
	static gzBool	removeGlobalKey(gzString key, const gzString & password="");

	// ------------ local user key values -------------
	static gzBool  	existUserKey(gzString key, const gzString & password="", gzBool onlyUserKey=FALSE, gzBool useEnv = TRUE);

	static gzBool  	setUserKey(gzString key , gzString value , const gzString & password="", gzBool useEnv = TRUE);
	static gzString getUserKey(gzString key , const gzString & password="" , gzBool onlyUserKey=FALSE, gzBool useEnv = TRUE);
	static gzString getDefaultUserKey(gzString key , const gzString &defaultValue , const gzString & password="" , gzBool onlyUserKey=FALSE, gzBool useEnv = TRUE);
	static gzBool	removeUserKey(gzString key , const gzString & password="", gzBool onlyUserKey=FALSE);

	// ------------ generic key values ----------------
	static gzBool	setRegKey(gzRegKeyHeader keyRootHeader, gzString  keyHeader, const gzString &keyName , const gzString &value);
	static gzBool	existRegKey(gzRegKeyHeader keyRootHeader, gzString  keyHeader, const gzString &keyName );
	static gzBool	removeRegKey(gzRegKeyHeader keyRootHeader, gzString  keyHeader, const gzString &keyName );
	static gzString getRegKey(gzRegKeyHeader keyRootHeader, gzString  keyHeader, const gzString &keyName );
	static gzString getDefaultRegKey(gzRegKeyHeader keyRootHeader, gzString  keyHeader, const gzString &keyName, const gzString &defaultValue);

	static gzVoid			setDefaultKeyHeader(const gzString &header);
	static const gzString &	getDefaultKeyHeader();

	static gzBool			setDefaultRegistry(const gzString &file_url, gzString password=GZ_EMPTY_STRING, gzString* errorString=nullptr, gzSerializeAdapterError* errorType=nullptr);
	static const gzString &	getDefaultRegistry();

	// ------------ local settings --------------------
	static gzBool	setLocalRegistry(const gzString &url, gzString password=GZ_EMPTY_STRING, gzString* errorString=nullptr, gzSerializeAdapterError* errorType=nullptr,gzBool useChecksum=FALSE);
	static gzVoid	enableSystemRegistry(gzBool enable=TRUE);

	// ------------ get settings --------------------
	static gzString	getLocalRegistryURL(void);

};

//******************************************************************************
// Class	: gzDirectory
//									
// Purpose  : General purpose class for Filesystem access etc.
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990602	Created 
//									
//******************************************************************************
/*! \brief General purpose class for Filesystem access etc.

The gzDirectory encapsulates the platform dependant file system. 

*/
class GZ_BASE_EXPORT gzDirectory
{
public:
	// Searches the system key GIZMO_PATH variable and expands the filename to full path
	static gzString getExtendedFileName(gzString filename);
};

//******************************************************************************
// Class	: gzDirectoryEntry
//									
// Purpose  : Holds data about a directory entry
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990602	Created 
//									
//******************************************************************************
//! Holds data about a directory entry
class GZ_BASE_EXPORT gzDirectoryEntry
{
public:
	gzDirectoryEntry():m_isDirectory(FALSE){};

	gzBool isDirectory();
	
	gzString getPath();
	
	gzString getEntryName();

private:

	friend class gzDirectoryIterator;
	gzDirectoryEntry(gzString name , gzString path , gzBool isDirectory);
	
	gzString	m_name;
	gzString	m_path;
	gzBool		m_isDirectory;
};

//******************************************************************************
// Class	: gzDirectoryIterator
//									
// Purpose  : iterates a given path to find files or directories
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990602	Created 
//									
//******************************************************************************
//! Iterator class for directory entries
class  GZ_BASE_EXPORT gzDirectoryIterator
{
public:
	gzDirectoryIterator(const gzString &path , gzBool recursive=FALSE );
	
	virtual ~gzDirectoryIterator();

	gzBool 				foundEntry();
	
	gzDirectoryEntry 	getEntry();

	GZ_NO_IMPLICITS(gzDirectoryIterator);
	
private:

	gzDirHandle			m_dirp;
	gzDirEntry			m_entry;
	gzString			m_path;
	gzBool				m_recursive;
	gzDirectoryEntry	m_currentEntry;
	gzDirectoryIterator *m_iterator;
};

class gzSerializeAdapter; // Forward decl for serializers

//******************************************************************************
// Class	: gzNameInterface
//									
// Purpose  : Interface for named objects. 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	990520	Created 
//									
//******************************************************************************
class gzNameInterface
{
public:
	GZ_BASE_EXPORT	gzNameInterface(const gzString &name=GZ_EMPTY_STRING);

	GZ_BASE_EXPORT	virtual ~gzNameInterface(){};

	GZ_BASE_EXPORT	const gzString &	getName() const;
	GZ_BASE_EXPORT	gzVoid				setName(const gzString &name);
	GZ_BASE_EXPORT	gzBool				hasName() const;

	GZ_BASE_EXPORT gzVoid	write(gzSerializeAdapter *adapter);
	GZ_BASE_EXPORT gzVoid	read(gzSerializeAdapter *adapter);
	GZ_BASE_EXPORT gzUInt32	getDataSize(gzSerializeAdapter *adapter=nullptr) const;


private:

	gzLateBindData<gzString>	m_name;
};

//******************************************************************************
// Class	: gzUpdateIDInterface
//									
// Purpose  : Interface for update numbers of a counter 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	001206	Created 
//									
//******************************************************************************
//! The purpose of these functions is to assure that there are no changes to the data in an
//! instanse as long as the update id value is the same. The user is responsible to call updateID()
//! when he alters the contents in the data.
class GZ_BASE_EXPORT gzUpdateIDInterface
{
public:

	gzUpdateIDInterface(){m_updateID=(gzUInt32)gzPtr2Val(this);}

	gzUpdateIDInterface(const gzUpdateIDInterface & /*copy*/ ){m_updateID=(gzUInt32)gzPtr2Val(this);}

	gzUpdateIDInterface & operator=(const gzUpdateIDInterface & /*copy*/ ){m_updateID=(gzUInt32)gzPtr2Val(this);return *this;}

	gzUInt32	getUpdateID()				{ return m_updateID; }

	gzVoid	setUpdateID(gzUInt32 id)		{ m_updateID=id; }

	gzVoid	updateID()					{ ++m_updateID;}

private:

	gzUInt32	m_updateID;
};

//******************************************************************************
// Class	: gzUpdateIDFeatureInterface
//									
// Purpose  : Interface for update numbers of a counter 
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040601	Created 
//									
//******************************************************************************
//! The purpose of these functions is to assure that there are no changes to the data in an
//! instanse as long as the update id value is the same. The user is responsible to call updateID()
//! when he alters the contents in the data.
class gzUpdateIDFeatureInterface
{
public:

	GZ_BASE_EXPORT gzUpdateIDFeatureInterface();

	GZ_BASE_EXPORT gzUpdateIDFeatureInterface(const gzUpdateIDFeatureInterface &copy);

	GZ_BASE_EXPORT gzUpdateIDFeatureInterface & operator=(const gzUpdateIDFeatureInterface &copy);

	GZ_BASE_EXPORT gzUInt32	getUpdateID();

	GZ_BASE_EXPORT gzVoid	setUpdateID(gzUInt32 id);

	GZ_BASE_EXPORT gzVoid	updateID(gzUInt32 featureMask=0xFFFFFFFFUL);

	// Feature mask

	GZ_BASE_EXPORT gzVoid	setFeatureMask(gzUInt32 mask);

	// Done per lookup id
	
	GZ_BASE_EXPORT gzVoid	resetFeatureMask(gzUInt32 mask=0xFFFFFFFFUL,gzUInt32 lookup=0);

	GZ_BASE_EXPORT gzBool	checkFeature(gzUInt32 mask,gzUInt32 lookup=0);

private:

	class gzUpdateIDFeature
	{
	public:

		gzUpdateIDFeature():m_featureMask(0xFFFFFFFFUL){};
		
		gzUInt32	m_featureMask;
	};

	gzUInt32	m_updateID;

	gzDynamicArray<gzUpdateIDFeature>	m_lookup_feature_data;
};

//******************************************************************************
// Class	: gzLookupUpdateID
//									
// Purpose  : Manages update id per lockup id
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	040601	Created 
//									
//******************************************************************************
class gzLookupUpdateID 
{
public:

	GZ_BASE_EXPORT	gzLookupUpdateID();

	GZ_BASE_EXPORT	gzVoid	setUpdateID(gzUInt32 lookup,gzUInt32 id);

	GZ_BASE_EXPORT	gzUInt32	getUpdateID(gzUInt32 lookup);

	GZ_BASE_EXPORT	gzVoid	clear();

private:

	class gzLookupUpdateData 
	{
		public:
			gzLookupUpdateData():m_id(0){}

		gzUInt32 m_id;
	};

	gzDynamicArray<gzLookupUpdateData> m_lookup_id;
};


//******************************************************************************
// Class	: gzUniqueIDManager
//									
// Purpose  : Manages a set of unique IDs
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030313	Created 
//									
//******************************************************************************
class gzUniqueIDManager 
{
public:

	GZ_BASE_EXPORT gzUniqueIDManager();

	GZ_BASE_EXPORT virtual ~gzUniqueIDManager();

	GZ_BASE_EXPORT gzUInt32 allocateID();

	GZ_BASE_EXPORT gzVoid freeID(gzUInt32 id);

private:

	gzQueue<gzUInt32>	m_idRep;

	gzUInt32				m_lastID;
};

//******************************************************************************
// Class	: gzFlag
//									
// Purpose  : Boolean flag with default false value
//									
// Notes	: 
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	030313	Created 
//									
//******************************************************************************
class gzFlag
{
public:

	gzFlag():m_flag(FALSE){}
	
	gzFlag(const gzBool &right):m_flag(right){}
	
	gzVoid operator =(const gzBool &right)
	{
		m_flag=right;
	}
	
	gzVoid setFlag(gzBool on)
	{
		m_flag=on;
	}
	
	operator gzBool() const
	{
		return m_flag!=0;
	}
	

private:

	gzBool m_flag;
};

//------------------------------ SAFE utilities for platform independance -----------------------

GZ_BASE_EXPORT gzVoid strcpy_safe(gzChar * destination, const gzChar * source, gzUInt16 maxBufferSize);
GZ_BASE_EXPORT gzUInt16 strlen_safe(const gzChar * source, gzUInt16 maxBufferSize);

#endif // __GZ_BASE_H__

