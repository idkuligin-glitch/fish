#include "object.h"
#include <raylib.h>
Image2d::Image2d(const char *id, Vector2 position) {
    texture = LoadTexture(id);
    this->position = position;
}
void Image2d::draw() {
    DrawTextureV(texture, position, WHITE);
}
bool Image2d::ispressed(Vector2 mousePosition) {
    if (mousePosition.x >= position.x && mousePosition.x <= position.x + texture.width && mousePosition.y >= position.y && mousePosition.y <= position.y + texture.height) {
        return true;
    }
    else {
        return false;
    }
}
Image2d::~Image2d() = default;





Figure2d::Figure2d(const std::string type, Vector2 position, Vector2 size, Color color) {
    this->position = new Vector2{position.x,position.y};
    this->size = new Vector2{size.x,size.y};
    this->type = new std::string(type);
    this->color = new Color(color);
}
void Figure2d::draw() {
    if (*type == "rectangle") {
        DrawRectangle(position->x, position->y, size->x,size->y,*color);
    }
    else if (*type == "circle") {
        DrawCircle(position->x,position->y, size->x, *color);
    }
}
bool Figure2d::ispressed(Vector2 mousePosition) {
    if (mousePosition.x >= position->x && mousePosition.x <= position->x + size->x && mousePosition.y >= position->y && mousePosition.y <= position->y + size->y) {
        return true;
    }
    else {
        return false;
    }
}
Figure2d::~Figure2d() = default;





