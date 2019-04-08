/*
 * CS4815 - Computer Graphics
 *
 * spin.cc - skeleton file for week 04 assignment.
 */


#include <math.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



#define WINDOW_WIDTH        512
#define WINDOW_HEIGHT       512
#define WINDOW_CAPTION      "CS4815: Week 04"
#define DIRECTON 1
#define SPEED 2
#define QUIT 3
#define REVERSE 4
#define	CLOCKWISE 5
#define	ANTICLOCKWISE 6
#define	HALF 7
#define DOUBLE 8



/*
 * Globals
 */
int timer = 0;
float angle = 0;
int rotate = 0;
float speed = 0.090f;
int clockwise = 0;

void idle(void);


/**
 * Return number of timer ticks (miliseconds).
 */
int
get_ticks()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        return 0;

    return tv.tv_sec * 1000 + (tv.tv_usec / 1000);
}

    
/**
 * Initialise OpenGL state variables.
 */
void
init_gl()
{
    /* Set the background color to be light blue.  */
    glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
}


/**
 * Re-display callback funcion.
 *
 * This function is called when contents of the window need to be
 * repainted.
 */
void
display(void)
{
    int dt;

    /* Clear the colour buffer.  */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Update timer value and calulate time elapsed from the last frame.
     * Limit delta time to maximum of one second.
     */
    dt = get_ticks() - timer;
    timer += dt;
    if (dt < 0) dt = 0;
    if (dt > 1000) dt = 1000;
    
    /* Calucate rotation (if enabled).  */
    if (rotate) {
        angle += speed * ((float) dt); /* 15 RPM */
        if (angle >  360.0f) angle -= 360.0f;
    }

    glPushMatrix();
    /* Rotate rectangle.  */
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    /* Draw rectangles.  */
    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

    float w = 1.0/20;
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(-0.5f, 0.5f-w, -0.5f+w, 0.5f);

    glPopMatrix();


    /* Display contents of the back buffer (the draw buffer).  */
    glutSwapBuffers();
}


/**
 * Window resize callback function.
 *
 * This function is called when application window is resized.
 */
void
reshape(int width, int height)
{
    /* Update the viewport area to occupy the entire window.  */
    glViewport(0, 0, width, height);


    /* Refresh the screen contents.  */
    glutPostRedisplay();
}


/**
 * Keyboard callback function.
 *
 * This function is called when a key is pressed/released.
 */
void
keyboard(unsigned char key, int x, int y)
{
}


/**
 * Special key callback function.
 *
 * This function is called when a special key is pressed/released.
 * Special keys include: SHIFT, ALT ...
 */
void
special(int key, int x, int y)
{
}


/**
 * Mouse button callback function.
 *
 * This function is called when a mouse button is pressed/releassed.
 */
void
mouse(int button, int state, int x, int y)
{
    /* Left button starts rotatation.  */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        timer = get_ticks();
        glutIdleFunc(idle); /* Start updating the screen.  */
        rotate = 1; /* Start rotation.  */
    }
    /* Middle button stops rotation.  */
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        rotate = 0; /* Stop updating angle value.  */
        glutIdleFunc(NULL); /* Stop updating the screen.  */
    }

}


/**
 * Mouse motion callback function. 
 *
 * This function is called when mouse is moved (passive) and one of the
 * buttons is pressed (normal).
 */
void
motion(int x, int y)
{
}

void processMenuEvents(int option) {

	switch (option) {
	case QUIT: exit(0); break;
	case REVERSE: speed = speed*-1; break;
	case CLOCKWISE: if(speed>0)
	  {
	    speed = speed*-1;
	  }
	  break;
	case ANTICLOCKWISE: if(speed<0)
	    {
	      speed = speed*-1;
	    }
	  break;
	case HALF: speed = speed*0.5;break;
        case DOUBLE: speed = speed*2;break;
	}
}

void createGLUTMenus() {

  int menu, direction, speed;

	direction = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Reverse",REVERSE);
	glutAddMenuEntry("Clockwise",CLOCKWISE);
	glutAddMenuEntry("Anti-Clockwise",ANTICLOCKWISE);

	speed = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Half",HALF);
	glutAddMenuEntry("Double",DOUBLE);

        menu = glutCreateMenu(processMenuEvents);
	glutAddSubMenu("Direction",direction);
        glutAddSubMenu("Speed",speed);
	glutAddMenuEntry("Quit",QUIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

/**
 * Idle callback function.
 *
 * This function is called when the program is idle (nothing to do).
 */
void
idle(void)
{
    /* Redraw the screen.  */
    glutPostRedisplay();
}


/** 
 * `main' function is every C program entry point.
 *
 * This is where the execution starts.
 */
int
main(int argc, char *argv[])
{
    /* Initialise the GLUT library.  */
    glutInit(&argc, argv);

    /* Specify bufffer format, double buffered RGBA.  */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    /* Create an OpenGL capable window. This also initialises OpenGL
     * context.
     *
     * NOTE: You are not allowed to call any OpenGL function prior to
     * the window creation!
     */
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_CAPTION);


    /* Initialise application state.  */
    init_gl();

    /* Register callback functions. Callback functions are called by
     * GLUT in response to various events.
     */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    /* glutSpecialFunc(special); */
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    /* glutPassiveMotionFunc(motion); */
    /* glutIdleFunc(idle); */

    /* Enter the event processing loop. All the mouse, keyboard, screen
     * events will be processed and dispatchted to earlier registered
     * callback functions.
     */
    createGLUTMenus();
    glutMainLoop();
    return EXIT_SUCCESS;
}

/* vi:set tw=72 sw=4 ts=4 et: */