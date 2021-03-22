////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __DICTIONARY_INC__
#   include <Dictionary.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Dictionary
// ----- ----------
Dictionary::Dictionary(const tchar* _filename, uint _count, uint _limit)
          : Dict(_count, 16, 0, _Array::AutoResize|_Array::Init), Index(0), Limit(_limit)
{
    _xassertv(Dictionary::XDictionary, _filename != null && _taccess(_filename, 0) == 0, X::InvalidArg)
    //
    FILE* f = ::fopen(_filename, _t("rb"));

    if(f != null)
    {
        //
        const short _line_size_ = 48;
        //
        tchar line[_line_size_];

        while(!feof(f) && Index < Limit)
        {
            line[0] = 0;

            if(::fgets(line, _line_size_, f) != null && line[0] != 0)
            {
                if(!Table.HasString(line))
                {
                    Dict[Index] = StrClone(line);
                    Table.Insert(Dict[Index].GetP(), Dict[Index]);
                    Index++;
                }
            }
        }
      ::fclose(f);
    }
}

Dictionary::~Dictionary()
{
}

void Dictionary::Insert(const tchar* _e)
{
    _xassertv(Dictionary::XDictionary, _e != null, X::InvalidArg)
    //    
    if(Index < Limit && !Table.HasString(_e))
    {
        Dict[Index] = StrClone(_e);
        Table.Insert(Dict[Index].GetP(), Dict[Index]);
        Index++;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class XDictionary
// ----- -----------
Dictionary::XDictionary::XDictionary(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
