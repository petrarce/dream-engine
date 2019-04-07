#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>

using namespace std;

class gui_window{
public:
	typedef size_t guiTextureIndex;
	typedef struct{
		SDL_Texture* texture;
		SDL_Point textureSize;
	} guiTextureContainer;
	typedef pair<const string,guiTextureContainer> guiTextureHashPair;
private:
	size_t resolution_H;
	size_t resolution_W;
	string wind_name;
	bool is_initialised;

	SDL_Renderer* renderer;
	SDL_Window* window;
	unordered_map<string, guiTextureContainer> texture_hash_map;
public:
	static gui_window* get_instance();
	opcode init();
	opcode deinit();
	opcode loadTexture( std::string path );
	opcode render_texture(string, const SDL_Point&, double);
	opcode render_scene();
	opcode render_clear();
	usrInp get_usr_input();


private:
	gui_window();
	~gui_window();
	gui_window(gui_window&){};
	const gui_window& operator=(gui_window&){return *this;};
};

