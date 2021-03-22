////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2004 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COMMANDLINE_MANAGER_H__
#define __COMMANDLINE_MANAGER_H__

#pragma once
#pragma warning(disable : 4290)

#define MAX_ARGS 16

//__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class CommandLineManager
// ----- ------------------
template <typename _C = char> class CommandLineManager
{
	public:
	
		enum EFlags
		{
			eParamMandatory = 0x0001,	// param is mandatory
			eParamOptional  = 0x0002,	// param is optional
			eArgMandatory	= 0x0040,	// arg of param is mandatory, always must be present
			eArgOptional	= 0x0080,	// arg of param is optional, rules define restrictions
			eArgValue		= 0x0010,	// arg is value, will be populated from command line
		};

	private:

		enum EToken
		{
			eTokenUnknown	 = 0x0000,
			eTokenLongParam	 = 0x0002,
			eTokenShortParam = 0x0004,
			eTokenArg		 = 0x0008,
			eTokenWhiteSpace = 0x0010
		};
		
		struct Token
		{
			EToken	Type;			// token type
			int		LexemeOffset;	// offset to lexeme in commandline string
			int		LexemeLength;	// length of lexeme
			int		NameOffset;		// offset to name in commandline string
			int		NameLength;		// length of name
		};

		struct Entry
		{
			int Index;	// id of arg
			int Offset;	// offset in command line
			int Length;	// length
		};

	protected:
		typedef _C								_CharType;
		typedef std::char_traits<_CharType>		_CharTraits;
		typedef std::basic_string<_CharType>	_StringType;
		typedef std::map<unsigned int, Entry>	_Params;

		struct Arg
		{
			unsigned int	Id;			// id of arg
			unsigned int	Flags;		// flags EFlags
		   _CharType*		Value;		// value of arg
		   _CharType*		HelpValue;	// description of arg
		};

		struct Param
		{
			unsigned int	Id;				// id of param
			unsigned int	Flags;			// flags EFlags
		   _CharType*		ShortValue;		// short value of a param '-h'
		   _CharType*		LongValue;		// long value of a param '-help'
		   _CharType*		HelpValue;		// description of param
			Arg				Args[MAX_ARGS];	// optional args for param, -cpp -wrap [cpp|java]
		};

		struct AndRule
		{
			unsigned int Id;
			unsigned int List[MAX_RULES];
		};

		struct OrRule
		{
			unsigned int Id;
			unsigned int List[MAX_RULES];
		};

		struct XorRule
		{
			unsigned int List[MAX_RULES];
		};

		Param*	(*GetParamsInternal)();
		AndRule*(*GetAndRulesInternal)();
		OrRule*	(*GetOrRulesInternal)();
		XorRule*(*GetXorRulesInternal)();

		bool			Validate;			// validate input params
	   _CharType		ParamSign;			// default '-'; '/'
	   _CharType		ParamSeparator;		// default ' '
	   _StringType		CommandLine;		// commad line params as string, primary input for automata
	   _StringType		Application;		// application full path and name
	   _Params			Params;				// param map<id, index>
	protected:
		void BuildCommandLine(int _argc, const _CharType* const _argv[])
		{
			if(_argc > 0)
			{
				Application = _argv[0];
			}

			if(_argc > 1)
			{
				for(int i = 1; i < _argc; i++)
				{
#ifdef UNICODE
					int len = static_cast<int>(wcslen(_argv[i]));
#else
					int len = static_cast<int>(strlen(_argv[i]));
#endif					
					
					if(len > 0)
					{
						int off = 0;

						if(_argv[i][0] == ParamSign)
						{
							CommandLine += ParamSign;
							off++;

							if(len > 1)
							{
								if(_argv[i][1] == ParamSign)
								{
									CommandLine += ParamSign;
									off++;
								}
							}
						}

						CommandLine += '\"';
						CommandLine += _argv[i]+off;
						CommandLine += '\"';

						if(i < _argc-1)
						{
							CommandLine += _CharType(ParamSeparator);
						}
					}
				}
			}
		}

		void Parse()
		{
			if(CommandLine.empty())
			{
				throw std::invalid_argument("error: invalid argument");
			}

			Token token;

			token.Type			= eTokenUnknown;
			token.LexemeOffset	= 0;
			token.LexemeLength	= 0;
			token.NameOffset	= 0;
			token.NameLength	= 0;

			int last_param = 0;
			
			for(;;)
			{
				NextLexeme(token);

				if(token.Type == eTokenUnknown)
				{
					break;
				}
				else if(token.Type == eTokenLongParam || token.Type == eTokenShortParam)
				{
					Param* params = (Param*)GetParamsInternal();

					std::string param(CommandLine, token.NameOffset, token.NameLength);
					
					if(!param.empty())
					{
						int i;
						
						for(i = 0; params[i].Id != 0; i++)
						{
							if((token.Type == eTokenLongParam && param == params[i].LongValue) ||
							   (token.Type == eTokenShortParam && param == params[i].ShortValue))
							{
								Entry e;
								e.Index  = last_param = i;
								e.Offset = token.NameOffset;
								e.Length = token.NameLength;
								Params.insert(std::pair<int, Entry>(params[i].Id, e));
								break;
							}
						}
					}
				}
				else if(token.Type == eTokenArg)
				{
					Param& param = ((Param*)GetParamsInternal())[last_param];
					
					std::string arg(CommandLine, token.NameOffset, token.NameLength);
					
					if(!arg.empty())
					{
						int i;
						
						for(i = 0; param.Args[i].Id != 0; i++)
						{
							if(arg == param.Args[i].Value || (param.Args[i].Flags & eArgValue))
							{
								Entry e;
								e.Index  = last_param = i;
								e.Offset = token.NameOffset;
								e.Length = token.NameLength;
								Params.insert(std::pair<int, Entry>(param.Args[i].Id, e));
								break;
							}
						}
					}
				}
#ifdef _DEBUG
				std::string lexeme(CommandLine, token.LexemeOffset, token.LexemeLength);
				std::cout << lexeme.c_str() << std::endl;
#endif
			}
		}

		void ValidateInput()
		{
			if(Validate)
			{
				// validate missing params/args
				ValidateMissingParams();

				// validate 'and' params
				ValidateAndParams();

				// validate 'or' params
				ValidateOrParams();

				// validate 'xor' params
				ValidateXorParams();
			}
		}

		void ValidateMissingParams()
		{
			Param* params = (Param*)GetParamsInternal();

			for(int i = 0; params[i].Id != 0; i++)
			{
				if(params[i].Flags & eParamMandatory)
				{
					if(!HasEntry(params[i].Id))
					{
						std::string error("param is mandatory: ");
						error += params[i].LongValue;
						throw std::underflow_error(error);
					}
				
					for(int k = 0; params[i].Args[k].Id != 0; k++)
					{
						if((params[i].Args[k].Flags & eArgMandatory) && !HasEntry(params[i].Args[k].Id))
						{
							std::string error("argument: ");
							error += params[i].Args[k].Value;
							error += " of param: ";
							error += params[i].LongValue;
							error += " is mandatory";
							throw std::underflow_error(error);
						}
					}
				}
			}
		}

		void ValidateAndParams()
		{
			AndRule* rules = GetAndRulesInternal();

			_Params::iterator it = Params.begin();
			_Params::iterator it_end = Params.end();

			for(; it != it_end; ++it)
			{
				int id = (*it).first;

				for(int i = 0; rules[i].Id != 0; i++)
				{
					if(rules[i].Id == id)
					{
						for(int k = 0; rules[i].List[k] != 0; i++)
						{
							if(!HasEntry(rules[i].List[k]))
							{
								std::string error("'and' rule is broken");
								throw std::underflow_error(error);
							}
						}
					}
				}
			}
		}

		void ValidateOrParams()
		{
			OrRule* rules = GetOrRulesInternal();

			_Params::iterator it = Params.begin();
			_Params::iterator it_end = Params.end();

			for(; it != it_end; ++it)
			{
				int id = (*it).first;
				
				for(int i = 0; rules[i].Id != 0; i++)
				{
					if(rules[i].Id == id)
					{
						int e = 0;
						
						for(int k = 0; rules[i].List[k] != 0; i++)
						{
							if(HasEntry(rules[i].List[k]))
							{
								e++;
							}
						}
						
						if(e == 0 || e > 1)
						{
							std::string error("'or' rule is broken");
							throw std::underflow_error(error);
						}
					}
				}
			}
		}

		void ValidateXorParams()
		{
			XorRule* rules = GetXorRulesInternal();

			for(int i = 0; rules[i].List[0] != 0; i++)
			{
				int e = 0;
				
				for(int k = 0; rules[i].List[k] != 0; i++)
				{
					if(HasEntry(rules[i].List[k]))
					{
						e++;
					}
				}
				
				if(e > 1)
				{
					std::string error("'xor' rule is broken");
					throw std::underflow_error(error);
				}
			}
		}

		void NextLexeme(Token& token)
		{
			#define NEXTCHAR \
				++p_curr; if(*p_curr == 0) { return; }
				
			register int type   = 0; // param type
			register int quoted = 0; // is quoted?
			register int index  = token.LexemeOffset+token.LexemeLength;

			register const _CharType* p_curr = CommandLine.c_str()+index;

			token.Type = eTokenUnknown;

			while(*p_curr != 0 && *p_curr == ParamSeparator)
			{
				NEXTCHAR
				index++;
			}

			if(*p_curr == _CharType('\"'))
			{
				quoted++;
				goto _q1;
			}
			else if(IsChar(*p_curr, quoted))
			{
				goto _q3;
			}
			else if(*p_curr == ParamSign)
			{
				type++;
				goto _q5;
			}
			else
			{
				goto _e;
			}
_q1:			
			NEXTCHAR
			if(IsChar(*p_curr, quoted))
			{
				goto _q1;
			}
			else if(*p_curr == _CharType('\"'))
			{
				quoted++;
				goto _q2;
			}
			else
			{
				goto _e;
			}
_q4:			
			NEXTCHAR
			if(IsChar(*p_curr, quoted))
			{
				goto _q3;
			}
			else if(*p_curr == _CharType('\"'))
			{
				quoted++;
				goto _q1;
			}
			else
			{
				goto _e;
			}
_q5:			
			NEXTCHAR
			if(IsChar(*p_curr, quoted))
			{
				goto _q3;
			}
			else if(*p_curr == _CharType('\"'))
			{
				quoted++;
				goto _q1;
			}
			else if(*p_curr == ParamSign)
			{
				type++;
				goto _q4;
			}
			else
			{
				goto _e;
			}
_q2:			
			p_curr++;
_q2_process:
			if(type == 0)
			{
				token.Type = eTokenArg;
			}
			else if(type == 1)
			{
				token.Type = eTokenShortParam;
			}
			else if(type == 2)
			{
				token.Type = eTokenLongParam;
			}
			token.LexemeOffset	= index;
			token.LexemeLength	= static_cast<int>(p_curr-(CommandLine.c_str()+index));
			token.NameOffset	= index+std::max(0, quoted-1)+type; // +1 for "
			token.NameLength	= (static_cast<int>(p_curr-(CommandLine.c_str()+index)))-(quoted+type); // +2 for ""
			goto _e;
_q3:			
			++p_curr;
			if(IsChar(*p_curr, quoted))
			{
				goto _q3;
			}
			else if(*p_curr == 0 || *p_curr == ParamSeparator)
			{
				goto _q2_process;
			}
			goto _e;
_e:
			return;
			#undef NEXTCHAR
		}

		bool IsWhiteSpace(_CharType _c)
		{
			return _c == 0x20 || _c == 0x0D || _c == 0x0A || _c == 0x09 || _c == 0x0B/*c++*/;
		}

		bool IsChar(_CharType _c, int quoted)
		{
			bool rc = IsInRange(_c, _CharType('a'), _CharType('z'))		 ||
					  IsInRange(_c, _CharType('A'), _CharType('Z'))		 ||
					  IsInRange(_c, 0x0030, 0x0039)						 ||
					  (quoted > 0 && _c == _CharType(' '))				 ||
					  _c == _CharType('/') && ParamSign	!= _CharType('/')||
					  _c == _CharType('.')								 ||
					  _c == _CharType('_')								 ||
					  _c == _CharType('*')								 ||
					  _c == _CharType('!')								 ||
					  _c == _CharType('@')								 ||
					  _c == _CharType('$')								 ||
					  _c == _CharType('~')								 ||
					  _c == _CharType('^')								 ||
					  _c == _CharType('%')								 ||
					  _c == _CharType('#');
			return rc;
		}

		bool IsInRange(_CharType _c, int _r1, int _r2)
		{
			return _c >= _r1 && _c <= _r2;
		}
		
		virtual _StringType ToString() = 0;

	public:
		CommandLineManager(int _argc, const _CharType* const _argv[], bool _validate = true, _CharType sign = _CharType('-'), _CharType sep = _CharType(' '))
			throw(std::invalid_argument/*unknow param*/, std::out_of_range/*param has arg*/, std::underflow_error/*mandatory param*/)
			: Validate(_validate), ParamSign(sign), ParamSeparator(sep)
		{
			BuildCommandLine(_argc, _argv);
		}
															  
		CommandLineManager(const _CharType* _application, const _CharType* _cline, bool _validate = true, _CharType sign = _CharType('-'), _CharType sep = _CharType(' '))
			throw(std::invalid_argument/*unknow param*/, std::out_of_range/*param has arg*/, std::underflow_error/*mandatory param*/)
			: Validate(_validate), Application(_application), CommandLine(_cline), ParamSign(sign), ParamSeparator(sep)
		{
		}
		
		CommandLineManager(const _StringType& _application, const _StringType& _cline, bool _validate = true, _CharType sign = _CharType('-'), _CharType sep = _CharType(' '))
			throw(std::invalid_argument/*unknow param*/, std::out_of_range/*param has arg*/, std::underflow_error/*mandatory param*/)
			: Validate(_validate), Application(_application), CommandLine(_cline), ParamSign(sign), ParamSeparator(sep)
		{
		}
		
	   ~CommandLineManager()
		{
		}

		bool HasEntry(unsigned int _id)
		{
			return !Params.empty() && Params.find(_id) != Params.end();
		}
		
		bool operator & (unsigned int _id)
		{
			return HasEntry(_id);
		}
		
		std::string GetValue(unsigned int _id)
		{
			std::string value;

			if(!Params.empty())
			{
			   _Params::iterator it = Params.find(_id);

				if(it != Params.end())
				{
					value.assign(CommandLine, (*it).second.Offset, (*it).second.Length);
				}
			}
			return value;
		}
};

