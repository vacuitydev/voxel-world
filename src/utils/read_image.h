#include <stb/stb_image.cpp>
using namespace std;
struct ImageData{
    int width;
    int height;
    int nrChannels;
    unsigned char* data;
    ImageData(int w,int h, int n, unsigned char* d):width(w), height(h), nrChannels(n), data(d){

    }
    ~ImageData(){
        stbi_image_free(data);
    }
};
ImageData read_image_from_file(string_view path){
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("images/popcat.jpg", &width, &height, &nrChannels, 0);

    return ImageData(width, height, nrChannels, data);	
}