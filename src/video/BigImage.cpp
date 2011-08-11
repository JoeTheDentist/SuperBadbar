#include "BigImage.h"
#include <iostream>
#include <SOIL.h>

namespace
{
    struct Rectangles
    {
        unsigned x,y,w,h;
        Rectangles(unsigned x, unsigned y, unsigned w, unsigned h) : x(x), y(y), w(w), h(h){}
    };
    GLint initialise_max();
    sf::Image GetImageFromRectangle(const Rectangles& r, const sf::Uint32*p, unsigned pw);
    std::pair<std::vector<sf::Image>, std::pair<unsigned,unsigned> > CreateVectorFromPixels(unsigned int rect_size, const sf::Uint32* pixels, unsigned width, unsigned height);
    std::pair<std::vector<sf::Image>, std::pair<unsigned,unsigned> > CreateVectorFromColor(unsigned int rect_size, const sf::Color& col, unsigned width, unsigned height);

    GLint initialise_max()
    {
		return 512;
        GLint r;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &r);
        if(glGetError()==GL_INVALID_OPERATION)
        {
            r=512;
            std::cerr<<"Couldn't retrieve max texture size.\n";
        }
        return r;
    }
    sf::Image GetImageFromRectangle(const Rectangles& r, const sf::Uint32*p, unsigned pw)
    {
        sf::Uint32*pixels=new sf::Uint32[r.w*r.h];
        for(unsigned x=r.x;x<r.x+r.w;x++)
        {
            for(unsigned y=r.y;y<r.y+r.h;y++)
            {
                pixels[(x-r.x)+(y-r.y)*r.w]=p[x+y*pw];
            }
        }
        sf::Uint8*pi=(sf::Uint8*)pixels;
        sf::Image img;
        img.LoadFromPixels(r.w, r.h,pi);
        delete[] pixels;
        return img;
    }
    std::pair<std::vector<sf::Image>, std::pair<unsigned,unsigned> > CreateVectorFromPixels(unsigned int rect_size, const sf::Uint32* pixels, unsigned width, unsigned height)
    {
        std::vector<sf::Image> img;
        unsigned h=0,w=0;
        unsigned nbimageheight=0;
        while(height>h+rect_size)
        {
            nbimageheight++;
            w=0;
            while(width>w+rect_size)
            {
                img.push_back(GetImageFromRectangle(Rectangles(w,h,rect_size,rect_size), pixels, width));
                w+=rect_size;
            }
            if(w!=width-1)
            {
                img.push_back(GetImageFromRectangle(Rectangles(w,h,width-w,rect_size), pixels, width));
            }

            h+=rect_size;
        }
        if(height-1!=h)
        {
            nbimageheight++;
            w=0;
            while(width>w+rect_size)
            {
                img.push_back(GetImageFromRectangle(Rectangles(w,h,rect_size,height-h), pixels, width));
                w+=rect_size;
            }
            if(w!=width-1)
            {
                img.push_back(GetImageFromRectangle(Rectangles(w,h,width-w,height-h), pixels, width));
            }
        }
        return std::make_pair(img, std::make_pair(img.size()/nbimageheight, nbimageheight));
    }

    std::pair<std::vector<sf::Image>, std::pair<unsigned,unsigned> > CreateVectorFromColor(unsigned int rect_size, const sf::Color& col, unsigned width, unsigned height)
    {
        std::vector<sf::Image> img;
        unsigned h=0,w=0;
        unsigned nbimageheight=0;
        while(height>h+rect_size)
        {
            nbimageheight++;
            w=0;
            while(width>w+rect_size)
            {
                img.push_back(sf::Image(rect_size,rect_size, col));
                w+=rect_size;
            }
            if(w!=width-1)
            {
                img.push_back(sf::Image(width-w,rect_size,col));
            }

            h+=rect_size;
        }
        if(height-1!=h)
        {
            nbimageheight++;
            w=0;
            while(width>w+rect_size)
            {
                img.push_back(sf::Image(rect_size,height-h, col));
                w+=rect_size;
            }
            if(w!=width-1)
            {
                img.push_back(sf::Image(width-w,height-h,col));
            }
        }
        return std::make_pair(img, std::make_pair(img.size()/nbimageheight, nbimageheight));
    }
    bool WriteBMPFromPixel(const sf::Uint32* pixels, unsigned width, unsigned height, const std::string& filename)
    {
        return SOIL_save_image(filename.c_str(), SOIL_SAVE_TYPE_BMP, width, height, 4, (const unsigned char*)pixels);
    }
}




