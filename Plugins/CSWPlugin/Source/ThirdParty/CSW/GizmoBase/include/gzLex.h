//******************************************************************************
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
// File			: gzLex.h
// Module		: gzBase
// Description	: Class definition of Lex classes
// Author		: Anders Modén		
// Product		: GizmoBase 2.12.275
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
// AMO	000728	Created file 	
// AMO	121011	Updated BNF tracing with exit information		(2.6.16)
//
//******************************************************************************

#ifndef __GZ_LEX_H__
#define __GZ_LEX_H__

/*!	\file
	\brief Lexical utilities
*/

#include "gzSerialize.h"
#include "gzDynamic.h"
#include "gzPerformance.h"
#include "gzUniqueStrings.h"

typedef enum
{
	GZ_LEX_EMPTY = 0,
	GZ_LEX_TOKEN = (1 << 0),
	GZ_LEX_IDENTIFIER = (1 << 1),

	GZ_LEX_DOUBLE_STRING = (1 << 2),
	GZ_LEX_SINGLE_STRING = (1 << 3),
	GZ_LEX_STRING = GZ_LEX_SINGLE_STRING + GZ_LEX_DOUBLE_STRING,

	GZ_LEX_INTEGER = (1 << 4),
	GZ_LEX_REAL = (1 << 5),
	GZ_LEX_LONGLONG = (1 << 6),
	GZ_LEX_NUMBER = GZ_LEX_INTEGER + GZ_LEX_REAL + GZ_LEX_LONGLONG,

	GZ_LEX_COMMENT = (1 << 7),
	GZ_LEX_WHITESPACE = (1 << 8),
	GZ_LEX_ERROR = (1 << 9),
	GZ_LEX_SET = (1 << 10)

} gzLexDataType;

typedef enum
{
	GZ_LEX_ERROR_IN_INTEGER = 1,
	GZ_LEX_ERROR_IN_REAL,
	GZ_LEX_ERROR_UNEXPECTED_END_OF_COMMENT,
	GZ_LEX_ERROR_UNEXPECTED_END_OF_INTEGER,
	GZ_LEX_ERROR_UNEXPECTED_END_OF_REAL,
	GZ_LEX_ERROR_UNEXPECTED_END_OF_STRING,
	GZ_LEX_ERROR_UNEXPECTED_END_OF_SET
} gzLexErrorType;

const gzUInt16 USE_COMMA_AND_DOT = 9999; //! Allow both '.' and ',' as decimal separator

class gzLexTokenData
{
public:

	gzBool operator==(const gzLexTokenData& right) { return (type == right.type) && (data == right.data); }
	gzBool operator!=(const gzLexTokenData& right) { return (type != right.type) || (data != right.data); }

	gzLexDataType	type;
	gzDynamicType	data;
};

//******************************************************************************
// Class	: gzSerializeLex
//									
// Purpose  : -
//									
// Notes	: -
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	000728	Created 
//									
//******************************************************************************
class  gzSerializeLex : public gzSerializeData
{
public:

	GZ_BASE_EXPORT gzSerializeLex(gzBool useUnicodeTag = FALSE, gzBool useUtf8Tag = FALSE);

	GZ_BASE_EXPORT virtual ~gzSerializeLex() {};

	GZ_BASE_EXPORT virtual gzVoid write(gzSerializeAdapter* adapter) override;

	GZ_BASE_EXPORT virtual gzVoid read(gzSerializeAdapter* adapter) override;

	GZ_BASE_EXPORT virtual gzVoid pushBack(gzSerializeAdapter* adapter) override;

	GZ_BASE_EXPORT virtual gzUInt32	getDataSize(gzSerializeAdapter* adapter = nullptr) const override;

	GZ_BASE_EXPORT	gzLexDataType getDataType();

	GZ_BASE_EXPORT	gzDynamicType getData();

	//Generic settings for scanner

