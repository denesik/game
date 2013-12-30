#ifndef FontFactory_h__
#define FontFactory_h__

#include "Font.h"
#include <vector>

#undef CreateFont

class IFontFactory;
class IFontFactoryDestroyer
{
private:
	IFontFactory* p_instance;
public:    
	~IFontFactoryDestroyer();
	void initialize( IFontFactory* p );
};


class IFontFactory
{
protected:
	static IFontFactory* p_instance;
	static IFontFactoryDestroyer destroyer;

protected: 
	IFontFactory(){};
	virtual ~IFontFactory(){};

	IFontFactory(const IFontFactory&);
	IFontFactory &operator = (IFontFactory&);

	friend class IFontFactoryDestroyer;

public:
	static IFontFactory &getInstance(){};

	virtual IFont *CreateFont(std::string fileName, std::string fontName, unsigned int size) = 0;
	virtual IFont *GetFont(std::string fontName) = 0;
	virtual bool RemoveFont(std::string fontName) = 0;
	virtual void CleanUp() = 0;
};

class FontTTFFactory : public IFontFactory
{
protected: 
	FontTTFFactory();
	virtual ~FontTTFFactory();

private:
	std::vector<IFont*> fontsVector;

public:
	static IFontFactory &getInstance();

	virtual IFont *CreateFont(std::string fileName, std::string fontName, unsigned int size);
	virtual IFont *GetFont(std::string fontName);
	virtual bool RemoveFont(std::string fontName);

	virtual void CleanUp();
};


#endif // FontFactory_h__