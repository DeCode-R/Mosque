// Base Code For Assignment - 3
#include <windows.h>

#define GL_SILENCE_DEPRECATION
//#include <OpenGL/gl3.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include<math.h>
#include <iostream>
#include "BmpLoader.h"
//stbi_set_flip_vertically_on_load(true);


using namespace std;
const int width = 700;
const int height = 700;

GLfloat eyeX = 31;
GLfloat eyeY = 5;
GLfloat eyeZ = -27;

GLfloat centerX = 7;
GLfloat centerY = 5;
GLfloat centerZ = 28;
double angle = 0 ;
bool l_on1 = true;
bool l_on2 = true;
bool l_on3 = true;
bool l_on4 = false;
float rot = 0;
int stop=1;
float door_angle=.5;
float l_height =.5;
float spt_cutoff = 30;
unsigned int ID;
//vector<int>v;


#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
#include<iostream>
using namespace std;


void myInit ()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 700, 0, 800, -10.0, 10.0);
}

void circle(GLfloat rx,GLfloat ry,GLfloat cx,GLfloat cy)///radius_x,radius_y,centre_position_x,centre_position_y///
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);
    for(int i=0; i<=360; i++)
    {
        float angle = 3.1416f * i/180;
        float x = rx * cosf(angle);
        float y = ry * sinf(angle);
        glVertex2f((x+cx),(y+cy));
    }
    glEnd();


}

float p = -10;
int i= -700;
float j= -250;
float k= -100;



static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {3,1,5,7},  //front
    {6,4,0,2},  //back
    {2,3,7,6},  //top
    {1,0,4,5},  //bottom
    {7,5,4,6},  //right
    {2,0,1,3}   //left
};


void cube(float R=0.5, float G=0.5, float B=0.5, int type=0, float val=1)
{

    GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,1};
    GLfloat m_diff[] = {R,G,B,1};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {30};

    GLfloat m_em[] = {1,1,1,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);
    if(type==1)
    {

        if(l_on1)
            glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
        else
            glMaterialfv(GL_FRONT, GL_EMISSION, m_no);

    }
    else if(type==2)
    {
        if(l_on3)
            glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
        else
            glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    }
    else
        glMaterialfv(GL_FRONT, GL_EMISSION, m_no);


    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);
        glTexCoord2f(0,val);
        glVertex3fv(&v_cube[c_ind[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[c_ind[i][1]][0]);
        glTexCoord2f(val,0);
        glVertex3fv(&v_cube[c_ind[i][2]][0]);
        glTexCoord2f(val,val);
        glVertex3fv(&v_cube[c_ind[i][3]][0]);
    }
    glEnd();
}


void cube2(float R = 0.5, float G = 0.5, float B = 0.5, float alpha = 0.2, int type = 0, float val = 1)
{

    GLfloat m_no[] = {0, 0, 0, 0.2};
    GLfloat m_amb[] = {R, G, B, alpha};  // Set alpha for ambient, diffuse, and specular
    GLfloat m_diff[] = {R, G, B, alpha};
    GLfloat m_spec[] = {1, 1, 1, alpha};
    GLfloat m_sh[] = {30};

    GLfloat m_em[] = {1,1,1,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);
    if(type==1)
    {

        if(l_on1)
            glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
        else
            glMaterialfv(GL_FRONT, GL_EMISSION, m_no);

    }
    else if(type==2)
    {
        if(l_on3)
            glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
        else
            glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    }
    else
        glMaterialfv(GL_FRONT, GL_EMISSION, m_no);


    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);
        glTexCoord2f(0,val);
        glVertex3fv(&v_cube[c_ind[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[c_ind[i][1]][0]);
        glTexCoord2f(val,0);
        glVertex3fv(&v_cube[c_ind[i][2]][0]);
        glTexCoord2f(val,val);
        glVertex3fv(&v_cube[c_ind[i][3]][0]);
    }
    glEnd();
}

void Cube()
{

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_cube[c_ind[i][0]][0]);glTexCoord2f(1,1);
            glVertex3fv(&v_cube[c_ind[i][1]][0]);glTexCoord2f(1,0);
            glVertex3fv(&v_cube[c_ind[i][2]][0]);glTexCoord2f(0,0);
            glVertex3fv(&v_cube[c_ind[i][3]][0]);glTexCoord2f(0,1);
        }
    }
    glEnd();
}



void cubeT(float R=0.5, float G=0.5, float B=0.5, float a=1, int type=0, float val=1)
{

    GLfloat m_no[] = {0, 0, 0, 1.0};
    GLfloat m_amb[] = {R,G,B,a};
    GLfloat m_diff[] = {R,G,B,a};
    GLfloat m_spec[] = {1,1,1,1};
    GLfloat m_sh[] = {30};

    GLfloat m_em[] = {1,1,1,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_sh);
    if(type==1)
    {

        if(l_on1)
            glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
        else
            glMaterialfv(GL_FRONT, GL_EMISSION, m_no);

    }
    else if(type==2)
    {
        if(l_on3)
            glMaterialfv(GL_FRONT, GL_EMISSION, m_em);
        else
            glMaterialfv(GL_FRONT, GL_EMISSION, m_no);
    }
    else
        glMaterialfv(GL_FRONT, GL_EMISSION, m_no);


    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);
        glTexCoord2f(0,val);
        glVertex3fv(&v_cube[c_ind[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[c_ind[i][1]][0]);
        glTexCoord2f(val,0);
        glVertex3fv(&v_cube[c_ind[i][2]][0]);
        glTexCoord2f(val,val);
        glVertex3fv(&v_cube[c_ind[i][3]][0]);
    }
    glEnd();
}
void axes()
{
    float length = 10;
    float width = 0.3;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.8,0.1,0.1);
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.8,0.1);
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.1,0.8);
    glPopMatrix();
}


void cse()
{

    glPushMatrix();
    glScalef(.3,.5,1);
    glTranslatef(45,15,1);
    glPushMatrix();

    //C
    glScalef(.4,1.5,2.9);


    glTranslatef(45,3,2);
    float length=3.4;
    float width=.4;
    //ground
    float a=1,b=0,c=.5;
    glPushMatrix();
    glTranslatef(length/2,1,1);;
    glScalef(3*length,width,width);
    glTranslatef(-.75,-0.5,-0.5);
    cube(a,b,c);
    glPopMatrix();

//right

    glPushMatrix();
    glPushMatrix();
    glTranslatef(1,length/2,1);;
    glScalef(width+3,length+.5,width);
    glTranslatef(0,-0.2,-0.5);
    cube(a,b,c);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(length/2,1,1);;
    glScalef(length*3,width,width);
    glTranslatef(-.75,8.7,-0.5);
    cube(a,b,c);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

//E


    glPushMatrix();

    glScalef(.4,1.5,2.9);

    glTranslatef(15,3,2);

    //ground
    glPushMatrix();
    glTranslatef(length/2,1,1);;
    glScalef(3*length,width,width);
    glTranslatef(-.75,-0.5,-0.5);
    cube(a,b,c);
    glPopMatrix();

//right

    glPushMatrix();
    glPushMatrix();
    glTranslatef(1,length/2+.1,1);;
    glScalef(width+3,length,width);
    glTranslatef(0,-0.2,-0.5);
    cube(a,b,c);
    glPopMatrix();

    //top
    glPushMatrix();
    glTranslatef(length/2,1,1);;
    glScalef(length*3,width,width);
    glTranslatef(-.75,8.7,-0.5);
    cube(a,b,c);
    glPopMatrix();
    //right
    /*
    */
    //rack4
    glPushMatrix();
    glTranslatef(length,1,1);;
    glScalef(3*length,width,width);
    glTranslatef(-.94,4,-0.5);
    cube(a,b,c);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();



//s


    glPushMatrix();

    glScalef(.4,1.5,2.9);
    glTranslatef(30,3,2);

    //ground
    glPushMatrix();
    glTranslatef(length/2,1,1);;
    glScalef(3*length,width,width);
    glTranslatef(-.75,-0.5,-0.5);
    cube(a,b,c);
    glPopMatrix();

//right

    glPushMatrix();
    glPushMatrix();
    glTranslatef(1,length/2,1);;
    glScalef(width+3,length/2,width);
    glTranslatef(0,0.7,-0.5);
    cube(a,b,c);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,length/2,1);;
    glScalef(width+3,length/2+.1,width);
    glTranslatef(-2,-0.5,-0.5);
    cube(a,b,c);
    glPopMatrix();


    //top
    glPushMatrix();
    glTranslatef(length/2,1,1);;
    glScalef(length*3,width,width);
    glTranslatef(-.75,8.7,-0.5);
    cube(a,b,c);
    glPopMatrix();

    //rack4
    glPushMatrix();
    glTranslatef(length,1,1);;
    glScalef(3*length,width,width);
    glTranslatef(-.9,4,-0.5);
    cube(a,b,c);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

}

void road(){
    //bottom

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glScalef(500,0.7,25);
    glTranslatef(-0.5,0.5,-5.5);
    //glRotatef(-90,1,0,0);
    //cube(0.8, 0.8, 0.8);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void floorWallsCeiling(float scale)
{



    //bottom

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glScalef(1400,1,1200);
    glTranslatef(-0.5,-1,-0.5);
    //cube(0.8, 0.8, 0.8);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //behind
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(0,scale/4,scale/2);
    glScalef(1800,1600/2,1);
    glTranslatef(-0.5,-0.5,-31);
   // cube(1.000, 0.855, 0.725);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


/*

    //left
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(scale/2,scale/4,0);
    glScalef(1200,1200/2,1);
    glTranslatef(-1,-0.5,-0.5);
   // cube(0.871, 0.722, 0.529);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //right
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    glTranslatef(-scale/2+1,scale/4,0);
    glScalef(1200,1200/2,1);
    glTranslatef(-1,-0.5,-0.5);
   // cube(0.871, 0.722, 0.529);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



   glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glTranslatef(0,scale/4,scale/2);
    glScalef(1200,1200/2,1);
    glTranslatef(-0.5,-0.5,-1);
   //cube(1.000, 0.855, 0.725);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);    */





}


void flr()
{



    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(0,-0.5,0);
    glScalef(60,1,60);
    glTranslatef(-0.5,19,-0.5);
    //cube(0.690, 0.769, 0.871,0,4);
    Cube();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);



    /*glPushMatrix();


    glTranslatef(0,-0.5,0);
    glScalef(60,1,60);
   glTranslatef(-0.5,-1,-0.5);
    cube(1,1,1,0,8);
    glPopMatrix();




  /* for(int i=-10; i<=35; i++)
    {
        for(float j=-15; j<=14; j+=2)
        {
            glPushMatrix();
//  glTranslatef(0,-0.5,0);

            glScalef(2,.5,1);
            glTranslatef(j,-.999,-i);
            if(i%2==0)
                cube(1, 1, 1);
            else
                cube(0, 0, .5);
            glPopMatrix();
        }
    }

    /*for(int i=-10; i<=35; i++)
    {
        for(float j=-14; j<=14; j+=2)
        {
            glPushMatrix();
//    glTranslatef(0,-0.5,0);

            glScalef(2,.5,1);
            glTranslatef(j,-.999,-i);
            if(i%2!=0)
                cube(1, 1, 1);
            else
                cube(0, 0, .5);
            glPopMatrix();
        }
    }*/


}

//right wall
void wall1()
{
    glPushMatrix();
  //  glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
       //         glEnable(GL_TEXTURE_2D);
     //   glBindTexture(GL_TEXTURE_2D,36);

//    glTranslatef(0,-0.5,0);
    glScalef(1,20,43);
    glTranslatef(-21,0,-0.7);
    cube(1,1,1);
    glPopMatrix();
   //glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);



}

//left Wall
void wall2()
{
    glPushMatrix();
  //  glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //    glEnable(GL_TEXTURE_2D);
     //   glBindTexture(GL_TEXTURE_2D,36);
	glTranslatef(-14,-0.5,0);
    glScalef(1,20,43);
    glTranslatef(29,0,-0.7);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);

}


//behind
void wall3()
{
    glPushMatrix();
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(0,-0.5,0);
    glScalef(33,20,1);
    glTranslatef(-.55,0,12);
    //cube(0.741, 0.718, 0.420,0,2);
    cube(1,1,1);

    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
  //  glDisable(GL_BLEND);


}


//behind
void wall33()
{
    glPushMatrix();
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,16);
//    glTranslatef(0,-0.5,0);
    glScalef(36,20,1);
    glTranslatef(-.55,0,12);
    //cube(0.741, 0.718, 0.420,0,2);
    cube(1,1,1);

    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
  //  glDisable(GL_BLEND);


}
void wall4()
{
    glPushMatrix();
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(0,-0.5,0);
    glScalef(36,20,1);
    glTranslatef(-.55,0,12);
    //cube(0.741, 0.718, 0.420,0,2);
    cube(0.3,0.7,0.7);

    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);


}


void door()
{
    //toppart
    glPushMatrix();
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(0,-0.5,0);
    glScalef(30,19,1);
    glTranslatef(-.7,-0,-31);
    //cube2(1,.69,.0,0.05);
    cube(1,1,1);
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);




   //restHalfPart
    glPushMatrix();
 //   glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //  glEnable(GL_TEXTURE_2D);
 //   glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(0,-0.5,0);
    glScalef(22,7,1);
    glTranslatef(-.13,1.8,-31);
    //cube2(1,.69,.0,0.05);
 //   cube2(1, 1, 1, 0.5, 2, 1);  // Adjust the alpha value as needed
     cube(1,1,1);

    glPopMatrix();
 //   glDisable(GL_TEXTURE_2D);
    //glDisable(GL_BLEND);


}


void door11()
{
    //toppart
    glPushMatrix();
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     //glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D,16);
//    glTranslatef(0,-0.5,0);
    glScalef(30,19,1);
    glTranslatef(-.7,-0,-31);
    //cube2(1,.69,.0,0.05);
   // cube(1,1,1);
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);




   //restHalfPart
    glPushMatrix();
 //   glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,31);
//    glTranslatef(0,-0.5,0);
    glScalef(9,6,1);
    glTranslatef(1,2.1,-33);
    //cube2(1,.69,.0,0.05);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_BLEND);


}


void door110()
{
    //toppart
    glPushMatrix();
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     //glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D,16);
//    glTranslatef(0,-0.5,0);
    glScalef(30,19,1);
    glTranslatef(-.7,-0,-31);
    //cube2(1,.69,.0,0.05);
   // cube(1,1,1);
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);




   //restHalfPart
    glPushMatrix();
 //   glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,31);
//    glTranslatef(0,-0.5,0);
    glScalef(9,6,1);
    glTranslatef(1,2.1,-33);
    //cube2(1,.69,.0,0.05);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_BLEND);


      //baranda
    glPushMatrix();
 //   glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,53);
//    glTranslatef(0,-0.5,0);
    glScalef(9,6,1);
    glTranslatef(1,0,-33);
    //cube2(1,.69,.0,0.05);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_BLEND);


}


void door12()
{
    //toppart
    glPushMatrix();
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     //glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D,16);
//    glTranslatef(0,-0.5,0);
    glScalef(30,19,1);
    glTranslatef(-.22,-0,-31);
    //cube2(1,.69,.0,0.05);
    cube(1,1,1);
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);




   //restHalfPart
    glPushMatrix();
 //   glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,16);
