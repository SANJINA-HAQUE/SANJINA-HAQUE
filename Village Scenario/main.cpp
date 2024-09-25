#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include<math.h>

bool DayNight = 0;  // 0 = day, 1 = night
float TrainPosition = 0.0f;
float TrainSpeed = 0.0f;
bool TrainMoving = true; // controls train movement
bool TrainMovingLeft = true;
bool TrainMovingRight = true;
float cloudPosition = 0.0f;
float boat1PositionX = 0.0f;
float boat2PositionX = 0.0f;
float boat1PositionY = 0.0f;
float boat2PositionY = 0.0f;
bool boat1Moving = true; // Controls boat 1 movement
bool boat2Moving = true; // Controls boat 2 movement
float bladeRotationAngle = 0.0f;  // Rotation angle for windmill blades
bool windmillRotating = true; //handle windmill blades rotation

void drawScene(float x, float y, float R) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float pi=3.1416;
        float A = 2 * pi * i / 180;
        float dx = R * cos(A);
        float dy = R * sin(A);
        glVertex2f(x+dx, y+dy);
    }
    glEnd();
}

// Function to draw the body of the Dhaner Gola
void drawDhanerGola(float centerX, float centerY) {
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 180; ++i) {
        float r = 100.0f;
        float pi=3.1416;
        float a =  3.1416 * i / 180;  // Calculate the angle
        float x = r * cosf(a);  // x coordinate relative to the center
        float y = r * sinf(a);  // y coordinate relative to the center
        glVertex2f(centerX + x, centerY + y);  // Translate circle to (centerX, centerY)
    }
    glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

//---------------------Sky---------------------------
    if(DayNight == 0) {
        glColor3f(0.396f, 0.78f, 1.0f); //  for day
    }else{
        glColor3f(0.0f, 0.0f, 0.2f); // Dark blue for night sky
    }
	glBegin(GL_QUADS);
    glVertex2i(0, 720);
	glVertex2i(0, 1100);
    glVertex2i(3300, 1100);
	glVertex2i(3300, 720);
	glEnd();

// ------------------------------Draw Sun & Moon-------------------------------------------
    if (DayNight == 0) {
        glColor3f(0.953f, 0.89f, 0.0f);  // Sun color (yellow)
    } else {
        glColor3f(0.9f, 0.9f, 1.0f);  // Moon color (soft white)
    }
    drawScene(1200.0f, 1000.0f, 50.0f);

//----------------------Grass-----------------------------
	if(DayNight == 0) {
        glColor3f(0.498f, 0.796f, 0.239f);  //  for day
    } else {
        glColor3f(0.031f, 0.122f, 0.059f); //  for night
    }
    glBegin(GL_QUADS);
    glVertex2i(0, 720);
	glVertex2i(3300, 720);
    glVertex2i(3300, 540);
	glVertex2i(0, 320);
	glEnd();

//------------------------River-----------------------------
	if(DayNight == 0) {
        glColor3f(0.0f, 0.0f, 1.0f);    //  for day
    } else {
        glColor3f(0.004f, 0.019f, 0.118f); //  for night
    }
	glBegin(GL_QUADS);
    glVertex2i(0, 320);
	glVertex2i(3300, 540);
    glVertex2i(3300, 0);
	glVertex2i(0, 0);
	glEnd();

    if(DayNight == 0) {
//-----------------Green Hills----------------------
	glColor3f(0.078f, 0.33f, 0.039f);
	}else{
//-----------------Green Hills (Dark Green)----------------------
	glColor3f(0.0f, 0.039f, 0.012f); // Dark green for hills
	}
	glBegin(GL_POLYGON);
    glVertex2i(0, 720);
	glVertex2i(0, 780);
    glVertex2i(400, 820);
	glVertex2i(500, 725);
	glVertex2i(850, 820);
	glVertex2i(1000, 725);
    glVertex2i(1250, 820);
	glVertex2i(1400, 725);
	glVertex2i(1750, 840);
	glVertex2i(2000, 725);
    glVertex2i(2300, 820);
	glVertex2i(2500, 725);
	glVertex2i(2750, 800);
	glVertex2i(3000, 725);
    glVertex2i(3100, 800);
	glVertex2i(3300, 780);
	glVertex2i(3300, 720);
	glEnd();

