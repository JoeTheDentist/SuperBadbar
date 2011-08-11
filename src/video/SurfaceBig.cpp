#include "SurfaceBig.h"
#include "video/PicturesContainer.h"

SurfaceBig::SurfaceBig(std::string filename)
{
	m_bigSprite = m_pictures_container->loadBigPicture(filename);
	setSurface(m_bigSprite);
}

int SurfaceBig::w()
{
	return m_bigSprite ? m_bigSprite->GetSize().x : 5;	
}

int SurfaceBig::h()
{
	return m_bigSprite ? m_bigSprite->GetSize().y : 5;		
}