typedef CommandLineManager<char> CLM;
typedef CommandLineManager<wchar_t> CLMW;

//
#define COMMANDLINE_MAP_BEGIN()										\
	static Param* GetParams()										\
	{																\
		static Param _params[] =									\
		{
#define COMMANDLINE_MAP_PARAM_BEGIN()								\
			{
#define COMMANDLINE_MAP_PARAM(_id, _f, _sv, _lv, _hv)				\
			_id, _f, _sv, _lv, _hv , {
#define COMMANDLINE_MAP_ARG(_id, _f, _v, _hv)						\
			{ _id, _f, _v, _hv },
#define COMMANDLINE_MAP_PARAM_END()									\
			{ 0, 0, "", "" } } },
#define COMMANDLINE_MAP_END()										\
			{ 0, 0, "", "", "" }									\
		};															\
		return _params;												\
	}																\
	void Bind()														\
	{																\
		GetParamsInternal	= &GetParams;							\
		GetAndRulesInternal	= &GetAndRules;							\
		GetOrRulesInternal	= &GetOrRules;							\
		GetXorRulesInternal	= &GetXorRules;							\
	}
#define COMMANDLINE_MAP_BIND()										\
	Bind();															\
	Parse();														\
	ValidateInput();
#define COMMANDLINE_MAP_AND_RULES_BEGIN()							\
	static AndRule* GetAndRules()									\
	{																\
		static AndRule _rules[] =									\
		{
#define COMMANDLINE_MAP_AND_RULE_BEGIN(_id)							\
			_id, {
#define COMMANDLINE_MAP_AND_RULE_ENTRY(_id)							\
			{ _id },
#define COMMANDLINE_MAP_AND_RULE_END()								\
			{ 0 } },
#define COMMANDLINE_MAP_AND_RULES_END()								\
		};															\
		return _rules;												\
	}