//    glTranslatef(0,-0.5,0);
    glScalef(22,7,1);
    glTranslatef(-.94,1.8,-31);
    //cube2(1,.69,.0,0.05);
    cube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    //glDisable(GL_BLEND);


}

void door13()
{
    //toppart
    glPushMatrix();
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     //glEnable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D,16);
//    glTranslatef(0,-0.5,0);
    glScalef(68,19,1);
    glTranslatef(-.3,-0,-31);
    //cube2(1,.69,.0,0.05);
    cube(1,1,1);
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);




   //restHalfPart
    glPushMatrix();
 //   glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,16);
//    glTranslatef(0,-0.5,0);
    glScalef(22,7,1);
    glTranslatef(-.94,1.8,-31);
    //cube2(1,.69,.0,0.05);
    //cube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
    //glDisable(GL_BLEND);


}

void door2()
{
    //toppart
    glPushMatrix();
   // glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(0,-0.5,0);
    glScalef(37,19,1);
    glTranslatef(-.8,-0,-31);
    //cube2(1,.69,.0,0.05);
    cube(0.3,0.7,0.7);
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);




   //restHalfPart
    glPushMatrix();
    //glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(0,-0.5,0);
    glScalef(23,7,1);
    glTranslatef(-.3,1.8,-30);
    //cube2(1,.69,.0,0.05);
    cube(0.3,0.7,0.7);
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);


}


//float k=0;
float angle1=0;
bool markdoor=0;
double window_val=0;
void spin()
{
    angle = (angle+k)*stop;
    k+=.001;
    if (angle >= 360)
        angle = 0;
    angle1+=.2;
    if (angle1 >= 360)
        angle1 = 0;
    bool ok=0;
    bool ok1=0;
    if(markdoor&&door_angle>-2)
    {
        door_angle-=.05,ok=1;
        if(door_angle<.1)
            window_val+=0.05;
        window_val=min( window_val,1.00);
        l_on4=1;


    }
    if(!markdoor&&door_angle<.5)
    {
        door_angle+=.05,ok=1;
        window_val-=.05;
        window_val=max(window_val,0.00);

    }
    if(!ok)
        l_on4=markdoor;

}

void headwall()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,18);

//    glTranslatef(0,-0.5,0);
    glScalef(37,1,50);
    glTranslatef(-0.57,19,-0.7);
    //cube(0.690, 0.769, 0.871,0,4);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}




void topBoard(){
       //restHalfPart
    glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(0,-0.5,0);
  //  glColor3f(1.0, 0.0, 0.0);  // Set color to red

    glScalef(23,7,1);
    glTranslatef(-.3,1.8,-30);
    Cube();
    glPopMatrix();
  //  glDisable(GL_TEXTURE_2D);

}

void board()
{
    glPushMatrix();
//    glTranslatef(0,-0.5,0);
    glScalef(10,10,1);
    glTranslatef(-.7,.4,9);
    cube(1,1,1);
    glPopMatrix();


    glPushMatrix();
//    glTranslatef(0,-0.5,0);
    glScalef(31.5,11,1);
    glTranslatef(-.601,.32,9.5);
    cube(0,0,0);

}



double a=2;
double b=1;
double c= 10;
void fan()
{
    //fan stand
    float length = 10;
    float width = 0.3;
    glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,28);
    glTranslatef(1,length/2,-4);
    glScalef(width,length,width);
    glTranslatef(-20,1,20);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);



    glPushMatrix();
                glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,28);
    glScalef(1,.1,1);
    glTranslatef(-5,150,2);
    cube(1, 1, 1);            // Set color as glColor3f(R,G,B)
    glRotatef(angle, 0, 0, 1);
    glRecti(-a, -a, a, a);
    cube(1, 1, 1);
    glRecti(-b, a, b, c);
    glRecti(-c, -b, -a, b);
    glRecti(-b, -c, b, -a);
    glRecti(a, -b, c, b);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

}


void drop()
{

    glPushMatrix();
//wear drop front
    cube(113/255.0,74/255.0,44/255.0);
    //glColor3ub (113,74,44);
    glBegin(GL_POLYGON);
    glVertex3f (460, 660, 0);
    glVertex3f (470, 670, 0);
    glVertex3f (330, 670,0);
    glVertex3f (340, 660, 0);
    glVertex3f (340, 320, 0);
    glVertex3f (460, 320, 0);
    glEnd();


//wear drop front-drawer 3 - outer

    glPopMatrix();

    glPushMatrix();


    glTranslatef(0,0,0);
    glScalef(105,95,10);

    glPushMatrix();
    glTranslatef(3.32,4.6,-.49);
    cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(3.32,5.7,-.49);
    cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.32,3.5,-.49);
    cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();
    glPopMatrix();


    //wear drop front-drawer 1 - handel

    glPushMatrix();
    glTranslatef(1,0,0);
    glScalef(20,10,10);
    glPushMatrix();
    glTranslatef(19.5,38,-.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19.5,58,-.5);
    cube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19.5,48,-.5);
    cube(1,1,1);
    glPopMatrix();

    glPopMatrix();

//wear drop side

    cube(62/255.0,43/255.0,35/255.0);
    glColor3ub (62,43,35);
    glBegin(GL_POLYGON);
    glVertex3f (470, 670, 0);
    glVertex3f (500, 667, 0);
    glVertex3f (492, 657, 0);
    glVertex3f (492, 330, 0);
    glVertex3f (460, 320, 0);
    glVertex3f (460, 660, 0);
    glEnd();

    glPopMatrix();

}


void drop2()
{

    glPushMatrix();
    glPushMatrix();
//wear drop front
    cube(113/255.0,74/255.0,44/255.0);
    //glColor3ub (113,74,44);
    glBegin(GL_POLYGON);
    glVertex3f (460, 660, 0);
    glVertex3f (470, 670, 0);
    glVertex3f (330, 670,0);
    glVertex3f (340, 660, 0);
    glVertex3f (340, 320, 0);
    glVertex3f (460, 320, 0);
    glEnd();


//wear drop front-drawer 3 - outer

    glPopMatrix();

    glPushMatrix();


    glTranslatef(0,0,0);
    glScalef(105,95,10);

    glPushMatrix();
    glTranslatef(3.32,4.6,-1);
    glScalef(1,0.1,2);
    cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(3.32,5.7,-1);
    glScalef(1,0.1,2);
    cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.32,3.5,-1);
    glScalef(1,0.1,2);
    cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();
    glPopMatrix();


//wear drop side

    cube(62/255.0,43/255.0,35/255.0);
    glColor3ub (62,43,35);
    glBegin(GL_POLYGON);
    glVertex3f (470, 670, 0);
    glVertex3f (500, 667, 0);
    glVertex3f (492, 657, 0);
    glVertex3f (492, 330, 0);
    glVertex3f (460, 320, 0);
    glVertex3f (460, 660, 0);
    glEnd();

    glPopMatrix();
    glPopMatrix();


}


void drop3()
{

    glPushMatrix();
    glPushMatrix();
//wear drop front
    cube(113/255.0,74/255.0,44/255.0);
    //glColor3ub (113,74,44);
    glBegin(GL_POLYGON);
    glVertex3f (460, 660, 0);
    glVertex3f (470, 670, 0);
    glVertex3f (330, 670,0);
    glVertex3f (340, 660, 0);
    glVertex3f (340, 320, 0);
    glVertex3f (460, 320, 0);
    glEnd();


//wear drop front-drawer 3 - outer

    glPopMatrix();

    glPushMatrix();


    glTranslatef(0,0,0);
    glScalef(105,95,10);

    glPushMatrix();
    glTranslatef(3.32,4.6,-2);
    glScalef(1,0.1,2);
    cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(3.32,5.7,-2);
    glScalef(1,0.1,2);
    cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.32,3.5,-2);
    glScalef(1,0.1,2);
    cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();
    glPopMatrix();





//wear drop side

    cube(62/255.0,43/255.0,35/255.0);
    glColor3ub (62,43,35);
    glBegin(GL_POLYGON);
    glVertex3f (470, 670, 0);
    glVertex3f (500, 667, 0);
    glVertex3f (492, 657, 0);
    glVertex3f (492, 330, 0);
    glVertex3f (460, 320, 0);
    glVertex3f (460, 660, 0);
    glEnd();

    glPopMatrix();
    glPopMatrix();


}



void drop4()
{

    glPushMatrix();
    glPushMatrix();
//wear drop front
    cube(113/255.0,74/255.0,44/255.0);
    //glColor3ub (113,74,44);
    glBegin(GL_POLYGON);
  //  glVertex3f (460, 660, 0);
   // glVertex3f (470, 670, 0);
   // glVertex3f (330, 670,0);
   // glVertex3f (340, 660, 0);
   // glVertex3f (340, 320, 0);
   // glVertex3f (460, 320, 0);
    glEnd();


//wear drop front-drawer 3 - outer

    glPopMatrix();

    glPushMatrix();


    glTranslatef(0,0,0);
    glScalef(105,95,10);

    glPushMatrix();
    glTranslatef(3.32,4.6,-2);
    glScalef(1,0.1,2);
    //cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(3.32,5.7,-2);
    glScalef(1,0.1,2);
   // cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.32,3.5,-2);
    glScalef(1,0.1,2);
  //  cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();
    glPopMatrix();





//wear drop side

  //  cube(62/255.0,43/255.0,35/255.0);
  //  glColor3ub (62,43,35);
  //  glBegin(GL_POLYGON);
  //  glVertex3f (470, 670, 0);
   // glVertex3f (500, 667, 0);
   // glVertex3f (492, 657, 0);
  //  glVertex3f (492, 330, 0);
   // glVertex3f (460, 320, 0);
   // glVertex3f (460, 660, 0);
    glEnd();

    glPopMatrix();
    glPopMatrix();


}

void drop5()
{

    glPushMatrix();
    glPushMatrix();
//wear drop front
    cube(113/255.0,74/255.0,44/255.0);
    //glColor3ub (113,74,44);
    glBegin(GL_POLYGON);
    glVertex3f (460, 660, 0);
    glVertex3f (470, 670, 0);
    glVertex3f (330, 670,0);
    glVertex3f (340, 660, 0);
    glVertex3f (340, 320, 0);
    glVertex3f (460, 320, 0);
    glEnd();


//wear drop front-drawer 3 - outer

    glPopMatrix();

    glPushMatrix();


    glTranslatef(0,0,0);
    glScalef(105,95,10);

    glPushMatrix();
    glTranslatef(3.32,4.6,-2);
    glScalef(1,0.1,2);
    //cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(3.32,5.7,-2);
    glScalef(1,0.1,2);
    //cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.32,3.5,-2);
    glScalef(1,0.1,2);
    //cube(62/255.0,43/255.0,45/255.0);
    glPopMatrix();
    glPopMatrix();





//wear drop side

    //cube(62/255.0,43/255.0,35/255.0);
   // glColor3ub (62,43,35);
   // glBegin(GL_POLYGON);
  //  glVertex3f (470, 670, 0);
  //  glVertex3f (500, 667, 0);
  //  glVertex3f (492, 657, 0);
   // glVertex3f (492, 330, 0);
   // glVertex3f (460, 320, 0);
    //glVertex3f (460, 660, 0);
    glEnd();

    glPopMatrix();
    glPopMatrix();


}
void weardrop()
{
    glPushMatrix();
//    glTranslatef(0,-0.5,0);



    glTranslatef(9,-7,8);
//glRotatef(rot,0,1,1);
    //glScalef(.04,.022,.03);
    drop2();
    glPopMatrix();
}


void weardrop2()
{
    glPushMatrix();
   // glTranslatef(-42,-7,6.5);


    glTranslatef(-35,-7,1);

   //glTranslatef(9,-7,8);
//glRotatef(rot,0,1,1);
    glScalef(.04,.022,.03);
     drop4();
    glPopMatrix();
}


void weardrop3(){
    glPushMatrix();
//    glTranslatef(0,-0.5,0);



    glTranslatef(9,-7,8);
    //glRotatef(rot,0,1,1);
    glScalef(.04,.022,.03);
    drop3();
    glPopMatrix();
}

void weardrop5(){
    glPushMatrix();
//    glTranslatef(0,-0.5,0);



    glTranslatef(9,-7,8);
    //glRotatef(rot,0,1,1);
    glScalef(.04,.022,.03);
    drop5();
    glPopMatrix();

}

void projector()
{
     glPushMatrix();
    glScalef(2,.7,1.8);
    glTranslatef(-0.43,15,-.4);
    cube(1, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,3.4,.5);
    glTranslatef(0,3.2,0);
    cube(0.392, 0.3, 0.929);
    glPopMatrix();

    glPushMatrix();
    glScalef(.68,.68,.68);
    glTranslatef(0,15.45,1);
    cube(1,0,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.60,.60,.60);
    glTranslatef(0.05,17.55,1.4);
    cube(0,0,0);
    glPopMatrix();
}


void projector_board()
{
    glPushMatrix();
    glScalef(6,6,0.1);
    glTranslatef(-0.2,.8,130);
    cube(1, 1, 1);
    glPopMatrix();

}


void AC()
{
    glPushMatrix();
    glScalef(6,2,2);
    glTranslatef(-1.5,6,-10.5);
    cube(.8, .8,.8);
    glPopMatrix();



}

void AC2()
{
    glPushMatrix();
    glScalef(6,2,2);
    glTranslatef(1.5,8,5);
    cube(.8, .8,.8);
    glPopMatrix();



}


void clock1()
{

    glPushMatrix();
//clock outer
    glPushMatrix();
    glScalef(1.5,1.3,1);
    glTranslatef(-220,-200,1);
    cube(0,0,0);
    glBegin(GL_QUADS);
    glVertex3f (680, 800, 0);
    glVertex3f (630, 800, 0);
    glVertex3f (630, 900, 0);
    glVertex3f (680, 900, 0);
    glEnd();

//clock inner
    glPushMatrix();
    glTranslatef(0,0,-.98);
    cube(0.847, 0.749, 0.847);
    glBegin(GL_QUADS);
    glVertex3f (675, 805, 0);
    glVertex3f (635, 805, 0);
    glVertex3f (635, 895, 0);
    glVertex3f (675, 895, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-2);
////////////////////////////
    glPushMatrix();
    glTranslatef(653,847,1);
    glRotatef(angle1, 0, 0, 1);

    cube(0, 0, 0);
    glRecti(-b, a, b, 3*c);
    glPopMatrix();
    /////////////////////////////
//clock second
    cube(0,0,0);

    glBegin(GL_LINES);
    glVertex3f (655, 850, 0);
    glVertex3f (655, 870, 0);
    glEnd();





//clock hour
    cube(0,0,0);
    glBegin(GL_LINES);

//glBegin(GL_POINT_SIZE);
    glVertex3f (655, 850, 0);
    glVertex3f (645, 810, 0);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}
void clock2()
{


    glPushMatrix();
//    glTranslatef(0,-0.5,0);

    glTranslatef(-60,-20,9);
//glRotatef(rot,0,1,1);
    glScalef(.07,.04,.04);
    clock1();
    glPopMatrix();
}

void fan1()
{
    glPushMatrix();
    glTranslatef(1,-.5,-15);
    fan();
    glPopMatrix();
}


