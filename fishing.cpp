#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string.h>
#include <thread>
#include "cstdlib"
#include "object.h"
#include "raylib.h"
#include "vector"

int main() {
    srand(time(nullptr));
    const int screenWidth = 1280;
    const int screenHeight = 960;
    int rbx = 0;
    int invs = 3;
    int udochka = 0;
    int pr1 = 0;
    int pr2 = 0;
    int pr3 = 0;
    int pr4 = 0;
    std::vector<std::string> id= {"../sprites/IMG_0050.PNG","../sprites/IMG_0051.PNG","../sprites/IMG_0052.PNG","../sprites/IMG_0053.PNG","../sprites/IMG_0054.PNG","../sprites/IMG_0059.PNG"};
    std::vector<int> item;
    std::vector<int> weight;
    std::vector<std::string> variants = {"salmon", "trout", "cod", "pike", "carp", "shark"};
    InitWindow(screenWidth, screenHeight, "Fishing");
    SetTargetFPS(60);
    SetExitKey(KEY_RIGHT_ALT);
    std::string scene = "menu";
    while (!WindowShouldClose()) {
        if (scene == "menu") {
            Figure2d play = Figure2d("rectangle", Vector2{540,300}, Vector2{200,75}, GREEN);
            Figure2d quit("rectangle", Vector2{540,400}, Vector2{200,75}, RED);
            while (scene=="menu"&&!WindowShouldClose()) {
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 tmp = GetMousePosition();
                    if (play.ispressed(tmp)) {
                        scene = "game";
                    }
                    else if (quit.ispressed(tmp)) {
                        scene = "quit";
                    }
                    else {
                        scene = "menu";
                    }
                }
                BeginDrawing();
                ClearBackground(BLUE);
                play.draw();
                quit.draw();
                DrawText("PLAY",545,300,75,BLACK);
                DrawText("QUIT",545,400,75,BLACK);
                DrawText("FISHING", 1280/2-50*4.5, 100,100, BLACK);
                EndDrawing();
            }
        }
        else if (scene == "game") {
            Image2d ud("../sprites/IMG_0056.PNG", Vector2{600,200});
            Image2d money("../sprites/money.png",Vector2{1200,10});
            Figure2d UI("rectangle", Vector2{400,700}, Vector2{500,75}, GRAY);
            Figure2d UI2("rectangle", Vector2{400,700}, Vector2{20,75}, RED);
            Figure2d UI3("rectangle", Vector2{400,700}, Vector2{100,75}, WHITE);
            int type;
            Image2d image[6] = {Image2d(id[0].c_str(),Vector2{400,200}), Image2d(id[1].c_str(),Vector2{400,200}), Image2d(id[2].c_str(),Vector2{400,200}), Image2d(id[3].c_str(),Vector2{400,200}),Image2d(id[4].c_str(),Vector2{400,200}),Image2d(id[5].c_str(),Vector2{400,200})};
            bool flag = false, flag_text = false;
            bool non = true;
            int f = 5, f2 = -1;
            char text[100] = "YOU HAVE: ";
            Image2d inventory = Image2d("../sprites/inventory.PNG",Vector2{10,300});
            Image2d shop = Image2d("../sprites/store.PNG",Vector2{10,435});
            int fps = 0;
            int l = 0;
            bool flag2 = 0;
            while (scene=="game"&&!WindowShouldClose()) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 tmp = GetMousePosition();
                    if (inventory.ispressed(tmp)) {
                        scene = "inventory";
                        non = false;
                    }
                    if (shop.ispressed(tmp)) {
                        scene = "shop";
                        non = false;
                    }
                }
                if(non&&(IsKeyPressed (KEY_SPACE)||IsMouseButtonPressed(MOUSE_LEFT_BUTTON))&&(item.size()<invs||flag_text)) {
                    non=true;
                    if (flag_text) {
                        strcpy(text, "YOU HAVE: ");
                        flag_text=false;
                        f2=-1;
                        flag = 0;
                    }
                    else {
                        if (f2==-1) {
                            l = (rand()%3+1)*60;
                            flag2 = 1;
                            f = 5;
                            UI2.position->x = 405;
                            UI3.position->x = rand()%(int)(UI.size->x-UI3.size->x)+UI.position->x;
                            f2=0;
                        }
                        else if (!flag2){
                            if (UI2.position->x>UI3.position->x&&UI2.position->x<UI3.position->x+UI3.size->x-UI2.size->x&&f2<2) {
                                UI3.position->x = rand()%400+400;
                                f2++;
                            }
                            else if(!(UI2.position->x>UI3.position->x&&UI2.position->x<UI3.position->x+UI3.size->x-UI2.size->x)){
                                f2=-1;
                                flag = 0;
                            }
                            else{
                                type = rand()%3+udochka;
                                int tmp2 = rand()%6+1;
                                if (pr4) {
                                    pr4--;
                                    tmp2+=20;
                                }
                                else if (pr3) {
                                    pr3--;
                                    tmp2+=15;
                                }
                                else if (pr2) {
                                    pr2--;
                                    tmp2+=10;
                                }
                                else if (pr1) {
                                    pr1--;
                                    tmp2+=5;
                                }
                                strcat(text, variants[type].c_str());
                                strcat(text, "\nWEIGHT: ");
                                strcat(text, std::to_string(tmp2).c_str());
                                flag_text = true;
                                item.push_back(type);
                                weight.push_back(tmp2);
                                f2=0;
                                flag = 0;
                            }
                        }
                    }
                }
                else if(IsKeyPressed(KEY_ESCAPE)) {
                    scene = "menu";
                }
                BeginDrawing();
                ClearBackground(BLUE);
                money.draw();
                DrawText(std::to_string(rbx).c_str(),1200 - strlen(std::to_string(rbx).c_str())*30-15, 14              , 60, BLACK);
                inventory.draw();
                shop.draw();
                if (flag2) {
                    ud.draw();
                    if (++fps==l) {
                        flag2 = false;
                        fps = 0;
                        flag = true;
                    }
                }
                if (flag) {
                    if (!(UI2.position->x > UI.position->x && UI2.position->x < UI.position->x + UI.size->x-UI2.size->x)) {
                        f*=-1;
                    }
                    UI2.position->x += f;
                    ud.draw();
                    UI.draw();
                    UI3.draw();
                    UI2.draw();
                }
                if (flag_text) {
                    image[type].draw();
                    DrawText(text,screenWidth/2-strlen(text)*30/2 + 7*30,550,30,BLACK);
                }
                EndDrawing();
            }
        }
        else if (scene == "quit") {
            break;
        }
        else if (scene == "shop") {
            std::vector<Image2d> bg;
            std::vector<Figure2d> buy;
            Image2d udka("../sprites/IMG_0055.PNG",Vector2{585,130});
            Image2d money("../sprites/money.png",Vector2{1200,10});
            Figure2d ui1("circle"  ,Vector2{1045,210}, Vector2{50,0}, BLUE);
            Figure2d ui2("circle"  ,Vector2{225,630}, Vector2{50,0}, YELLOW);
            Figure2d ui3("circle"  ,Vector2{635,630}, Vector2{50,0}, BROWN);
            Figure2d ui4("circle"  ,Vector2{1045,630}, Vector2{50,0}, BLACK);
            for (int i = 0; i<6; i++) {
                Image2d ru("../sprites/bg.png", Vector2{float(i%3*410+30), float(130+i/3*410)});
                Figure2d gr("rectangle", Vector2{float(i%3*410+175), float(i/3*400+450)}, Vector2{128,64}, GREEN);
                bg.push_back(ru);
                buy.push_back(gr);
            }
            Image2d inv("../sprites/inventory.PNG",Vector2{175 ,130});
            while (scene=="shop"&&!WindowShouldClose()) {
                if(IsKeyPressed(KEY_ESCAPE)) {
                    scene = "game";
                }
                BeginDrawing();
                ClearBackground(RED);
                money.draw();
                DrawText("THE SHOP", 1280/2-50*4.5, 16,100, BLACK);
                DrawText(std::to_string(rbx).c_str(),1200 - strlen(std::to_string(rbx).c_str())*30-15, 14, 60, BLACK);

                for (int i = 0; i<6; i++) {
                    bg[i].draw();
                    if (!(i==1 and udochka>3)) {
                        buy[i].draw();
                        DrawText("BUY",float(i%3*410+185), float(i/3*400+460),50,BLACK);
                    }
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)&&buy[i].ispressed(GetMousePosition())) {
                        if (i==0 and rbx >= 5000*(invs/3)) {
                            rbx-=5000*(invs/3);
                            invs+=3;
                        }
                        else if (i==1 and rbx >= 10000*(udochka+1)and udochka<=3) {
                            rbx-=10000*(udochka+1);
                            udochka++;
                        }
                        else if (i==2 and rbx >= 200) {
                            rbx-=200;
                            pr1++;
                        }
                        else if (i==3 and rbx >= 450) {
                            rbx-=450;
                            pr2++;
                        }
                        else if (i==4 and rbx >= 700) {
                            rbx-=700;
                            pr3++;
                        }
                        else if (i==5 and rbx >= 950) {
                            rbx-=950;
                            pr4++;
                        }
                    }
                }
                DrawText("  +3 size\ninventory", 120, 280,50, BLACK);
                DrawText("+5kg", 995, 280,50, BLACK);
                DrawText("+10kg", 175, 700,50, BLACK);
                DrawText("+15kg", 585, 700,50, BLACK);
                DrawText("+20kg", 995, 700,50, BLACK);
                DrawText(std::to_string(5000*(invs/3)).c_str(), 175, 380,50, BLACK);
                if (udochka<=3) {
                    DrawText("more chance\nof better fish", 480, 280,50, BLACK);
                    DrawText(std::to_string(10000*(udochka+1)).c_str(), 585, 380,50, BLACK);
                }
                else {
                    DrawText("SOLD\n OUT", 500, 260,100, BLACK);
                }
                DrawText("200", 995, 380,50, BLACK);
                DrawText("450", 175, 800,50, BLACK);
                DrawText("700", 585, 800,50, BLACK);
                DrawText("950", 995, 800,50, BLACK);
                inv.draw();
                udka.draw();
                ui1.draw();
                ui2.draw();
                ui3.draw();
                ui4.draw();
                EndDrawing();
            }
        }
        else if (scene == "inventory") {
            std::vector<Figure2d> sell;
            Image2d left("../sprites/left.png", Vector2{50, 450});
            Image2d right("../sprites/right.png", Vector2{1102, 450});
            std::vector<Image2d> image;
            std::vector<Image2d> bg;
            Image2d money("../sprites/money.png",Vector2{1200,10});
            for (int i=0; i<item.size(); i++) {
                float t1 = 30+i%3*410, t2 = 500;
                Image2d tr(id[item[i]].c_str(), Vector2{t1, t2-50});
                Image2d ru("../sprites/bg.png", Vector2{t1-10, t2+30});
                Figure2d gr("rectangle", Vector2{t1+125, 850}, Vector2{128,64}, GREEN);
                image.push_back(tr);
                bg.push_back(ru);
                sell.push_back(gr);
            }
            int page = 0;
            while (scene=="inventory"&&!WindowShouldClose()) {
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 tmp = GetMousePosition();
                    if (right.ispressed(tmp)&&item.size()/(((float)page+1)*3)>1) {
                        page++;
                    }
                    if (left.ispressed(tmp)&&page>0) {
                        page--;
                    }
                }
                if(IsKeyPressed(KEY_ESCAPE)) {
                    scene = "game";
                }
                BeginDrawing();
                ClearBackground(BROWN);
                money.draw();
                DrawText("THE INVENTORY", 100, 16,100, BLACK);
                DrawText(std::to_string(rbx).c_str(),1200 - strlen(std::to_string(rbx).c_str())*30-15, 14, 60, BLACK);
                DrawText(("+5kg: "+std::to_string(pr1)).c_str(), 150, 280,50, BLACK);
                DrawText(("+10kg: "+std::to_string(pr2)).c_str(), 150, 400,50, BLACK);
                DrawText(("+15kg: "+std::to_string(pr3)).c_str(), 400, 280,50, BLACK);
                DrawText(("+20kg: "+std::to_string(pr4)).c_str(), 400, 400,50, BLACK);
                DrawText(("inventory size: "+std::to_string(invs)).c_str(), 700, 280,50, BLACK);
                DrawText(("fishing rod: "+std::to_string(udochka)).c_str(), 700, 400,50, BLACK);
                if (item.size()>0) {
                    int startIndex = page * 3;
                    int endIndex = std::min(startIndex + 3, (int)item.size());
                    for (int i = startIndex; i < endIndex; i++) {
                        bg[i].draw();
                        float t1 = 150+i%3*410, t2 = 750;
                        DrawText(variants[item[i]].c_str(),t1, t2, 50, BLACK);
                        char tem[10];
                        strcpy(tem,std::to_string(weight[i]).c_str());
                        sell[i].draw();
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)&&sell[i].ispressed(GetMousePosition())) {
                            rbx+=item[i]*100+weight[i]*50+rand()%50;
                            item.erase(item.begin()+i);
                            weight.erase(weight.begin()+i);
                            bg.erase(bg.end());
                            image.erase(image.end());
                        }
                        strcat(tem, " kg");
                        DrawText(tem,t1, t2+50, 50, BLACK);
                        DrawText("SELL",t1+10, 860, 50, BLACK);
                        image[i].draw();
                    }
                }
                if (item.size()/(((float)page+1)*3)>1) {
                    right.draw();
                }
                if (page>0) {
                    left.draw();
                }
                EndDrawing();
            }
        }
    }
    CloseWindow();
    return 0;
}