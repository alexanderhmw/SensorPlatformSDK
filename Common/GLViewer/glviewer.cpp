#include "glviewer.h"

#define GL_PI 3.1415926535897932384626433832795

GLviewer::GLviewer(QWidget *parent) :
    QGLWidget(parent)
{
    parameters.viewAngle=60;
    parameters.viewheight=50;
    parameters.minView=0.001;
    parameters.maxView=1000;
    parameters.width=0;
    parameters.height=0;
    parameters.background=Eigen::Vector4d(0,0,0,1);
    parameters.transform.setIdentity();
    parameters.tspeed=10;
    parameters.rspeed=1;
    parameters.pointsize=1;
    bperspective=1;
    setMouseTracking(1);
}

GLviewer::~GLviewer()
{
    makeCurrent();
    int i,n=displaylist.size();
    for(i=0;i<n;i++)
    {
        glDeleteLists(displaylist[i].listid,1);
    }
    displaylist.clear();
}


void GLviewer::initializeGL()
{
    glShadeModel(GL_FLAT);
    glClearColor(parameters.background(0),parameters.background(1),parameters.background(2),parameters.background(3));
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    return;
}

void GLviewer::paintGL()
{
    makeCurrent();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(parameters.background(0),parameters.background(1),parameters.background(2),0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    Eigen::Vector4d eye=parameters.transform*Eigen::Vector4d(0,0,0,1);
    Eigen::Vector4d center=parameters.transform*Eigen::Vector4d(0,0,-1,1);
    Eigen::Vector4d up=parameters.transform*Eigen::Vector4d(0,1,0,0);
    gluLookAt(eye(0),eye(1),eye(2),center(0),center(1),center(2),up(0),up(1),up(2));
	glPushMatrix();
    int i,n=displaylist.size();
    glPointSize(parameters.pointsize);
    for(i=0;i<n;i++)
    {
        if(displaylist[i].show)
        {
			glPushMatrix();
			glTranslated(displaylist[i].T[0],displaylist[i].T[1],displaylist[i].T[2]);
			glRotated(displaylist[i].R[2],0,0,1);
			glRotated(displaylist[i].R[1],0,1,0);
			glRotated(displaylist[i].R[0],1,0,0);
			glScaled(displaylist[i].S[0],displaylist[i].S[1],displaylist[i].S[2]);
            glCallList(displaylist[i].listid);
			glPopMatrix();
        }
    }
    glBegin(GL_LINES);
    glColor4d(1,0,0,1);
    glVertex3d(0,0,0);glVertex3d(1,0,0);
    glColor4d(0,1,0,1);
    glVertex3d(0,0,0);glVertex3d(0,1,0);
    glColor4d(0,0,1,1);
    glVertex3d(0,0,0);glVertex3d(0,0,1);
    glEnd();
    return;
}

void GLviewer::setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(bperspective)
    {
        gluPerspective((GLdouble)parameters.viewAngle,(GLfloat)parameters.width/(GLfloat)parameters.height,(GLdouble) parameters.minView,(GLdouble) parameters.maxView);
    }
    else
    {
        double viewheight=parameters.viewheight;
        double viewwidth=viewheight*(double)parameters.width/(double)parameters.height;
        glOrtho((GLdouble)-viewwidth/2.0,(GLdouble)viewwidth/2.0,(GLdouble)-viewheight/2.0,(GLdouble)viewheight/2.0,parameters.minView,parameters.maxView);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return;
}

void GLviewer::resizeGL(int width, int height)
{
    makeCurrent();
    if(height==0)
    {
        height=1;
    }
    parameters.width=width;
    parameters.height=height;
    glViewport(0,0,(GLint)parameters.width,(GLint)parameters.height);
    setProjection();
    return;
}

void GLviewer::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        {
            parameters.transform.col(3)=parameters.transform*Eigen::Vector4d(0,0,-parameters.tspeed,1);
        }
        break;
    case Qt::Key_Down:
        {
            parameters.transform.col(3)=parameters.transform*Eigen::Vector4d(0,0,parameters.tspeed,1);
        }
        break;
    case Qt::Key_Left:
        {
            parameters.transform.col(3)=parameters.transform*Eigen::Vector4d(-parameters.tspeed,0,0,1);
        }
        break;
    case Qt::Key_Right:
        {
            parameters.transform.col(3)=parameters.transform*Eigen::Vector4d(parameters.tspeed,0,0,1);
        }
        break;
    case Qt::Key_PageUp:
        {
            parameters.transform.col(3)=parameters.transform*Eigen::Vector4d(0,parameters.tspeed,0,1);
        }
        break;
    case Qt::Key_PageDown:
        {
            parameters.transform.col(3)=parameters.transform*Eigen::Vector4d(0,-parameters.tspeed,0,1);
        }
        break;
    case Qt::Key_W://w
        {
            parameters.transform.block<3,3>(0,0)=parameters.transform.block<3,3>(0,0)*Eigen::AngleAxisd(parameters.rspeed*GL_PI/180.0,Eigen::Vector3d::UnitX());
        }
        break;
    case Qt::Key_S://s
        {
            parameters.transform.block<3,3>(0,0)=parameters.transform.block<3,3>(0,0)*Eigen::AngleAxisd(-parameters.rspeed*GL_PI/180.0,Eigen::Vector3d::UnitX());
        }
        break;
    case Qt::Key_A://a
        {
            parameters.transform.block<3,3>(0,0)=parameters.transform.block<3,3>(0,0)*Eigen::AngleAxisd(parameters.rspeed*GL_PI/180.0,Eigen::Vector3d::UnitY());
        }
        break;
    case Qt::Key_D://d
        {
            parameters.transform.block<3,3>(0,0)=parameters.transform.block<3,3>(0,0)*Eigen::AngleAxisd(-parameters.rspeed*GL_PI/180.0,Eigen::Vector3d::UnitY());
        }
        break;
    case Qt::Key_Q://q
        {
            parameters.transform.block<3,3>(0,0)=parameters.transform.block<3,3>(0,0)*Eigen::AngleAxisd(parameters.rspeed*GL_PI/180.0,Eigen::Vector3d::UnitZ());
        }
        break;
    case Qt::Key_E://e
        {
            parameters.transform.block<3,3>(0,0)=parameters.transform.block<3,3>(0,0)*Eigen::AngleAxisd(-parameters.rspeed*GL_PI/180.0,Eigen::Vector3d::UnitZ());
        }
        break;
    case Qt::Key_Home:
        {
            parameters.transform.setIdentity();
        }
        break;
    case Qt::Key_1:
        {
            bperspective=1;
            setProjection();
        }
        break;
    case Qt::Key_2:
        {
            bperspective=0;
            setProjection();
        }
        break;
    case Qt::Key_Equal:
        {
            if(bperspective)
            {
                parameters.viewAngle+=1;
            }
            else
            {
                parameters.viewheight+=1;
            }
            setProjection();
        }
        break;
    case Qt::Key_Minus:
        {
            if(bperspective)
            {
                parameters.viewAngle-=1;
            }
            else
            {
                parameters.viewheight-=1;
            }
            setProjection();
        }
        break;
    case Qt::Key_Period:
        {
            if(bperspective)
            {
                parameters.viewAngle+=10;
            }
            else
            {
                parameters.viewheight+=10;
            }
            setProjection();
        }
        break;
    case Qt::Key_Comma:
        {
            if(bperspective)
            {
                parameters.viewAngle-=10;
            }
            else
            {
                parameters.viewheight-=10;
            }
            setProjection();
        }
        break;
    case Qt::Key_B:
        {
            QColor color(parameters.background(0)*255,parameters.background(1)*255,parameters.background(2)*255,parameters.background(3)*255);
            color=QColorDialog::getColor(color,this);
            if(color.isValid())
            {
                parameters.background(0)=color.red()/255.0;
                parameters.background(1)=color.green()/255.0;
                parameters.background(2)=color.blue()/255.0;
                parameters.background(3)=color.alpha()/255.0;
            }
         }
        break;
    case Qt::Key_O:
        {
               parameters.pointsize--;
               if(parameters.pointsize<1)
               {
                   parameters.pointsize=1;
               }
        }
        break;
    case Qt::Key_P:
        {
            parameters.pointsize++;
        }
        break;
    }
    update();
    return;
}