void fan2()
{
    glPushMatrix();
    glTranslatef(20,-.10,-5);
    fan();
    glPopMatrix();
}

void fan3()
{
    glPushMatrix();
    glTranslatef(-15,-.10,-5);
    fan();
    glPopMatrix();
}


float al1,dl1,sl1;
float al2,dl2,sl2;
float al3,dl3,sl3;
void light1(float a,float b,float c)
{
    glEnable(GL_LIGHT0);

    //light
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {0.4+al1, 0.4+al1, 0.4+al1, 1.0};
    GLfloat l_dif[] = {.4+dl1,.4+dl1,.4+dl1,1};
    GLfloat l_spec[] = {.4+sl1,.4+sl1,.4+sl1,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on1)
        glLightfv(GL_LIGHT0, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT0, GL_AMBIENT, l_no);
    if(l_on1)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT0, GL_DIFFUSE, l_no);
    if(l_on1)
        glLightfv(GL_LIGHT0, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT0, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT0, GL_POSITION, l_pos);


}

void light2(float a,float b,float c)
{
    glEnable(GL_LIGHT2);
    //light
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {0.3+al2, 0.3+al2, 0.3+al2, 1.0};
    GLfloat l_dif[] = {.6+dl2,.6+dl2,.6+dl2,1};
    GLfloat l_spec[] = {5+sl2,5+sl2,5+sl2,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on3)
        glLightfv(GL_LIGHT2, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT2, GL_AMBIENT, l_no);
    if(l_on3)
        glLightfv(GL_LIGHT2, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT2, GL_DIFFUSE, l_no);
    if(l_on3)
        glLightfv(GL_LIGHT2, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT2, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT2, GL_POSITION, l_pos);
    // GLfloat l_spt[] = {0,-1,0,1};
//    GLfloat spt_ct[] = {66};
//    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l_spt);
//    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);


}

void spot_light(float a,float b,float c)
{
    //light
    glEnable(GL_LIGHT1);

    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {1+al3, 1+al3, 1+al3, 1.0};
    GLfloat l_dif[] = {0.4+dl3,1+dl3,1+dl3,1};
    GLfloat l_spec[] = {1+sl3,1+sl3,1+sl3,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on2)
        glLightfv(GL_LIGHT1, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT1, GL_AMBIENT, l_no);
    if(l_on2)
        glLightfv(GL_LIGHT1, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT1, GL_DIFFUSE, l_no);
    if(l_on2)
        glLightfv(GL_LIGHT1, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT1, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT1, GL_POSITION, l_pos);
    GLfloat l_spt[] = {0,-1,0,1};
    GLfloat spt_ct[] = {15};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l_spt);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, spt_ct);

}

void window_light(float a,float b,float c)
{
    //light
    glEnable(GL_LIGHT3);

    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_amb[] = {.5* window_val, .5* window_val, .5* window_val, 1.0};
    GLfloat l_dif[] = {1* window_val,1* window_val,1* window_val,1};
    GLfloat l_spec[] = {1* window_val,1* window_val,1* window_val,1};
    GLfloat l_pos[] = {a,b,c,1.0};

    if(l_on4)
        glLightfv(GL_LIGHT3, GL_AMBIENT, l_amb);
    else
        glLightfv(GL_LIGHT3, GL_AMBIENT, l_no);
    if(l_on4)
        glLightfv(GL_LIGHT3, GL_DIFFUSE, l_dif);
    else
        glLightfv(GL_LIGHT3, GL_DIFFUSE, l_no);
    if(l_on4)
        glLightfv(GL_LIGHT3, GL_SPECULAR, l_spec);
    else
        glLightfv(GL_LIGHT3, GL_SPECULAR, l_no);

    glLightfv(GL_LIGHT3, GL_POSITION, l_pos);
    GLfloat l_spt[] = {0,-1,0,1};
    GLfloat spt_ct[] = {84};
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, l_spt);
    glLightfv(GL_LIGHT3, GL_SPOT_CUTOFF, spt_ct);

}


void light()
{

//light 1

    glPushMatrix();
    glPushMatrix();

    glRotatef(200, 0,1,0);
    float a=-20,b=400,c=180;
    light1(a,b,c);
    glPopMatrix();
    glTranslatef(a,b+1,c);
    glScalef(0.1,0.1,0.1);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,1,1,1);
    glPopMatrix();
    // cout<<l_height<<" "<<spt_cutoff<<endl;

//light2

    glPushMatrix();
    glPushMatrix();

    glRotatef(200, 0,1,0);
    a=15,b=17,c=-15;
    light2(a,b,c);
    glPopMatrix();
    glTranslatef(a,b+1,c);
    glScalef(0.1,0.1,0.1);
    glTranslatef(1,-0.5,-0.5);
    cube(1,1,1,2);
    glPopMatrix();


    //spot light
    glPushMatrix();
    glPushMatrix();
    glRotatef(-95, 0,1,0);
    a=-40,b=390,c=75;
    spot_light(a,b,c);

    glPopMatrix();
    glTranslatef(a,b+1,c);
    glScalef(0.1,0.1,0.1);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,1,1,true);
    glPopMatrix();


    //window light
    glPushMatrix();
    glPushMatrix();
    glRotatef(0, 0,1,0);
    a=35,b=15,c=-10;
    window_light(a,b,c);

    glPopMatrix();
    glTranslatef(a,b+1,c);
    glScalef(0.1,0.1,0.1);
    glTranslatef(-0.5,-0.5,-0.5);
   // cube(1,0,0,true);
    glPopMatrix();
    // cout<<sl2<<endl;
    //  cout<<window_val<<endl;
    // cout<<l_height<<" "<<spt_cutoff<<endl;
}


void window()
{
    glPushMatrix();
    glPushMatrix();
//    glTranslatef(0,-0.5,0);
    glScalef(1,8,15);
    glTranslatef(28,.5,-1);
   // glColor4f(1.0, 1.0, 1.0, 0.5); // The fourth parameter (alpha) controls transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    cube2(1, 1, 1, 0.1, 2, 1);  // Adjust the alpha value as needed
    glBindTexture(GL_TEXTURE_2D,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    glPushMatrix();
//    glTranslatef(0,-0.5,0);
    glScalef(1,8,.2);
    glTranslatef(28,.5,-76);
   // glColor4f(1.0, 1.0, 1.0, 0.5); // Use glColor4f for RGBA with alpha
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    cube(1,.59,.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);
       // Rotate the door based on the door_angle
    glRotatef(door_angle, 0, 1, 0);

    // Draw the door components
    glPushMatrix();
   // glEnable(GL_BLEND);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
    glScalef(1, 0.2, 15);
    glTranslatef(27.9, 50, -1);
    cube(0, 0, 0);
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);

    glPushMatrix();
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   // glEnable(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D,1);
    glScalef(1, 0.2, 15);
    glTranslatef(27.9, 30, -1);
    cube(0, 0, 0);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);

    for (int i = 0; i >= -75; i -= 2)
    {
        glPushMatrix();
       // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //  glEnable(GL_TEXTURE_2D);
       // glBindTexture(GL_TEXTURE_2D,1);
        glScalef(1, 8, .2);
        glTranslatef(27.9, .5, i);
        cube(0, 0, 0);
        glPopMatrix();
       // glDisable(GL_TEXTURE_2D);
        //glDisable(GL_BLEND);
    }

    glPopMatrix();

    light();
}

void windows()
{
    glPushMatrix();
    window();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180,0,1,0);
   // window();
    glPopMatrix();
}



void room1(){
  //glEnable(GL_LIGHTING);
   // lightOne();
    //lightTwo();
   // lampLight();
   // glViewport(0, 0, 800, 600);


   // lightBulb1();
  //  lightBulb2();
    //lightBulb3();
   // glDisable(GL_LIGHTING);


    /*eyeX, eyeY, eyeZ Specifies the position of the eye point.
    centerX, centerY, centerZ Specifies the position of the reference point.
    upX, upY, upZ Specifies the direction of the up vector.
    */
    //  glViewport(0, 0, width, height);

    //axes();
  //  cse();
   // table();
    //flr();
    //wall1();


    wall2();
    wall3();
    glPushMatrix();
    glTranslatef(-.7,0,-41);
    wall3();
    glPopMatrix();
    headwall();

   // fan();
//    test();
   // window();
   // clock1();




    glPushMatrix();
    glTranslatef(1,0,-40);
   // clock2();
    glPopMatrix();



    glPushMatrix();
    glScalef(5.2,1.2,2.2);
    glTranslatef(-5.3,0,25);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    //weardrop3();
    glPopMatrix();


    glPushMatrix();
    glScalef(5.2,1.2,2.2);
    glTranslatef(-5.3,0,20);
    glRotatef(90.0, 0.0, 1.0, 0.0);
  //  weardrop3();
    glPopMatrix();

    glPushMatrix();
    glScalef(3.2,1.2,2.2);
    glTranslatef(-24.5,0,-5.5);
    //glRotatef(-90.0, 0.0, 1.0, 0.0);
   // glRotatef(-90.0, 0.0, 1.0, 0.0);
  //  weardrop3();
    glPopMatrix();


    light();


//projector();
//AC();
    //AC2();

//projector_board();


    //  glTranslatef(1,-.5,-15);
    //
    //cout<<eyeX<<" "<<eyeY<<" "<<eyeZ<<" "<<centerX<<" "<<centerY<<" "<<centerZ<<" "<<rot<<endl;
//cout<<rot<<endl;
}

void room2(){
 // glEnable(GL_LIGHTING);
   // lightOne();
    //lightTwo();
   // lampLight();
   // glViewport(0, 0, 800, 600);


   // lightBulb1();
  //  lightBulb2();
    //lightBulb3();
   // glDisable(GL_LIGHTING);


    /*eyeX, eyeY, eyeZ Specifies the position of the eye point.
    centerX, centerY, centerZ Specifies the position of the reference point.
    upX, upY, upZ Specifies the direction of the up vector.
    */
    //  glViewport(0, 0, width, height);


    glPushMatrix();
    glTranslatef(10,0,-15);
    glRotatef(90.0, 0.0, 1.0, 0.0);
   // door2();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-70,-0.5,0);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall2();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-34,0,0);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall3();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,0,0);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    door();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,0,-0.5);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    headwall();
    glPopMatrix();


    glPushMatrix();
   // clock2();
    glPopMatrix();

    glPushMatrix();
    glScalef(5.2,1.2,2.2);
    glTranslatef(-5.3,0,25);
    glRotatef(90.0, 0.0, 1.0, 0.0);
   // weardrop3();
    glPopMatrix();

    light();

}

void room3(){
 // glEnable(GL_LIGHTING);
   // lightOne();
    //lightTwo();
   // lampLight();
   // glViewport(0, 0, 800, 600);


   // lightBulb1();
  //  lightBulb2();
    //lightBulb3();
   // glDisable(GL_LIGHTING);


    /*eyeX, eyeY, eyeZ Specifies the position of the eye point.
    centerX, centerY, centerZ Specifies the position of the reference point.
    upX, upY, upZ Specifies the direction of the up vector.
    */
    //  glViewport(0, 0, width, height);


    glPushMatrix();
    glTranslatef(10,0,-15);
    glRotatef(90.0, 0.0, 1.0, 0.0);
  //  door2();
    glPopMatrix();

    glPushMatrix();

	glTranslatef(-40,-0.5,-43);
    glScalef(1,1,1);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    ///wall1();
    glPopMatrix();


    glPushMatrix();
	glTranslatef(-0.5,-0.5,-44);
    glScalef(1,1,1.1);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
   /// wall2();
    glPopMatrix();

    ///mayneed

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,28);
	glTranslatef(1,0,-90);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall3();
    glPopMatrix();
                glDisable(GL_TEXTURE_2D);


    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,28);
	glTranslatef(-36,0,-47);
    glScalef(1.21,1,1);

    //glRotatef(90.0, 0.0, 1.0, 0.0);
    door();
    glPopMatrix();
                glDisable(GL_TEXTURE_2D);


    glPushMatrix();
	glTranslatef(-36,0,-50);
    glScalef(1.2,1,1.45);
    headwall();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0,0,-50);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1,1,1.45);
    headwall();
    glPopMatrix();

    //myclock
    glPushMatrix();
    glTranslatef(50,10,50);
    //clock2();
    glPopMatrix();

    glPushMatrix();
    glScalef(5.2,1.2,2.2);
    glTranslatef(-5.3,0,25);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    //weardrop3();
    glPopMatrix();

   // fan();

    light();

}


void room33(){
 // glEnable(GL_LIGHTING);
   // lightOne();
    //lightTwo();
   // lampLight();
   // glViewport(0, 0, 800, 600);


   // lightBulb1();
  //  lightBulb2();
    //lightBulb3();
   // glDisable(GL_LIGHTING);


    /*eyeX, eyeY, eyeZ Specifies the position of the eye point.
    centerX, centerY, centerZ Specifies the position of the reference point.
    upX, upY, upZ Specifies the direction of the up vector.
    */
    //  glViewport(0, 0, width, height);


    glPushMatrix();
    glTranslatef(10,0,-15);
    glRotatef(90.0, 0.0, 1.0, 0.0);
  //  door2();
    glPopMatrix();

    glPushMatrix();
   // glEnable(GL_BLEND);
  //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(-40,-0.5,-36);
    glScalef(1,1,1.27);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
   /// wall1();
    glPopMatrix();
   // glDisable(GL_BLEND);


    glPushMatrix();
	glTranslatef(-0.5,-0.5,-42);
    glScalef(1,1,1.1);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
   /// wall2();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(1,0,-87);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
   // wall33();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,0,-40);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    door11();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,0,-32);
    glScalef(1,1,1.3);
  //  headwall();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0,0,-32);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1,1,1.3);
   // headwall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,0,-87);
    //clock2();
    glPopMatrix();

    glPushMatrix();
    glScalef(5.2,1.2,2.2);
    glTranslatef(-5.3,0,25);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    //weardrop3();
    glPopMatrix();

    light();

}

void room110(){
 // glEnable(GL_LIGHTING);
   // lightOne();
    //lightTwo();
   // lampLight();
   // glViewport(0, 0, 800, 600);


   // lightBulb1();
  //  lightBulb2();
    //lightBulb3();
   // glDisable(GL_LIGHTING);


    /*eyeX, eyeY, eyeZ Specifies the position of the eye point.
    centerX, centerY, centerZ Specifies the position of the reference point.
    upX, upY, upZ Specifies the direction of the up vector.
    */
    //  glViewport(0, 0, width, height);


    glPushMatrix();
    glTranslatef(10,0,-15);
    glRotatef(90.0, 0.0, 1.0, 0.0);
  //  door2();
    glPopMatrix();

    glPushMatrix();
   // glEnable(GL_BLEND);
  //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTranslatef(-40,-0.5,-36);
    glScalef(1,1,1.27);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
   /// wall1();
    glPopMatrix();
   // glDisable(GL_BLEND);


    glPushMatrix();
	glTranslatef(-0.5,-0.5,-42);
    glScalef(1,1,1.1);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
   /// wall2();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(1,0,-87);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
   // wall33();
    glPopMatrix();

            //baranda
    glPushMatrix();
	glTranslatef(-36,0,-40);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    door110();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,0,-32);
    glScalef(1,1,1.3);
  //  headwall();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0,0,-32);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1,1,1.3);
   // headwall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,0,-87);
    //clock2();
    glPopMatrix();

    glPushMatrix();
    glScalef(5.2,1.2,2.2);
    glTranslatef(-5.3,0,25);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    //weardrop3();
    glPopMatrix();

    light();

}


