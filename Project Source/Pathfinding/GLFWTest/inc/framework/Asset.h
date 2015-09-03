/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Asset Parent class

-----------------------------------------------------------------------------*/

#ifndef ASSET_H
#define ASSET_H

#include <map>
#include <locale>
#include <string>

template<class T>
class TAsset
{
public:
	TAsset(const char *filename)
	{
		m_id = ms_nextID;
		ms_nextID += 1;
		
		ms_byID[m_id] = (void *)(this);

		ms_byFilename[ std::string(filename) ] = (void *)this;
	}

	virtual ~TAsset()
	{

	}
	
	T *GetByID(unsigned int id)
	{
		auto iter = ms_byID.find(id);
		if( iter != ms_byID.end() )
			return (T *)(iter->second);
			
		return NULL;
	}

	T *GetByFilename(const char *filename)
	{
		auto iter = ms_byFilename.find( (filename) );
		if( iter != ms_byFilename.end() )
			return (T *)(iter->second);
			
		return NULL;
	}

private:

	static std::map<unsigned int, void *> ms_byID;
	static std::map<std::string,  void *>  ms_byFilename;

	static unsigned int ms_nextID;
	unsigned int m_id;

	
};

template<class T>
unsigned int TAsset<T>::ms_nextID = 0;

template<class T>
std::map<unsigned int, void *> TAsset<T>::ms_byID;

template<class T>
std::map<std::string,  void *>  TAsset<T>::ms_byFilename;

#endif