//------------------------Draw Rail Line-----------------------------
	if(DayNight == 0) {
        glColor3f(0.0f, 0.0f, 0.0f);    //  for day
    } else {
        glColor3f(0.0f, 0.0f, 0.0f); //  for night
    }
    glBegin(GL_QUADS);
    glVertex2i(0, 720);
	glVertex2i(0, 715);
    glVertex2i(3300, 715);
	glVertex2i(3300, 720);
	glEnd();

    glPushMatrix();
    glTranslatef(TrainPosition, 0.0f, 0.0f); //moving along x-axis
//------------------------Draw Train-----------------------------
	if(DayNight == 0) {
        glColor3f(1.0f, 0.0f, 0.0f);    //  for day
    } else {
        glColor3f(0.004f, 0.0f, 0.0f); //  for night
    }
    glBegin(GL_QUADS); // Main body
    glVertex2i(-700, 720);
    glVertex2i(0, 720);
    glVertex2i(-50, 760);
    glVertex2i(-700, 760);
    glEnd();

	if(DayNight == 0) {
        glColor3f(1.0f, 1.0f, 1.0f);    //  for day
    } else {
        glColor3f(0.078f, 0.031f, 0.031f); //  for night
    }
    glBegin(GL_QUADS); // white part
    glVertex2i(-700, 735);
    glVertex2i(-20, 735);
    glVertex2i(-35, 745);
    glVertex2i(-700, 745);
    glEnd();

//------------------------Draw Train Window-----------------------------
    if(DayNight == 0) {
        glColor3f(0.0f, 0.0f, 0.33f);    //  Train window for day
    } else {
        glColor3f(1.0f, 1.0f, 0.0f);  //  for night
    }
    glBegin(GL_QUADS); // First window
    glVertex2i(-670, 730);
    glVertex2i(-670, 750);
    glVertex2i(-620, 750);
    glVertex2i(-620, 730);
    glEnd();

    glBegin(GL_QUADS); // Second window
    glVertex2i(-540, 730);
    glVertex2i(-540, 750);
    glVertex2i(-490, 750);
    glVertex2i(-490, 730);
    glEnd();

    glBegin(GL_QUADS); // Third window
    glVertex2i(-410, 730);
    glVertex2i(-410, 750);
    glVertex2i(-360, 750);
    glVertex2i(-360, 730);
    glEnd();

    glBegin(GL_QUADS); // Fourth window
    glVertex2i(-280, 730);
    glVertex2i(-280, 750);
    glVertex2i(-230, 750);
    glVertex2i(-230, 730);
    glEnd();

    glBegin(GL_QUADS); // Fifth window
    glVertex2i(-150, 730);
    glVertex2i(-150, 750);
    glVertex2i(-100, 750);
    glVertex2i(-100, 730);
    glEnd();

//------------------------Draw Train Light-----------------------------
    if(DayNight == 0) {
        glColor3f(0.0f, 0.0f, 0.0f);    //  Train window for day
    } else {
        glColor3f(1.0f, 1.0f, 0.0f);  //  for night
    }
    drawScene(-52.0f, 758.0f, 3.0f);
    glPopMatrix();

//----------------------------Draw Dhaner Gola------------------------
    if(DayNight == 0) {
        glColor3f(0.651f, 0.588f, 0.008f);  //  for day
    } else {
        glColor3f(0.055f, 0.055f, 0.0f);  // for night
    }
    drawDhanerGola(2080.0f, 600.0f);
    drawDhanerGola(210.0f, 560.0f);