void GLviewer::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    Eigen::Vector3d eye=parameters.transform.block<3,1>(0,3);
    emit mousePosition(event->x(),event->y(),eye,parameters.minView,parameters.maxView,event);
    return;
}

void GLviewer::wheelEvent(QWheelEvent * event)
{
    int numdegrees=event->delta()/8;
    int numsteps=numdegrees/15;
    parameters.tspeed*=pow(2.0,(double)numsteps);
    if(parameters.tspeed>10)
    {
        parameters.tspeed=10;
    }
    else if(parameters.tspeed<0.01)
    {
        parameters.tspeed=0.01;
    }
}

void GLviewer::mouseMoveEvent(QMouseEvent *event)
{
    Eigen::Vector3d eye=parameters.transform.block<3,1>(0,3);
    emit mousePosition(event->x(),event->y(),eye,parameters.minView,parameters.maxView,event);
    return;
}

void GLviewer::addDisplayList(GLuint listid)
{
    if(listid<0)
    {
        return;
    }
    else
    {
        DISPLAYLIST templist;
        templist.listid=listid;
        templist.show=1;
		templist.R[0]=templist.R[1]=templist.R[2]=0;
		templist.T[0]=templist.T[1]=templist.T[2]=0;
		templist.S[0]=templist.S[1]=templist.S[2]=1;
        displaylist.push_back(templist);
    }
    return;
}