const GLint BigImage::max_texture_size=initialise_max();

unsigned BigImage::CalculHeight()const
{
    unsigned r=0;
    for(unsigned i=0;i<nbimageheight;i++)
    {
        r+=img[i*nbimagewidth].GetHeight();
    }

    return r;
}

unsigned int BigImage::CalculWidth () const
{
    unsigned r=0;
    for(unsigned i=0;i<nbimagewidth;i++)
    {
        sf::Image im=img[i];
        r+=im.GetWidth();
    }
    return r;
}

BigImage::BigImage (unsigned int Width, unsigned int Height, const sf::Color &col)
{
    std::pair<std::vector<sf::Image>, std::pair<unsigned, unsigned> > r=CreateVectorFromColor(max_texture_size, col, Width, Height);
    img=r.first;
    nbimagewidth=r.second.first;
    nbimageheight=r.second.second;
    for(unsigned i=0;i<img.size();i++)
        img[i].SetSmooth(false);
    width=Width;
    height=Height;
}

BigImage::BigImage (unsigned int Width, unsigned int Height, const sf::Uint8 *Data)
{
    if(!LoadFromPixels(Width, Height, Data))
    {
        std::cerr<<"Could not load image from pixels.\n";
        *this=BigImage();
    }
    width=Width;
    height=Height;
}

bool BigImage::LoadFromFile(const std::string& filename)
{
    int wmax, hmax;
    int ImgChannels;
    sf::Uint32*pixels=(sf::Uint32*)(SOIL_load_image(filename.c_str(), &wmax, &hmax, &ImgChannels, SOIL_LOAD_RGBA));
    if(!pixels)
        return false;
    std::pair<std::vector<sf::Image>, std::pair<unsigned, unsigned> > r=CreateVectorFromPixels(max_texture_size, pixels, wmax, hmax);
    img=r.first;
    nbimagewidth=r.second.first;
    nbimageheight=r.second.second;
    free(pixels);
    for(unsigned i=0;i<img.size();i++)
        img[i].SetSmooth(false);
    width=CalculWidth();
    height=CalculHeight();
    return true;
}

bool BigImage::LoadFromPixels(unsigned width, unsigned height, const sf::Uint8*data)
{
    const sf::Uint32*pixels=(sf::Uint32*)(data);
    if(!pixels)
        return false;
    std::pair<std::vector<sf::Image>, std::pair<unsigned, unsigned> > r=CreateVectorFromPixels(max_texture_size, pixels, width, height);
    img=r.first;
    nbimagewidth=r.second.first;
    nbimageheight=r.second.second;
    for(unsigned i=0;i<img.size();i++)
        img[i].SetSmooth(false);
    this->width=width;
    this->height=height;
    return true;
}


bool BigImage::LoadFromMemory (const unsigned char *Data, std::size_t SizeInBytes)
{
    int width, height, imgc;
    unsigned char*pixels=SOIL_load_image_from_memory(Data, SizeInBytes, &width, &height, &imgc, SOIL_LOAD_RGBA);
    if(!pixels)
        return false;
    std::pair<std::vector<sf::Image>, std::pair<unsigned, unsigned> > r=CreateVectorFromPixels(max_texture_size, (sf::Uint32*)pixels, width, height);
    img=r.first;
    nbimagewidth=r.second.first;
    nbimageheight=r.second.second;
    for(unsigned i=0;i<img.size();i++)
        img[i].SetSmooth(false);
    free(pixels);
    width=CalculWidth();
    height=CalculHeight();
    return true;
}

