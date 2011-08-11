#ifndef BIGIMAGE_HPP_INCLUDED
#define BIGIMAGE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

class BigSprite;

class BigImage
{
    friend class BigSprite;
    private :
        std::vector<sf::Image> img;
        unsigned nbimagewidth;
        unsigned nbimageheight;
        static const GLint max_texture_size;
        unsigned width;
        unsigned height;
        unsigned int CalculWidth () const;
        unsigned int CalculHeight () const;
    public :
        BigImage():nbimagewidth(0), nbimageheight(0),width(0), height(0){}
        BigImage (unsigned int Width, unsigned int Height, const sf::Color &Col=sf::Color(0, 0, 0, 255));
        BigImage (unsigned int Width, unsigned int Height, const sf::Uint8 *Data);

        bool LoadFromFile(const std::string& f);
        bool LoadFromPixels(unsigned Width,unsigned Height,const sf::Uint8*Data);
        bool LoadFromMemory (const unsigned char *Data, std::size_t SizeInBytes);

        sf::Color GetPixel(unsigned x,unsigned y)const;
        void SetPixel(unsigned int x, unsigned int y, const sf::Color& Col);

        unsigned int GetWidth () const;
        unsigned int GetHeight () const;

        bool Create(unsigned int Width, unsigned int Height, const sf::Color& Col=sf::Color(0, 0, 0, 255));
        void CreateMaskFromColor (const sf::Color& ColorKey, sf::Uint8 Alpha=0);

        void Copy (const sf::Image &Source, unsigned int DestX, unsigned int DestY, const sf::IntRect &SourceRect=sf::IntRect(0, 0, 0, 0), bool ApplyAlpha=false);

        bool SaveToFile (const std::string &Filename) const;

        sf::FloatRect GetTexCoords (const sf::IntRect &Rect) const;
};

class BigSprite : public sf::Drawable
{
    protected :
        const BigImage* image;
        std::vector<sf::Sprite>sprt;
        sf::IntRect SubRect;
        std::set<int> HideSprite;
        virtual void Render (sf::RenderTarget &Target) const;
    public :
        BigSprite(): image(NULL), SubRect(0,0,0,0){}
        BigSprite (const BigImage &Img, const sf::Vector2f &Position=sf::Vector2f(0, 0), const sf::Vector2f &Scale=sf::Vector2f(1, 1), float Rotation=0.f, const sf::Color &Col=sf::Color(255, 255, 255, 255));

        sf::Vector2f GetSize () const;
        void Resize (float Width, float Height);
        void Resize (const sf::Vector2f &Size);


        const sf::IntRect & GetSubRect () const;
        void SetSubRect (const sf::IntRect &SubRect);

        const BigImage * GetImage () const;
        void SetImage (const BigImage &Img);
};
#endif // BIGIMAGE_HPP_INCLUDED
