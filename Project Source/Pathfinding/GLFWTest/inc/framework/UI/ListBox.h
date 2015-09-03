/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Basic ListBox class 
-----------------------------------------------------------------------------*/

#ifndef LIST_BOX_H
#define	LIST_BOX_H

#include "framework\Framework.h"
#include "framework\Texture2D.h"
#include "SceneNode.h"
#include "Box.h"
#include <list>


namespace AIE
{

class ListBox : public SceneNode
{
public:

	ListBox(Framework* framework, Vec2 boxSize, char* title, std::string fileName);

	virtual ~ListBox();

	virtual void Update(float dt);

	virtual void Draw();


protected:
private:


	Framework* m_framework;

	std::string m_fileName;

	Texture2D* m_topTexture;
	Texture2D* m_centerTexture;
	Texture2D* m_bottomTexture;
	Texture2D* m_seperatorTexture;


	AIE::Vec2 m_boxSize;
	AIE::Vec2 m_position;

	std::list<Box* > m_boxes;
	std::list<Box* > m_seperators;

	std::list<std::string > m_list;
	std::list<AIE::Vec2 > m_positions;

	void LoadItems();
	void CalculatePositions();

	bool open;
};

}
#endif