	GZ_BASE_EXPORT gzVoid usePlainIdentifier(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid useIdentifiers(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid useUnicode(gzBool on = FALSE, gzBool bigEndian = TRUE);
	GZ_BASE_EXPORT gzVoid useUtf8(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid useHashComment(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid useSlashComment(gzBool on = TRUE);
	GZ_BASE_EXPORT gzVoid useComment(gzBool on = TRUE);
	GZ_BASE_EXPORT gzVoid useStrings(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid useSet(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid useEscape(gzBool on = TRUE);
	GZ_BASE_EXPORT gzVoid useEscapeUnicode(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid useTokensOnly(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid useDecimalToken(gzUInt16 token = '.');
	GZ_BASE_EXPORT gzVoid useHexMode(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid useBinMode(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid useOctMode(gzBool on = FALSE);
	GZ_BASE_EXPORT gzVoid setMaxScanTokens(gzUInt32 tokens = 0xFFFFFFFFUL);

	//! Combined data type and data
	GZ_BASE_EXPORT	gzLexTokenData getTokenData();

	GZ_BASE_EXPORT	gzString	getScannedBuffer();

	GZ_BASE_EXPORT	gzVoid		qPush(gzUInt16 data);

	GZ_BASE_EXPORT	gzVoid		qPushBack(gzSerializeAdapter* adapter);

	GZ_BASE_EXPORT	gzVoid		pushBack(gzSerializeAdapter* adapter, gzWideChar token);

	GZ_BASE_EXPORT	gzUInt32	getEncoding(gzUInt16 data);

	GZ_BASE_EXPORT	gzWideChar	getLexToken(gzSerializeAdapter* adapter);

	GZ_BASE_EXPORT	gzUByte		getTokenSize() const;

private:

	typedef enum
	{
		ENCODE_WHITESPACE = (1 << 0),
		ENCODE_BINARY_DIGIT = (1 << 1),
		ENCODE_OCTAL_DIGIT = (1 << 2),
		ENCODE_HEX_DIGIT = (1 << 3),
		ENCODE_LETTER = (1 << 4),
		ENCODE_DIGIT = (1 << 5),
		ENCODE_ID_START = (1 << 6),
		ENCODE_ID_REST = (1 << 7),
		ENCODE_HEX_DIGIT_SMALL = (1 << 8),
		ENCODE_HEX_DIGIT_LARGE = (1 << 9),
	} Encoding;

	typedef enum
	{
		STATE_DEFAULT,
		STATE_IDENTIFIER,
		STATE_INTEGER,
		STATE_SIGNED_INTEGER_ADD,
		STATE_SIGNED_INTEGER_SUB,
		STATE_REAL,
		STATE_REAL_EXP,
		STATE_REAL_EXP_SIGN,
		STATE_REAL_EXP_ADD,
		STATE_REAL_EXP_SUB,
		STATE_DOUBLE_STRING,
		STATE_SINGLE_STRING,
		STATE_SET,
		STATE_ESQAPE_STRING,
		STATE_ESQAPE_SINGLE_STRING,
		STATE_ESQAPE_SET,
		STATE_IN_DIV,
		STATE_COMMENT_CPP,
		STATE_COMMENT_C,
		STATE_COMMENT_C_END,
		STATE_WHITESPACE,
		STATE_EXT_INTEGER,
		STATE_HEX_INTEGER,
		STATE_BIN_INTEGER,
		STATE_OCT_INTEGER,
	} LexState;


	gzLexDataType		m_dataType;
	gzDynamicType		m_data;
	gzQueue<gzUByte>	m_queue;

	gzUInt16			m_decimalToken;

	gzBool				m_useHashComment : 1;
	gzBool				m_useSlashComment : 1;
	gzBool				m_useComment : 1;
	gzBool				m_useUnicodeTag : 1;
	gzBool				m_useUtf8Tag : 1;
	gzBool				m_useStrings : 1;
	gzBool				m_useSet : 1;
	gzBool				m_useEscape : 1;
	gzBool				m_useUnicode : 1;
	gzBool				m_bigEndian : 1;
	gzBool				m_firstRun : 1;
	gzBool				m_usePlainIdentifier : 1;
	gzBool				m_useTokensOnly : 1;
	gzBool				m_useHexMode : 1;
	gzBool				m_useBinMode : 1;
	gzBool				m_useOctMode : 1;
	gzBool				m_useUtf8 : 1;
	gzBool				m_useIdentifiers : 1;
	gzBool				m_useEscapeUnicode : 1;

	gzUInt32			m_maxScanTokens;

};

class gzStringTokenizer : public gzSerializeLex
{
public:

	GZ_BASE_EXPORT gzStringTokenizer(const char* string, gzInt32 len = -1);

	GZ_BASE_EXPORT gzStringTokenizer(const gzString& string);

	GZ_BASE_EXPORT gzStringTokenizer(const gzWideChar* string, gzInt32 len = -1);

	GZ_BASE_EXPORT ~gzStringTokenizer();

	GZ_BASE_EXPORT gzLexDataType getDataType(gzBool iterate = TRUE);

	GZ_BASE_EXPORT gzString getRemainingBuffer();

	GZ_BASE_EXPORT gzUInt32 getRemainingTokens();

	using gzSerializeLex::pushBack;		// Tell compiler we want this as well

	GZ_BASE_EXPORT gzVoid pushBack(const gzString& back);

	GZ_BASE_EXPORT gzVoid pushBack();

	GZ_BASE_EXPORT gzBool hasData(gzUInt32 minCount = 1);

	GZ_BASE_EXPORT gzWideChar getLexToken();

	//! Combined data type and data
	GZ_BASE_EXPORT	gzLexTokenData getTokenData(gzBool iterate = TRUE);

private:

	gzArray<gzUByte>			m_data;
	gzSerializeAdapterMemory	m_adapter;
	gzBool						m_unicode;
};

typedef gzArray<gzLexTokenData> gzLexTokenDataArray;

//! Utility to tokenize a string into a gzLexTokenDataArray
gzLexTokenDataArray	GZ_BASE_EXPORT getLexTokenDataArray(const char* string, gzBool skipWhiteSpace = TRUE);

//! Utility to check argument argPos in array for value
gzBool GZ_BASE_EXPORT checkLexToken(const gzLexTokenDataArray& array, const gzUInt32 argPos, const gzLexDataType& type, const gzDynamicType& data);

//! Utility to check argument argPos in array. Gets value in valid pointer
gzBool GZ_BASE_EXPORT checkLexToken(const gzLexTokenDataArray& array, const gzUInt32 argPos, const gzLexDataType& type, gzDynamicType* data = nullptr);

//! Parse a string with syntax values
/*! The following format parser control can be used

	%l	-	parse for GZ_LEX_INTEGER or GZ_LEX_LONGLONG
	%n	-	parse for GZ_LEX_NUMBER
	%x	-	parse for GZ_LEX_INTEGER or GZ_LEX_LONGLONG in hex

	%s	-	parse for GZ_STRING

	%e  -	parse for rest of indata string

	%t	-	parse for GZ_LEX_TOKEN
	%i	-	parse for GZ_LEX_IDENTIFIER
	%p  -	parse for GZ_LEX_IDENTIFIER with only plain charachers

	%w	-	skip optional whitespace

	%';./&'	- skip for optional character in set of tokens ';' or '.' or '/' or '&'

	%" bnf syntax " - use extended bnf syntax

	All other tokens and identifiers as matched
*/
gzArray<gzString> GZ_BASE_EXPORT parse(const gzString& parseFormatString, const gzString& dataString, gzBool* success = nullptr, gzUInt16 decimalToken = '.', gzBool useUTF8 = TRUE);


//******************************************************************************
// Class	: gzArgumentParser
//									
// Purpose  : parse arguments from main or from a given string
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
//! Parse arguments from main() or from a given string
class gzArgumentParser
{
public:

	//! Used to create the gzArgumentParser from the parameters given in main(argc,argv)
	GZ_BASE_EXPORT	gzArgumentParser(int argc, char* argv[], const gzString& optionPrefix = "-");

	//! Used to create the gzArgumentParser from the parameters given in main(argc,argv)
	GZ_BASE_EXPORT	gzArgumentParser(int argc, gzWideChar* argv[], const gzString& optionPrefix = "-");

	//! Used to create the gzArgumentParser from a given generic string
	GZ_BASE_EXPORT	gzArgumentParser(const gzString& argString, const gzString& optionPrefix = "-");

	//! Destructor
	GZ_BASE_EXPORT	virtual ~gzArgumentParser();

	//! Used to parse a new given string
	GZ_BASE_EXPORT	gzVoid setArgumentString(const gzString& argString, const gzString& optionPrefix = "-");

	GZ_BASE_EXPORT gzString getArgumentString(gzBool notUsedForOptions = TRUE) const;

	GZ_BASE_EXPORT gzString getArgOptString() const;

	// Option based -option or --option

	//! Get number of options
	/*!
		\return the number of given options. An option is a string preceeded by the optionPrefix normally set to -
	*/
	GZ_BASE_EXPORT	gzUInt32		getOptionCount() const;

	//! Check if option is present
	/*!
		\return TRUE if the option is present
	*/
	GZ_BASE_EXPORT	gzBool		hasOption(const gzString& option, gzBool caseSensitive = FALSE, gzUInt32* argument = nullptr, gzUInt32* maxArgument = nullptr) const;

	GZ_BASE_EXPORT	gzBool		getOptionValue(const gzString& option, const gzBool& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;
	GZ_BASE_EXPORT	gzByte		getOptionValue(const gzString& option, const gzByte& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;
	GZ_BASE_EXPORT	gzUInt16	getOptionValue(const gzString& option, const gzUInt16& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;
	GZ_BASE_EXPORT	gzInt16		getOptionValue(const gzString& option, const gzInt16& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;
	GZ_BASE_EXPORT	gzUInt32	getOptionValue(const gzString& option, const gzUInt32& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;
	GZ_BASE_EXPORT	gzInt32		getOptionValue(const gzString& option, const gzInt32& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;
	GZ_BASE_EXPORT	gzInt64		getOptionValue(const gzString& option, const gzInt64& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;
	GZ_BASE_EXPORT	gzUInt64	getOptionValue(const gzString& option, const gzUInt64& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;
	GZ_BASE_EXPORT	gzFloat		getOptionValue(const gzString& option, const gzFloat& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;
	GZ_BASE_EXPORT	gzDouble	getOptionValue(const gzString& option, const gzDouble& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;
	GZ_BASE_EXPORT	gzString	getOptionValue(const gzString& option, const gzString& defaultValue, gzUInt32 argument = 0, gzBool useDefault = TRUE, gzBool caseSensitive = FALSE) const;

	GZ_BASE_EXPORT	gzString	getOptionString(const gzString& option, gzBool caseSensitive = FALSE) const;

	// argument position based (options excluded)

	GZ_BASE_EXPORT	gzUInt32	getArgumentCount(gzBool notUsedForOption = TRUE) const;

	GZ_BASE_EXPORT	gzString	getArgument(gzUInt32 argpos, gzBool notUsedForOption = TRUE) const;

	GZ_BASE_EXPORT	gzBool		getArgumentValue(gzUInt32 argpos, const gzBool& defaultValue) const;
	GZ_BASE_EXPORT	gzByte		getArgumentValue(gzUInt32 argpos, const gzByte& defaultValue) const;
	GZ_BASE_EXPORT	gzUInt16	getArgumentValue(gzUInt32 argpos, const gzUInt16& defaultValue) const;
	GZ_BASE_EXPORT	gzInt16		getArgumentValue(gzUInt32 argpos, const gzInt16& defaultValue) const;
	GZ_BASE_EXPORT	gzUInt32	getArgumentValue(gzUInt32 argpos, const gzUInt32& defaultValue) const;
	GZ_BASE_EXPORT	gzInt32		getArgumentValue(gzUInt32 argpos, const gzInt32& defaultValue) const;
	GZ_BASE_EXPORT	gzInt64		getArgumentValue(gzUInt32 argpos, const gzInt64& defaultValue) const;
	GZ_BASE_EXPORT	gzUInt64	getArgumentValue(gzUInt32 argpos, const gzUInt64& defaultValue) const;
	GZ_BASE_EXPORT	gzDouble	getArgumentValue(gzUInt32 argpos, const gzDouble& defaultValue) const;
	GZ_BASE_EXPORT	gzString	getArgumentValue(gzUInt32 argpos, const gzString& defaultValue) const;

	// Error management

	GZ_BASE_EXPORT	gzVoid		exitOnError(gzBool on = TRUE);
	GZ_BASE_EXPORT	gzBool		hasError() const;
	GZ_BASE_EXPORT	gzString	getError() const;
	GZ_BASE_EXPORT	gzVoid		setSyntaxString(const gzString& syntax);
	GZ_BASE_EXPORT	gzVoid		checkArgumentCount(gzUInt32 required) const;

private:

	gzVoid	terminateCheck() const;

	class gzArgOption : public gzReference
	{
	public:
		gzString		option;
		gzUInt32			argument;

		gzReference* clone() const { return new gzArgOption(*this); }

	};

	class gzArgArgument : public gzReference
	{
	public:
		gzString		argument;
		gzBool			usedForOption;

		gzReference* clone() const { return new gzArgArgument(*this); };
	};

	gzRefList<gzArgOption>		m_optionList;

	gzRefList<gzArgArgument>	m_argList;

	gzString					m_error;

	gzString					m_syntax;

	gzString					m_argOptString;

	gzBool						m_exitOnError;

};

// ----------------------- Parser Stuff --------------------------------

//! Possible exceptions during parsing in gzBasicParser
enum gzBasicParseException
{
	GZ_PARSE_EXCEPTION_OUT_OF_DATA,
	GZ_PARSE_EXCEPTION_DATA_IS_DISCARDED,
	GZ_PARSE_EXCEPTION_USER_EXIT,
	GZ_PARSE_EXCEPTION_GENERIC_ERROR,
	GZ_PARSE_EXCEPTION_EARLY_EXIT,				//! Controlled early exit. No Error generated
};

//! Generic returnvalues of parsing functions
enum gzParseResult
{
	GZ_PARSE_ERROR = 0,	// Error occured
	GZ_PARSE_OK = 1,	// Ok
	GZ_PARSE_NO_MATCH = 2,	// Tested tokens did not match. Tokens are pushed back
};


struct gzTokenPos
{
	gzUInt32	tokenPos;
	gzUInt32	itemID;
	gzBool		accepted;
};

//******************************************************************************
// Class	: gzParserFunction
//									
// Purpose  : Generic utility to register you parser callback functions
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
template <class T, class BaseParser> class gzParserFunction : public BaseParser
{
public:

	gzParserFunction() :m_itemID(0)
	{
		m_propertyEnableTrace = FALSE;
		m_propertyEnablePerfMon = FALSE;
		m_propertyCaseSensitive = TRUE;
	}

	virtual ~gzParserFunction()
	{
	}

	typedef gzParseResult(T::* ThisPtr)();

	class gzFuncInfo : public gzReference
	{
	public:

		gzFuncInfo(ThisPtr func) :m_func(func) {}

		virtual ~gzFuncInfo() {}

		ThisPtr getFunction() { return m_func; }

	private:

		ThisPtr m_func;
	};

	class gzRuleInfo : public gzReference
	{
	public:

		gzRuleInfo(const gzString& rule) :m_rule(rule) {}

		virtual ~gzRuleInfo() {}

		const gzString& getRule() { return m_rule; }

	private:

		gzString m_rule;
	};


	gzParseResult parse_OR(ThisPtr func1, ThisPtr func2)	// OR(func1,func2) ::= func1 | func2
	{
		gzParseResult result = (((T*)this)->*func1)();

		if (result != GZ_PARSE_NO_MATCH)
			return result;

		result = (((T*)this)->*func2)();

		return result;
	}

	gzParseResult parse_OR(ThisPtr func1, ThisPtr func2, ThisPtr func3)	// OR(func1,func2,func3) ::= func1 | func2 | func3
	{
		gzParseResult result = parse_OR(func1, func2);

		if (result != GZ_PARSE_NO_MATCH)
			return result;

		result = (((T*)this)->*func3)();

		return result;
	}

	gzParseResult parse_OR(ThisPtr func1, ThisPtr func2, ThisPtr func3, ThisPtr func4)	// OR(func1,func2,func3,func4) ::= func1 | func2 | func3 | func4
	{
		gzParseResult result = parse_OR(func1, func2);

		if (result != GZ_PARSE_NO_MATCH)
			return result;

		result = parse_OR(func3, func4);

		return result;
	}

	gzParseResult parse_OR(ThisPtr func1, ThisPtr func2, ThisPtr func3, ThisPtr func4, ThisPtr func5)	// OR(func1,func2,func3,func4,func5) ::= func1 | func2 | func3 | func4 | func5
	{
		gzParseResult result = parse_OR(func1, func2, func3);

		if (result != GZ_PARSE_NO_MATCH)
			return result;

		result = parse_OR(func4, func5);

		return result;
	}

	gzParseResult parse_AND(ThisPtr func1, ThisPtr func2)	// AND(func1,func2) ::= func1 func2
	{
		gzUInt32 tokenPos = BaseParser::getTokenPos();

		gzParseResult result = (((T*)this)->*func1)();

		if (result != GZ_PARSE_OK)
			return result;

		result = (((T*)this)->*func2)();

		if (result == GZ_PARSE_NO_MATCH)	// No match. Lets make entire func no match
			pushBackTokens(BaseParser::getTokenPos() - tokenPos);

		return result;
	}

	gzParseResult parse_AND(ThisPtr func1, ThisPtr func2, ThisPtr func3)	// AND(func1,func2,func3) ::= func1 func2 func3
	{
		gzUInt32 tokenPos = BaseParser::getTokenPos();

		gzParseResult result = parse_AND(func1, func2);

		if (result != GZ_PARSE_OK)
			return result;

		result = (((T*)this)->*func3)();

		if (result == GZ_PARSE_NO_MATCH)	// No match. Lets make entire func no match
			pushBackTokens(BaseParser::getTokenPos() - tokenPos);

		return result;
	}

	gzParseResult parse_AND(ThisPtr func1, ThisPtr func2, ThisPtr func3, ThisPtr func4)	// AND(func1,func2,func3,func4) ::= func1  func2  func3  func4
	{
		gzUInt32 tokenPos = BaseParser::getTokenPos();

		gzParseResult result = parse_AND(func1, func2);

		if (result != GZ_PARSE_OK)
			return result;

		result = parse_AND(func3, func4);

		if (result == GZ_PARSE_NO_MATCH)	// No match. Lets make entire func no match
			pushBackTokens(BaseParser::getTokenPos() - tokenPos);

		return result;
	}

	gzParseResult parse_AND(ThisPtr func1, ThisPtr func2, ThisPtr func3, ThisPtr func4, ThisPtr func5)	// AND(func1,func2,func3,func4,func5) ::= func1  func2  func3  func4  func5
	{
		gzUInt32 tokenPos = BaseParser::getTokenPos();

		gzParseResult result = parse_AND(func1, func2, func3);

		if (result != GZ_PARSE_OK)
			return result;

		result = parse_AND(func4, func5);

		if (result == GZ_PARSE_NO_MATCH)	// No match. Lets make entire func no match
			pushBackTokens(BaseParser::getTokenPos() - tokenPos);

		return result;
	}

	gzParseResult parse_TOKEN(gzWideChar token)	// TOKEN('token') ::= 'token'
	{
		if (!BaseParser::checkTokens(&token, 1))
			return GZ_PARSE_NO_MATCH;

		return GZ_PARSE_OK;
	}


	gzParseResult parseMultiple(ThisPtr func, gzUInt32 min = 0, gzUInt32 max = 0xFFFFFFFFUL)	// Mul(func) ::= [min,max](func)
	{
		gzUInt32 tokenPos = BaseParser::getTokenPos();
		gzUInt32 count = 0;

		while ((count < max) && BaseParser::hasData())
		{
			gzParseResult result = (((T*)this)->*func)();

			if (!result)	// Error
				return result;

			if (result != GZ_PARSE_OK)
				break;

			++count;
		}

		if (count >= min)
			return GZ_PARSE_OK;

		BaseParser::pushBackTokens(BaseParser::getTokenPos() - tokenPos);

		return GZ_PARSE_NO_MATCH;
	}

	gzParseResult parseTokens(const gzString& string)
	{
		gzUInt16 len = string.getWideStringLength();

		if (BaseParser::checkTokens(string.getWideString(len), len, !getCaseSensitive()))
			return GZ_PARSE_OK;

		return GZ_PARSE_NO_MATCH;
	}

	gzParseResult parseSet(const gzString& string)
	{
		if (!string)
			return GZ_PARSE_OK;

		gzUInt32 len = string.getWideStringLength();

		m_buffer.setSize(len);

		gzWideChar* buffer = m_buffer.getAddress();

		string.getWideString(buffer, FALSE);

		gzBool inverse = (*buffer == '^');

		gzBool match = FALSE;

		gzUInt32 valueStart, valueEnd, i;

		if (BaseParser::hasData() && len)
		{
			gzUInt16 token = BaseParser::getNextToken(FALSE);

			i = inverse ? 1 : 0;

			while (i < len)
			{
				valueStart = valueEnd = buffer[i];

				// Hexadecimal token value #xABCD etc

				if (((i + 2) < len) && (valueStart == '#') && (buffer[i + 1] == 'x'))
				{
					i += 2;

					valueStart = 0;

					while ((i < len) && (((buffer[i] >= '0') && (buffer[i] <= '9')) || ((buffer[i] >= 'a') && (buffer[i] <= 'f')) || ((buffer[i] >= 'A') && (buffer[i] <= 'F'))))
					{
						if (buffer[i] <= '9')
							valueStart = (valueStart << 4) + (buffer[i] - '0');
						else if (buffer[i] >= 'a')
							valueStart = (valueStart << 4) + (buffer[i] - 'a') + 10;
						else
							valueStart = (valueStart << 4) + (buffer[i] - 'A') + 10;

						i++;
					}

					valueEnd = valueStart;

					i--;
				}

				// Range values A-Z or #x36-#x38
				if (((i + 2) < len) && (buffer[i + 1] == '-'))
				{
					i += 2;
					valueEnd = buffer[i];

					if (((i + 2) < len) && (valueEnd == '#') && (buffer[i + 1] == 'x'))
					{
						i += 2;

						valueEnd = 0;

						while ((i < len) && (((buffer[i] >= '0') && (buffer[i] <= '9')) || ((buffer[i] >= 'a') && (buffer[i] <= 'f')) || ((buffer[i] >= 'A') && (buffer[i] <= 'F'))))
						{
							if (buffer[i] <= '9')
								valueEnd = (valueEnd << 4) + (buffer[i] - '0');
							else if (buffer[i] >= 'a')
								valueEnd = (valueEnd << 4) + (buffer[i] - 'a') + 10;
							else
								valueEnd = (valueEnd << 4) + (buffer[i] - 'A') + 10;

							i++;
						}

						i--;
					}
				}

				if ((token >= valueStart) && (token <= valueEnd))
				{
					match = TRUE;
					break;
				}

				i++;
			}

			if (match == inverse)
				BaseParser::pushBackTokens(1);
		}
		else
			match = inverse;

		if (match != inverse)
			return GZ_PARSE_OK;
		else
			return GZ_PARSE_NO_MATCH;
	}

	gzVoid registerFunction(const gzString& name, ThisPtr func)
	{
		gzString compressedName = getCompressedIdentifier(name);

		m_registeredFunctions.remove(compressedName);
		m_registeredFunctions.enter(compressedName, new gzFuncInfo(func));
	}

	gzBool registerRule(const gzString& rule, gzBool useUTF8 = TRUE)
	{
		return registerRulesFromString(rule, useUTF8);
	}

	gzBool registerCompressedRule(const gzString& rule)
	{
		gzString ruleName = rule.leftOf(GZ_RULE_DELIMITER).stripWhiteSpace();
		gzString ruleExpression = rule.rightOf(GZ_RULE_DELIMITER, FALSE).stripWhiteSpace();

		if (!ruleName || !ruleExpression)
		{
			GZMESSAGE(GZ_MESSAGE_WARNING, "Malformed rule in parser -> '%s'  Are you missing '::='", rule);
			return FALSE;
		}

		m_registeredRules.remove(ruleName);
		m_registeredRules.enter(ruleName, new gzRuleInfo(ruleExpression));

		return TRUE;
	}

	gzString getRule(const gzString& rule)
	{
		gzString theRule = rule.stripWhiteSpace();

		gzRuleInfo* info = m_registeredRules.find(getCompressedIdentifier(theRule));

		if (info)
		{
			gzStringTokenizer lexer(info->getRule());
			gzString retval;

			lexer.useStrings(TRUE);
			lexer.useSet(TRUE);
			lexer.useEscape(FALSE);

			while (lexer.getDataType() != GZ_LEX_EMPTY)
			{
				switch (lexer.getDataType(FALSE))
				{
					case GZ_LEX_DOUBLE_STRING:
						{
							retval += "\"";
							retval += getUnCompressedIdentifier(lexer.getData().getString());
							retval += "\"";

							continue;
						}

					case GZ_LEX_SINGLE_STRING:
						{
							retval += "'";
							retval += lexer.getData().getString();
							retval += "'";

							continue;
						}

					case GZ_LEX_SET:
						{
							retval += "[";
							retval += lexer.getData().getString();
							retval += "]";

							continue;
						}


					case GZ_LEX_WHITESPACE:
						{
							retval += " ";
							continue;
						}

					case GZ_LEX_IDENTIFIER:
						{
							retval += getUnCompressedIdentifier(lexer.getData().getString());
							continue;
						}

					default:
						break;
				}

				retval = retval + lexer.getScannedBuffer();
			}

			return retval;
		}

		return GZ_EMPTY_STRING;
	}

	gzVoid removeCompressedIdentifier(const gzString& name)
	{
		gzRefData<gzString>* data = m_identifierLookupB.find(name);

		m_identifierLookupA.remove(*data);
		m_identifierLookupB.remove(name);
	}

	gzString getCompressedIdentifier(const gzString& name, gzBool* created = nullptr)
	{
		gzRefData<gzString>* data = m_identifierLookupA.find(name);

		if (!data)
		{
			data = new gzRefData<gzString>(gzString::identifier(m_identifierLookupA.entries()));

			m_identifierLookupA.enter(name, data);

			gzRefData<gzString>* dataB = new gzRefData<gzString>(name);

			m_identifierLookupB.enter(*data, dataB);

			if (created)
				*created = TRUE;
		}
		else if (created)
		{
			*created = FALSE;
		}

		return *data;
	}

	gzString getUnCompressedIdentifier(const gzString& name)
	{
		gzRefData<gzString>* data = m_identifierLookupB.find(name);

		if (!data)
			return GZ_MISSING_IDENTIFIER;

		return *data;
	}

	gzBool registerRulesFromURL(const gzString& url)
	{
		gzSerializeAdapterPtr adapter = gzSerializeAdapter::getURLAdapter(url);

		if (!adapter)
			return FALSE;

		gzSerializeLex lexer(TRUE, TRUE);

		lexer.useStrings(TRUE);
		lexer.useSet(TRUE);
		lexer.useEscape(FALSE);

		lexer.read(adapter);

		gzString rule, compressed;

		gzBool result = TRUE;

		gzBool created;

		gzUInt32 rulenum = 1;

		while (lexer.getDataType() != GZ_LEX_EMPTY)
		{
			switch (lexer.getDataType())
			{
				case GZ_LEX_DOUBLE_STRING:
				case GZ_LEX_SINGLE_STRING:
					{
						compressed = getCompressedIdentifier(lexer.getData().getString(), &created);

						if (compressed.length() < lexer.getData().getString().length())
						{
							rule += "\"";
							rule += compressed;
							rule += "\"";
						}
						else
						{
							rule += "'";
							rule += lexer.getData().getString().convertCtrlToText();
							rule += "'";

							if (created)
								removeCompressedIdentifier(compressed);
						}


						lexer.read(adapter);
						continue;
					}


				case GZ_LEX_SET:
					{
						rule += "[";
						rule += lexer.getData().getString();
						rule += "]";

						lexer.read(adapter);
						continue;
					}


				case GZ_LEX_TOKEN:
					{
						if (lexer.getData().getNumber() == ';')
						{
							if (!registerCompressedRule(rule))
							{
								GZMESSAGE(GZ_MESSAGE_WARNING, "Malformed rule in parser url:%s rule nr:%d", url, rulenum);
								result = FALSE;
							}

							++rulenum;

							rule.clear();
							lexer.read(adapter);
							continue;
						}
					}
					break;

				case GZ_LEX_WHITESPACE:
					{
						rule += " ";
						lexer.read(adapter);
						continue;
					}

				case GZ_LEX_COMMENT:
					{
						lexer.read(adapter);
						continue;
					}

				case GZ_LEX_IDENTIFIER:
					{
						rule += getCompressedIdentifier(lexer.getData().getString());

						lexer.read(adapter);
						continue;
					}

				default:
					break;
			}

			rule = rule + lexer.getScannedBuffer();

			lexer.read(adapter);
		}

		if (rule.contains(GZ_RULE_DELIMITER))
		{
			if (!registerCompressedRule(rule))
			{
				GZMESSAGE(GZ_MESSAGE_WARNING, "Malformed rule in parser url:%s rule nr:%d", url, rulenum);
				result = FALSE;
			}
		}

		return result;
	}

	gzBool registerRulesFromString(const gzString& string, gzBool useUTF8 = TRUE)
	{
		gzSerializeAdapterMemoryPtr adapter = new gzSerializeAdapterMemory((gzVoid*)string.getString(), string.length());

		gzSerializeLex lexer(TRUE, TRUE);

		lexer.useStrings(TRUE);
		lexer.useSet(TRUE);
		lexer.useEscape(FALSE);
		lexer.useUtf8(useUTF8);

		lexer.read(adapter);

		gzString rule, compressed;

		gzBool result = TRUE;

		gzBool created;

		gzUInt32 rulenum = 1;

		while (lexer.getDataType() != GZ_LEX_EMPTY)
		{
			switch (lexer.getDataType())
			{
				case GZ_LEX_DOUBLE_STRING:
				case GZ_LEX_SINGLE_STRING:
					{
						compressed = getCompressedIdentifier(lexer.getData().getString(), &created);

						if (compressed.length() < lexer.getData().getString().length())
						{
							rule += "\"";
							rule += compressed;
							rule += "\"";
						}
						else
						{
							rule += "'";
							rule += lexer.getData().getString().convertCtrlToText();
							rule += "'";

							if (created)
								removeCompressedIdentifier(compressed);
						}


						lexer.read(adapter);
						continue;
					}


				case GZ_LEX_SET:
					{
						rule += "[";
						rule += lexer.getData().getString();
						rule += "]";

						lexer.read(adapter);
						continue;
					}


				case GZ_LEX_TOKEN:
					{
						if (lexer.getData().getNumber() == ';')
						{
							if (!registerCompressedRule(rule))
							{
								GZMESSAGE(GZ_MESSAGE_WARNING, "Malformed rule in parser string:%s rule nr:%d", string, rulenum);
								result = FALSE;
							}

							++rulenum;

							rule.clear();
							lexer.read(adapter);
							continue;
						}
					}
					break;

				case GZ_LEX_WHITESPACE:
					{
						rule += " ";
						lexer.read(adapter);
						continue;
					}

				case GZ_LEX_COMMENT:
					{
						lexer.read(adapter);
						continue;
					}

				case GZ_LEX_IDENTIFIER:
					{
						rule += getCompressedIdentifier(lexer.getData().getString());

						lexer.read(adapter);
						continue;
					}

				default:
					break;
			}

			rule = rule + lexer.getScannedBuffer();

			lexer.read(adapter);
		}

		if (rule.contains(GZ_RULE_DELIMITER))
		{
			if (!registerCompressedRule(rule))
			{
				GZMESSAGE(GZ_MESSAGE_WARNING, "Malformed rule in parser string:%s rule nr:%d", string, rulenum);
				result = FALSE;
			}
		}

		return result;
	}

	gzParseResult parseFunction(const gzString& name)
	{
		return parseCompressedFunction(getCompressedIdentifier(name));
	}

	gzParseResult parseCompressedFunction(const gzString& name)
	{
		gzFuncInfo* funcInfo = m_registeredFunctions.find(name);

		if (!funcInfo)
			return BaseParser::parseFunction(getUnCompressedIdentifier(name));

		return (((T*)this)->*funcInfo->getFunction())();
	}

	gzParseResult parseRule(const gzString& rule)
	{
		return parseCompressedRule(getCompressedIdentifier(rule));
	}

	gzParseResult parseCompressedRule(const gzString& rule);

	gzUInt32 addItem()
	{
		return m_itemID++;
	}

	gzBool rejectItem(gzUInt32 restore)
	{
		m_itemID = restore;

		gzBool retval = TRUE;

		while (m_tokenPos.entries() && m_tokenPos.top().itemID > restore)
		{
			if (m_tokenPos.top().accepted)
				retval = onRejectAcceptedItem(m_tokenPos.top().itemID, retval);

			m_tokenPos.pop();
		}

		retval = onRejectItem(restore, retval);

		return retval;
	}

	gzUInt32 getItemID()
	{
		return m_itemID;
	}

	gzVoid pushTokenPos(gzBool accepted = FALSE)
	{
		gzTokenPos pos = { BaseParser::getTokenPos(),m_itemID,accepted };
		m_tokenPos.push(pos);
	}

	gzVoid clearPushedTokenEntries()
	{
		m_tokenPos.clear();
	}

	gzUInt32 getPushedTokenEntries()
	{
		return m_tokenPos.entries();
	}

	gzUInt32 getPushedTokenPos()
	{
		if (m_tokenPos.entries())
			return m_tokenPos.popNoClear().tokenPos;
		else
			return 0;
	}

	gzString getPushedTokenData()
	{
		gzUInt32 pushedTokenPos = getPushedTokenPos();

		return BaseParser::getTokenData(pushedTokenPos, (gzUInt16)(BaseParser::getTokenPos() - pushedTokenPos));
	}

	gzString getPushedTokenData(gzUInt32 stackIndex)
	{
		if (m_tokenPos.getStopIndex() <= stackIndex)
			return GZ_EMPTY_STRING;

		if (stackIndex)
		{
			stackIndex = m_tokenPos.getStopIndex() - stackIndex - 1;

			gzUInt32 start = m_tokenPos.getArray().get(stackIndex).tokenPos;
			gzUInt32 stop = m_tokenPos.getArray().get(stackIndex + 1).tokenPos;

			return BaseParser::getTokenData(start, (gzUInt16)(stop - start));
		}
		else
		{
			gzUInt32 start = m_tokenPos.getArray().get(m_tokenPos.getStopIndex() - 1).tokenPos;
			return BaseParser::getTokenData(start, (gzUInt16)(BaseParser::getTokenPos() - start));
		}
	}

	gzBool virtual onRejectItem(gzUInt32 /*id*/, gzBool continueParsing) { return continueParsing; }
	gzBool virtual onRejectAcceptedItem(gzUInt32 /*id*/, gzBool continueParsing) { return continueParsing; }

	GZ_PROPERTY(gzBool, EnableTrace);
	GZ_PROPERTY(gzBool, EnablePerfMon);
	GZ_PROPERTY(gzBool, CaseSensitive);

private:

	gzRefDict<gzString, gzFuncInfo>				m_registeredFunctions;
	gzRefDict<gzString, gzRuleInfo>				m_registeredRules;
	gzRefDict<gzString, gzRefData<gzString> >	m_identifierLookupA;
	gzRefDict<gzString, gzRefData<gzString> >	m_identifierLookupB;

	gzUInt32							m_itemID;
	gzDynamicArray<gzWideChar>			m_buffer;
	gzQueue<gzTokenPos>					m_tokenPos;
};

//******************************************************************************
// Class	: gzBasicParser
//									
// Purpose  : Basic parser utility
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050601	Created 
//									
//******************************************************************************
class gzBasicParser
{
public:

	GZ_BASE_EXPORT	gzBasicParser();
	GZ_BASE_EXPORT	virtual ~gzBasicParser();

	GZ_BASE_EXPORT	gzVoid				setAdapter(gzSerializeAdapter* adapter);
	GZ_BASE_EXPORT	gzSerializeAdapter* getAdapter();

	GZ_BASE_EXPORT	gzVoid				setError(const gzString& error, ARG_DECL_LIST);
	GZ_BASE_EXPORT	gzBool				hasError();
	GZ_BASE_EXPORT	const gzString& getError();


	GZ_BASE_EXPORT	gzBool				hasData();

	GZ_BASE_EXPORT	gzVoid				continueParsingFrom(gzBasicParser* original);

	GZ_BASE_EXPORT	gzUInt32			getLine();
	GZ_BASE_EXPORT	gzUInt32			getColumn();
	GZ_BASE_EXPORT	gzVoid				setLine(gzUInt32 line);
	GZ_BASE_EXPORT	gzVoid				setColumn(gzUInt32 column);
	GZ_BASE_EXPORT	gzVoid				reset();

	GZ_BASE_EXPORT	gzVoid				setProgressMessage(const gzString& message, ARG_DECL_LIST);
	GZ_BASE_EXPORT	gzString			getProgressMessage();
	GZ_BASE_EXPORT	gzBool				hasProgressMessage();
	GZ_BASE_EXPORT	gzVoid				reportProgress(gzBool finished = FALSE);
	GZ_BASE_EXPORT	gzVoid				useProgress(gzBool on);
	GZ_BASE_EXPORT	gzBool				useProgress();

	GZ_BASE_EXPORT	gzUInt16			getNextToken(gzBool checkAvailData = TRUE);
	GZ_BASE_EXPORT	gzBool				checkTokens(const gzWideChar* string, gzUInt32 len, gzBool compareUpperCase = FALSE);
	GZ_BASE_EXPORT	gzUInt32			getTokenPos();
	GZ_BASE_EXPORT	gzVoid				pushBackTokens(gzUInt32 count);
	GZ_BASE_EXPORT	gzString			getTokenData(gzUInt32 start, gzUInt16 len);
	GZ_BASE_EXPORT	gzVoid				getTokenData(gzUInt32 start, gzUInt32 len, gzArray<gzUByte>& data);

	GZ_BASE_EXPORT	gzUInt32			getMaxBufferSize();
	GZ_BASE_EXPORT	gzVoid				setMaxBufferSize(gzUInt32 size = 1000);

	GZ_BASE_EXPORT	gzParseResult		skipWS();				// Tab and Space
	GZ_BASE_EXPORT	gzParseResult		skipAllWS();			// +LF and CR
	GZ_BASE_EXPORT	gzParseResult		skipToEOL();			// All until and including LF
	GZ_BASE_EXPORT	gzParseResult		skipToCREOL();			// All until and including CR+LF
	GZ_BASE_EXPORT	gzParseResult		skipAllExceptCREOL();	// All until and including CR+LF

	GZ_BASE_EXPORT	gzVoid				useUtf8(gzBool on);
	GZ_BASE_EXPORT	gzVoid				useUnicode(gzBool on, gzBool bigendian = TRUE);

	GZ_BASE_EXPORT	gzVoid				useEscapeUnicode(gzBool on = TRUE);


	//// Routes

	GZ_BASE_EXPORT	gzParseResult		parseFunction(const gzString& name);

	// Utilties

	GZ_BASE_EXPORT	gzParseResult		parseAny();						//	any token
	GZ_BASE_EXPORT	gzParseResult		parseAlpha();					//	[a-zA-Z]				
	GZ_BASE_EXPORT	gzParseResult		parseHex();						//	[a-fA-F0-9]
	GZ_BASE_EXPORT	gzParseResult		parseDigit();					//	[0-9]
	GZ_BASE_EXPORT	gzParseResult		parseSingleQuoteTokenEscape();	//	\'
	GZ_BASE_EXPORT	gzParseResult		parseQuoteTokenEscape();		//	\"
	GZ_BASE_EXPORT	gzParseResult		parseSetTokenEscape();			//	\]
	GZ_BASE_EXPORT	gzParseResult		parseSingleQuoteToken();		//	up to ending '
	GZ_BASE_EXPORT	gzParseResult		parseQuoteToken();				//	up to ending "
	GZ_BASE_EXPORT	gzParseResult		parseSetToken();				//	up to ending ]
	GZ_BASE_EXPORT	gzParseResult		parseChar();					//	[#x0-#x80]
	GZ_BASE_EXPORT	gzParseResult		parseUpAlpha();					//	[A-Z]
	GZ_BASE_EXPORT	gzParseResult		parseLoAlpha();					//	[a-z]
	GZ_BASE_EXPORT	gzParseResult		parseAlphaNum();				//	[a-zA-Z0-9]
	GZ_BASE_EXPORT	gzParseResult		parseCTL();						//	[#x0-#x1f#7f]
	GZ_BASE_EXPORT	gzParseResult		parseCR();						//	'\r'
	GZ_BASE_EXPORT	gzParseResult		parseLF();						//	'\n'
	GZ_BASE_EXPORT	gzParseResult		parseSP();						//	' '
	GZ_BASE_EXPORT	gzParseResult		parseHT();						//	'\t'
	GZ_BASE_EXPORT	gzParseResult		parseCRLF();					//	'\r\n'
	GZ_BASE_EXPORT	gzParseResult		parseWS();						//	' ' | \t
	GZ_BASE_EXPORT	gzParseResult		parseAllWS();					//	' ' | \t | \r | \n
	GZ_BASE_EXPORT	gzParseResult		parseAllExceptWS();				//	All except ' ' | \t | \r | \n
	GZ_BASE_EXPORT	gzParseResult		parseToEOL();					//	[^#xa]* [#xa]
	GZ_BASE_EXPORT	gzParseResult		parseToCREOL();					//	[^#xa#xd]* [#xa#xd]
	GZ_BASE_EXPORT	gzParseResult		parseAllExceptCREOL();			//	[^#xa#xd]* 

	// Compounds
	GZ_BASE_EXPORT	gzParseResult		parseIdentifier();				//	Generic C++ identifier
	GZ_BASE_EXPORT	gzParseResult		parsePlainIdentifier();			//	Generic C++ identifier but no underscore and no digits
	GZ_BASE_EXPORT	gzParseResult		parseString();					//	Generic " double quote delimited data "
	GZ_BASE_EXPORT	gzParseResult		parsePlainText();				//	Generic Text, no WS
	GZ_BASE_EXPORT	gzParseResult		parseInteger();					//	( '-' | '+'? ) Generic integer (digits)
	GZ_BASE_EXPORT	gzParseResult		parseNumber();					//  ( '-' | '+'? ) digit+ ('.' digit* )? ( [eE] ( '-' | '+'? ) digit+ )?
	GZ_BASE_EXPORT	gzParseResult		parseUnary();					//  digit+ ('.' digit* )?


	// Output of parse
	GZ_BASE_EXPORT	gzString			parseResultString(gzParseResult result);

private:

	gzSerializeLex				m_lex;

	gzString					m_error;

	gzDList<gzVoid>* m_queue;

	gzSerializeAdapterPtr 		m_adapter;

	gzString					m_progressMessage;
	gzUByte						m_lastProgress;
	gzUByte						m_newProgress;

	gzUInt32					m_line;
	gzUInt32					m_column;
	gzUInt32					m_lastColumn;
	gzUInt32					m_tokenPos;
	gzUInt32					m_queueStart;

	gzUInt32					m_maxBufferSize;

	gzBool						m_useProgress;

	gzDynamicArray<gzWideChar>	m_buffer;

};

//******************************************************************************
// Class	: gzParserFunctionEvaluator
//									
// Purpose  : Utility for EBNF evaluation. Only used internally
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	050601	Created 
//									
//******************************************************************************
template <class T, class BaseParser> class gzParserFunctionEvaluator : public gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>
{
public:

	gzVoid setRouter(gzParserFunction<T, BaseParser>* router)
	{
		m_router = router;
		m_result = GZ_PARSE_OK;
	}

	// The EBNF for the EBNF parser

	// group		::= '(' expression ')'
	// control		::= item ('+' | '*' | '?' | INTEGER | '{' INTEGER ',' INTEGER '}' )?
	// exception	::= control (- exception) ?
	// comment		::= '/*' (comment|X) '*/'
	// item			::= SPACE* (PUSH | RULE_IDENTIFIER | DQSTRING | QSTRING | SET | HEXITEM | comment | group) 
	// orexceptionn ::= '|' exception+
	// expression	::= exception+ orexception*
	// PUSH			::= '$'
	// ACCEPT		::= '@'
	// NOCASE		::= '~'
	// CASE			::= '^'

	// Parse a hexadecimal sequence
	gzParseResult parseHexItem()					// HEXITEM ::= '#x'HEX
	{
		if (!gzBasicParser::checkTokens(L("#x"), 2))
			return GZ_PARSE_NO_MATCH;

		if (gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>::parseMultiple(&gzParserFunctionEvaluator::parseHex, 1) == GZ_PARSE_NO_MATCH)
		{
			gzBasicParser::pushBackTokens(2);
			return GZ_PARSE_NO_MATCH;
		}

		return GZ_PARSE_OK;
	}

	// Parses a single quote string. ' can be escaped with backslash ' xxxx\' xxx '
	gzParseResult parseSingleQuoteTokenString()
	{
		gzUInt16 token = gzBasicParser::getNextToken();

		if (token != '\'')
		{
			gzBasicParser::pushBackTokens(1);

			return GZ_PARSE_NO_MATCH;
		}

		gzParseResult result = gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>::parseMultiple(&gzParserFunctionEvaluator::parseSingleQuoteToken);

		if (!result)
			return result;

		if (!gzBasicParser::hasData())
		{
			m_router->setError("Unbalansed single quoted string in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));
			return GZ_PARSE_ERROR;
		}

		token = gzBasicParser::getNextToken(FALSE);

		if (token == '\'')
			return GZ_PARSE_OK;

		m_router->setError("Unbalansed single quoted string in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));

		return GZ_PARSE_ERROR;
	}

	// Parses a double quoted string. " can be escaped with backslash " xxxx\" xxx "
	gzParseResult parseQuoteTokenString()
	{
		gzUInt16 token = gzBasicParser::getNextToken();

		if (token != '"')
		{
			gzBasicParser::pushBackTokens(1);

			return GZ_PARSE_NO_MATCH;
		}

		gzParseResult result = gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>::parseMultiple(&gzParserFunctionEvaluator::parseQuoteToken);

		if (!result)
			return result;

		if (!gzBasicParser::hasData())
		{
			m_router->setError("Unbalansed quote string in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));
			return GZ_PARSE_ERROR;
		}

		token = gzBasicParser::getNextToken(FALSE);

		if (token == '"')
			return GZ_PARSE_OK;

		m_router->setError("Unbalansed quote string in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));

		return GZ_PARSE_ERROR;
	}

	// parses a token in a comment and can be recursive
	gzParseResult parseCommentToken()
	{
		gzParseResult result = parseComment();

		if (!result)
			return result;

		if (gzBasicParser::checkTokens(L("*/"), 2))
		{
			gzBasicParser::pushBackTokens(2);
			return GZ_PARSE_NO_MATCH;
		}

		gzBasicParser::getNextToken();

		return GZ_PARSE_OK;
	}

	// parses a comment /*    /* can be recursive */              */
	gzParseResult parseComment()
	{
		if (!gzBasicParser::checkTokens(L("/*"), 2))
			return GZ_PARSE_NO_MATCH;

		gzParseResult result = gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>::parseMultiple(&gzParserFunctionEvaluator::parseCommentToken);

		if (!result)
			return result;

		if (!gzBasicParser::hasData())
		{
			m_router->setError("Unbalansed comment in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));

			return GZ_PARSE_ERROR;
		}

		if (gzBasicParser::checkTokens(L("*/"), 2))
			return GZ_PARSE_OK;

		m_router->setError("Unbalansed comment in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));

		return GZ_PARSE_ERROR;
	}

	// Parses a logical set [asdfcea-zA-S#x10] with chars and ranges. Can be negated with [^abc]. ] can be escaped with \]
	gzParseResult parseSet()
	{
		gzUInt16 token = gzBasicParser::getNextToken();

		if (token != '[')
		{
			gzBasicParser::pushBackTokens(1);

			return GZ_PARSE_NO_MATCH;
		}

		gzParseResult result = gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>::parseMultiple(&gzParserFunctionEvaluator::parseSetToken);

		if (!result)
			return result;

		if (!gzBasicParser::hasData())
		{
			m_router->setError("Unbalansed Set [] in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));
			return GZ_PARSE_ERROR;
		}

		token = gzBasicParser::getNextToken(FALSE);

		if (token == ']')
			return GZ_PARSE_OK;

		gzBasicParser::pushBackTokens(1);

		m_router->setError("Unbalansed Set [] in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));

		return GZ_PARSE_ERROR;
	}


	// Parses a grouped item
	gzParseResult parseGroup()				// group ::= '(' expression ')'
	{
		gzUInt16 token = gzBasicParser::getNextToken();

		if (token != '(')
		{
			gzBasicParser::pushBackTokens(1);

			return GZ_PARSE_NO_MATCH;
		}

		gzParseResult result = parseExpression();

		if (!result)
			return result;

		gzBasicParser::skipWS();

		if (!gzBasicParser::hasData())
		{
			m_router->setError("Missing right ')' in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));
			return GZ_PARSE_ERROR;
		}

		token = gzBasicParser::getNextToken(FALSE);

		if (token != ')')
		{
			m_router->setError("Missing right ')' in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));
			return GZ_PARSE_ERROR;
		}

		return GZ_PARSE_OK;
	}

	// Parses a generic EBNF item
	gzParseResult parseItem()						// item	::= SPACE* (CASE | NOCASE | PUSH | ACCCEPT | RULE_IDENTIFIER | DQSTRING | QSTRING | SET | HEXITEM | group ) 
	{
		gzUInt32 id = m_router->addItem();

		gzParseResult result;

		gzBasicParser::skipWS();			// SPACE

		gzUInt32 tokenPos = gzBasicParser::getTokenPos();

		// --------- IDENTIFIER --------------

		result = gzBasicParser::parseIdentifier();

		if (!result)
			return result;

		if (result == GZ_PARSE_OK)
		{
			if (m_result == GZ_PARSE_OK)
			{
				m_result = m_router->parseCompressedRule(gzBasicParser::getTokenData(tokenPos, (gzUInt16)(gzBasicParser::getTokenPos() - tokenPos)));

				if (m_result == GZ_PARSE_ERROR)
					return GZ_PARSE_ERROR;
			}

			return GZ_PARSE_OK;
		}

		//-------- DQSTRING -------------------

		result = parseQuoteTokenString();

		if (!result)
			return result;

		if (result == GZ_PARSE_OK)
		{
			if (m_result == GZ_PARSE_OK)
				m_result = m_router->parseTokens(m_router->getUnCompressedIdentifier(gzBasicParser::getTokenData(tokenPos + 1, (gzUInt16)(gzBasicParser::getTokenPos() - tokenPos - 2))).convertTextToCtrl());

			return GZ_PARSE_OK;
		}

		//---------- QSTRING ------------------

		result = parseSingleQuoteTokenString();

		if (!result)
			return result;

		if (result == GZ_PARSE_OK)
		{
			if (m_result == GZ_PARSE_OK)
				m_result = m_router->parseTokens(gzBasicParser::getTokenData(tokenPos + 1, (gzUInt16)(gzBasicParser::getTokenPos() - tokenPos - 2)).convertTextToCtrl());

			return GZ_PARSE_OK;
		}

		//---------- Group ---------------------

		result = parseGroup();

		if (result != GZ_PARSE_NO_MATCH)
			return result;

		//--------- SET ----------------------

		result = parseSet();

		if (!result)
			return result;

		if (result == GZ_PARSE_OK)
		{
			if (m_result == GZ_PARSE_OK)
				m_result = m_router->parseSet(gzBasicParser::getTokenData(tokenPos + 1, (gzUInt16)(gzBasicParser::getTokenPos() - tokenPos - 2)));

			return GZ_PARSE_OK;
		}

		// --------- PUSH --------------------

		if (gzBasicParser::getNextToken(FALSE) == '$')
		{
			m_router->pushTokenPos();

			return GZ_PARSE_OK;;
		}
		else
			gzBasicParser::pushBackTokens(1);

		// --------- ACCEPT --------------------

		if (gzBasicParser::getNextToken(FALSE) == '@')
		{
			m_router->pushTokenPos(m_result == GZ_PARSE_OK);

			return GZ_PARSE_OK;;
		}
		else
			gzBasicParser::pushBackTokens(1);

		// --------- CASE --------------------

		if (gzBasicParser::getNextToken(FALSE) == '^')
		{
			m_router->setCaseSensitive(TRUE);

			return GZ_PARSE_OK;;
		}
		else
			gzBasicParser::pushBackTokens(1);

		// --------- NOCASE --------------------

		if (gzBasicParser::getNextToken(FALSE) == '~')
		{
			m_router->setCaseSensitive(FALSE);

			return GZ_PARSE_OK;;
		}
		else
			gzBasicParser::pushBackTokens(1);

		//--------- HEXITEM ----------------------

		if (gzBasicParser::getNextToken(FALSE) == '#')
		{
			// Hexitem will be interpreted as a # followed by x and then a hex number
			// however the xABCD56 etc will be compressed to a single token

			result = gzBasicParser::parseIdentifier();

			if (result == GZ_PARSE_OK)
			{
				gzString hexValue = m_router->getUnCompressedIdentifier(gzBasicParser::getTokenData(tokenPos + 1, (gzUInt16)(gzBasicParser::getTokenPos() - tokenPos - 1)));

				m_result = m_router->parseSet(GZ_STRING_HASH+hexValue);

				return GZ_PARSE_OK;
			}

			gzBasicParser::pushBackTokens(gzBasicParser::getTokenPos() - tokenPos);
		}
		else
			gzBasicParser::pushBackTokens(1);
		
		//---------- Comment ---------------------

		result = parseComment();

		if (result != GZ_PARSE_NO_MATCH)
			return result;

		//---------- reject --------------------

		if (!m_router->rejectItem(id))
			return GZ_PARSE_ERROR;

		return GZ_PARSE_NO_MATCH;
	}

	gzParseResult parseControl()	// control		::= item SPACE? ('+' | '*' | '?' | INTEGER | '{' INTEGER ',' INTEGER '}' )?
	{
		gzUInt32 tokenPos = gzBasicParser::getTokenPos();

		gzParseResult prevresult = m_result;

		gzParseResult result = parseItem();

		if (result != GZ_PARSE_OK)
			return result;

		gzBasicParser::skipWS();	// Skip WS up to control tokens

		if (!gzBasicParser::hasData())
			return GZ_PARSE_OK;

		gzUInt16 token = gzBasicParser::getNextToken(FALSE);

		gzUInt32 tokenPos2 = gzBasicParser::getTokenPos();

		if (token == '+')
		{
			if (m_result != GZ_PARSE_OK)	// We expected at least one
			{
				return GZ_PARSE_OK;
			}

			while (m_router->hasData())
			{
				// Rewind parser to expression
				gzBasicParser::pushBackTokens(gzBasicParser::getTokenPos() - tokenPos);

				result = parseItem();

				if (result != GZ_PARSE_OK)
					return result;

				if (m_result != GZ_PARSE_OK)
					break;
			}

			m_result = prevresult;

			while (gzBasicParser::getTokenPos() < tokenPos2)
				gzBasicParser::getNextToken(FALSE);

			return GZ_PARSE_OK;
		}
		else if (token == '*')
		{
			if (m_result != GZ_PARSE_OK)	// We expected at least zero
			{
				m_result = prevresult;
				return GZ_PARSE_OK;
			}

			while (m_router->hasData())
			{
				// Rewind parser to expression
				gzBasicParser::pushBackTokens(gzBasicParser::getTokenPos() - tokenPos);

				result = parseItem();

				if (result != GZ_PARSE_OK)
					return result;

				if (m_result != GZ_PARSE_OK)
					break;
			}

			m_result = prevresult;

			while (gzBasicParser::getTokenPos() < tokenPos2)
				gzBasicParser::getNextToken(FALSE);

			return GZ_PARSE_OK;
		}
		else if (token == '?')
		{
			m_result = prevresult;

			return GZ_PARSE_OK;
		}
		else if (token == '{')
		{
			gzBasicParser::skipWS();

			gzUInt32 digitTokenPos = gzBasicParser::getTokenPos();

			result = gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>::parseMultiple(&gzParserFunctionEvaluator::parseDigit, 1);

			if (result != GZ_PARSE_OK)
			{
				m_router->setError("Missing Min number in set {Min,Max} in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));

				return GZ_PARSE_ERROR;
			}

			gzUInt32 minrepeats = (gzUInt32)gzBasicParser::getTokenData(digitTokenPos, (gzUInt16)(gzBasicParser::getTokenPos() - digitTokenPos)).num();

			gzBasicParser::skipWS();

			if (gzBasicParser::getNextToken() != ',')
			{
				m_router->setError("Missing ',' in set {Min,Max} in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));

				return GZ_PARSE_ERROR;
			}

			gzBasicParser::skipWS();

			digitTokenPos = gzBasicParser::getTokenPos();

			result = gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>::parseMultiple(&gzParserFunctionEvaluator::parseDigit, 1);

			if (result != GZ_PARSE_OK)
			{
				m_router->setError("Missing Max number in set {Min,Max} in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));

				return GZ_PARSE_ERROR;
			}

			gzUInt32 maxrepeats = (gzUInt32)gzBasicParser::getTokenData(digitTokenPos, (gzUInt16)(gzBasicParser::getTokenPos() - digitTokenPos)).num();

			gzBasicParser::skipWS();

			if (gzBasicParser::getNextToken() != '}')
			{
				m_router->setError("Missing right '}' in set {Min,Max} in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));

				return GZ_PARSE_ERROR;
			}

			tokenPos2 = gzBasicParser::getTokenPos();

			if (minrepeats > maxrepeats)
			{
				m_router->setError("Min>Max in set {Min,Max} in rule '%s' at (Line:%d,Col:%d) -> %s", m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName()), gzBasicParser::getLine(), gzBasicParser::getColumn(), m_router->getRule(m_router->getUnCompressedIdentifier(gzBasicParser::getAdapter()->getName())));

				return GZ_PARSE_ERROR;
			}


			if (maxrepeats == 0)
			{
				if (m_result != GZ_PARSE_OK)	// We expected at least zero
				{
					m_result = prevresult;
					return GZ_PARSE_OK;
				}
			}

			gzUInt32 i;

			for (i = 1; i < maxrepeats; i++)
			{
				if (m_router->hasData())
				{
					// Rewind parser to expression
					gzBasicParser::pushBackTokens(gzBasicParser::getTokenPos() - tokenPos);

					result = parseItem();

					if (result != GZ_PARSE_OK)
						return result;

					if (m_result != GZ_PARSE_OK)
						break;
				}
				else
				{
					if (i < minrepeats)
						m_result = GZ_PARSE_NO_MATCH;

					break;
				}
			}

			if (i >= minrepeats)
				m_result = prevresult;

			while (gzBasicParser::getTokenPos() < tokenPos2)
				gzBasicParser::getNextToken(FALSE);

			return GZ_PARSE_OK;
		}

		gzBasicParser::pushBackTokens(1);

		// Check for INTEGER repeats

		gzUInt32 digitTokenPos = gzBasicParser::getTokenPos();

		result = gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>::parseMultiple(&gzParserFunctionEvaluator::parseDigit, 1);

		if (result == GZ_PARSE_OK)
		{
			tokenPos2 = gzBasicParser::getTokenPos();	// Position after number

			gzUInt32 repeats = (gzUInt32)gzBasicParser::getTokenData(digitTokenPos, (gzUInt16)(tokenPos2 - digitTokenPos)).num();

			if (repeats == 0)
			{
				if (m_result != GZ_PARSE_OK)	// We expected at least zero
				{
					m_result = prevresult;
					return GZ_PARSE_OK;
				}
			}

			gzUInt32 i;

			for (i = 1; i < repeats; i++)
			{
				if (m_router->hasData())
				{
					// Rewind parser to expression
					gzBasicParser::pushBackTokens(gzBasicParser::getTokenPos() - tokenPos);

					result = parseItem();

					if (result != GZ_PARSE_OK)
						return result;

					if (m_result != GZ_PARSE_OK)
						break;
				}
				else
				{
					m_result = GZ_PARSE_NO_MATCH;
					break;
				}
			}

			if (i < repeats)
				return GZ_PARSE_OK;

			while (gzBasicParser::getTokenPos() < tokenPos2)
				gzBasicParser::getNextToken(FALSE);

			return GZ_PARSE_OK;
		}

		return GZ_PARSE_OK;
	}

	gzParseResult parseException()					// exception	::= control (- exception) ?
	{
		gzParseResult result;

		gzUInt32 tokenPos = m_router->getTokenPos();

		gzParseResult prev = m_result;				// Result before first control

		result = parseControl();

		if (result != GZ_PARSE_OK)
			return result;

		gzBasicParser::skipWS();

		if (!gzBasicParser::hasData())
			return GZ_PARSE_OK;

		if (gzBasicParser::getNextToken(FALSE) != '-')
		{
			gzBasicParser::pushBackTokens(1);
			return GZ_PARSE_OK;
		}

		gzParseResult res = m_result;					// Store result after control
		m_result = prev;

		gzUInt32 tokenPos2 = m_router->getTokenPos();

		// Restart the router parser at expression
		m_router->pushBackTokens(tokenPos2 - tokenPos);

		result = parseException();

		if (m_result != GZ_PARSE_OK)	// No exception
		{
			while (m_router->getTokenPos() < tokenPos2)
				m_router->getNextToken(FALSE);

			m_result = res;

			return GZ_PARSE_OK;
		}

		// We have an exception

		m_router->pushBackTokens(m_router->getTokenPos() - tokenPos);

		m_result = GZ_PARSE_NO_MATCH;

		return GZ_PARSE_OK;
	}

	gzParseResult parseOrException()				// orexceptionn ::= '|' exception+ 
	{
		gzBasicParser::skipWS();

		if (gzBasicParser::getNextToken() != '|')
		{
			gzBasicParser::pushBackTokens(1);

			return GZ_PARSE_NO_MATCH;
		}

		return gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>::parseMultiple(&gzParserFunctionEvaluator::parseException, 1);
	}


	gzParseResult parseExpression()					// expression ::= exception+ orexception*
	{
		gzParseResult result;

		gzUInt32 _id = m_router->getItemID();
		gzUInt32 tokenPos = m_router->getTokenPos();

		result = gzParserFunction<gzParserFunctionEvaluator<T, BaseParser>, gzBasicParser>::parseMultiple(&gzParserFunctionEvaluator::parseException, 1);

		if (result != GZ_PARSE_OK)
			return result;

		gzUInt32 tokenPos2 = m_router->getTokenPos();

		if (m_result != GZ_PARSE_OK)
			tokenPos2 = tokenPos;

		if (m_result != GZ_PARSE_OK)
		{
			if (!m_router->rejectItem(_id))
				return GZ_PARSE_ERROR;
		}


		while (gzBasicParser::hasData())
		{
			//Reset parser to beginning
			m_router->pushBackTokens(m_router->getTokenPos() - tokenPos);

			// Save prev result
			gzParseResult res = m_result;

			m_result = GZ_PARSE_OK;

			_id = m_router->getItemID();

			result = parseOrException();

			if (!result)
				return result;

			if (result == GZ_PARSE_NO_MATCH)
			{
				m_result = res;
				break;
			}

			if (m_result != GZ_PARSE_OK)		// use previous value as this was not ok 
			{
				if (!m_router->rejectItem(_id))
					return GZ_PARSE_ERROR;

				m_result = res;
			}
			else							// use this result if prev was not ok
			{
				if (res != GZ_PARSE_OK)		// Earlier 
				{
					tokenPos2 = m_router->getTokenPos();
				}
				else
				{
					if (!m_router->rejectItem(_id))
						return GZ_PARSE_ERROR;
				}

			}
		}

		if (m_router->getTokenPos() > tokenPos2)
			m_router->pushBackTokens(m_router->getTokenPos() > tokenPos2);
		else
			while (m_router->getTokenPos() < tokenPos2)
				m_router->getNextToken(FALSE);

		return GZ_PARSE_OK;
	}

	gzParseResult getResult()
	{
		return m_result;
	}

private:

	gzParserFunction<T, BaseParser>* m_router;

	gzParseResult					m_result;
};

template <class T, class BaseParser> class gzRecycledFunctionEvaluator : public gzRecycleData< gzParserFunctionEvaluator<T, BaseParser> >
{
public:

};


// The actual parse of a rule. The rule can contain surrounding WS that is skipped
template <class T, class BaseParser> inline gzParseResult gzParserFunction<T, BaseParser>::parseCompressedRule(const gzString& rule)
{
	gzParseResult result;

	gzString theRule = rule.stripWhiteSpace();

	gzBool perf = getEnablePerfMon();

	if (perf)
		gzEnterPerformanceSection(getUnCompressedIdentifier(theRule));

	gzRuleInfo* info = m_registeredRules.find(theRule);

	if (!info)
	{
		if (getEnableTrace())
		{
			gzString spaces = gzString::spaces(20 - gzMin(getUnCompressedIdentifier(theRule).length(), (gzUInt16)19));
			GZMESSAGE(GZ_MESSAGE_DEBUG, "Parsing Function : %s%s(Line:%d,Col:%d)", getUnCompressedIdentifier(theRule), spaces, gzBasicParser::getLine(), gzBasicParser::getColumn());
		}

		result = parseCompressedFunction(theRule);

		if (getEnableTrace())
		{
			gzString spaces = gzString::spaces(20 - gzMin(getUnCompressedIdentifier(theRule).length(), (gzUInt16)19));
			GZMESSAGE(GZ_MESSAGE_DEBUG, "Exit Function    : %s%s(Line:%d,Col:%d)\tResult:%s", getUnCompressedIdentifier(theRule), spaces, gzBasicParser::getLine(), gzBasicParser::getColumn(), BaseParser::parseResultString(result));
		}

		if (perf)
			gzLeavePerformanceSection();

		return result;
	}

	gzSerializeAdapterMemoryPtr  adapter = new gzSerializeAdapterMemory((gzVoid*)info->getRule().getString(), info->getRule().length());

	adapter->setName(theRule);

	gzRecycledFunctionEvaluator<T, BaseParser> parser;

	parser->reset();
	parser->setRouter(this);
	parser->setAdapter(adapter);

	if (getEnableTrace())
	{
		gzString spaces = gzString::spaces(20 - gzMin(getUnCompressedIdentifier(theRule).length(), (gzUInt16)19));
		GZMESSAGE(GZ_MESSAGE_DEBUG, "Parsing Rule     : %s%s(Line:%d,Col:%d)", getUnCompressedIdentifier(theRule), spaces, gzBasicParser::getLine(), gzBasicParser::getColumn());
	}

	try
	{
		result = parser->parseExpression();
	}
	catch (gzBasicParseException)
	{
		result = GZ_PARSE_ERROR;
	}

	if (perf)
		gzLeavePerformanceSection();


	if (result != GZ_PARSE_OK)	// Mismatch in rule
	{
		if (!BaseParser::getError())
			BaseParser::setError("Expression mismatch in rule '%s' at (Line:%d,Col:%d) -> %s", getUnCompressedIdentifier(theRule), parser->getLine(), parser->getColumn(), getRule(getUnCompressedIdentifier(theRule)));

		if (getEnableTrace())
			GZMESSAGE(GZ_MESSAGE_DEBUG, "Parse Error:'%s' in rule '%s' at (Line:%d,Col:%d) -> %s", BaseParser::getError(), getUnCompressedIdentifier(theRule), parser->getLine(), parser->getColumn(), getRule(getUnCompressedIdentifier(theRule)));

		return GZ_PARSE_ERROR;
	}

	if (getEnableTrace())
	{
		gzString spaces = gzString::spaces(20 - gzMin(getUnCompressedIdentifier(theRule).length(), (gzUInt16)19));
		GZMESSAGE(GZ_MESSAGE_DEBUG, "Exit Rule        : %s%s(Line:%d,Col:%d)\tResult:%s", getUnCompressedIdentifier(theRule), spaces, gzBasicParser::getLine(), gzBasicParser::getColumn(), BaseParser::parseResultString(parser->getResult()));
	}

	parser->setAdapter(NULL);

	return parser->getResult();
}

// ------------------------ gzDynamicTypeArgumentParser ----------------------------

//******************************************************************************
// Class	: gzDynamicTypeArgumentParser
//									
// Purpose  : Dynamic type Argument parser utility
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	070310	Created 
//									
//******************************************************************************
class gzDynamicTypeArgumentParser : public gzParserFunction<gzDynamicTypeArgumentParser, gzBasicParser>
{
public:

	GZ_BASE_EXPORT gzDynamicTypeArgumentParser();

	GZ_BASE_EXPORT gzArray<gzDynamicType> parseArguments(const gzString& rule = "arg_list");

private:

	gzParseResult fNum();
	gzParseResult fString();
	gzParseResult fBool();
	gzParseResult fArrayBegin();
	gzParseResult fArrayEnd();
	gzParseResult fGUID();

	gzQueue<gzDynamicType>				m_stack;
	gzQueue<gzQueue<gzDynamicType> >	m_arrayStack;
};

// ------------------------ gzRegKeyExpandParser ----------------------------

//******************************************************************************
// Class	: gzRegKeyExpandParser
//									
// Purpose  : Reg key expand parser utility
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	071126	Created 
//									
//******************************************************************************
class gzRegKeyExpandParser : public gzParserFunction<gzRegKeyExpandParser, gzBasicParser>
{
public:

	GZ_BASE_EXPORT gzRegKeyExpandParser();

	GZ_BASE_EXPORT gzString parse();

private:

	gzParseResult fString();
	gzParseResult fRegKey();
	gzParseResult fIFace();
	gzParseResult fEnv();
	gzParseResult fEsc();

	gzString m_result;
};

// ------------------------ gzDynamicTypeArgumentParser ----------------------------

//******************************************************************************
// Class	: gzStringParser
//									
// Purpose  : String Argument parser utility
//									
// Notes	: -	
//									
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	070310	Created 
//									
//******************************************************************************
class gzStringParser : public gzParserFunction<gzStringParser, gzBasicParser>,
	public gzReference
{
public:

	GZ_BASE_EXPORT gzStringParser(const gzString& bnf, gzBool useUTF8 = TRUE);

	GZ_BASE_EXPORT virtual ~gzStringParser() {};

	GZ_BASE_EXPORT gzArray<gzString> parseArguments(const gzString& rule, gzBool* success = nullptr);

	GZ_BASE_EXPORT static gzVoid cleanUpParsers();

private:

	gzParseResult				fPush();

	gzParseResult				fPushStr();

	gzDynamicArray<gzString>	m_result;
};

GZ_DECLARE_REFPTR(gzStringParser);


#endif