//----------------------------Draw House------------------------------
    if(DayNight == 0) {
        glColor3f(0.4f, 0.2f, 0.0f);    // for day
    } else {
        glColor3f(0.051f, 0.027f, 0.0f); // for night
    }
	glBegin(GL_QUADS);                   //2-roof
    glVertex2i(1250, 680);
	glVertex2i(1310, 620);
    glVertex2i(850, 620);
	glVertex2i(910, 680);
	glEnd();

	if(DayNight == 0) {
        glColor3f(0.6f, 0.0f, 0.298f);    // for day
    } else {
        glColor3f(0.027f, 0.0f, 0.012f);   // for night
    }
	glBegin(GL_QUADS);                  //2-body
    glVertex2i(1280, 620);
	glVertex2i(1280, 500);
    glVertex2i(880, 500);
	glVertex2i(880, 620);
	glEnd();

	if(DayNight == 0) {
        glColor3f(0.4f, 0.2f, 0.0f);   // for day
    } else {
        glColor3f(0.051f, 0.027f, 0.0f); // for night
    }
	glBegin(GL_QUADS);                    //3-roof
    glVertex2i(2500, 680);
	glVertex2i(2460, 725);
    glVertex2i(2240, 725);
	glVertex2i(2200, 680);
	glEnd();

	if(DayNight == 0) {
        glColor3f(0.0f, 0.6f, 0.6f);    // for day
    } else {
        glColor3f(0.0f, 0.019f, 0.027f);   // for night
    }
	glBegin(GL_QUADS);                     //3-body
    glVertex2i(2480, 680);
	glVertex2i(2480, 590);
    glVertex2i(2220, 590);
	glVertex2i(2220, 680);
	glEnd();

    if(DayNight == 0) {
        glColor3f(0.4f, 0.2f, 0.0f);    // for day
    } else {
        glColor3f(0.051f, 0.027f, 0.0f);   // for night
    }
	glBegin(GL_QUADS);                  //1-roof
	glVertex2i(920, 620);
    glVertex2i(960, 560);
	glVertex2i(490, 560);
	glVertex2i(550, 620);
	glEnd();

    if(DayNight == 0) {
        glColor3f(1.0f, 0.698f, 0.4f);   // for day
    } else {
        glColor3f(0.055f, 0.043f, 0.035f);  // for night
    }
	glBegin(GL_QUADS);                  //1-body
	glVertex2i(925, 560);
    glVertex2i(925, 440);
	glVertex2i(520, 440);
	glVertex2i(520, 560);
	glEnd();

//----------------------Door---------------------------
    if(DayNight == 0) {
        glColor3f(0.0f, 0.2f, 0.4f);   // for day
    } else {
        glColor3f(0.008f, 0.004f, 0.039f);  // for night
    }
	glBegin(GL_QUADS);                  //House 1
    glVertex2i(650, 550);
	glVertex2i(650, 440);
    glVertex2i(790, 440);
	glVertex2i(790, 550);
	glEnd();

	glBegin(GL_QUADS);                  //House 2
    glVertex2i(1035, 610);
	glVertex2i(1035, 500);
    glVertex2i(1125, 500);
	glVertex2i(1125, 610);
	glEnd();

	glBegin(GL_QUADS);                  //House 3
    glVertex2i(2320, 670);
	glVertex2i(2320, 590);
    glVertex2i(2380, 590);
	glVertex2i(2380, 670);
	glEnd();

//--------------------------------Draw Dhan Kheter math------------------------
	if(DayNight == 0) {
        glColor3f(0.675f, 0.686f, 0.329f);   // for day
    } else {
        glColor3f(0.024f, 0.024f, 0.004f);  // for night
    }
    glBegin(GL_QUADS);
    glVertex2i(0, 320);
	glVertex2i(300, 340);
    glVertex2i(280, 460);
	glVertex2i(0, 560);
	glEnd();