void room34(){
 // glEnable(GL_LIGHTING);
   // lightOne();
    //lightTwo();
   // lampLight();
   // glViewport(0, 0, 800, 600);


   // lightBulb1();
  //  lightBulb2();
    //lightBulb3();
   // glDisable(GL_LIGHTING);


    /*eyeX, eyeY, eyeZ Specifies the position of the eye point.
    centerX, centerY, centerZ Specifies the position of the reference point.
    upX, upY, upZ Specifies the direction of the up vector.
    */
    //  glViewport(0, 0, width, height);


    glPushMatrix();
    glTranslatef(10,0,-15);
    glRotatef(90.0, 0.0, 1.0, 0.0);
  //  door2();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,-0.5,-36);
    glScalef(1,1,1.27);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall1();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-0.5,-0.5,-43);
    glScalef(1,1,1.1);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall2();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(1,0,-87);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall33();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,0,-43);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    door12();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,0,-32);
    glScalef(1,1,1.3);
    headwall();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0,0,-32);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1,1,1.3);
    headwall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,0,-87);
    //clock2();
    glPopMatrix();

    glPushMatrix();
    glScalef(5.2,1.2,2.2);
    glTranslatef(-5.3,0,25);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    //weardrop3();
    glPopMatrix();

    light();

}


void room35(){
 // glEnable(GL_LIGHTING);
   // lightOne();
    //lightTwo();
   // lampLight();
   // glViewport(0, 0, 800, 600);


   // lightBulb1();
  //  lightBulb2();
    //lightBulb3();
   // glDisable(GL_LIGHTING);


    /*eyeX, eyeY, eyeZ Specifies the position of the eye point.
    centerX, centerY, centerZ Specifies the position of the reference point.
    upX, upY, upZ Specifies the direction of the up vector.
    */
    //  glViewport(0, 0, width, height);


    glPushMatrix();
    glTranslatef(10,0,-15);
    glRotatef(90.0, 0.0, 1.0, 0.0);
  //  door2();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,-0.5,-36);
    glScalef(1,1,1.27);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall1();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-0.5,-0.5,-43);
    glScalef(1,1,1.1);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall2();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(1,0,-87);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall33();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,0,-43);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    door13();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,0,-32);
    glScalef(1,1,1.3);
    headwall();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0,0,-32);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1,1,1.3);
    headwall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,0,-87);
    //clock2();
    glPopMatrix();

    glPushMatrix();
    glScalef(5.2,1.2,2.2);
    glTranslatef(-5.3,0,25);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    //weardrop3();
    glPopMatrix();

    light();

}
void room4(){
 // glEnable(GL_LIGHTING);
   // lightOne();
    //lightTwo();
   // lampLight();
   // glViewport(0, 0, 800, 600);


   // lightBulb1();
  //  lightBulb2();
    //lightBulb3();
   // glDisable(GL_LIGHTING);


    /*eyeX, eyeY, eyeZ Specifies the position of the eye point.
    centerX, centerY, centerZ Specifies the position of the reference point.
    upX, upY, upZ Specifies the direction of the up vector.
    */
    //  glViewport(0, 0, width, height);


    glPushMatrix();
    glTranslatef(10,0,-15);
    glRotatef(90.0, 0.0, 1.0, 0.0);
  //  door2();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,-0.5,-36);
    glScalef(1,1,1.27);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall1();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-0.5,-0.5,-43);
    glScalef(1,1,1.1);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    wall2();
    glPopMatrix();


    //front wall without door
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
	glTranslatef(-17,0,-87);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(2,1,1.1);
    wall4();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);


    //TopBanner
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,9);
	glTranslatef(-17,20,-87);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(2,1,1.1);
   // wall4();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_BLEND);


    glPushMatrix();
	glTranslatef(-36,0,-43);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
  //  wall4();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-36,0,-32);
    glScalef(1,1,1.3);
    headwall();
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0,0,-32);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1,1,1.3);
    headwall();
    glPopMatrix();

    glPushMatrix();
    //clock2();
    glPopMatrix();

    glPushMatrix();
    glScalef(5.2,1.2,2.2);
    glTranslatef(-5.3,0,25);
    glRotatef(90.0, 0.0, 1.0, 0.0);
   // weardrop3();
    glPopMatrix();

    light();

}


void room5(){

    //TopBanner
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
	glTranslatef(-17,20,-87);
    glScalef(2,1,1.1);
    wall4();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    light();

}

void floorWall()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,15);

//    glTranslatef(0,-0.5,0);
    glScalef(38,0.6,50);
    glTranslatef(-0.59,0,-0.7);
    //cube(0.690, 0.769, 0.871,0,4);
    cube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void topFLoor(){
        glPushMatrix();
        glPushMatrix();
        glTranslatef(0,21,0);
        glScalef(1,1,1);
        room1();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,21,0);
        glScalef(1,1,1);
        room2();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,21,0);
        glScalef(1,1,1);
        room4();
        glPopMatrix();
        glPopMatrix();

}

void FullHouse2(){


    //room1();

    glPushMatrix();
    //glScalef(5.2,1.2,2.2);
    glTranslatef(0,0,70);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1,1.2,2);
   // room1();
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1.2,2);
    glTranslatef(0,0,37);
    //room2();
    glPopMatrix();

//----
    glPushMatrix();
    //glTranslatef(-5,0,0);
    glScalef(3,1.9,2);
    glTranslatef(0,0,60);
    room3();
    glPopMatrix();


//frontRoom
    glPushMatrix();
    //glTranslatef(-5,0,0);
    glScalef(3,1.9,0.8);
    glTranslatef(0,0,0);
    room34();
    glPopMatrix();



    glPushMatrix();
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(0,-0.5,0);
    glScalef(230,34,1);
    glTranslatef(-0.80,0,55);
    //cube(0.741, 0.718, 0.420,0,2);
    cube(0.3,0.7,0.7);

    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);



    }

void FullHouse3(){


    //room1();

    glPushMatrix();
    //glScalef(5.2,1.2,2.2);
    glTranslatef(0,0,70);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1,1.2,2);
   // room1();
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1.2,2);
    glTranslatef(0,0,37);
    //room2();
    glPopMatrix();

//----
    glPushMatrix();
    //glTranslatef(-5,0,0);
    glScalef(3,1.9,2);
    glTranslatef(0,0,60);
    room3();
    glPopMatrix();


//frontRoom
    glPushMatrix();
    //glTranslatef(-5,0,0);
    glScalef(3,1.9,0.8);
    glTranslatef(0,0,0);
    room35();
    glPopMatrix();



    glPushMatrix();
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   // glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,1);
//    glTranslatef(0,-0.5,0);
    glScalef(230,34,1);
    glTranslatef(-0.80,0,55);
    //cube(0.741, 0.718, 0.420,0,2);
    cube(0.3,0.7,0.7);

    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
   // glDisable(GL_BLEND);



    }

    void FullHouse(){


    //room1();

    glPushMatrix();
    //glScalef(5.2,1.2,2.2);
    glTranslatef(0,0,70);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1,1.2,2);
   // room1();
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1.2,2);
    glTranslatef(0,0,37);
    //room2();
    glPopMatrix();

//----
    glPushMatrix();
    //glTranslatef(-5,0,0);
    glScalef(3,1.9,2);
    glTranslatef(0,0,60);
    room3();
    glPopMatrix();


//frontRoom
    glPushMatrix();
    //glTranslatef(-5,0,0);
    glScalef(3,1.9,1);
    glTranslatef(0,0,-5);
    room33();
    glPopMatrix();



    glPushMatrix();
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,28);
//    glTranslatef(0,-0.5,0);
    glScalef(232,36,1);
    glTranslatef(-0.79,0,55);
    //cube(0.741, 0.718, 0.420,0,2);
    cube(1,1,1);

    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
            glDisable(GL_TEXTURE_2D);




    }


    void FullHouse110(){


    //room1();

    glPushMatrix();
    //glScalef(5.2,1.2,2.2);
    glTranslatef(0,0,70);
    //glRotatef(90.0, 0.0, 1.0, 0.0);
    glScalef(1,1.2,2);
   // room1();
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1.2,2);
    glTranslatef(0,0,37);
    //room2();
    glPopMatrix();

//----
    glPushMatrix();
    //glTranslatef(-5,0,0);
    glScalef(3,1.9,2);
    glTranslatef(0,0,60);
    room3();
    glPopMatrix();


//frontRoom
    glPushMatrix();
    //glTranslatef(-5,0,0);
    glScalef(3,1.9,1);
    glTranslatef(0,0,-5);
    room110();
    glPopMatrix();



    glPushMatrix();
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,28);
//    glTranslatef(0,-0.5,0);
    glScalef(232,36,1);
    glTranslatef(-0.79,0,55);
    //cube(0.741, 0.718, 0.420,0,2);
    cube(1,1,1);

    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);
            glDisable(GL_TEXTURE_2D);




    }



void allFloor(){


    //room4

    glPushMatrix();
  //  glTranslatef(0,-19,0);
    //glScalef(1,0.2,1);
    glTranslatef(0,0,0);
    glScalef(10.5,1.2,4.5);
    glTranslatef(-3,0,7);
    floorWall();
    glPopMatrix();





}





//right wall
void wall11()
{
    glPushMatrix();
//    glTranslatef(0,-0.5,0);
    glScalef(1,20,43);
    glTranslatef(-21,0,-0.7);
    cube2(0, 0, 0, 0.5, 2, 1);  // Adjust the alpha value as needed
    glPopMatrix();
}

//left Wall
void wall12()
{
    glPushMatrix();
	glTranslatef(-14,-0.5,0);
    glScalef(1,20,43);
    glTranslatef(29,0,-0.7);
    cube2(1, 1, 1, 0.5, 2, 1);  // Adjust the alpha value as needed
    glPopMatrix();
}

//behind
void wall13()
{
    glPushMatrix();
//    glTranslatef(0,-0.5,0);
    glScalef(36,20,1);
    glTranslatef(-.55,0,12);
    //cube(0.741, 0.718, 0.420,0,2);
    cube2(1, 1, 1, 0.5, 2, 1);  // Adjust the alpha value as needed

    glPopMatrix();
}


void wall14()
{
    glPushMatrix();
    glScalef(36,20,1);
    glTranslatef(-.55,0,12);
    cube2(1, 1, 1, 0.5, 2, 1);  // Adjust the alpha value as needed
    glPopMatrix();
}


void door15()
{
    //toppart
    glPushMatrix();
    glScalef(30,19,1);
    glTranslatef(-.7,-0,-31);
    cube2(1, 1, 1, 0.5, 2, 1);  // Adjust the alpha value as needed
    glPopMatrix();

   //restHalfPart
    glPushMatrix();
    glScalef(22,7,1);
    glTranslatef(-.3,1.8,-31);
    cube2(1, 1, 1, 0.5, 2, 1);  // Adjust the alpha value as needed
    glPopMatrix();
}

void door21()
{
    //toppart
    glPushMatrix();
    glScalef(37,19,1);
    glTranslatef(-.8,-0,-31);
    cube2(1, 1, 1, 0.5, 2, 1);  // Adjust the alpha value as needed
    glPopMatrix();

   //restHalfPart
    glPushMatrix();
    glScalef(23,7,1);
    glTranslatef(-.3,1.8,-30);
    cube2(1, 1, 1, 0.5, 2, 1);  // Adjust the alpha value as needed
    glPopMatrix();
}



void leftHouse(){

    glPushMatrix();
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room1();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,5);

            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,5);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,1);
          //  door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,55);
            glTranslatef(0,0,0);
            //headwall();
            glPushMatrix();
                glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,55);

                //    glTranslatef(0,-0.5,0);
                    glScalef(32,1,45);
                    glTranslatef(-0.55,12,-0.7);
                    //cube(0.690, 0.769, 0.871,0,4);
                    Cube();
                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                glPopMatrix();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//--------------------------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room2();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,1);
            glTranslatef(10,0,-15);
            glRotatef(90.0, 0.0, 1.0, 0.0);
           // door21();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,5);
            glTranslatef(-72,-0.5,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,5);
            glTranslatef(-34,0,0);
            glScalef(1.2,1,1);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,1);
            glTranslatef(-36,0,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
           // door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,55);
            glTranslatef(-36,0,-0.5);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            //headwall();
            glPushMatrix();
                glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,55);

                //    glTranslatef(0,-0.5,0);
                    glScalef(32,1,45);
                    glTranslatef(-0.55,12,-0.7);
                    //cube(0.690, 0.769, 0.871,0,4);
                    Cube();
                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                glPopMatrix();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//----------------------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
       // room3();

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,5);
            glTranslatef(-36,-0.5,-36);
            glScalef(1,1,1.27);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall11();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,5);
            glTranslatef(-0.5,-0.5,-43);
            glScalef(1,1,1.1);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,5);
            glTranslatef(-1,0,-87);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,5);
            glTranslatef(-27,0,-43);
            glScalef(1.5,1,1);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,55);
            glTranslatef(-36,0,-32);
            glScalef(1,1,1.3);
            //headwall();
            glPushMatrix();
                glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,55);

                //    glTranslatef(0,-0.5,0);
                    glScalef(32,1,45);
                    glTranslatef(-0.55,12,-0.7);
                    //cube(0.690, 0.769, 0.871,0,4);
                    Cube();
                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                glPopMatrix();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();

            glTranslatef(0,0,-32);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            glScalef(1,1,1.3);
            //headwall();
            glPushMatrix();
                glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,55);

                //    glTranslatef(0,-0.5,0);
                    glScalef(71,1,62.5);
                    glTranslatef(-0.8,12,-0.5);
                    //cube(0.690, 0.769, 0.871,0,4);
                    Cube();
                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                glPopMatrix();


            glPopMatrix();



        glPopMatrix();

//-----------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
       // room5();
           //TopBanner
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,5);
            glTranslatef(-17,20,-87);
            glScalef(2,1,1.1);
           // wall14();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();

    glPopMatrix();

