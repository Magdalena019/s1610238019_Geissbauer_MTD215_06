#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <time.h>
#include <math.h>
#include <iostream>
// #include <windows.h>

float move = 0.0f;
float first = 0.0f;
float second = 0.0f;
float bucket = 0.0f;

float preX = 0.0f;
float rotation = 0.0f;

//ROTATION_SPEED1 and ROTATION_SPEED2 can be used to change the rotation speed of the two small outer spheres
#define ROTATION_SPEED1 -150.0
#define ROTATION_SPEED2 -300.0

//materialSpecular and materialShininess can be used to change the initial settings of the light source
static const GLfloat materialSpecular[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat materialShininess = 20.0;

static const GLfloat materialAmbient[] = {0.0, 0.0, 0.0, 0.0};
static const GLfloat materialDiffuse = 0.0;

//the following colors can be used to set either the ambient or diffuse material color
static const GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
static const GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
static const GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};
static const GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat darkGray[] = {0.05, 0.05, 0.05, 1.0};
static const GLfloat black[] = {0.0, 0.0, 0.0, 1.0};

//use scenePosition to change the observers initial position in the scene
static const GLfloat scenePosition[] = {0.0, 0.0, -10.0};

//the rotationMatrix should be used to manipulate the observers actual rotated position
static GLdouble rotationMatrix[] = {1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0};

//use lightPosition to change the light position in the scene
static GLfloat lightPosition[] = {1.0, 1.0, 1.0, 0.0};

//pause is used to stop or resume the animation
static int pause = 1;

//observerSystem defines if the light source is relative to the obeserver coordinate system or the sphere coordinate system
static int observerSystem = 0;

//scene rotation parameters
static GLfloat angleX = 30; 
static GLfloat angleY = -150; 
static int moving, startx, starty;

//window size parameters
static int windowWidth = 320;
static int windowHeight = 240;

// rotates everything
void onMotion(int x, int y) {
    if (fabs(x - preX))    {
        rotation = ((x - preX) > 0) ? rotation += 10.0 * 0.11 : rotation -= 10.0 * 0.11;
    }
    
    preX = x;
    glutPostRedisplay();
}

// mouse input with left button pressed
void onMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        preX = x;
        glutMotionFunc(onMotion);
    }
}

void description()
{
    std::cout << "You move the excavot in one direction. --> m" << std::endl;
    std::cout << "You move up the first arm. --> f" << std::endl;
    std::cout << "You move the first arm down --> F" << std::endl;
    std::cout << "You move up the second arm. --> s" << std::endl;
    std::cout << "You move the wirst second down --> S" << std::endl;
    std::cout << "You open the bucket --> o" << std::endl;
    std::cout << "You clorse the bucket --> c" << std::endl;
}

// EXCAVATOR - PARTS
// -----------------------------------------

// ----- drawing the arm combined with the spheres -----
void createArmWithSphere()
{
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.0);
    glScaled(3.0, 1, 1);
    glutSolidCube(1);
    //glutWireCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); // TODO: Change color
    glTranslatef(-1.5, 0, 0);
    glutSolidSphere(0.8, 10, 10);
    //glutWireSphere(0.8, 10, 10);
    glPopMatrix();
    
}

void createBucket()
{
    glPushMatrix();
    glTranslatef(-0.6, -0.1, 0);
    glScaled(1.1, 0.7, 1.3);
    glutSolidCube(2);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(-1.7, -0.4, 0);
    glScaled(0.07, 1, 1.5);
    glutSolidCube(2);
    glPopMatrix();
}

void createExcavatorArmAndBucket () {
    glPushMatrix();
    glRotatef(-45, 0, 0, 1);
    
    createArmWithSphere();
    glTranslatef(-1.5, 0, 0);
    glRotatef(first, 0, 0, 1);
    glTranslatef(1.5, 0, 0);
    
    glTranslatef(-1.5, 0, 0);
    glRotatef(40, 0, 0, 1);
    glTranslatef(-1.5, 0, 0);
    
    createArmWithSphere();
    glTranslatef(-1.5, 0, 0);
    glRotatef(second, 0, 0, 1);
    glTranslatef(1.5, 0, 0);
    
    glTranslatef(-1.5, 0, 0);
    glRotatef(80, 0, 0, 1);
    glTranslatef(-1.5, 0, 0);
    
    createArmWithSphere();
    glTranslatef(-1.5, 0, 0);
    glRotatef(bucket, 0, 0, 1);
    glTranslatef(1.5, 0, 0);
    
    glColor3f(0.9, 0.9, 0.0);
    glTranslatef(-1.3, 0, 0);
    glRotatef(90, 0, 0, 1);
    glTranslatef(-0.4, 0.6, 0);
    createBucket();
    
    glPopMatrix();
}

