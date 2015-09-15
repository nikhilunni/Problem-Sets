#include "scene.h"
#include "image.h"
#include <iostream>

using namespace std;
Scene::Scene(int maximum)
{
	max = maximum;
	images = new Image*[max];
	coords = new int*[max];
	for(int i = 0; i < max; i++)
	{
		images[i] = NULL;
		coords[i] = NULL;
	}	
}

Scene::Scene(const Scene& source)
{
	copy(source);
}

Scene::~Scene() 
{
	clean();
}
void Scene::clean()
{
	for(int i = 0; i < max; i++)
	{
		delete images[i];
		delete[] coords[i];
	}
	delete[] images;
	delete[] coords;
}

void Scene::copy(const Scene& other)
{
	max = other.max;
	images = new Image*[other.max];
	coords = new int*[other.max];
	for(int i = 0; i < max; i++) 
	{
		if(other.images[i] == NULL)
		{
			images[i] = NULL;
			coords[i] = NULL;
		}
		else 
		{
			images[i] = new Image(*other.images[i]);
			coords[i] = new int[2];
			coords[i][0] = other.coords[i][0];
			coords[i][1] = other.coords[i][1];
		}
	}
}
const Scene& Scene::operator=(const Scene& source)
{
	if(&source == this)
	{
		return *this;
	}
	clean();
	copy(source);
	return *this;
}

void Scene::changemaxlayers(int newmax)
{
	if(newmax < 0) {
		cout << "invalid newmax" << endl;
		return;
	}
	int i = 0;
	if(newmax < max)
	{
		for(i = newmax; i < max; i++) 
		{
			if(images[i] != NULL)
			{
				cout << "invalid newmax" << endl;
				break;	
			}
		} 
	}
	else
	{
		Image** newImages = new Image*[newmax];
		int** newCoords = new int*[newmax];
		for(i = 0; i < newmax; i++)
		{
			newImages[i] = images[i];	
			newCoords[i] = coords[i];
		}
		delete[] images;
		delete[] coords;
		images = newImages;
		coords = newCoords;
	}
}

void Scene::addpicture(const char* FileName, int index, int x, int y)
{
	if(index < 0 || index >= max)
	{
		cout << "index out of bounds" << endl;
	}
	else 
	{
		Image* newImage = new Image();
		newImage->readFromFile(FileName);
		delete images[index];
		delete[] coords[index];
		images[index] = newImage;

		coords[index] = new int[2];
		coords[index][0]=x;
		coords[index][1]=y;
	}
}

void Scene::changelayer(int index, int newindex)
{
	if(index != newindex && index >= 0 && index < max && newindex >= 0 && newindex < max)
	{
		if(images[newindex] != NULL)
		{
			delete images[newindex];
			delete[] coords[newindex];
		}
		images[newindex] = images[index];
		coords[newindex] = coords[index];
		images[index] = NULL;
		coords[index] = NULL;
	}
	else
	{
		cout << "invalid index" << endl;
	}
}

void Scene::translate(int index, int xcoord, int ycoord)
{
	if(index < 0 || index >= max || images[index]==NULL)
	{
		cout << "invalid index" << endl;
	}
	else
	{
		coords[index][0] = xcoord;
		coords[index][1] = ycoord;
	}
}

void Scene::deletepicture(int index)
{
	if(index < 0 || index >= max || images[index]==NULL)
	{
		cout << "invalid index" << endl;
	}
	else
	{
		delete images[index];
		delete[] coords[index];
		images[index] = NULL;
		coords[index] = NULL;
	}
}

Image* Scene::getpicture(int index) const
{
	if(index < 0 || index >= max)
	{
		cout << "invalid index" << endl;
		return NULL;
	}
	else
	{
		return images[index];
	}
}

Image Scene::drawscene() const
{
	int width = 0;
	int height = 0;
	for(int index = 0; index < max; index++)
	{
		if(images[index] != NULL)
		{
			int newWidth = coords[index][0]+images[index]->width();
			int newHeight = coords[index][1]+images[index]->height();
			width = (newWidth > width) ? newWidth : width;
			height = (newHeight > height) ? newHeight : height;
		}
	}
	Image output;
	output.resize(width,height);
	for(int index = 0; index < max; index++)
	{
		if(images[index] != NULL)
		{
			Image* pntr = images[index];
			for(size_t x = 0; x < pntr->width(); x++)
			{
				for(size_t y = 0; y < pntr->height(); y++)
				{
					int newX = coords[index][0]+x;
					int newY = coords[index][1]+y;
					if(newX >= 0 && newY >= 0)
					{
						RGBAPixel* temp = (*pntr)(x,y);
						output(newX,newY)->red = temp->red;
						output(newX,newY)->green = temp->green;
						output(newX,newY)->blue = temp->blue;
						output(newX,newY)->alpha = temp->alpha;
					}
				}
			}
		}
	}
	return output;
}

