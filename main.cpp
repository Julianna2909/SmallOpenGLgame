#include <iostream>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include <GL/glut.h>

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilut.h>
#include <IL/ilu.h>

void OutText(float x, float y, float z, char *string){
    glRasterPos3f(x,y,z);
    for (char *c=string; *c!= '\0'; c++ ){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}


void GameOver (){

glutIdleFunc(NULL);
glColor3f(1,1,1);
OutText(-0.5 , 1, 7, "GAME OVER");
}

float Ground[9][9] =
    {
        { 5.0, 4.0, 3.0, 2.0, 1.0, 2.0, 3.0, 4.0, 5.0 },
        { 4.0, 3.0, 2.0, 1.0, 1.0, 1.0, 2.0, 3.0, 4.0 },
        { 3.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 3.0 },
        { 2.0, 1.0, 1.0, 2.0, 3.0, 2.0, 1.0, 1.0, 2.0 },
        { 1.0, 1.0, 1.0, 3.0, 4.0, 3.0, 1.0, 1.0, 1.0 },
        { 2.0, 1.0, 1.0, 2.0, 3.0, 2.0, 1.0, 1.0, 2.0 },
        { 3.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 3.0 },
        { 4.0, 3.0, 2.0, 1.0, 1.0, 1.0, 2.0, 3.0, 4.0 },
        { 5.0, 4.0, 3.0, 2.0, 1.0, 2.0, 3.0, 4.0, 5.0 }
    };

    class Enemie
{
    public:
    float x;
    float y;
    float z;

    float size;

    bool colliding;
    bool toc;

    Enemie(){}

    Enemie(float _x, float _y, float _z, float _size, bool _toc)
    {
        x=_x;
        y=_y;
        z=_z;
        size = _size;
        colliding = false;
        toc = _toc;

    }

    void Show()
    {
    glColor3f(1.0, 0.0, 0.0);
        glTranslatef(x,y,z);
        glutSolidSphere(size, 30 ,30);
        glTranslatef(-x,-y,-z);
    }

    void Move(float _x, float _y, float _z)
    {
        x+=_x;
        y+=_y;
        z+=_z;
    }


    bool CheckCollisions(float _x, float _y, float _z, float radius)
    {
        float distance = sqrt((x-_x)*(x-_x)+(y-_y)*(y-_y)+(z-_z)*(z-_z));
        colliding = distance < size/2 + radius;
        return colliding;
    }
};

Enemie enemies[] =
{
    {2.0, 1, 0.0, 0.25f,1},
    {4.0, 1, 2.0, 0.25f,1},
    {2.0, 1, 4.0, 0.25f,1},
    {0.0, 1, 2.0, 0.25f,1}
};

class Sphere
{
    public:
    float x;
    float y;
    float z;

    float r;
    float g;
    float b;

    float size;

    bool colliding;

    Sphere(){}

    Sphere(float _x, float _y, float _z, float _size)
    {
        x=_x;
        y=_y;
        z=_z;
        r=1.0f;
        g=0.0f;
        b=1.0f;
        size = _size;
        colliding = false;

    }

    void Show()
    {
    glColor3f(1.0, 0.0, 1.0);
        glTranslatef(x,y,z);
        glutSolidSphere(size, 30 ,30);
        glTranslatef(-x,-y,-z);
    }

    void Move(float _x, float _y, float _z)
    {
        x+=_x;
        y+=_y;
        z+=_z;
    }


    bool CheckCollisions(float _x, float _y)
    {
        if (_x == x && _y == y )
        return true;
        else return false;
    }
};

    Sphere spheres[] =
    {
        {0.0, 3, 0.0, 0.13f},
        {0.0, 3, 4.0, 0.13f},
        {4.0, 3, 0.0, 0.13f},
        {4.0, 3, 4.0, 0.13f}
    };

void ResetCoins(){
spheres[0].Move(0.0, 3.0, 0.0);
spheres[1].Move(0.0, 3, 4.0);
spheres[2].Move(4.0, 3, 0.0);
spheres[3].Move(4.0, 3, 4.0);
}

class Player
{
public:
    float x;
    float y;
    float z;

    int coins;

    Player(){}

   Player(float _x, float _y, float _z)
    {
        x=_x;
        y=_y;
        z=_z;

        coins;
    }

    void Show()
    {
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(x,y,z);
        glutSolidSphere(0.2, 30 ,30);
        glTranslatef(-x,-y,-z);
    }


    void MoveDown(float _x, float _z){
    int pointerX = _x * 2;
    int pointerZ = _z * 2;


    y = Ground [pointerX][pointerZ]* 0.5 + 0.5;
     printf("Kord y = %f\n",y);
     printf("Kord gr = %f\n", Ground[pointerX][pointerZ]);
          printf("Kord x = %f\n",x);
               printf("Kord z = %f\n",z);

    }
};

void moveenemy1 (){
if (enemies[0].toc) enemies[0].z+=0.005;
if (enemies[0].z > 1) enemies[0].toc = !enemies[0].toc;

if (!enemies[0].toc) enemies[0].z-=0.005;
if (enemies[0].z < 0) enemies[0].toc = !enemies[0].toc;
}

void moveenemy2 (){
if (enemies[1].toc) enemies[1].x-=0.005;
if (enemies[1].x < 3 ) enemies[1].toc = !enemies[1].toc;

if (!enemies[1].toc) enemies[1].x+=0.005;
if (enemies[1].x > 4) enemies[1].toc = !enemies[1].toc;
}

void moveenemy3 (){
if (enemies[2].toc) enemies[2].z-=0.005;
if (enemies[2].z < 3 ) enemies[2].toc = !enemies[2].toc;

if (!enemies[2].toc) enemies[2].z+=0.005;
if (enemies[2].z > 4) enemies[2].toc = !enemies[2].toc;
}

void moveenemy4 (){
if (enemies[3].toc) enemies[3].x-=0.005;
if (enemies[3].x > 1 ) enemies[3].toc = !enemies[3].toc;

if (!enemies[3].toc) enemies[3].x+=0.005;
if (enemies[3].x < 0) enemies[3].toc = !enemies[3].toc;
}

Player player = Player(2.0, 2.5, 2.0);
int ccoins =0;

void init (void)
{
float pos[4] = {3,3,3,1};
float color[4] = {1,1,1,1};
float sp[4] = {0.5,0.5,0.5,0.5};
float mat_specular[] = {1,1,1,1};
    glLightfv(GL_LIGHT3, GL_SPECULAR, sp);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, color);
    glLightfv(GL_LIGHT3, GL_POSITION, pos);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
}