#define COMMANDLINE_MAP_OR_RULES_BEGIN()							\
	static OrRule* GetOrRules()										\
	{																\
		static OrRule _rules[] =									\
		{
#define COMMANDLINE_MAP_OR_RULE_BEGIN(_id)							\
			_id, {
#define COMMANDLINE_MAP_OR_RULE_ENTRY(_id)							\
			{ _id },
#define COMMANDLINE_MAP_OR_RULE_END()								\
			{ 0 } },
#define COMMANDLINE_MAP_OR_RULES_END()								\
		};															\
		return _rules;												\
	}
#define COMMANDLINE_MAP_XOR_RULES_BEGIN()							\
	static XorRule* GetXorRules()									\
	{																\
		static XorRule _rules[] =									\
		{
#define COMMANDLINE_MAP_XOR_RULE_BEGIN()							\
			{
#define COMMANDLINE_MAP_XOR_RULE_ENTRY(_id)							\
			_id ,
#define COMMANDLINE_MAP_XOR_RULE_END()								\
			0 },
#define COMMANDLINE_MAP_XOR_RULES_END()								\
		};															\
		return _rules;												\
	}
////////////////////////////////////////////////////////////////////////////////////////
//__END_NAMESPACE__

#endif // ifndef __COMMANDLINE_MANAGER_H__