sf::Color BigImage::GetPixel(unsigned x,unsigned y)const
{
    unsigned nbx=x%max_texture_size;
    unsigned nby=y%max_texture_size;
    unsigned ix=(unsigned)(x/max_texture_size);
    unsigned iy=(unsigned int)(y/max_texture_size);
    if(ix<nbimagewidth &&iy<nbimageheight)
        return img[ix+iy*nbimagewidth].GetPixel(nbx,nby);
    else
        return sf::Color(0,0,0,0);
}
void BigImage::SetPixel (unsigned int x, unsigned int y, const sf::Color &col)
{
    unsigned nbx=x%max_texture_size;
    unsigned nby=y%max_texture_size;
    unsigned ix=(unsigned)(x/max_texture_size);
    unsigned iy=(unsigned int)(y/max_texture_size);
    if(ix<nbimagewidth &&iy<nbimageheight)
        img[ix+iy*nbimagewidth].SetPixel(nbx,nby, col);
}


unsigned int BigImage::GetWidth () const
{
    return width;
}
unsigned int BigImage::GetHeight () const
{
    return height;
}

bool BigImage::Create (unsigned int Width, unsigned int Height, const sf::Color& Col)
{
    *this=BigImage(Width,Height,Col);
    return true;
}

void BigImage::CreateMaskFromColor (const sf::Color& col, sf::Uint8 Alpha)
{
    for(unsigned x=0;x<width;x++)
    {
        for(unsigned y=0;y<height;y++)
        {
            if(GetPixel(x,y)==col)
            {
                SetPixel(x,y, sf::Color(col.r, col.g, col.b, Alpha));
            }
        }
    }
}

void BigImage::Copy (const sf::Image &Source, unsigned int DestX, unsigned int DestY, const sf::IntRect &SourceRect, bool ApplyAlpha)
{
    for(int x=0;x<SourceRect.GetWidth();x++)
    {
        for(int y=0;y<SourceRect.GetHeight();y++)
        {
            if(ApplyAlpha)
                SetPixel(x+DestX,y+DestY, Source.GetPixel(x+SourceRect.Left,y+SourceRect.Top));
            else
            {
                sf::Color c=Source.GetPixel(x+SourceRect.Left,y+SourceRect.Top);
                SetPixel(x+DestX,y+DestY, sf::Color(c.r, c.g, c.b));
            }

        }
    }
}

bool BigImage::SaveToFile (const std::string &filename) const
{
    std::string Extension = filename.substr(filename.size() - 3);
    if(Extension!="bmp"&&Extension!="BMP" )
    {
        std::cerr<<"Format non pris en charge.\n";
        return false;
    }
    sf::Uint32 *pixels=new sf::Uint32[width*height];
    for(unsigned int x=0;x<width;x++)
    {
        for(unsigned int y=0;y<height;y++)
        {
            sf::Uint8* p=(sf::Uint8*)(&(pixels[x+y*width]));
            sf::Color c=GetPixel(x,y);
            p[0]=c.r;
            p[1]=c.g;
            p[2]=c.b;
            p[3]=255;
        }
    }
    if(WriteBMPFromPixel(pixels, width, height, filename))
        return true;
    return false;
}

sf::FloatRect BigImage::GetTexCoords (const sf::IntRect &Rect) const
{
    return sf::FloatRect(Rect.Left/static_cast<float>(width), Rect.Top/static_cast<float>(height),Rect.Right/static_cast<float>(width),Rect.Bottom/static_cast<float>(height));
}


















void BigSprite::Render (sf::RenderTarget &Target) const
{
    for(unsigned i=0;i<sprt.size();i++)
    {
        if(HideSprite.find(i)==HideSprite.end())
            Target.Draw(sprt[i]);
    }

}