//--------------------------------Draw Dhan khet------------------------
	if(DayNight == 0) {
        glColor3f(0.792f, 0.886f, 0.161f);   // for day
    } else {
        glColor3f(0.043f, 0.051f, 0.004f);  // for night
    }
    glBegin(GL_QUADS);
    glVertex2i(0, 325);
	glVertex2i(0, 345);
    glVertex2i(295, 365);
	glVertex2i(298, 345);
	glEnd();

    glBegin(GL_QUADS);
    glVertex2i(0, 355);
	glVertex2i(0, 375);
    glVertex2i(293, 395);
	glVertex2i(296, 375);
	glEnd();

    glBegin(GL_QUADS);
    glVertex2i(0, 385);
	glVertex2i(0, 405);
    glVertex2i(285, 425);
	glVertex2i(290, 405);
	glEnd();

    glBegin(GL_QUADS);
    glVertex2i(0, 415);
	glVertex2i(0, 435);
    glVertex2i(280, 455);
	glVertex2i(285, 435);
	glEnd();

    glBegin(GL_QUADS);
    glVertex2i(0, 445);
	glVertex2i(0, 465);
    glVertex2i(210, 485);
	glVertex2i(265, 465);
	glEnd();

    glBegin(GL_QUADS);
    glVertex2i(0, 475);
	glVertex2i(0, 495);
    glVertex2i(130, 515);
	glVertex2i(185, 495);
	glEnd();

    glBegin(GL_QUADS);
    glVertex2i(0, 505);
	glVertex2i(0, 530);
    glVertex2i(45, 545);
	glVertex2i(85, 530);
	glEnd();

//--------------------------Draw Boats-----------------------------
    if(DayNight == 0) {
    glPushMatrix();
    glTranslatef(boat1PositionX, boat1PositionY, 0.0f); //moving along x-axis & y-axis
    glBegin(GL_QUADS);                  //Boat 1
	glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(-1400, 240);
	glVertex2i(-1330, 190);
    glVertex2i(-970, 190);
	glVertex2i(-900, 240);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.0f, 0.4f);
    glVertex2i(-1300, 240);
	glVertex2i(-1000, 240);
	glVertex2i(-1000, 290);
    glVertex2i(-1300, 290);
	glEnd();

    glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.6f, 0.6f);
    glVertex2i(-1300, 290);
	glVertex2i(-1150, 320);
    glVertex2i(-1000, 290);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(boat2PositionX, boat2PositionY, 0.0f); //moving along x-axis & y-axis
    glBegin(GL_QUADS);                  //Boat 2
	glColor3f(0.2f, 0.0f, 0.0f);
    glVertex2i(-510, 270);
	glVertex2i(-430, 220);
    glVertex2i(-100, 220);
	glVertex2i(0, 270);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.0f, 0.4f);
    glVertex2i(-400, 270);
	glVertex2i(-120, 270);
	glVertex2i(-120, 320);
    glVertex2i(-400, 320);
	glEnd();

    glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.0f, 0.4f);
    glVertex2i(-400, 320);
	glVertex2i(-260, 350);
    glVertex2i(-120, 320);
    glEnd();
    glPopMatrix();

    }else{

//-------------------------Draw Stars------------------------------
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 0.0); // yellow stars
    glVertex2f(200.0, 800.0);
    glVertex2f(600.0, 950.0);
    glVertex2f(1300.0, 900.0);
    glVertex2f(1600.0, 850.0);
    glVertex2f(1800.0, 1000.0);
    glVertex2f(2500.0, 920.0);
    glVertex2f(2700.0, 860.0);
    glVertex2f(3000.0, 900.0);
    glEnd();

//--------------------------Draw Boats-----------------------------
    glPushMatrix();
    glTranslatef(boat1PositionX, boat1PositionY, 0.0f); //moving along x-axis & y-axis
    glBegin(GL_QUADS);                  //Boat 1
	glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(-1400, 240);
	glVertex2i(-1330, 190);
    glVertex2i(-970, 190);
	glVertex2i(-900, 240);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.063f, 0.004f, 0.071f);
    glVertex2i(-1300, 240);
	glVertex2i(-1000, 240);
	glVertex2i(-1000, 290);
    glVertex2i(-1300, 290);
	glEnd();

    glBegin(GL_TRIANGLES);
	glColor3f(0.004f, 0.067f, 0.071f);
    glVertex2i(-1300, 290);
	glVertex2i(-1150, 320);
    glVertex2i(-1000, 290);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(boat2PositionX, boat2PositionY, 0.0f); //moving along x-axis & y-axis
    glBegin(GL_QUADS);                  //Boat 2
	glColor3f(0.039f, 0.019f, 0.0f);
    glVertex2i(-510, 270);
	glVertex2i(-430, 220);
    glVertex2i(-100, 220);
	glVertex2i(0, 270);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.078f, 0.004f, 0.075f);
    glVertex2i(-400, 270);
	glVertex2i(-120, 270);
	glVertex2i(-120, 320);
    glVertex2i(-400, 320);
	glEnd();

    glBegin(GL_TRIANGLES);
	glColor3f(0.129f, 0.004f, 0.071f);
    glVertex2i(-400, 320);
	glVertex2i(-260, 350);
    glVertex2i(-120, 320);
    glEnd();
    glPopMatrix();
    }