void createExcavatorCabin()
{
    glPushMatrix();
    glTranslatef(5, 1, 2);
    glScaled(1, 1.3, 1);
    glutSolidCube(2);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(0.1, -0.9, 2);
    glScaled(0.8, 1, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(3, -0.8, 2);
    glScaled(1.3, 0.5, 1);
    glutSolidCube(4);
    glPopMatrix();
    
    
    glTranslatef(1, -1.5, -2);
    
    
}

void createWheels()
{
    glPushMatrix();
    glScaled(1.2, 1.2, 0.5);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();
}


void drawExcavator()
{
    glTranslatef(-3, 1, -16);
    
    createExcavatorArmAndBucket();

    
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(1, -2, -3);
    createWheels();
    glTranslatef(5.5, 0, 0);
    createWheels();
    glPopMatrix();
    
    glColor3f(0.9, 0.9, 0.0);
    glTranslatef(1, -0.35, 0);
    createExcavatorCabin();
    
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0, -1, -1);
    createWheels();
    glTranslatef(5.5, 0, 0);
    createWheels();
    glPopMatrix();
    
}

void drawSurface()
{
    glPushMatrix();
    glColor3f(0.2, 0.2, 0.2);
    glTranslatef(0, -2, -15);
    glScaled(25, 0.1, 10);
    glutSolidCube(1);
    
    glPopMatrix();
}


static void init(void) 
{
    //select clearing color (color that is used as 'background')
	glClearColor (0.0, 0.0, 0.0, 0.0);
    
    
	glShadeModel (GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
    glMaterialf(GL_FRONT_AND_BACK, GL_DIFFUSE, green[3]);
    
     
    //initialize view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float width = glutGet(GLUT_WINDOW_WIDTH);
    float height = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(65, width/height, 0.1, 60);
    
    //set matrix-mode back to model-view for rendering
    glMatrixMode(GL_MODELVIEW);
    
}

//renders a sphere with the given radius at the specified position
static void renderSphere(double radius, double x, double y, double z) 
{
	glPushMatrix();
		glTranslated(x, y, z);
		glutSolidSphere(radius, 20, 16);
	glPopMatrix();
}

//helper function to set materials (diffuse and ambient color) in a little bit "nicer" way
void setMaterial(const GLfloat *materialDiffuse, const GLfloat *materialAmbient)
{
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
}

//renders the whole scene conatining three spheres (two small and one larger sphere)
static void display(void) 
{
    // | GL_DEPTH_BUFFER_BIT
	glClear (GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
    
    glColor3f(1.0, 1.0, 1.0);
    
    glRotatef(rotation, 0, 1, 0);

    drawSurface();
    
	// glTranslated(scenePosition[0], scenePosition[1], scenePosition[2]);

    /*
	renderSphere(1.0, 0, 0, 0.0);
	renderSphere(0.5, -3, 0.0, 0.0);
	renderSphere(0.5, 0, 2, 0.0);
     */
    
    glTranslatef(move, 0, 0);
    drawExcavator();
    
    glFlush();

	//glutSwapBuffers();
}

static void reshape (int w, int h) 
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, ((GLdouble)w) / ((GLdouble)h), 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void keyboard(unsigned char key, int x, int y) 
{
	switch (key) 
	{
		case 27:
			exit(0);
			break;
            
        case 'm':
            move -= 0.3;
            break;
        
        case 'M':
            move += 0.3;
            break;
            
        case 'h':
            description();
            break;
            
        case 'f':
            if (first > -60) // collision avoidance
            {
                first -= 10;
            }
            break;
            
        case 'F':
            if (first < 40) // collision avoidance
            {
                first += 10;
            }
            break;
            
        case 's':
            if (second > -80) // collision avoidance
            {
                second -= 10;
            }
            break;
            
        case 'S':
            if (second < 50) // collision avoidance
            {
                second += 10;
            }
            break;
            
        case 'o':
            if (bucket < 20) // collision avoidance
            {
                bucket += 10;
            }
            break;
            
        case 'c':
            if (bucket > -120) // collision avoidance
            {
                bucket -= 10;
            }
            break;
        
        case 'L' :
            // switch between observer and scene coordinate system for the light source
            
            break;
        case '1':
            // change velocity of animation, duration 1 sec
            break;
        case '2':
            // change velocity of animation, duration 2 sec
            break;
            
        case '3':
            // change velocity of animation, duration 3 sec
            break;
        
        case '4':
            // change velocity of animation, duration 4 sec
            break;
        
        case '5':
            // change velocity of animation, duration 5 sec
            break;
        
            
    }
    
    glutPostRedisplay();
	}


int main(int argc, char** argv) 
{
	glutInit(&argc, argv);

	//init display mode (double buffer, RGB, z-buffer support)
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    /*
	//initialize window
	glutInitWindowSize(windowWidth, windowHeight); 
	glutCreateWindow("LightExample");
	init();
     */
    
    //initialize window size and position. open window
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("OpenGL - CGR");
    
    //call initialization routine
    init();

	//register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
