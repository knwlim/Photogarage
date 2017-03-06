#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BMPImage.h"
unsigned char r, g, b, gred, ggreen, gblue,er,eg,eb,in;
int res_x, res_y;
char input;
bool isInsideCircle( double x, double y)
{
	const double x_c = res_x/2;
	const double y_c = res_y/2;
	const double r = res_y / 3;

	double f = (x - x_c)*(x - x_c) + (y - y_c)*(y - y_c) - r * r;

	if (f > 0.0) return false;
	else return true;
}
bool isInsideCircleforRed(double x, double y)
{
	const double x_c = 160;
	const double y_c = 200;
	const double r = 70;

	double f = (x - x_c)*(x - x_c) + (y - y_c)*(y - y_c) - r * r;

	if (f > 0.0) return false;
	else return true;
}
grayscale() {
	float gr = r * 0.299;
	float gg = g * 0.587;
	float gb = b * 0.114;
	unsigned char gray = gr + gg + gb; 
	gred = gray;
	ggreen = gray;
	gblue = gray;
}
printwords() {
	printf("\n\nWelcome To The Consol Photogarage. \n\nif you want to change your photo, please type one of the characters below\n\n");
	printf("----------------------\n\n");
	printf("For grayscale, Type g\n\nFor coloring only face, Type c\n\nFor Coloring White Background to Blue, Type b\n");
	printf("\nFor Coloring eyes to red, Type r\n\nTo ecnrypt the photo, Type e\n\nTo decrypt the photo, Type d\n");
	printf("\n----------------------");
	printf("\n# Only Lowercase Characters should be typed.\n\n");
	printf("TYPE:");
}
void main()
{
	unsigned char* rgb_array = 0;
	readBMP24("cf.bmp", &res_x, &res_y, &rgb_array);
	printwords();
	scanf("%c", &input );
	printf("\nDone.\n\n");

	switch (input) 
	{

	case 'g' : for (int j = res_y - 1; j >= 0; j--)
		{
			for (int i = 0; i < res_x; i++)
			{
				int ix = i + res_x*j;
				r = rgb_array[ix * 3 + 0];
				g = rgb_array[ix * 3 + 1];
				b = rgb_array[ix * 3 + 2];
				grayscale();
				rgb_array[ix * 3 + 0] = gred;
				rgb_array[ix * 3 + 1] = ggreen;
				rgb_array[ix * 3 + 2] = gblue;
			}
	    }
			   break;

	case 'c': for (int j = res_y - 1; j >= 0; j--)
	{
		for (int i = 0; i < res_x; i++)
		{
			if (isInsideCircle(i,j)==false)
			{
			int ix = i + res_x*j;
			r = rgb_array[ix * 3 + 0];
			g = rgb_array[ix * 3 + 1];
			b = rgb_array[ix * 3 + 2];
			grayscale();
			rgb_array[ix * 3 + 0] = gred;
			rgb_array[ix * 3 + 1] = ggreen;
			rgb_array[ix * 3 + 2] = gblue;
			}
		}
	}
			 break;

	case 'b': for (int j = res_y - 1; j >= 0; j--)
	{
		for (int i = 0; i < res_x; i++)
		{
			int ix = i + res_x*j;
			r = rgb_array[ix * 3 + 0];
			g = rgb_array[ix * 3 + 1];
			b = rgb_array[ix * 3 + 2];
			if (r >= 190 && b >= 190 && b >= 190)
			{
				rgb_array[ix * 3 + 0] = 110;
				rgb_array[ix * 3 + 1] = 110;
				rgb_array[ix * 3 + 2] = 255;

			}

		}
	}
			  break;
	case 'r': for (int j = res_y - 1; j >= 0; j--)
	{
		for (int i = 0; i < res_x; i++) 
		{
			if (isInsideCircleforRed(i, j) == true)
			{
				int ix = i + res_x*j;
				r = rgb_array[ix * 3 + 0];
				g = rgb_array[ix * 3 + 1];
				b = rgb_array[ix * 3 + 2];
				if (r < 25 && g < 25 && b < 25) {
					rgb_array[ix * 3 + 0] = 255;
					rgb_array[ix * 3 + 1] = 0;
					rgb_array[ix * 3 + 2] = 0;
				}
			}

		}
	}
			  break;
	case 'e': for (int j = res_y - 1; j >= 0; j--) {
		for (int i = 0; i < res_x; i++) {
			int ix = i + res_x*j;
			r = rgb_array[ix * 3 + 0];
			g = rgb_array[ix * 3 + 1];
			b = rgb_array[ix * 3 + 2];

			in = ix % 8;

			er= (r << (in)) | (r >> (8 - (in)));
			eg= (g << (in)) | (g >> (8 - (in)));
			eb= (b << (in)) | (b >> (8 - (in)));
			
			rgb_array[ix * 3 + 0] = er^128; 
			rgb_array[ix * 3 + 1] = eg^128;
			rgb_array[ix * 3 + 2] = eb^128;
		}
	}
			  break;
	case 'd': for (int j = res_y - 1; j >= 0; j--) {
		for (int i = 0; i < res_x; i++) {
			int ix = i + res_x*j;
			r = rgb_array[ix * 3 + 0];
			g = rgb_array[ix * 3 + 1];
			b = rgb_array[ix * 3 + 2];

			in = ix % 8;
			er = ((r^128) >> (in)) | ((r^128) << (8 - (in)));
			eg = ((g^128) >> (in)) | ((g^128) << (8 - (in)));
			eb = ((b^128) >> (in)) | ((b^128) << (8 - (in)));

			rgb_array[ix * 3 + 0] = er;
			rgb_array[ix * 3 + 1] = eg;
			rgb_array[ix * 3 + 2] = eb;
		}
	}
			 break;
	}

	writeBMP24("gf.bmp", res_x, res_y, rgb_array);
	system("gf.bmp");
}