//-------------------------Draw Clouds----------------------------
    if(DayNight == 0) {
    glColor3f(0.961f, 0.961f, 0.961f);//white Color for day clouds
    }else{
//-------------------------Draw Night Clouds----------------------------
    glColor3f(0.5f, 0.5f, 0.5f); // Darker gray for night clouds
    }
    glPushMatrix();
    glTranslatef(cloudPosition, 0.0f, 0.0f); //moving along x-axis
    drawScene(-960.0f, 1000.0f, 50.0f);
    drawScene(-1020.0f, 1010.0f, 55.0f);
    drawScene(-1080.0f, 1000.0f, 50.0f);

    drawScene(-560.0f, 1000.0f, 50.0f);
    drawScene(-620.0f, 1010.0f, 55.0f);
    drawScene(-680.0f, 1000.0f, 50.0f);

    drawScene(-160.0f, 1000.0f, 50.0f);
    drawScene(-220.0f, 1010.0f, 55.0f);
    drawScene(-280.0f, 1000.0f, 50.0f);

    drawScene(-1060.0f, 1000.0f, 50.0f);
    drawScene(-1120.0f, 1010.0f, 55.0f);
    drawScene(-1180.0f, 1000.0f, 50.0f);

    drawScene(-2000.0f, 1000.0f, 50.0f);
    drawScene(-2080.0f, 1010.0f, 55.0f);
    drawScene(-2160.0f, 1000.0f, 50.0f);

    drawScene(-2220.0f, 980.0f, 50.0f);
    drawScene(-2280.0f, 990.0f, 55.0f);
    drawScene(-2340.0f, 980.0f, 50.0f);

    drawScene(1280.0f, 1000.0f, 50.0f);
    drawScene(1340.0f, 1010.0f, 55.0f);
    drawScene(1400.0f, 1000.0f, 50.0f);

    drawScene(560.0f, 1000.0f, 50.0f);
    drawScene(620.0f, 1010.0f, 55.0f);
    drawScene(680.0f, 1000.0f, 50.0f);

    drawScene(960.0f, 1000.0f, 50.0f);
    drawScene(1020.0f, 1010.0f, 55.0f);
    drawScene(1080.0f, 1000.0f, 50.0f);

    drawScene(2000.0f, 1000.0f, 50.0f);
    drawScene(2080.0f, 1010.0f, 55.0f);
    drawScene(2160.0f, 1000.0f, 50.0f);

    drawScene(2220.0f, 980.0f, 50.0f);
    drawScene(2280.0f, 990.0f, 55.0f);
    drawScene(2340.0f, 980.0f, 50.0f);
    glPopMatrix();

