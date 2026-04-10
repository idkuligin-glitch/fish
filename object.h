#include <raylib.h>
#include <string>

struct Image2d{
    Texture2D texture;
    Vector2 position;
    Image2d(const char *id, Vector2 position);
    void draw();
    bool ispressed(Vector2 mousePosition);
    ~Image2d();
};

struct Figure2d {
    Vector2 *position;
    Vector2 *size;
    Color *color;
    std::string *type;
    Figure2d(const std::string type, Vector2 position, Vector2 size, Color color);
    void draw();
    bool ispressed(Vector2 mousePosition);
};
