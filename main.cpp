

#include <SDL.h>


#include <iostream>
#include <cfloat>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;






/*
 * Log an SDL error with some error message to the output stream of our choice
 * @param os The output stream to write the message too
 * @param msg The error message to write, format will be msg error: SDL_GetError()
 */
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

/*
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}








int main(int argc, char** argv) {
  int num_cols = 480;
  int num_rows = 270;

  Uint32 rmask, gmask, bmask, amask;
  int shift = 8;
  rmask = 0xff000000 >> shift;
  gmask = 0x00ff0000 >> shift;
  bmask = 0x0000ff00 >> shift;
  amask = 0x000000ff >> shift;

//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	//Setup our window and renderer
	SDL_Window *window = SDL_CreateWindow("Basic SDL Test", 100, 100, num_cols, num_rows, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
    SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//The textures we'll be using
	SDL_Texture *background;

  unsigned char* data = new unsigned char[num_cols*num_rows*3];
  
  for (int r=0; r<num_rows; r++) {
    for (int c=0; c<num_cols; c++) {
      for (int ch=0; ch<3; ch++) {
        data[3*(r*num_cols + c) + ch] = 255*float(c)/num_cols;
      }
    }
  }

  background = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB24,SDL_TEXTUREACCESS_STATIC,num_cols,num_rows);
  SDL_UpdateTexture(background, NULL, data, 3*num_cols);
  //SDL_FreeSurface(loadedImage);
  //Make sure converting went ok too
  if (background == nullptr){
    logSDLError(std::cout, "CreateTextureFromSurface");
  }


  //Make sure they both loaded ok
	if (background == nullptr){
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}




  SDL_Event event;
	bool quit = false;
  bool leftMouseButtonDown = false;
  int start_mouseX;
  int start_mouseY;
  float orig_x_angle;
  float orig_y_angle;

	while (!quit){
		//Event Polling
    const Uint64 start = SDL_GetPerformanceCounter();
    SDL_RenderClear(renderer);
		
    
    while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				quit = true;
			}
      //Use number input to select which clip should be drawn
      if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
          case SDLK_ESCAPE:
            quit = true;
            break;
          default:
            break;
        }
      } else if (event.type == SDL_MOUSEBUTTONUP ) {
        if (event.button.button == SDL_BUTTON_LEFT)
          leftMouseButtonDown = false;

      } else if (event.type == SDL_MOUSEBUTTONDOWN ) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          leftMouseButtonDown = true;
        }
      } else if (event.type == SDL_MOUSEMOTION ) {
        if (leftMouseButtonDown)
        {
          int mouseX = event.motion.x;
          int mouseY = event.motion.y;

          data[3*(mouseY*num_cols + mouseX) + 0] = 255;
          data[3*(mouseY*num_cols + mouseX) + 1] = 0;
          data[3*(mouseY*num_cols + mouseX) + 2] = 0;
        }
      }
    }

    SDL_UpdateTexture(background, NULL, data, 3*num_cols);


    //We want to tile our background so draw it 4 times
    renderTexture(background, renderer, 0, 0);
    //Update the screen
    SDL_RenderPresent(renderer);

    const Uint64 end = SDL_GetPerformanceCounter();
    const static Uint64 freq = SDL_GetPerformanceFrequency();
    const double seconds = ( end - start ) / static_cast< double >( freq );
    cout << "Frame time: " << seconds * 1000.0 << "ms" << endl;
  }

  delete[] data;
  SDL_DestroyTexture(background);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
	SDL_Quit();



  return 0;
}