light();

}
void shoeReck(){

    glPushMatrix();
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room1();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,57);

            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,57);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,1);
          //  door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,55);
            glTranslatef(0,0,0);
            //headwall();
            glPushMatrix();
                glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,55);

                //    glTranslatef(0,-0.5,0);
                    glScalef(32,1,45);
                    glTranslatef(-0.55,12,-0.7);
                    //cube(0.690, 0.769, 0.871,0,4);
                   // Cube();
                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                glPopMatrix();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//--------------------------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room2();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,1);
            glTranslatef(10,0,-15);
            glRotatef(90.0, 0.0, 1.0, 0.0);
           // door21();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,57);
            glTranslatef(-72,-0.5,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,57);
            glTranslatef(-34,0,0);
            glScalef(1.2,1,1);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,1);
            glTranslatef(-36,0,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
           // door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,55);
            glTranslatef(-36,0,-0.5);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            //headwall();
            glPushMatrix();
                glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,55);

                //    glTranslatef(0,-0.5,0);
                    glScalef(32,1,45);
                    glTranslatef(-0.55,12,-0.7);
                    //cube(0.690, 0.769, 0.871,0,4);
                  //  Cube();
                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                glPopMatrix();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//----------------------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
       // room3();

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,57);
            glTranslatef(-36,-0.5,-36);
            glScalef(1,1,1.27);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall11();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,57);
            glTranslatef(-0.5,-0.5,-43);
            glScalef(1,1,1.1);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,57);
            glTranslatef(-1,0,-87);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,57);
            glTranslatef(-27,0,-43);
            glScalef(1.5,1,1);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,55);
            glTranslatef(-36,0,-32);
            glScalef(1,1,1.3);
            //headwall();
            glPushMatrix();
                glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,55);

                //    glTranslatef(0,-0.5,0);
                    glScalef(32,1,45);
                    glTranslatef(-0.55,12,-0.7);
                    //cube(0.690, 0.769, 0.871,0,4);
                   // Cube();
                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                glPopMatrix();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();

            glTranslatef(0,0,-32);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            glScalef(1,1,1.3);
            //headwall();
            glPushMatrix();
                glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,56);

                //    glTranslatef(0,-0.5,0);
                    glScalef(71,1,65);
                    glTranslatef(-0.8,5,-0.5);
                    //cube(0.690, 0.769, 0.871,0,4);
                    Cube();
                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                glPopMatrix();


            glPopMatrix();



        glPopMatrix();

//-----------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
       // room5();
           //TopBanner
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,5);
            glTranslatef(-17,20,-87);
            glScalef(2,1,1.1);
           // wall14();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();

    glPopMatrix();



}


void leftHouse2(){

    glPushMatrix();
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room1();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,11);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            headwall();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//--------------------------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room2();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(10,0,-15);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            door21();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-70,-0.5,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-34,0,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,11);
            glTranslatef(-36,0,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-36,0,-0.5);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            headwall();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//----------------------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
       // room3();

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-36,-0.5,-36);
            glScalef(1,1,1.27);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall11();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-0.5,-0.5,-43);
            glScalef(1,1,1.1);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-1,0,-87);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-36,0,-43);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-36,0,-32);
            glScalef(1,1,1.3);
            headwall();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glTranslatef(0,0,-32);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            glScalef(1,1,1.3);
            headwall();
            glPopMatrix();

        glPopMatrix();

//-----------------------------------------------------------------


    glPopMatrix();


}

void left_topFLoor(){
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room1();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            headwall();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//--------------------------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room2();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(10,0,-15);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            door21();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-70,-0.5,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-34,0,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,11);
            glTranslatef(-36,0,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-36,0,-0.5);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            headwall();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//----------------------------------------------------------------------------

        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room4();

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-36,-0.5,-36);
            glScalef(1,1,1.27);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall11();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-0.5,-0.5,-43);
            glScalef(1,1,1.1);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);



            //front wall without door
            glPushMatrix();;
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,14);
            glTranslatef(-17,0,-87);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            glScalef(2,1,1.1);
            wall14();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);






            glPushMatrix();
            glTranslatef(-36,0,-43);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
          //  wall4();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-36,0,-32);
            glScalef(1,1,1.3);
            headwall();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,0,-32);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            glScalef(1,1,1.3);
            headwall();
            glPopMatrix();
        glPopMatrix();




}

void All_leftTop(){

        //TopFloor

    glPushMatrix();
    glTranslatef(70,19,0);
    //glScalef(0.9,0.9,0.9);
    left_topFLoor();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(70,38,0);
    //glScalef(0.9,0.9,0.9);
    left_topFLoor();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(70,57,0);
    //glScalef(0.9,0.9,0.9);
    left_topFLoor();
    glPopMatrix();
/*
    glPushMatrix();
    glTranslatef(140,21,-40);
    glScalef(0.9,0.9,0.9);
    left_topFLoor();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(140,42,-40);
    glScalef(0.9,0.9,0.9);
    left_topFLoor();
    glPopMatrix(); */

}

void topDesign(){
        glPushMatrix();
    glTranslatef(-35,7,-40);
    glScalef(3.17,1,1);
    topBoard();
    glPopMatrix();


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,8);
    glTranslatef(-32,14,-40);
    glScalef(2.7,1,1);
    topBoard();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,7);
    glTranslatef(-25,14,-47);
    glScalef(0.5,1,1);
    topBoard();
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);



    glPushMatrix();
    glTranslatef(-35,21,-40);
    glScalef(3.17,1,1);
    topBoard();
    glPopMatrix();
}


void rightHouse2(){

    glPushMatrix();
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room1();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            headwall();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//--------------------------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room2();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(10,0,-15);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            door21();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-70,-0.5,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-34,0,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,11);
            glTranslatef(-36,0,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-36,0,-0.5);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            headwall();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//----------------------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
       // room3();

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-36,-0.5,-36);
            glScalef(1,1,1.27);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall11();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-0.5,-0.5,-43);
            glScalef(1,1,1.1);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-1,0,-87);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-36,0,-43);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-36,0,-32);
            glScalef(1,1,1.3);
            headwall();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glTranslatef(0,0,-32);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            glScalef(1,1,1.3);
            headwall();
            glPopMatrix();

        glPopMatrix();

//-----------------------------------------------------------------


    glPopMatrix();


}

void right_topFLoor(){
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room1();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            headwall();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//--------------------------------------------------------------------------------
        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room2();
            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(10,0,-15);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            door21();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-70,-0.5,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-34,0,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall13();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,11);
            glTranslatef(-36,0,0);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            door15();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-36,0,-0.5);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            headwall();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


        glPopMatrix();
//----------------------------------------------------------------------------

        glPushMatrix();
            glTranslatef(70,0,0);
            glScalef(0.9,0.9,0.9);
        //room4();

            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-36,-0.5,-36);
            glScalef(1,1,1.27);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall11();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);


            glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-0.5,-0.5,-43);
            glScalef(1,1,1.1);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            wall12();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);



            //front wall without door
            glPushMatrix();;
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,13);
            glTranslatef(-17,0,-87);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            glScalef(2,1,1.1);
            wall14();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);






            glPushMatrix();
            glTranslatef(-36,0,-43);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
          //  wall4();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-36,0,-32);
            glScalef(1,1,1.3);
            headwall();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,0,-32);
            //glRotatef(90.0, 0.0, 1.0, 0.0);
            glScalef(1,1,1.3);
            headwall();
            glPopMatrix();
        glPopMatrix();




}

void All_rightTop(){

        //TopFloor

    glPushMatrix();
    glTranslatef(70,19,0);
    //glScalef(0.9,0.9,0.9);
    right_topFLoor();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(70,38,0);
    //glScalef(0.9,0.9,0.9);
    right_topFLoor();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(70,57,0);
    //glScalef(0.9,0.9,0.9);
    right_topFLoor();
    glPopMatrix();
/*
    glPushMatrix();
    glTranslatef(140,21,-40);
    glScalef(0.9,0.9,0.9);
    left_topFLoor();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(140,42,-40);
    glScalef(0.9,0.9,0.9);
    left_topFLoor();
    glPopMatrix(); */

}





void sun(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}





void tree(){

    // House Tree
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,11);
    glColor3ub(128, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(50, 150);
    glVertex2d(65, 150);
    glVertex2d(65, 300);
    glVertex2d(50, 300);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    // Tree leaf
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glTranslatef(35, 320, 0);  // Adjust the position as needed
    glColor3ub(0, 128, 0);
    sun(30, 40, 0, 0);  // Call the sun function at a specific position
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glTranslatef(85, 320, 0);  // Adjust the position as needed
    glColor3ub(0, 128, 0);
    sun(30, 40, 0, 0);  // Call the sun function at a specific position
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glTranslatef(45, 370, 0);  // Adjust the position as needed
    glColor3ub(0, 128, 0);
    sun(25, 30, 0, 0);  // Call the sun function at a specific position
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glTranslatef(70, 370, 0);  // Adjust the position as needed
    glColor3ub(0, 128, 0);
    sun(30, 30, 0, 0);  // Call the sun function at a specific position
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,10);
    glTranslatef(55, 400, 0);  // Adjust the position as needed
    glColor3ub(0, 128, 0);
    sun(25, 30, 0, 0);  // Call the sun function at a specific position
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    light();

}
void tree2(){

    //center
    //smallTree
    glPushMatrix();
   // glRotatef(45,0,1,0);
    glScalef(0.1,0.1,0.1);
    glTranslatef(-5,-200,-1040);
  //  glRotatef(-90.0, 0.0, 1.0, 0.0);  // Adjust the angle as needed
    tree();
    glPopMatrix();


    //bigTree
    glPushMatrix();
   // glRotatef(45,0,1,0);
    glScalef(0.15,0.15,0.15);
    glTranslatef(40,-150,-550);
  //  glRotatef(-90.0, 0.0, 1.0, 0.0);  // Adjust the angle as needed
    tree();
    glPopMatrix();



    //leftSide

    //smallTree
    glPushMatrix();
   // glRotatef(45,0,1,0);
    glScalef(0.1,0.1,0.1);
    glTranslatef(620,-200,-1040);
  //  glRotatef(-90.0, 0.0, 1.0, 0.0);  // Adjust the angle as needed
    tree();
    glPopMatrix();

    //smallTree
    glPushMatrix();
   // glRotatef(45,0,1,0);
    glScalef(0.1,0.1,0.1);
    glTranslatef(650,-200,-1040);
  //  glRotatef(-90.0, 0.0, 1.0, 0.0);  // Adjust the angle as needed
    tree();
    glPopMatrix();

    //smallTree
    glPushMatrix();
    glScalef(0.1,0.1,0.1);
    glTranslatef(-550,-200,-1040);
    tree();
    glPopMatrix();
    //bigTree
    glPushMatrix();
    glScalef(0.15,0.15,0.15);
    glTranslatef(-500,-150,-550);
    tree();
    glPopMatrix();


    //rightSide

    //smallTree
    glPushMatrix();
    glScalef(0.1,0.1,0.1);
    glTranslatef(500,-200,-1040);
    tree();
    glPopMatrix();
    //bigTree
    glPushMatrix();
    glScalef(0.15,0.15,0.15);
    glTranslatef(500,-150,-550);
    tree();
    glPopMatrix();
}




void table()
{
    float length = .5;
    float height = 3;
    float width= .5;

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length*4,height,width);
    glTranslatef(0,0,0);
    cube(0.0,0.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length*4,height,width);
    glTranslatef(0,0,0);
    glRotatef(-90.0, 0.0, 0.0, 1.0);  // Adjust the angle as needed
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,height,width);
    glTranslatef(0,0,3);
   // cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    //glRotatef(90.0, 0.0, 1.0, 0.0);  // Adjust the angle as needed
    glScalef(length*4,height,width);
    glTranslatef(0,0,4);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glScalef(length*4,height/6,width*5);
    glTranslatef(0.12,6,0);
    cube(1,.8,.4);
    glPopMatrix();


    light();
}
void chair()
{
    float length = .5;
    float height = 2;
    float width= .5;


    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,height,width);
    glTranslatef(.5,0,-2);
    cube(1,0.8,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,height,width);
    glTranslatef(3.5,0,-2);
    cube(1,0.8,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,height,width);
    glTranslatef(.5,0,-4);
    cube(1,0.8,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,height,width);
    glTranslatef(3.5,0,-4);
    cube(1,0.8,0.4);    allFloor();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length*4,height/6,width*4);
    glTranslatef(0.15,6,-1.2);
    cube(1,0.7,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length*4,height*1.2,width);
    glTranslatef(.15,1,-5);
    cube(1,0.7,0.4);
    glPopMatrix();

    light();

}

void pc(){
    float length = .5;
    float height = 2;
    float width= .5;

    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length*4,height*1.2,width);
    glTranslatef(.15,1,-5);
    glScalef(1.2,0.9,0.4);
    //glRotatef(90.0, 0.0, 0.0, 1.0);  // Adjust the angle as needed
    cube(0,0,0);
    glPopMatrix();

}

void full_set()
{
    glPushMatrix();
    glScalef(7.5,1,1.3);
    glTranslatef(0.3,0,0);
    table();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,0,0);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,0,0);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,0,0);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,01,5);
    pc();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,1.3,-2);
    glRotatef(90.0, 1.0, 0.0, 0.0);  // Adjust the angle as needed
   // glTranslatef(15,01,5);
    pc();
    glPopMatrix();


}


void allWearDrop(){

    //room1 weardrop1

    glPushMatrix();
    glScalef(5.2,1.5,4);
    glTranslatef(-5.3,0.5,26);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    weardrop3();
    glPopMatrix();

    glPushMatrix();
    glScalef(5.2,1.5,4);
    glTranslatef(-5.3,5,26);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    weardrop3();
    glPopMatrix();


    //room1 weardrop2

    glPushMatrix();
    glScalef(5.2,1.5,4);
    glTranslatef(-5.3,0.5,20);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    weardrop3();
    glPopMatrix();

    glPushMatrix();
    glScalef(5.2,1.5,4);
    glTranslatef(-5.3,5,20);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    weardrop3();
    glPopMatrix();



    //fornt
    glPushMatrix();
    glScalef(5.2,1.5,2.2);
    glTranslatef(-5.5,0.5,-5);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    weardrop3();
    glPopMatrix();

    glPushMatrix();
    glScalef(5.2,1.5,2.2);
    glTranslatef(-5.5,5,-5);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    weardrop3();
    glPopMatrix();

    //--fridge


    //front

    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);

//    glTranslatef(0,-0.5,0);
    glScalef(1,20,43);
    glTranslatef(-21,0,-25);
    cube2(0, 0, 0, 0.5, 2, 1);  // Adjust the alpha value as needed
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);


    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glScalef(2.3,2.3,5);
    glTranslatef(17,0,0);
    weardrop2();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    //back
    glPushMatrix();
    glScalef(2.3,2.3,5);
    glTranslatef(17,0,1);
    weardrop2();
    glPopMatrix();

    //back
    glPushMatrix();
    glScalef(2.3,2.3,5);
    glTranslatef(17,0,1.2);
    weardrop2();
    glPopMatrix();

    //right
    glPushMatrix();
    glScalef(2.3,2.2,1.4);
    glTranslatef(-12.3,0.3,30.5);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    weardrop5();
    glPopMatrix();

    //left
    glPushMatrix();
    glScalef(2.3,2.2,1.4);
    glTranslatef(-7.5,0.3,30.5);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    weardrop5();
    glPopMatrix();

    light();

}

void drawSphere(float radius) {
    float PI = 3.141592f;
    float x, y, z, alpha, beta; // Storage for coordinates and angles
    int gradation = 20;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 17); // Assuming texture ID 17

    glBegin(GL_TRIANGLE_FAN);

    for (alpha = 0.0f; alpha < PI; alpha += PI / gradation) {
        for (beta = 0.0f; beta < 2.01 * PI; beta += PI / gradation) {
            x = radius * cos(beta) * sin(alpha);
            y = radius * sin(beta) * sin(alpha);
            z = radius * cos(alpha);

            glTexCoord2f(beta / (2.0 * PI), alpha / PI);
            glVertex3f(x, y, z);

            x = radius * cos(beta + PI / gradation) * sin(alpha + PI / gradation);
            y = radius * sin(beta + PI / gradation) * sin(alpha + PI / gradation);
            z = radius * cos(alpha + PI / gradation);

            glTexCoord2f((beta + PI / gradation) / (2.0 * PI), (alpha + PI / gradation) / PI);
            glVertex3f(x, y, z);

            x = radius * cos(beta + PI / gradation) * sin(alpha);
            y = radius * sin(beta + PI / gradation) * sin(alpha);
            z = radius * cos(alpha);

            glTexCoord2f((beta + PI / gradation) / (2.0 * PI), alpha / PI);
            glVertex3f(x, y, z);

            x = radius * cos(beta) * sin(alpha);
            y = radius * sin(beta) * sin(alpha);
            z = radius * cos(alpha);

            glTexCoord2f(beta / (2.0 * PI), alpha / PI);
            glVertex3f(x, y, z);
        }
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);

    light();
}