//------------------------Draw Trees--------------------------
	if(DayNight == 0) {
        glColor3f(0.18f, 0.569f, 0.06f); //green leaves
	}else{
        glColor3f(0.0f, 0.035f, 0.004f); // Dark green leaves
	}
	glBegin(GL_POLYGON); //leaves 1
    glVertex2i(390, 640);
	glVertex2i(290, 580);
    glVertex2i(330, 560);
	glVertex2i(290, 540);
	glVertex2i(330, 520);
	glVertex2i(290, 500);
    glVertex2i(490, 500);
	glVertex2i(450, 520);
	glVertex2i(490, 540);
	glVertex2i(450, 560);
    glVertex2i(490, 580);
    glEnd();

    glBegin(GL_POLYGON); //leaves 2
    glVertex2i(790, 780);
	glVertex2i(910, 680);
    glVertex2i(850, 620);
	glVertex2i(650, 620);
	glVertex2i(700, 640);
	glVertex2i(630, 660);
    glVertex2i(700, 680);
	glVertex2i(630, 700);
    glEnd();

    glBegin(GL_POLYGON); //leaves 3
    glVertex2i(1400, 720);
	glVertex2i(1300, 660);
    glVertex2i(1360, 640);
	glVertex2i(1300, 620);
	glVertex2i(1360, 600);
	glVertex2i(1300, 580);
    glVertex2i(1500, 580);
	glVertex2i(1440, 600);
	glVertex2i(1500, 620);
	glVertex2i(1440, 640);
    glVertex2i(1500, 660);
    glEnd();

    glBegin(GL_POLYGON); //leaves 4
    glVertex2i(1700, 740);
	glVertex2i(1600, 680);
    glVertex2i(1660, 660);
	glVertex2i(1600, 640);
	glVertex2i(1660, 620);
	glVertex2i(1600, 600);
    glVertex2i(1800, 600);
	glVertex2i(1740, 620);
	glVertex2i(1800, 640);
	glVertex2i(1740, 660);
    glVertex2i(1800, 680);
    glEnd();

    glBegin(GL_TRIANGLES); //leaves 5
    glVertex2i(2500, 680);
	glVertex2i(2550, 820);
    glVertex2i(2600, 680);
    glEnd();

    glBegin(GL_TRIANGLES); //leaves 6
    glVertex2i(2700, 680);
	glVertex2i(2750, 820);
    glVertex2i(2800, 680);
    glEnd();

    glBegin(GL_TRIANGLES); //leaves 7
    glVertex2i(2900, 680);
	glVertex2i(2950, 820);
    glVertex2i(3000, 680);
    glEnd();

//------------------------Draw Trees--------------------------
    if(DayNight == 0){
        glColor3f(0.6f, 0.298f, 0.0f); //Trunk
	}else{
        glColor3f(0.055f, 0.043f, 0.0f); //Dark Trunk
	}
	glBegin(GL_QUADS); //stick 1 for dhaner gola
    glVertex2i(205, 560);
	glVertex2i(215, 560);
    glVertex2i(215, 550);
	glVertex2i(205, 550);
	glEnd();

	glBegin(GL_QUADS); //stick 2 for dhaner gola
    glVertex2i(2075, 600);
	glVertex2i(2085, 600);
    glVertex2i(2085, 590);
	glVertex2i(2075, 590);
	glEnd();

    glBegin(GL_QUADS); //Trunk 1
    glVertex2i(380, 500);
	glVertex2i(380, 450);
    glVertex2i(400, 450);
	glVertex2i(400, 500);
	glEnd();

	glBegin(GL_QUADS); //Trunk 2
    glVertex2i(1690, 600);
	glVertex2i(1690, 560);
    glVertex2i(1710, 560);
	glVertex2i(1710, 600);
	glEnd();

	glBegin(GL_QUADS); //Trunk 3
    glVertex2i(1390, 580);
	glVertex2i(1390, 540);
    glVertex2i(1410, 540);
	glVertex2i(1410, 580);
	glEnd();

    glBegin(GL_QUADS); //Trunk 4
    glVertex2i(2545, 680);
	glVertex2i(2545, 640);
    glVertex2i(2555, 640);
	glVertex2i(2555, 680);
	glEnd();

	glBegin(GL_QUADS); //Trunk 5
    glVertex2i(2745, 680);
	glVertex2i(2745, 640);
    glVertex2i(2755, 640);
	glVertex2i(2755, 680);
	glEnd();

	glBegin(GL_QUADS); //Trunk 6
    glVertex2i(2945, 680);
	glVertex2i(2945, 640);
    glVertex2i(2955, 640);
	glVertex2i(2955, 680);
	glEnd();

