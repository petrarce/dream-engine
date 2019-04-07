#include <types.hpp>
#include <gui_window.hpp>
#include <SDL_image.h>

using namespace std;

const int defaultResulutionW = 1080;
const int defaultResulutionH = 1920;


gui_window* gui_window::get_instance()
{
	static gui_window instance;
	return &instance;
}

opcode gui_window::init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		pr_err("failed to init sdl video subsystem: %s", SDL_GetError());
		deinit();
		return STATUS_NOK;
	}

	if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") < 0){
		pr_err("failed to init sdl: %s", SDL_GetError());
		deinit();
		return STATUS_NOK;
	}
	if(SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1") < 0){
		pr_warn("cannot set VSync: %s\nConsider controll framerate manually", SDL_GetError());
	}

	this->window = SDL_CreateWindow(this->wind_name.c_str(), 
										SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
										this->resolution_H, this->resolution_W,
										SDL_WINDOW_SHOWN);
	if(this->window == NULL){
		pr_err("failed to init sdl: %s", SDL_GetError());
		deinit();
		return STATUS_NOK;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if(this->renderer == NULL){
		pr_err("failed to init sdl: %s", SDL_GetError());
		deinit();
		return STATUS_NOK;
	}
	SDL_SetRenderDrawColor( this->renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		pr_err("failed to init sdl: %s", SDL_GetError());
		deinit();
		return STATUS_NOK;
	}
	this->is_initialised = true;
	return STATUS_OK;
}

opcode gui_window::deinit()
{
	for(guiTextureHashPair& textrContainer : this->texture_hash_map){
		SDL_DestroyTexture(textrContainer.second.texture);
		textrContainer.second.texture = NULL;
	}
	this->texture_hash_map.clear();

	//Destroy window	
	SDL_DestroyRenderer( this->renderer );
	this->renderer = NULL;
	
	SDL_DestroyWindow( this->window );
	this->window = NULL;
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	
	this->is_initialised = false;
	return STATUS_OK;
}

opcode gui_window::loadTexture( std::string path )
{
	if(this->is_initialised == false){
		pr_err("cannot load texture before initialisation of SDL subsystems");
		return STATUS_NOK;
	}
	//texture is already present in hashmap (was loaded previously) 
	if(this->texture_hash_map.find(path) != this->texture_hash_map.end()){
		return STATUS_OK;
	}
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		pr_err( "Unable to load image %s: %s\n", path.c_str(), IMG_GetError() );
		return STATUS_NOK;
	}

	//Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface( this->renderer, loadedSurface );
	if( newTexture == NULL )
	{
		pr_err( "Unable to create texture from %s: %s\n", path.c_str(), SDL_GetError() );
		return STATUS_NOK;
	}

	guiTextureContainer newGuiTexture = {newTexture, {loadedSurface->w, loadedSurface->h}};

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );

	this->texture_hash_map.emplace(path, newGuiTexture);
	return STATUS_OK;
}

opcode gui_window::render_texture(string path, 
									const SDL_Point& position, 
									double rotation_angle)
{
	auto texture_iterator = this->texture_hash_map.find(path);
	if(texture_iterator == this->texture_hash_map.end()){
		pr_err("Texture %s was not loaded previously...", path.c_str());
		return STATUS_NOK;
	}
	guiTextureContainer& txtrCont = texture_iterator->second;
	SDL_Rect txtrDstRect = {	position.x - txtrCont.textureSize.x/2, 
								position.y - txtrCont.textureSize.y/2,
								txtrCont.textureSize.x,
								txtrCont.textureSize.y
	};
	SDL_Point rotation_point = {txtrCont.textureSize.x/2,txtrCont.textureSize.y/2};
	SDL_RenderCopyEx( this->renderer, 
						txtrCont.texture, 
						NULL, 
						&txtrDstRect, 
						rotation_angle, 
						&rotation_point, 
						SDL_FLIP_NONE);
	return STATUS_OK;

}

opcode gui_window::render_scene()
{
	SDL_RenderPresent(this->renderer);
	return STATUS_OK;
}

opcode gui_window::render_clear()
{
	SDL_RenderClear(this->renderer);
	return STATUS_OK;
}

usrInp gui_window::get_usr_input()
{
	SDL_Event* event;
	usrInp inp = NO_INP;
	if(SDL_PollEvent(event) == 0){
		return inp;
	}

	switch(event->type){
		case SDL_QUIT:
		inp = EXIT;
		break;

		case SDL_KEYDOWN:
		if(event->key.repeat){
			return NO_INP;
		}
		switch(event->key.keysym.sym){
			case 'w':
			inp = MOVE_UP;
			break;

			case 's':
			inp = MOVE_DOWN;
			break;

			case 'a':
			inp = MOVE_LEFT;
			break;

			case 'd':
			inp = MOVE_RIGHT;
			break;

			case 'q':
			inp = ROTATE_LEFT;
			break;

			case 'e':
			inp = ROTATE_RIGHT;
			break;

			case 'r':
			inp = SWIRCH_ROOF;
			break;

			case 't':
			inp = SWITCH_DOOR;
			break;

			case 'y':
			inp = SWITCH_WALL;
			break;

			default:
			pr_warn("%c key press is not supported", event->key.keysym.sym);
			break;

		}
		break;

		case SDL_KEYUP:
		if(event->key.repeat){
			return NO_INP;
		}
		switch(event->key.keysym.sym){

			case 'w':
			inp = STOP_MOVE_UP;
			break;

			case 's':
			inp = STOP_MOVE_DOWN;
			break;

			case 'a':
			inp = STOP_MOVE_LEFT;
			break;

			case 'd':
			inp = STOP_MOVE_RIGHT;
			break;

			case 'q':
			inp = STOP_ROTATE_LEFT;
			break;

			case 'e':
			inp = STOP_ROTATE_RIGHT;
			break;

			default:
			pr_warn("%c key up is not supported", event->key.keysym.sym);
			break;
		}
		break;
	}

	return inp;

}


gui_window::gui_window():
	wind_name("Dream Engine"),
	resolution_W(defaultResulutionW),
	resolution_H(defaultResulutionH),
	is_initialised(false),
	renderer(NULL),
	window(NULL)
{

}

gui_window::~gui_window()
{
	deinit();
}