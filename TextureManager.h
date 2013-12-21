#ifndef TextureManager_h__
#define TextureManager_h__

#include <string>
#include <map>

class TextureManager
{
	std::map<std::string, unsigned int> textureList;
public:
	TextureManager(void);
	~TextureManager(void);

	unsigned int AddFromFile(std::string fileName, std::string name);
	int Get(std::string name);
	void Cleanup();
};

#endif // TextureManager_h__