void gumbazz(){
/* Draw the bottom box */
 glPushMatrix();
 glScaled(0.8,0.04,0.8);
 glTranslatef(0.0,-30.2,0.0);
 //glutSolidCube(7.0);
 glPopMatrix();

    //main cube
 glPushMatrix();
 glTranslatef(0.0,0.3,0.0);
  glScaled(1,0.2,1);
 glutSolidCube(2.0);
 glPopMatrix();

 glTranslatef(0.0,-.6,0.0);

 //main gumbazz
 glPushMatrix();
   //  glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D, 25);
 glScaled(0.8,1.0,0.8);
 glTranslatef(0.0,1.5,0.0);
 glutSolidSphere(0.8,80,120);
 glPopMatrix();
    // glDisable(GL_TEXTURE_2D);


 glTranslatef(0.0,1.0,0.0);
 glScaled(1.2,0.25,1.2);
 glutSolidCube(0.9);

 //gumbaz pointer

 glPushMatrix();
 glScaled(0.03,0.5,0.03);
 glTranslatef(0.0,10.8,0.0);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();



 //short Minars
 glPushMatrix();
 glTranslated(0.6,0.5,0.6);
 glScaled(.2,7,.2);
 glutSolidSphere(0.2,80,120);
 glPopMatrix();

 //short minar's sphere
 glPushMatrix();
 glTranslated(0.6,0.5,0.6);
 glScaled(0.3,1.5,0.3);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();

 //short Minars
 glPushMatrix();
 glTranslated(0.6,0.5,-0.6);
 glScaled(.2,7,.2);
 glutSolidSphere(0.2,80,120);
 glPopMatrix();

 //short minar's sphere
 glPushMatrix();
 glTranslated(0.6,0.5,-0.6);
 glScaled(0.3,1.5,0.3);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();

 //short Minars
 glPushMatrix();
 glTranslated(-0.6,0.5,-0.6);
 glScaled(.2,7,.2);
 glutSolidSphere(0.2,80,120);
 glPopMatrix();

 //short minar's sphere
 glPushMatrix();
 glTranslated(-0.6,0.5,-0.6);
 glScaled(0.3,1.5,0.3);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();

 //short Minars
 glPushMatrix();
 glTranslated(-0.6,0.5,0.6);
 glScaled(.2,7,.2);
 glutSolidSphere(0.2,80,120);
 glPopMatrix();

 //short minar's sphere
 glPushMatrix();
 glTranslated(-0.6,0.5,0.6);
 glScaled(0.3,1.5,0.3);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();

 light();

}


void gumbazz2(){

 glTranslatef(0.0,-.6,0.0);
  glTranslatef(0.0,1.0,0.0);
 glScaled(1.2,0.25,1.2);

 //Minars
 glPushMatrix();
 glTranslated(2.5,-3,1);
 glScaled(.2,10.5,.2);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();

 //minar's sphere
 glPushMatrix();
 glTranslated(2.5,-0.3,1);
 glScaled(0.3,1.5,0.3);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();

  //Minars
 glPushMatrix();
 glTranslated(2.5,-3,-1.5);
 glScaled(.2,10.5,.2);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();

 //minar's sphere
 glPushMatrix();
 glTranslated(2.5,-0.3,-1.5);
 glScaled(0.3,1.5,0.3);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();

 //Minars
 glPushMatrix();
 glTranslated(-2.6,-3,1);
 glScaled(.2,10.5,.2);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();

 //minar's sphere
 glPushMatrix();
 glTranslated(-2.6,-0.3,1);
 glScaled(0.3,1.5,0.3);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();


 //Minars
 glPushMatrix();
 glTranslated(-2.6,-3,-1.5);
 glScaled(.2,10.5,.2);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();

 //minar's sphere
 glPushMatrix();
 glTranslated(-2.6,-0.3,-1.5);
 glScaled(0.3,1.5,0.3);
 glutSolidSphere(0.4,80,120);
 glPopMatrix();





 light();

}

void jainamaj(){

        glPushMatrix();
        glScalef(70,1,85);
        glScalef(0.5,0.5,0.5);
        glTranslatef(-0.57,5,-0.7);
        cube();
        glPopMatrix();

}


void groupJainamaj(){
    //-------------------------------------------------------------------------jainajALl
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-30,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-0,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
 //   jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-5,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

                   glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(21,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

                           glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(34,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);


//double--------------
        glPushMatrix();
            glTranslatef(-12,0,0);


           //-------------------------------------------------------------------------jainajALl
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-30,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-2,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
 //   jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-5,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

                   glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(20,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        //single JaiNamaj
                           glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,22);
    glTranslatef(105,0,-100);
    glScalef(0.3,0.3,0.3);
   // glScalef(0.5,0.5,0.5);
    glRotatef(90,0,1,0);
   // jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        glPopMatrix();

}

void groupJainamaj2(){
    //-------------------------------------------------------------------------jainajALl
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-30,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-5,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

                   glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(20,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

                           glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-54,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

                           glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-66,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);
                                 glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-78,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);


        //double


        glPushMatrix();
                glTranslatef(-12,0,0);

           //-------------------------------------------------------------------------jainajALl
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-30,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(-5,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

                   glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(20,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

                           glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,21);
    glTranslatef(50,0,-100);
    glScalef(0.3,0.3,0.3);
    glRotatef(90,0,1,0);
    //jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();



}

void allJainamaj(){

//row 1------------------------//evenNumber
        glPushMatrix();
    glTranslatef(0,0,31);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj();
        glPopMatrix();

        glPushMatrix();
    glTranslatef(0,0,53);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj();
        glPopMatrix();


        //row2
               glPushMatrix();
    glTranslatef(0,0,75);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj();
        glPopMatrix();


           //row2
               glPushMatrix();
    glTranslatef(0,0,97);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj();
        glPopMatrix();

           //row2
               glPushMatrix();
    glTranslatef(0,0,119);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj();
        glPopMatrix();

                  //row2
               glPushMatrix();
    glTranslatef(0,0,130);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
       // groupJainamaj();
        glPopMatrix();



        //=-----------------------------part2---Evennumber
        glPushMatrix();

        glTranslatef(-75,0,0);

                glPushMatrix();
    glTranslatef(0,0,31);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj2();
        glPopMatrix();
                       glPushMatrix();
    glTranslatef(0,0,53);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj2();
        glPopMatrix();


        //row2
               glPushMatrix();
    glTranslatef(0,0,75);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj2();
        glPopMatrix();


           //row2
               glPushMatrix();
    glTranslatef(0,0,97);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj2();
        glPopMatrix();

           //row2
               glPushMatrix();
    glTranslatef(0,0,119);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj2();
        glPopMatrix();

        glPopMatrix();

  //test---------------------oddNumebr
        glPushMatrix();
        glTranslatef(0,0,11);


//row 1
        glPushMatrix();
    glTranslatef(0,0,31);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj();
        glPopMatrix();


        //row2
               glPushMatrix();
    glTranslatef(0,0,75);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj();
        glPopMatrix();


           //row2
               glPushMatrix();
    glTranslatef(0,0,97);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj();
        glPopMatrix();

           //row2
               glPushMatrix();
    glTranslatef(0,0,119);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj();
        glPopMatrix();



        //-------------------------------------------=oddNumber Jainamaj
        glPushMatrix();

        glTranslatef(-75,0,0);

                glPushMatrix();
    glTranslatef(0,0,31);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj2();
        glPopMatrix();


        //row2
               glPushMatrix();
    glTranslatef(0,0,75);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj2();
        glPopMatrix();


           //row2
               glPushMatrix();
    glTranslatef(0,0,97);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj2();
        glPopMatrix();

           //row2
               glPushMatrix();
    glTranslatef(0,0,119);
    //glScalef(0.3,0.3,0.3);
    //glRotatef(90,0,1,0);
        groupJainamaj2();
        glPopMatrix();
                 //row2

    glPushMatrix();
    glTranslatef(40,0,130);
   // glScalef(0,0,-5);
    //glRotatef(90,0,1,0);
      //  groupJainamaj2();
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();


}


void reckPart(){
        glPushMatrix();
        glScalef(70,1,85);
        glTranslatef(-0.57,5,-0.7);
        cubeT(0,0,0,1);
        glPopMatrix();

        glPushMatrix();
        glScalef(70,1,85);
        glTranslatef(-0.57,15,-0.7);
        cubeT(0,0,0,1);
        glPopMatrix();

        glPushMatrix();
        glScalef(70,1,85);
        glTranslatef(-0.57,25,-0.7);
        cubeT(0,0,0,1);
        glPopMatrix();


        glPushMatrix();
        glScalef(70,1,85);
        glTranslatef(-0.57,35,-0.7);
        cubeT(0,0,0,1);
        glPopMatrix();

}

void reck(){

    //right
    glPushMatrix();
    glEnable(GL_BLEND);
    glScalef(1,20,43);
    glTranslatef(-21,0,-0.7);
    cube(0.5,0.7,0.5);
    glPopMatrix();

    //left
    glPushMatrix();
	glTranslatef(-14,-0.5,0);
    glScalef(1,20,43);
    glTranslatef(29,0,-0.7);
    cube(0.5,0.7,0.5);
    glPopMatrix();

           //back
    glPushMatrix();
    glScalef(36,20,1);
    glTranslatef(-.57,0,-30);
    //cubeT(1,1,1,0.3);
    cube(0.5,0.7,0.5);
    glPopMatrix();

    //step

    glPushMatrix();
    glScalef(0.5,0.5,0.5);
    //glTranslatef(-.57,0,5);
    reckPart();
    glPopMatrix();


    light();
}


void fullreck(){
    glPushMatrix();
    glScalef(0.8,0.9,0.2);
    glTranslatef(-13,0,120);
    reck();
    glPopMatrix();


}


void reckPart3(){
        glPushMatrix();
        glScalef(70,1,85);
        glTranslatef(-0.57,10,-0.7);
        cubeT(0,0,0,1);
        glPopMatrix();


        glPushMatrix();
        glScalef(70,1,85);
        glTranslatef(-0.57,15,-0.7);
       // cubeT(0,0,0,1);
        glPopMatrix();

        glPushMatrix();
        glScalef(70,1,85);
        glTranslatef(-0.57,25,-0.7);
      //  cubeT(0,0,0,1);
        glPopMatrix();


        glPushMatrix();
        glScalef(70,1,85);
        glTranslatef(-0.57,35,-0.7);
       // cubeT(0,0,0,1);
        glPopMatrix();

}

void reck3(){

    //right
    glPushMatrix();
    glEnable(GL_BLEND);
    glScalef(1,5,43);
    glTranslatef(-20,0,-0.7);
    cube(0.5,0.7,0.5);
    glPopMatrix();

    //left
    glPushMatrix();
	glTranslatef(-14,0,0);
    glScalef(1,5,43);
    glTranslatef(29,0,-0.7);
    cube(0.5,0.7,0.5);
    glPopMatrix();

           //back
    glPushMatrix();
    glScalef(36,5,1);
    glTranslatef(-.57,0,-30);
    //cubeT(1,1,1,0.3);
    cube(0.5,0.7,0.5);
    glPopMatrix();


               //front
    glPushMatrix();
    glScalef(36,5,1);
    glTranslatef(-.57,0,11);
    //cubeT(1,1,1,0.3);
    cube(0.5,0.7,0.5);
    glPopMatrix();


    //step

    glPushMatrix();
    glScalef(0.5,0.5,0.5);
    //glTranslatef(-.57,0,5);
    reckPart3();
    glPopMatrix();


    light();
}


void fullreck3(){
    glPushMatrix();
    glScalef(0.8,0.9,0.2);
    glTranslatef(-13,0,120);
    reck3();
    glPopMatrix();


}
void fruitesReck(){



    //frutesReck
    glPushMatrix();
    glScalef(0.4,1.7,0.5);
    glTranslatef(-40,0,38);
    glRotatef(-180,0.0,1,0);
    fullreck3();
    glPopMatrix();

//frutesReck
    glPushMatrix();
    glScalef(0.4,1.1,0.5);
    glTranslatef(-40,0,30);
    glRotatef(-180,0.0,1,0);
    fullreck3();
    glPopMatrix();





    //frutesReck
    glPushMatrix();
    glScalef(0.4,0.6,0.5);
    glTranslatef(-40,0,21);
    glRotatef(-180,0.0,1,0);
    fullreck3();
    glPopMatrix();


      //frutesReck
    glPushMatrix();
                glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,26);
    glScalef(0.4,3,0.1);
    glTranslatef(-40,0,120);
    glRotatef(-180,0.0,1,0);
    fullreck3();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);



}
void masala(){
    glPushMatrix();
  //  glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D,23);
    glTranslatef(-37,16,48);
   // glRotatef(180,1,0,0);
   //glRotatef(-90,0,1,0);
    Cube();
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);

      }