BigSprite::BigSprite (const BigImage &img, const sf::Vector2f &Position, const sf::Vector2f &Scale, float Rotation, const sf::Color &Col) : sf::Drawable(Position, Scale,Rotation, Col)
{
    for(unsigned i=0;i<img.img.size();i++)
    {
        sprt.push_back(sf::Sprite(img.img[i]));
    }
    for(unsigned x=0;x<img.nbimagewidth;x++)
    {
        for(unsigned y=0;y<img.nbimageheight;y++)
        {
            sprt[x+y*img.nbimagewidth].Move(img.max_texture_size*x, img.max_texture_size*y);
        }
    }
    SubRect=sf::IntRect(0,0,img.GetWidth(), img.GetHeight());
    image=&img;
}

sf::Vector2f BigSprite::GetSize () const
{
    return sf::Vector2f(SubRect.GetWidth() * GetScale().x, SubRect.GetHeight() * GetScale().y);
}

void BigSprite::Resize (float Width, float Height)
{
    SetScale(Width/static_cast<float>(SubRect.GetWidth()), Height/static_cast<float>(SubRect.GetHeight()));
}

void BigSprite::Resize (const sf::Vector2f& v)
{
    Resize(v.x,v.y);
}

const sf::IntRect & BigSprite::GetSubRect () const
{
    return SubRect;
}