void GLviewer::addDisplayLists(std::vector<GLuint> &listids)
{
    makeCurrent();
    int i,n=listids.size();
    for(i=0;i<n;i++)
    {
        listids[i]=glGenLists(1);
        DISPLAYLIST list;
        list.listid=listids[i];
        list.show=1;
        displaylist.push_back(list);
    }
    return;
}

void GLviewer::enableShow(GLuint listid, bool show, bool islistid)
{
    if(islistid)
    {
        int i;
        int n=displaylist.size();
        for(i=0;i<n;i++)
        {
            if(displaylist[i].listid==listid)
            {
                displaylist[i].show=show;
                break;
            }
        }
    }
    else
    {
        displaylist[listid].show=show;
    }
    return;
}

void GLviewer::deleteDisplayList(GLuint listid, bool islistid)
{
    if(islistid)
    {
        int i;
        int n=displaylist.size();
        for(i=0;i<n;i++)
        {
            if(displaylist[i].listid==listid)
            {
                displaylist.erase(displaylist.begin()+i);
                break;
            }
        }
    }
    else
    {
        displaylist.erase(displaylist.begin()+listid);
    }
    return;
}

void GLviewer::clearDisplayList()
{
    displaylist.clear();
    return;
}

int GLviewer::listSize()
{
    return displaylist.size();
}

void GLviewer::setCameraPose(Eigen::Matrix4d transform)
{
    transform.block<3,3>(0,0).normalize();
    parameters.transform=transform;
    return;
}

Eigen::Matrix4d GLviewer::getCameraPose()
{
    return parameters.transform;
}

void GLviewer::setBackground(QColor color)
{
    parameters.background(0)=color.red()/255.0;
    parameters.background(1)=color.green()/255.0;
    parameters.background(2)=color.blue()/255.0;
    parameters.background(3)=color.alpha()/255.0;
    return;
}