void reckitem(){


        //PLateGlass//------------------------------------------------------------PLateGlass

            glPushMatrix();
                    glScalef(0.5,0.6,0.4);
                    glTranslatef(160,-11,70);
                    glRotatef(-90, 0,1,0);



    //------------------------------------------Toys2

                    glPushMatrix();
                        glTranslatef(-65,0,127);
                        glRotatef(90, 0,1,0);
                       // glScalef(3,3,3);


                        glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,38);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(35,-11,-24);
                        masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                           glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,39);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(36,-11,-24);
                        masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                               glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,40);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(37,-11,-24);
                        masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);


                                           glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,41);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(38,-11,-24);
                       // masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                glPopMatrix();

                //------------------------------------------Toys3

                    glPushMatrix();
                        glTranslatef(-65,0,148);
                        glRotatef(90, 0,1,0);
                       // glScalef(3,3,3);


                        glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,42);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(35,-11,-24);
                        masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                           glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,43);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(36,-11,-24);
                        masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                               glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,44);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(37,-11,-24);
                        masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);


                                           glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,45);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(38,-11,-24);
                       // masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                glPopMatrix();

                //------------------------------------------Toys4

                    glPushMatrix();
                        glTranslatef(-65,0,171);
                        glRotatef(90, 0,1,0);
                       // glScalef(3,3,3);


                        glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,46);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(35,-11,-24);
                       // masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                           glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,47);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(36,-11,-24);
                        masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                               glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,48);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(37,-11,-24);
                        masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);


                                           glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,49);
                       // glRotatef(90, 0,0,1);
                        glScalef(7,6,4);
                        glTranslatef(38,-11,-24);
                       // masala();
                        glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                glPopMatrix();


                //row2
                //------------------------------------------Toys2


                                glPushMatrix();
                                glTranslatef(-65,-7,127);
                                glRotatef(90, 0,1,0);
                               // glScalef(3,3,3);


                                glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,41);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(35,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,38);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(36,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                       glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,39);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(37,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);


                                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,40);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(38,-11,-24);
                               // masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                        glPopMatrix();

                        //------------------------------------------Toys3

                            glPushMatrix();
                                glTranslatef(-65,-7,148);
                                glRotatef(90, 0,1,0);
                               // glScalef(3,3,3);


                                glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,41);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(35,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,42);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(36,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                       glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,43);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(37,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);


                                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,44);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(38,-11,-24);
                               // masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                        glPopMatrix();

                        //------------------------------------------Toys4

                            glPushMatrix();
                                glTranslatef(-65,-7,171);
                                glRotatef(90, 0,1,0);
                               // glScalef(3,3,3);


                                glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,45);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(35,-11,-24);
                                //masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,46);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(36,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                       glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,47);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(37,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);


                                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,48);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(38,-11,-24);
                               // masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                        glPopMatrix();


                          //row2
                //------------------------------------------Toyslast


                                glPushMatrix();
                                glTranslatef(-65,-14,127);
                                glRotatef(90, 0,1,0);
                               // glScalef(3,3,3);


                                glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,48);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(35,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,42);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(36,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                       glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,38);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(37,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);


                                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,39);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(38,-11,-24);
                               // masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                        glPopMatrix();

                        //------------------------------------------Toys3

                            glPushMatrix();
                                glTranslatef(-65,-14,148);
                                glRotatef(90, 0,1,0);
                               // glScalef(3,3,3);


                                glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,40);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(35,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,41);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(36,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                       glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,42);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(37,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);


                                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,43);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(38,-11,-24);
                               // masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                        glPopMatrix();

                        //------------------------------------------Toys4

                            glPushMatrix();
                                glTranslatef(-65,-14,171);
                                glRotatef(90, 0,1,0);
                               // glScalef(3,3,3);


                                glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,44);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(35,-11,-24);
                                //masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,45);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(36,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                                       glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,46);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(37,-11,-24);
                                masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);


                                                   glPushMatrix();
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D,47);
                               // glRotatef(90, 0,0,1);
                                glScalef(7,6,4);
                                glTranslatef(38,-11,-24);
                               // masala();
                                glPopMatrix();
                                glDisable(GL_TEXTURE_2D);

                        glPopMatrix();
            glPopMatrix();




}

void walldesign(){

           //back
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,28);

    glScalef(120,40,0.2);
    glTranslatef(-1,0,272);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);


                     //back
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,29);

    glScalef(32,40,0.2);
    glTranslatef(-2.5,0,271);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

//------------------------------------------------------
                     //frontPArt
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,32);

    glScalef(35,41,0.2);
    glTranslatef(-1.6,-0.1,-389);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);


                     //front
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,33);

    glScalef(35,41,0.2);
    glTranslatef(-3.3,-0.1,-387);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);




            //fornt_top-----------------------------

                     //front
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,32);

    glScalef(35,41,0.2);
    glTranslatef(-1.6,0.8,-401);
    //cubeT(1,1,1,0.3);
   // cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);


                     //front
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,33);

    glScalef(35,41,0.2);
    glTranslatef(-3.3,0.8,-396);
    //cubeT(1,1,1,0.3);
   // cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);






//----------------------------------------------window

                     //frontWindowLeft bottom
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,34);

    glScalef(25,40,0.2);
    glTranslatef(-2.05,-0.1,-390);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                     //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,34);

    glScalef(25,40,0.2);
    glTranslatef(-1.05,-0.1,-390);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                     //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,34);

    glScalef(25,40,0.2);
    glTranslatef(-0.05,-0.1,-390);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                               //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,34);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-390);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);



    //frontdoor                              //rightWindow

    glPushMatrix();
    //    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,30);

    glScalef(32,40,0.2);
    glTranslatef(-2.6,-0.1,-389);
    //cubeT(1,1,1,0.3);
  //  cubeT(1,1,1,0.3);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);
               //glDisable(GL_BLEND);



               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,34);

    glScalef(25,40,0.2);
    glTranslatef(-4.37,-0.1,-388);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,34);

    glScalef(25,40,0.2);
    glTranslatef(-5.37,-0.1,-388);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,34);

    glScalef(25,40,0.2);
    glTranslatef(-6.37,-0.1,-388);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);


    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,34);

    glScalef(25,40,0.2);
    glTranslatef(-7.37,-0.1,-388);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);



            //----------------------------------------------------------------TopWindows

            glPushMatrix();

               // glTranslatef(0,0.2,0);

                                             //front window
                glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,32);

                glScalef(35,41,0.2);
                glTranslatef(-1.6,0.8,-389);
                //cubeT(1,1,1,0.3);
                cube(1,1,1);
                glPopMatrix();
                        glDisable(GL_TEXTURE_2D);


                                 //front
                glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,33);

                glScalef(35,41,0.2);
                glTranslatef(-3.3,0.8,-387);
                //cubeT(1,1,1,0.3);
                cube(1,1,1);
                glPopMatrix();
                        glDisable(GL_TEXTURE_2D);




                        //fornt_top-----------------------------

                                 //front
                glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,32);

                glScalef(35,41,0.2);
                glTranslatef(-1.6,0.8,-387);
                //cubeT(1,1,1,0.3);
               // cube(1,1,1);
                glPopMatrix();
                        glDisable(GL_TEXTURE_2D);


                                 //front
                glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,33);

                glScalef(35,41,0.2);
                glTranslatef(-3.3,0.8,-384);
                //cubeT(1,1,1,0.3);
               // cube(1,1,1);
                glPopMatrix();
                        glDisable(GL_TEXTURE_2D);






            //----------------------------------------------window

                                 //frontWindowLeft
                glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,34);

                glScalef(25,40,0.2);
                glTranslatef(-2.05,0.85,-390);
                //cubeT(1,1,1,0.3);
                cube(1,1,1);
                glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                                 //frontWin
                glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,34);

                glScalef(25,40,0.2);
                glTranslatef(-1.05,0.85,-390);
                //cubeT(1,1,1,0.3);
                cube(1,1,1);
                glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                                 //frontWin
                glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,34);

                glScalef(25,40,0.2);
                glTranslatef(-0.05,0.85,-390);
                //cubeT(1,1,1,0.3);
                cube(1,1,1);
                glPopMatrix();
                        glDisable(GL_TEXTURE_2D);

                                           //frontWin
                glPushMatrix();
                        glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D,34);

                glScalef(25,40,0.2);
                glTranslatef(0.95,0.85,-390);
                //cubeT(1,1,1,0.3);
                cube(1,1,1);
                glPopMatrix();
                        glDisable(GL_TEXTURE_2D);



                //front                               //rightWindow

               glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,34);

            glScalef(25,40,0.2);
            glTranslatef(-4.37,0.85,-388);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,34);

            glScalef(25,40,0.2);
            glTranslatef(-5.37,0.85,-388);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,34);

            glScalef(25,40,0.2);
            glTranslatef(-6.37,0.85,-388);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);


            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,34);

            glScalef(25,40,0.2);
            glTranslatef(-7.37,0.85,-388);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

//-------------------------------------------------------HouseLeft




            light();
}

void walldesign2(){

                               //frontWinLeft
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,-30);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                                          //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,-5);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                                                    //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,20);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                                                    //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,45);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);


                                                    //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,70);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);
                                                    //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,82);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

//-----------------------------------------leftAlltop

            glPushMatrix();
                   // glTranslatef(0,1,0);
                        //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,-30);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

                                                  //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,-5);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

                                                            //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,20);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

                                                            //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,45);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);


                                                            //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,70);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                                                            //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,82);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);


            glPopMatrix();




            //----------------------------------------------opposite---rightWindow


            glPushMatrix();

            glTranslatef(-233,0,0);


                                           //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,-30);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                                          //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,-5);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                                                    //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,20);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                                                    //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,45);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);


                                                    //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,70);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);
                                                    //frontWin
    glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);
            glTranslatef(129,0,82);

    glRotatef(90,0,1,0);

    glScalef(25,40,0.2);
    glTranslatef(0.95,-0.1,-404);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

//-----------------------------------------leftAlltop

            glPushMatrix();
                   // glTranslatef(0,1,0);
                        //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,-30);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

                                                  //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,-5);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

                                                            //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,20);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            //cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

                                                            //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,45);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);


                                                            //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,70);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);
                                                            //frontWin
            glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,37);
                    glTranslatef(129,0,82);

            glRotatef(90,0,1,0);

            glScalef(25,40,0.2);
            glTranslatef(0.95,0.9,-404);
            //cubeT(1,1,1,0.3);
            cube(1,1,1);
            glPopMatrix();
                    glDisable(GL_TEXTURE_2D);


            glPopMatrix();

            glPopMatrix();












}


void walldesign3(){

                   glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(-7.4,0.9,290);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);


                               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(-7.08,0.9,290);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                   glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(-6.08,0.9,290);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                   glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(-5.08,0.9,290);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                   glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(-4.08,0.9,290);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);


                               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(-3.08,0.9,290);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(-2.08,0.9,290);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(-1.08,0.9,290);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);


                               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(-0.08,0.9,290);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(0.92,0.9,290);
    //cubeT(1,1,1,0.3);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

                               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,37);

    glScalef(25,40,0.2);
    glTranslatef(1.63,0.9,290);
    //cubeT(1,1,1,0.3);
   // cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

}

void stairs(){


glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-25.2,.00,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-24.4,1.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-23.6,2.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-22.8,3.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-22.1,4.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-21.4,5.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-20.6,6.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-19.8,7.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
        glPushMatrix();

     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-19,8.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


        glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-18.2,9.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-17.4,10.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-16.6,11.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-15.8,12.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     glPushMatrix();
     glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glScalef(3.5,3,10);
    glTranslatef(-15,13.0,-.5);
 //glRotatef(-360, 1.0, 1, 1.0);
    //cube(1.5,1,1.7);
    Cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void allfan(){

//column1
    glPushMatrix();
    glTranslatef(12,11,10);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(12,11,-10);
    fan();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(12,11,-60);
    fan();
    glPopMatrix();

    //column2

    glPushMatrix();
    glTranslatef(-24,11,10);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-24,11,-10);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-24,11,-60);
    fan();
    glPopMatrix();

    //column3

    glPushMatrix();
    glTranslatef(-60,11,10);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-60,11,-10);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-60,11,40);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-60,11,-60);
    fan();
    glPopMatrix();

        //column4

    glPushMatrix();
    glTranslatef(-96,11,10);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-96,11,-10);
    fan();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(-96,11,-60);
    fan();
    glPopMatrix();

        //column5

    glPushMatrix();
    glTranslatef(-132,11,10);
    fan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-132,11,-10);
    fan();
    glPopMatrix();


       glPushMatrix();
    glTranslatef(-132,11,-60);
    fan();
    glPopMatrix();


    glPushMatrix();
    glScalef(2,1,1);
    glTranslatef(-10,18,41);
    AC2();
    glPopMatrix();


        glPushMatrix();
    glScalef(2,1,1);
    glTranslatef(-70,18,41);
    AC2();
    glPopMatrix();


    glPushMatrix();
    glScalef(2,1,1);
    glTranslatef(-10,18,-42);
    AC2();
    glPopMatrix();


        glPushMatrix();
    glScalef(2,1,1);
    glTranslatef(-70,18,-42);
    AC2();
    glPopMatrix();


    glPushMatrix();
    glScalef(2,1,1);
    glTranslatef(-10,18,-48);
    AC2();
    glPopMatrix();


        glPushMatrix();
    glScalef(2,1,1);
    glTranslatef(-70,18,-48);
    AC2();
    glPopMatrix();



}


void allQuranReck(){

        glPushMatrix();
    glScalef(1.1,1.0,0.6);
    glTranslatef(-7,0,90);
    glRotatef(-180,0.0,1,0);
    fullreck();
    glPopMatrix();


        glPushMatrix();
    glScalef(1.1,1.0,0.6);
    glTranslatef(-127,0,90);
    glRotatef(-180,0.0,1,0);
    fullreck();
    glPopMatrix();

    //reckitem
        glPushMatrix();
   // glScalef(1.1,1.0,0.6);
   // glTranslatef(-127,0,90);
   // glRotatef(-180,0.0,1,0);
    reckitem();
    glPopMatrix();

       //reckitem
        glPushMatrix();
   // glScalef(1.1,1.0,0.6);
    glTranslatef(-133,0,0);
   // glRotatef(-180,0.0,1,0);
    reckitem();
    glPopMatrix();





}

void allshoe(){
//shoe
//column1Left
        glPushMatrix();
        glTranslatef(42,0.2,25);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        shoeReck();
        glPopMatrix();

                glPushMatrix();
        glTranslatef(42,0.2,-5);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(42,0.2,-30);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(42,0.2,-72);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        shoeReck();
        glPopMatrix();

//----------------------------

//column1Right
        glPushMatrix();
        glTranslatef(-185,0.2,25);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        shoeReck();
        glPopMatrix();

                glPushMatrix();
        glTranslatef(-185,0.2,-5);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-185,0.2,-30);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
       // shoeReck();
        glPopMatrix();

//----------------------------//columnfront


        glPushMatrix();
        glTranslatef(-8,0.2,-30);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
      //  shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-50,0.2,-30);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-108,0.2,-30);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-145,0.2,-30);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
       // shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-185,0.2,-30);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        shoeReck();
        glPopMatrix();


//----------------------------//columnfront2


        glPushMatrix();
        glTranslatef(-8,0.2,-72);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
      //  shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-50,0.2,-72);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        //shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-108,0.2,-72);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
      //  shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-145,0.2,-72);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
       // shoeReck();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-185,0.2,-72);
        glScalef(0.10,0.23,0.10);
        glScalef(0.5,0.7,0.5);
        shoeReck();
        glPopMatrix();



}

void stairTop(){

       //topCloth

                      glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,28);
    glTranslatef(-200,70,0);
    glScalef(2,4,2);
   jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

    //pillar
    float length = 30;
    float width = 0.3;
    glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,28);
    glTranslatef(1,-110,-20);
    glScalef(3,100,3);
    glTranslatef(-80,0.9,10);
   // glScalef(1,100,1);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);

            //pillar2
               glPushMatrix();
                    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,28);
    glTranslatef(1,-110,-20);
    glScalef(3,100,3);
    glTranslatef(-80,0.9,-10);
   // glScalef(1,100,1);
    cube(1,1,1);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);










}

static void res(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / (float)height, 1, 800);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void init(void)
{

glClearColor(0.215686275, 0.450980392, 0.698039216, 1.0);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0, 1200.0, 0, 1200.0);


}




void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glMatrixMode( GL_PROJECTION );
   // glLoadIdentity();
    //gluPerspective(60,1,1,500);
    //gluOrtho2D(60,1,1,100);
   // glMatrixMode( GL_MODELVIEW );
   // glLoadIdentity();

	glFrustum(-3, 3, -3, 3, 2.0, 100.0);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, centerX,centerY,centerZ, 0,1,0);
    glRotatef(rot, 0,1,0);
    floorWallsCeiling(900);



        walldesign();
        walldesign2();
        walldesign3();
        allshoe();
        stairTop();


        glPushMatrix();
        glTranslatef(-85,0,120);
        glRotatef(-90, 0,1,0);
        stairTop();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,39,0);
        allshoe();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(130,-11,0);
        leftHouse();
        glPopMatrix();