void BigSprite::SetSubRect (const sf::IntRect &SubRectp)
{
    if(!image)
        return;
    *this=BigSprite(*image, GetPosition(), sf::Vector2f(1,1),GetRotation());
    SubRect=SubRectp;
    unsigned w=0,h=0;
    unsigned xmin,xmax, ymin, ymax;
    for(unsigned x=0;x<image->nbimagewidth;x++)
    {
        w+=image->img[x].GetWidth();
        if(w>SubRect.Left)
        {
            xmin=x;
            break;
        }

    }
    w=0;
    for(unsigned x=0;x<image->nbimagewidth;x++)
    {
        w+=image->img[x].GetWidth();
        if(w>SubRect.Right)
        {
            xmax=x;
            break;
        }

    }
    for(int y=0;y<image->nbimageheight;y++)
    {
        h+=image->img[y*image->nbimagewidth].GetHeight();
        if(h>SubRect.Top)
        {
            ymin=y;
            break;
        }
    }
    h=0;
    for(unsigned y=0;y<image->nbimageheight;y++)
    {
        h+=image->img[y*image->nbimagewidth].GetHeight();
        if(h>SubRect.Bottom)
        {
            ymax=y;
            break;
        }
    }

    for(unsigned x=0;x<xmin;x++)
    {
        for(unsigned y=0;y<image->nbimageheight;y++)
        {
            HideSprite.insert(x+y*image->nbimagewidth);
        }
    }

    for(unsigned x=xmax+1;x<image->nbimagewidth;x++)
    {
        for(unsigned y=0;y<image->nbimageheight;y++)
        {
            HideSprite.insert(x+y*image->nbimagewidth);
        }
    }

    for(unsigned y=0;y<ymin;y++)
    {
        for(unsigned x=0;x<image->nbimagewidth;x++)
        {
            HideSprite.insert(x+y*image->nbimagewidth);
        }
    }

    for(unsigned y=ymax+1;y<image->nbimageheight;y++)
    {
        for(unsigned x=0;x<image->nbimagewidth;x++)
        {
            HideSprite.insert(x+y*image->nbimagewidth);
        }
    }
    for(unsigned i=0;i<sprt.size();i++)
        sprt[i].Move(-static_cast<int>(SubRect.Left), -static_cast<int>(SubRect.Top));
    for(unsigned y=ymin+1; y<ymax;y++)
    {
        sf::IntRect tmp=sprt[xmin+image->nbimagewidth*y].GetSubRect();
        tmp.Left=SubRect.Left-(image->max_texture_size*xmin);
        sprt[xmin+image->nbimagewidth*y].SetSubRect(tmp);
        sprt[xmin+image->nbimagewidth*y].Move(SubRect.Left-(image->max_texture_size*xmin),0);
    }
    for(unsigned y=ymin+1; y<ymax;y++)
    {
        sf::IntRect tmp=sprt[xmax+image->nbimagewidth*y].GetSubRect();
        tmp.Right=SubRect.Right-(image->max_texture_size*xmax);
        sprt[xmax+image->nbimagewidth*y].SetSubRect(tmp);
    }

    for(unsigned x=xmin+1; x<xmax;x++)
    {
        sf::IntRect tmp=sprt[x+image->nbimagewidth*ymin].GetSubRect();
        tmp.Top=SubRect.Top-(image->max_texture_size*ymin);
        sprt[x+image->nbimagewidth*ymin].SetSubRect(tmp);
        sprt[x+image->nbimagewidth*ymin].Move(0,SubRect.Top-(image->max_texture_size*ymin));
    }
    for(unsigned x=xmin+1; x<xmax;x++)
    {
        sf::IntRect tmp=sprt[x+image->nbimagewidth*ymax].GetSubRect();
        tmp.Bottom=SubRect.Bottom-(image->max_texture_size*ymax);
        sprt[x+image->nbimagewidth*ymax].SetSubRect(tmp);
    }

    sf::IntRect t;
    t=sprt[xmin+ymin*image->nbimagewidth].GetSubRect();
    t.Left=SubRect.Left-(image->max_texture_size*xmin);
    t.Top=SubRect.Top-(image->max_texture_size*ymin);
    sprt[xmin+ymin*image->nbimagewidth].SetSubRect(t);
    sprt[xmin+ymin*image->nbimagewidth].Move(SubRect.Left-(image->max_texture_size*xmin),SubRect.Top-(image->max_texture_size*ymin));

    t=sprt[xmax+ymin*image->nbimagewidth].GetSubRect();
    t.Right=SubRect.Right-(image->max_texture_size*xmax);
    t.Top=SubRect.Top-(image->max_texture_size*ymin);
    sprt[xmax+ymin*image->nbimagewidth].SetSubRect(t);
    sprt[xmax+ymin*image->nbimagewidth].Move(0,SubRect.Top-(image->max_texture_size*ymin));

    t=sprt[xmin+ymax*image->nbimagewidth].GetSubRect();
    t.Left=SubRect.Left-(image->max_texture_size*xmin);
    t.Bottom=SubRect.Bottom-(image->max_texture_size*ymax);
    sprt[xmin+ymax*image->nbimagewidth].SetSubRect(t);
    sprt[xmin+ymax*image->nbimagewidth].Move(SubRect.Left-(image->max_texture_size*xmin),0);

    t=sprt[xmax+ymax*image->nbimagewidth].GetSubRect();
    t.Right=SubRect.Right-(image->max_texture_size*xmax);
    t.Bottom=SubRect.Bottom-(image->max_texture_size*ymax);
    sprt[xmax+ymax*image->nbimagewidth].SetSubRect(t);
}
const BigImage * BigSprite::GetImage () const
{
    return image;
}

void BigSprite::SetImage (const BigImage &img)
{
    sprt.clear();
    for(unsigned i=0;i<img.img.size();i++)
    {
        sprt.push_back(sf::Sprite(img.img[i]));
    }
    for(unsigned x=0;x<img.nbimagewidth;x++)
    {
        for(unsigned y=0;y<img.nbimageheight;y++)
        {
            sprt[x+y*img.nbimagewidth].Move(img.max_texture_size*x, img.max_texture_size*y);
        }
    }
    SubRect=sf::IntRect(0,0,img.GetWidth(), img.GetHeight());
    image=&img;
}
