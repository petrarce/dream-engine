#include <string>
#include <vector>
#include <SDL.h>

using namespace std;

class gui_window{
public:
	typedef size_t guiTextureIndex;
	typedef struct{
		SDL_Texture* texture;
		SDL_Point textureSize;
	} guiTextureContainer;
private:
	size_t resolution_H;
	size_t resolution_W;
	string wind_name;
	bool is_initialised;

	SDL_Renderer* renderer;
	SDL_Window* window;
	vector<guiTextureContainer> texture_list;
public:
	static gui_window* get_instance();
	opcode init();
	opcode deinit();
	guiTextureIndex loadTexture( std::string path );
	opcode render_texture(guiTextureIndex, const SDL_Point&, double);
	opcode render_scene();
	opcode render_clear();
	usrInp get_usr_input();


private:
	gui_window();
	~gui_window();
	gui_window(gui_window&){};
	const gui_window& operator=(gui_window&){return *this;};
};

