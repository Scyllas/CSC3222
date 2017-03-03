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

	pixelCoord = new Vector2[noOfPixels];
	pixelColour = new Vector3[noOfPixelColours];
	tiles = new Tile[noOfPixels];

	int modifier = 1;
	int temp = 0; 

	for (int i = 0; i < noOfPixels; i++) {
		int x = i % imageWidth;
		int y = (i - x) / imageWidth;

		pixelCoord[i] = Vector2((const float)x, (const float)y);
	}

	//colour read from top left to bottom right needs to be bottom left to top right, forloop does this
	for (int y = imageHeight-1; y >= 0; y--) {
		for (int x = noOfPixelColours - (modifier * 60); x < noOfPixelColours - ((modifier - 1) * 60); x += 3) {

			int r = background[x];
			int g = background[x + 1];
			int b = background[x + 2];
			pixelColour[temp] = Vector3((const float)r, (const float)g, (const float)b);
			temp++;
		}
		modifier++;
	}

	for (int i = 0; i < noOfPixels; i++) {

		tiles[i] = Tile(pixelCoord[i], pixelColour[i]);

	}

}

GenerateTiles::~GenerateTiles()
{
}
