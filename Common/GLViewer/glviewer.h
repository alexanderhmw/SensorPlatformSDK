#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <QtOpenGL/QtOpenGL>
#include <QWidget>
#include <Eigen/Dense>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QGLWidget>

struct CAMERAPARAMETERS
{
    double viewAngle;
    double viewheight;
    double minView, maxView;
    int width,height;
    Eigen::Vector4d background;
    Eigen::Matrix4d transform;
    double tspeed,rspeed;
    int pointsize;
};

struct DISPLAYLIST
{
    bool show;
    GLuint listid;
	double S[3];
	double R[3];
	double T[3];
};

class GLviewer : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLviewer(QWidget *parent = 0);
    ~GLviewer();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void keyPressEvent(QKeyEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
signals:
    void mousePosition(int mx, int my, Eigen::Vector3d eye, double minview, double maxview, QMouseEvent *event);
private:
    CAMERAPARAMETERS parameters;
    std::vector<DISPLAYLIST> displaylist;
    bool bperspective;
private:
    void setProjection();
public:
    void addDisplayList(GLuint listid);
    void addDisplayLists(std::vector<GLuint> & listids);
    void enableShow(GLuint listid, bool show, bool islistid=0);
    void deleteDisplayList(GLuint listid, bool islistid=0);
    void clearDisplayList();
    int listSize();
    void setCameraPose(Eigen::Matrix4d transform);
    Eigen::Matrix4d getCameraPose();
    void setBackground(QColor color);
};

#endif