//------------------------House Window-------------------------
    if(DayNight == 0) {
        glColor3f(0.0f, 0.2f, 0.4f);    //FOR DAY
	}else{
        glColor3f(1.0f, 1.0f, 0.0f); // Yellowish color for window light
	}
	glBegin(GL_QUADS);                  //House 2
    glVertex2i(1240, 610);
	glVertex2i(1240, 570);
    glVertex2i(1170, 570);
	glVertex2i(1170, 610);
	glEnd();

	glBegin(GL_QUADS);
    glVertex2i(990, 610);
	glVertex2i(990, 570);
	glVertex2i(945, 570);
    glVertex2i(925, 610);
	glEnd();


	glBegin(GL_QUADS);                  //House 3
    glVertex2i(2470, 670);
	glVertex2i(2470, 640);
    glVertex2i(2410, 640);
	glVertex2i(2410, 670);
	glEnd();

	glBegin(GL_QUADS);
    glVertex2i(2230, 670);
	glVertex2i(2230, 640);
    glVertex2i(2290, 640);
	glVertex2i(2290, 670);
	glEnd();

	glBegin(GL_QUADS);                  //House 1
    glVertex2i(905, 550);
	glVertex2i(905, 510);
    glVertex2i(835,510);
	glVertex2i(835, 550);
	glEnd();

	glBegin(GL_QUADS);
    glVertex2i(535, 550);
	glVertex2i(535, 510);
    glVertex2i(605, 510);
	glVertex2i(605, 550);
	glEnd();

//----------------------------------Draw windmill---------------------------------
    //Windmill Stand
    if(DayNight == 0) {
        glColor3f(0.988f, 0.8f, 0.369f);    //FOR DAY
	}else{
        glColor3f(0.004f, 0.004f, 0.004f); // for night
	}
	glBegin(GL_QUADS);
    glVertex2i(3080, 700);
	glVertex2i(3120, 700);
    glVertex2i(3140, 600);
	glVertex2i(3060, 600);
	glEnd();

    //Outer Circle
    if(DayNight == 0) {
        glColor3f(0.612f, 0.467f, 0.125f);    //FOR DAY
	}else{
        glColor3f(0.067f, 0.059f, 0.008f); // for night
	}
    drawScene(3100.0f, 700.0f, 40.0f);

    //Inner Circle
    if(DayNight == 0) {
        glColor3f(0.863f, 0.863f, 0.102f);    //FOR DAY
	}else{
        glColor3f(0.078f, 0.071f, 0.035f); // for night
	}
    drawScene(3100.0f, 700.0f, 20.0f);

    //Windill Blades
    if(DayNight == 0) {
        glColor3f(0.0f, 0.0f, 0.0f);    //FOR DAY
	}else{
        glColor3f(0.0f, 0.0f, 0.0f); // for night
	}

    // Apply rotation around the windmill center
    glPushMatrix();
    glTranslatef(3100.0f, 700.0f, 0.0f);  // Move to the windmill center
    glRotatef(bladeRotationAngle, 0.0f, 0.0f, 1.0f);  // Rotate blades around z-axis

    // Blade 1
    glBegin(GL_QUADS);
    glVertex2i(-5, 20);
    glVertex2i(0, 20);
    glVertex2i(5, 80);
    glVertex2i(-10, 80);
    glEnd();

    // Blade 2
    glRotatef(120.0f, 0.0f, 0.0f, 1.0f);  // Rotate 120 degrees for the next blade
    glBegin(GL_QUADS);
    glVertex2i(-5, 20);
    glVertex2i(0, 20);
    glVertex2i(5, 80);
    glVertex2i(-10, 80);
    glEnd();

    // Blade 3
    glRotatef(120.0f, 0.0f, 0.0f, 1.0f);  // Rotate another 120 degrees for the third blade
    glBegin(GL_QUADS);
    glVertex2i(-5, 20);
    glVertex2i(0, 20);
    glVertex2i(5, 80);
    glVertex2i(-10, 80);
    glEnd();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void myInit (void){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 3300.0, 0.0, 1100.0);
}

// Update the Train's position based on the current speed
void updateTrainPosition(int value) {
    // Update the position based on speed
    TrainSpeed = 1.0f;

    if (TrainMoving) {
            TrainPosition += TrainSpeed;  // Move Train
        if (TrainPosition > 3300.0f+1510.0f) {
            TrainPosition = -700.0f;        // Wrap around if it exits the screen
        }
    }

    glutPostRedisplay();    // Request a redraw
    glutTimerFunc(10, updateTrainPosition, 0);   // Call this function again after 10 ms
}