void resize(int w,int h)
{
if (h == 0) h = 1;
float ratio=w*1.0/h;
glViewport(0,0,w,h);
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluPerspective(45.0, ratio, 0.1,20);
gluLookAt( 5, 7, 5, 0,0,0, 0,1,0 );
glMatrixMode( GL_MODELVIEW );
}

    int rx=0,ry=0,ox=1,oy=1,r1=0;

void display(void)
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT3);

glPushMatrix();
            glRotatef(rx,0,0,0);
            glRotatef(ry,0,1,0);

//##....Ground....##//
  //**1st FLOR **//
   glColor3d(1,1,0);
           glTranslatef(0, -2.5, 0);
              glutSolidCube(4.5);
        glTranslatef(0, 2.5, 0);
 //**1st FLOR **//
         glTranslatef(-2, 0, -2);
for ( int i = 0; i < 9; i++ )
    for (int j = 0; j < 9; j++){
glColor3d(0,1,0);
float x = 0.5 * i;
float z = 0.5 * j;
float y = Ground[i][j];
        for (int k = 0; k <= y; k++){
        glTranslatef(x, k*0.5, z);
              glutSolidCube(0.5);
        glTranslatef(-x, -k*0.5, -z);
        }
}
//##....Ground....##//

player.Show();

for(int i = 0; i < 4; i++)
    {
        if (spheres[i].x == player.x && spheres[i].z == player.z) spheres[i].Move(9,9,9);
        spheres[i].Show();
    }

for(int i = 0; i < 4; i++)
    {
    moveenemy1();
    moveenemy2();
    moveenemy3();
    moveenemy4();
     if (enemies[i].CheckCollisions(player.x, player.y, player.z, 0.25f)) {ResetCoins(); GameOver();}
    enemies[i].Show();
    }
           glTranslatef(2, 0, 2);


glPopMatrix();
   glutSwapBuffers();
}

void mouserot(int x,int y)
{
if(ox>(-1))
    {
    ry+=x-ox;
    rx+=y-oy;
    }
    ox=x;
    oy=y;
}


void arrow_keys (int keys,int x,int y)
{
    switch(keys){
    case GLUT_KEY_UP: glutFullScreen(); break;
    case GLUT_KEY_DOWN :glutReshapeWindow(800,600); break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    float moveX = 0.0f;
    float moveZ = 0.0f;
	switch (key) {
        case 'd': moveX = 0.5; break;
		case 'a': moveX =-0.5; break;
        case 'w': moveZ =-0.5; break;
		case 's': moveZ = 0.5; break;
	}
	player.x += moveX;
	player.z += moveZ;

	if (player.x < 0) player.x +=0.5;
    if (player.x > 4) player.x -=0.5;

    if (player.z < 0) player.z +=0.5;
    if (player.z > 4) player.z -=0.5;

    	player.MoveDown(player.x, player.z);
}

int main(int argc, char **argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(500,500);
glutInitWindowPosition(100,100);
glutCreateWindow("Mario");
init();
glutMotionFunc(mouserot);
glutDisplayFunc(display);
glutIdleFunc(display);
glutKeyboardFunc(keyboard);
glutSpecialFunc(arrow_keys);
glutReshapeFunc(resize);
glutMainLoop();
return 0;
}
