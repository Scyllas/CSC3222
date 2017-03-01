#include "GenerateTiles.h"



GenerateTiles::GenerateTiles()
{

	int imageWidth = -1;
	int imageHeight = -1;
	int imageChannel = -1;
	int ImageChannelForce = SOIL_LOAD_AUTO;
	unsigned char* background = SOIL_load_image("Images/cw_map.bmp",
		&imageWidth, &imageHeight, &imageChannel, ImageChannelForce);

	int noOfPixels = imageWidth * imageHeight;
	int noOfPixelColours = noOfPixels * imageChannel;
	int temp = 0;

	pixelCoord = new Vector2[noOfPixels];
	pixelColour = new Vector3[noOfPixelColours];
	tiles = new Tile[noOfPixels];


	for (int i = 0; i < noOfPixels; i++) {
		int x = i / 10;
		int y = i % 10;
		pixelCoord[i] = Vector2((const float)x, (const float)y);

	}

	for (int i = 0; i < noOfPixelColours; i += 3) {
		int r = background[i];
		int g = background[i + 1];
		int b = background[i + 2];
		pixelColour[temp] = Vector3((const float)r, (const float)g, (const float)b);
		temp++;
	}

	for (int i = 0; i < noOfPixels; i++) {

		tiles[i] = Tile(pixelCoord[i], pixelColour[i]);

	}

}

GenerateTiles::~GenerateTiles()
{
}