// Update boats based on whether they are moving or not
void updateBoats(int value) {
    float boat1_Speed = 1.0f; // Speed of boat 1
    float boat2_Speed = 1.0f; // Speed of boat 2

    if (boat1Moving) {
        boat1PositionX += boat1_Speed;  // Move boat 1
        if (boat1PositionX > 3300.0f+1510.0f) {
            boat1PositionX = -1500.0f; // Wrap around if it exits the screen
        }
    }

    if (boat2Moving) {
        boat2PositionX += boat2_Speed;  // Move boat 2
        if (boat2PositionX > 3300.0f+1510.0f) {
            boat2PositionX = -1500.0f; // Wrap around if it exits the screen
        }
    }

    glutPostRedisplay();  // Redraw the scene
    glutTimerFunc(25, updateBoats, 0); // Call update again in 25 ms
}

void updateClouds(int value) {
    // Update cloud position
    cloudPosition += 0.8f; // Adjust speed as needed

    // Wrap around when clouds move off the screen
    if (cloudPosition > 3300.0f) {
    cloudPosition = -1000.0f;  // Reset to off-screen left position
    }

    glutPostRedisplay(); // Notify GLUT that the display has changed
    glutTimerFunc(50, updateClouds, 0); // Notify GLUT to call update again in 50 ms
}

void updateBladeRotation(int value) {

    if(windmillRotating){
    // Increase the rotation angle
        bladeRotationAngle += 1.5f;
    // Keep the angle within 0-360 degrees
        if (bladeRotationAngle >= 360.0f) {
            bladeRotationAngle = 0.0f;
        }
    }

    glutPostRedisplay();     // Redraw the scene with the new angle
    glutTimerFunc(30, updateBladeRotation, 0);  // Call this function again after 30 ms
}

// Handle keyboard events for arrow keys
void handleKeypress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            // Move boats upward
            boat1PositionY += 10.0f;
            boat2PositionY += 10.0f;
            break;
        case GLUT_KEY_DOWN:
            // Move boats downward
            boat1PositionY -= 10.0f;
            boat2PositionY -= 10.0f;
            break;
        case GLUT_KEY_LEFT:
            // Move boats left
            boat1PositionX -= 10.0f;
            boat2PositionX -= 10.0f;
            break;
        case GLUT_KEY_RIGHT:
            // Move boats right
            boat1PositionX += 10.0f;
            boat2PositionX += 10.0f;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// Handle normal keys
void handleNormalKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'g': // resume train moving
            TrainPosition += 10.0f;
            TrainMoving = true;
            break;
        case 'b': // Start moving left side
            TrainPosition -= 10.0f;
            TrainMovingLeft = true;
            break;
        case 'r': // Stop the train
            TrainMoving = false;
            break;
        case 'f': // move train right side
            TrainPosition += 10.0f;
            TrainMovingRight = true;
            break;
        case 's':
            boat1Moving = true;
            break;
        case 'e':
            boat2Moving = true;
            break;
        case 'o':
            windmillRotating = true;  //start rotating
            break;
        case 'p':
            windmillRotating = false;  //stop rotating
            break;
        case 'd':
            DayNight = 0;  // Switch to day
            break;
        case 'n':
            DayNight = 1;  // Switch to night
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Request a redraw to update the display
}

// Handle mouse clicks for stopping boat movement
void handleMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            // Stop boat 1
            boat1Moving = false;
        } else if (button == GLUT_RIGHT_BUTTON) {
            // Stop boat 2
            boat2Moving = false;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(3300, 1100);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Village Scenario");
    glutDisplayFunc(display);
    // Register input callbacks
    glutSpecialFunc(handleKeypress);      // For arrow keys
    glutKeyboardFunc(handleNormalKeypress);  // For normal keys
    glutMouseFunc(handleMouse);           // For mouse clicks
    glutTimerFunc(20, updateTrainPosition, 0);
    glutTimerFunc(20, updateClouds, 0); //Add a timer
    glutTimerFunc(20, updateBoats, 0);
    glutTimerFunc(20, updateBladeRotation, 0);
    myInit();
    glutMainLoop();
    return 0;
}