//-----------------------------------------------------------------
        allQuranReck();

        glPushMatrix();
        glTranslatef(0,38,0);
        allQuranReck();
        glPopMatrix();


//---------------------------------------------------------------------------------
    allJainamaj();

        glPushMatrix();
        glTranslatef(0,39,0);
            allJainamaj();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-137,-0.5,-17);
        glScalef(1,1,2.3);
            stairs();
        glPopMatrix();



    //emam
    glPushMatrix();
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,24);
        glScalef(0.5,0.5,0.5);
        glTranslatef(-140,03,80);
        fruitesReck();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);


    glPopMatrix();



//imam


    //frontCloth carpet
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,19);
    glTranslatef(-69,0,-95);
    glScalef(0.5,0.3,1);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

//imamHujur Jainamaj
               glPushMatrix();
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,23);
    glTranslatef(-64,0.38,49);
    glScalef(0.3,0.3,0.4);
    jainamaj();
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);






//LargeCarpet

//ground

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,19);
    glTranslatef(-52,-2.2,16);
    glScalef(6.4,1,3.1);
    jainamaj();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //LargeCarpet

    //firstfloor

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,19);
    glTranslatef(-52,36,16);
    glScalef(6.4,1,3.1);
    jainamaj();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ////LargeCarpet

    //frontCeiling

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,19);
    glTranslatef(-52,-12,16);
    glScalef(6.4,35,3.1);
    jainamaj();
   // light();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glPushMatrix();
    //glScalef(1,1.2,1);

    glPushMatrix();
    glTranslatef(-70,70,-5);
    glScalef(60,60,60);
    gumbazz();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-70,70,0);
    glScalef(60,60,60);
    gumbazz2();
    glPopMatrix();

//------------------------------------------------------------------


    allfan();

    glPushMatrix();
    glTranslatef(0,38,0);
    allfan();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-100,10,44);
    clock2();
    glPopMatrix();

    //ground
    glPushMatrix();
    glScalef(1,1,1);
    FullHouse();
    glPopMatrix();

//1st floor
    glPushMatrix();
    glTranslatef(0,38,0);
    FullHouse110();
    glPopMatrix();
    glPopMatrix();
    allFloor();

//---------------------------------------------------------------------
//--------------------------------------------------------------------
//-----------------------------------------------------------------
/*
    glPushMatrix();
    glTranslatef(0,76,0);
    glScalef(1,0.6,1);
    //FullHouse3();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,76,0);
    glScalef(3,0.6,3);
    //FullHouse3();
    glPopMatrix();


    glPushMatrix();
    //topFLoor();
    glPopMatrix();



    glPushMatrix();
   // glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,17);

    // glScalef(2, 0, 2);
     glTranslatef(0,40,0);
    //drawCircle();
		//drawSphere(10);
    // glRotatef(-30,0.0,1,.0);
    glPopMatrix();
   // glDisable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef(-20,-20,-35);
    glScalef(1,3.3,1);
    glRotatef(90.0, 0.0, 1.0, 0.0);  // Adjust the angle as needed
  //  windows();
    glPopMatrix();


    glPushMatrix();
    //road();
    glPopMatrix();

    //allWearDrop();

    glPushMatrix();
    glTranslatef(0,0,0);
   // tree2();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(5,0,-70);
    glScalef(2,2,2);
    glRotatef(-90.0, 0.0, 1.0, 0.0);  // Adjust the angle as needed
 //   full_set();
    glPopMatrix();




    glPushMatrix();
   // leftHouse();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
        glTranslatef(70,0,0);
        //leftHouse2();
        glPopMatrix();
       // All_leftTop();
    glPopMatrix();


    glPushMatrix();
        glPushMatrix();
        glTranslatef(-160,0,0);
       // rightHouse2();
        glPopMatrix();
        glTranslatef(-230,0,0);
        //All_rightTop();
    glPopMatrix();


    glPushMatrix();
    glScalef(0.8,1,0.8);
    glTranslatef(-5,20,-30);
   // topDesign();
    glPopMatrix();

*/


    glFlush();
    glutSwapBuffers();
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//DO NOT TOUCH!!!!


void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


static void key(unsigned char key, int x, int y);

float l_val=.1;

static void light14(unsigned char light1, int x, int y)
{

    switch (light1)
    {

    case 27:
        glutKeyboardFunc(key);
        break;
    case '1':
        al1+=l_val;
        break;
    case '2':
        al1-=l_val;
        break;
    case '3':
        dl1+=l_val;
        break;
    case '4':
        dl1-=l_val;
        break;
    case '5':
        sl1+=l_val;
        break;
    case '6':
        sl1-=l_val;
        break;
    }
reaF:
    return;
}

static void light24(unsigned char light2, int x, int y)
{
    switch (light2)
    {

    case 27:
        glutKeyboardFunc(key);

        break;
    case '1':
        al2+=l_val;
        break;
    case '2':
        al2-=l_val;
        break;
    case '3':
        dl2+=l_val;
        break;
    case '4':
        dl2-=l_val;
        break;
    case '5':
        sl2+=l_val;
        break;
    case '6':
        sl2-=l_val;
        break;
    }
}

static void spot_light14(unsigned char spot_light, int x, int y)
{
    switch (spot_light)
    {

    case 27:

        glutKeyboardFunc(key);
        break;
    case '1':
        al3+=l_val;
        break;
    case '2':
        al3-=l_val;
        break;
    case '3':
        dl3+=l_val;
        break;
    case '4':
        dl3-=l_val;
        break;
    case '5':
        sl3+=l_val;
        break;
    case '6':
        sl3-=l_val;
        break;
    }
}

/*void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
            glTranslatef(5.0, 0.0, 0.0);
            break;

        case 'd':
        case 'D':
            glTranslatef(-5.0, 0.0, 0.0);
            break;

        case 'w':
        case 'W':
            glTranslatef(0.0, 0.0, 5.0);
            break;

        case 's':
        case 'S':
            glTranslatef(0.0, 0.0, -5.0);
            break;

        case 't':
        case 'T':
            if (is_depth)
            {
                is_depth = 0;
                glDisable(GL_DEPTH_TEST);
            }
            else
            {
                is_depth = 1;
                glEnable(GL_DEPTH_TEST);
            }

        #Fall-through...
        case 'o':
        case 'O':
            door_Xpos += 90.0;
            break;
    }
    display();
}*/
static void key(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 27:
        exit(0);
        break;
    case '+':
        eyeZ++;
        //eyeY++;
        break;
    case '-':
        eyeZ--;
        // eyeY--;
        break;

    case 'a':
        eyeX++;

        //eyeY++;
        break;
    case 's':
        eyeX--;
        // eyeY--;
        break;

    case 'g':
        eyeY++;
        //eyeY++;
        break;
    case 'h':
        eyeY--;
        // eyeY--;
        break;

    case 'w':
        //centerX++;
        centerY++;
        //  centerZ++;
        break;
    case 'e':
        //  centerX--;
        centerY--;
        //  centerZ--;
        break;

    case 'o':
        centerX++;

        //centerY++;
        //  centerZ++;
        break;
    case 'p':
        centerX--;
        //centerY--;
        //  centerZ--;
        break;

    case 'k':
        centerZ++;
        //centerY++;
        //  centerZ++;
        break;
    case 'l':
        centerZ--;
        //centerY--;
        //  centerZ--;
        break;


    case ',':
        rot++;
        break;
    case '.':
        rot--;
        break;

    case '*':
        stop=0;
        break;

    case ';':
        angle=0,stop=1,k=0;
        break;

    case '1':
        l_height+=.1;
        break;
    case '2':
        l_height-=.1;
        break;

    case '3':
        spt_cutoff++;
        break;
    case '4':
        spt_cutoff--;
        break;
    case 't':
        l_on1=1-l_on1;
        break;

    case 'u':
        l_on2=1-l_on2;
        break;

    case 'y':
        l_on3=1-l_on3;
        break;
    case 'd':
        markdoor=1-markdoor;
        break;
    case 'b':
        glutKeyboardFunc(light14);
        break;
    case 'n':
        glutKeyboardFunc(light24);
        break;
    case 'm':
        glutKeyboardFunc(spot_light14);
        break;

    }
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
    spin();
}


/*void init(void)
{

glClearColor(0.215686275, 0.450980392, 0.698039216, 1.0);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0, 1200.0, 0, 1200.0);


}*/
/*void init(void)
{
    glClearColor(0.0, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}*/

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(100,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("test");
    glutReshapeFunc(res);
    glutDisplayFunc(display);

    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    LoadTexture("F:\\Mosque\\bmp\\b.bmp"); //1
    LoadTexture("F:\\Mosque\\bmp\\paint1.bmp");//2
    LoadTexture("F:\\Mosque\\bmp\\blue.bmp");//3
    LoadTexture("F:\\Mosque\\bmp\\sky2.bmp");//4
    LoadTexture("F:\\Mosque\\bmp\\grass2.bmp");//5
    LoadTexture("F:\\Mosque\\bmp\\table2.bmp");//6
    LoadTexture("F:\\Mosque\\bmp\\logo.bmp");//7
    LoadTexture("F:\\Mosque\\bmp\\black.bmp");//8
    LoadTexture("F:\\Mosque\\bmp\\superShop.bmp");//9
    LoadTexture("F:\\Mosque\\bmp\\green2.bmp");//10
    LoadTexture("F:\\Mosque\\bmp\\darkBrown.bmp");//11
    LoadTexture("F:\\Mosque\\bmp\\wall.bmp");//12
    LoadTexture("F:\\Mosque\\bmp\\bottle2.bmp");//13
    LoadTexture("F:\\Mosque\\bmp\\white.bmp");//14
    LoadTexture("F:\\Mosque\\bmp\\floor2.bmp");//15
    LoadTexture("F:\\Mosque\\bmp\\wall.bmp");//16
    LoadTexture("F:\\Mosque\\bmp\\apple.bmp");//17
    LoadTexture("F:\\Mosque\\bmp\\ceiling8.bmp");//18

//-----------------------------------------------------------------

    LoadTexture("F:\\Mosque\\bmp\\m_wall.bmp");//19
    LoadTexture("F:\\Mosque\\bmp\\m_door_carpet.bmp");//20
    LoadTexture("F:\\Mosque\\bmp\\m_jainamaj.bmp");//21
    LoadTexture("F:\\Mosque\\bmp\\m_jainamaj2.bmp");//22
    LoadTexture("F:\\Mosque\\bmp\\m_jainamaj3.bmp");//23
    LoadTexture("F:\\Mosque\\bmp\\m_cloth3.bmp");//24
    LoadTexture("F:\\Mosque\\bmp\\m_cloth2.bmp");//25
    LoadTexture("F:\\Mosque\\bmp\\m_cloth.bmp");//26
    LoadTexture("F:\\Mosque\\bmp\\m_backWall2.bmp");//27
    LoadTexture("F:\\Mosque\\bmp\\m_backWall3.bmp");//28
    LoadTexture("F:\\Mosque\\bmp\\m_backWall2.bmp");//29
    LoadTexture("F:\\Mosque\\bmp\\m_front2.bmp");//30
    LoadTexture("F:\\Mosque\\bmp\\m_up2.bmp");//31
    LoadTexture("F:\\Mosque\\bmp\\m_left2.bmp");//32
    LoadTexture("F:\\Mosque\\bmp\\m_right2.bmp");//33
    LoadTexture("F:\\Mosque\\bmp\\m_win.bmp");//34
    LoadTexture("F:\\Mosque\\bmp\\m_gumbaz.bmp");//35
    LoadTexture("F:\\Mosque\\bmp\\m_leftWall2.bmp");//36
    LoadTexture("F:\\Mosque\\bmp\\m_win2.bmp");//37
    LoadTexture("F:\\Mosque\\bmp\\book.bmp");//38
    LoadTexture("F:\\Mosque\\bmp\\book1.bmp");//39
    LoadTexture("F:\\Mosque\\bmp\\book2.bmp");//40
    LoadTexture("F:\\Mosque\\bmp\\book3.bmp");//41
    LoadTexture("F:\\Mosque\\bmp\\book4.bmp");//42
    LoadTexture("F:\\Mosque\\bmp\\book5.bmp");//43
    LoadTexture("F:\\Mosque\\bmp\\book6.bmp");//44
    LoadTexture("F:\\Mosque\\bmp\\book7.bmp");//45
    LoadTexture("F:\\Mosque\\bmp\\book8.bmp");//46
    LoadTexture("F:\\Mosque\\bmp\\book9.bmp");//47
    LoadTexture("F:\\Mosque\\bmp\\book10.bmp");//48
    LoadTexture("F:\\Mosque\\bmp\\book5.bmp");//49
    LoadTexture("F:\\Mosque\\bmp\\top.bmp");//50
    LoadTexture("F:\\Mosque\\bmp\\ceiling6.bmp");//51
    LoadTexture("F:\\Mosque\\bmp\\m_roomWallBack.bmp");//52
    LoadTexture("F:\\Mosque\\bmp\\m_baranda.bmp");//53
    LoadTexture("F:\\Mosque\\bmp\\m_water.bmp");//54
    LoadTexture("F:\\Mosque\\bmp\\water.bmp");//55
    LoadTexture("F:\\Mosque\\bmp\\shoe.bmp");//56
    LoadTexture("F:\\Mosque\\bmp\\reck.bmp");//57







    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);

    glEnable(GL_LIGHTING);
    GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
    int t=1;
    printf("Warning!!! please turn off caps lock and use shift key before * key and + key.\n");
    printf("%d. Press 't' for off light1.\n",t++);
    printf("%d. Press 'y' for off light2.\n",t++);
    printf("%d. Press 'u' for off cse light.\n",t++);

    printf("%d. Press '*' for stop fans.\n",t++);
    printf("%d. Press ';' for start fans.\n",t++);
    printf("%d. Press 'd' for window open/close.\n",t++);
    printf("%d. Press 'w' for up.\n%d. press 'e' for down.\n%d. press 's' for right.\n%d. press 'a' for left.\n",t+1,t+2,t+3,t+4);
    t+=4;
    printf("%d. Press 'o' to move camera left.\n%d. Press 'p' to move camera right.\n",t+1,t+2);
    t+=2;
    printf("%d. Press '+' to zoom in.\n%d. Press '-' for zoom out.\n",t+1,t+2);
    t+=2;
    printf("%d. Press b,n,m for operate with light1,light2 and CSE light respectively.\n",t++);
    printf("   1. Press '1' for add ambient.\n");
    printf("   2. Press '2' for reduce ambient.\n");
    printf("   3. Press '3' for add diffuse.\n");
    printf("   4. Press '4' for reduce diffuse.\n");

    printf("   5. Press '5' for add specular light.\n");
    printf("   6. Press '6' for reduce specular light.\n");
    printf("   7. Press ESC key for exit this operation and goto main programme\n");

    printf("%d. Press ESC key for exit the main programme\n",t++);

    init();
    glutMainLoop();


    return 0;
}
