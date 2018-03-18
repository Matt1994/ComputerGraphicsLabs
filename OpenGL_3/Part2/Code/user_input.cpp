#include "mainview.h"

#include <QDebug>

// Triggered by pressing a key
void MainView::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key()) {
    case 16777234: setRotation(currentRotateX, currentRotateY+1, currentRotateZ); break;
    case 16777235: setRotation(currentRotateX+1, currentRotateY, currentRotateZ); break;
    case 16777236: setRotation(currentRotateX, currentRotateY-1, currentRotateZ); break;
    case 16777237: setRotation(currentRotateX-1, currentRotateY, currentRotateZ); break;
    default:
        break;
    }

    update();
}

// Triggered by releasing a key
void MainView::keyReleaseEvent(QKeyEvent *ev)
{
    switch(ev->key()) {
    case 'A': qDebug() << "A released"; break;
    default:
        break;
    }

    update();
}

// Triggered by clicking two subsequent times on any mouse button
// It also fires two mousePress and mouseRelease events!
void MainView::mouseDoubleClickEvent(QMouseEvent *ev)
{
    qDebug() << "Mouse double clicked:" << ev->button();

    update();
}

// Triggered when moving the mouse inside the window (only when the mouse is clicked!)
void MainView::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug() << "x" << ev->x() << "y" << ev->y();

    update();
}

// Triggered when pressing any mouse button
void MainView::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << "Mouse button pressed:" << ev->button();

    update();
    // Do not remove the line below, clicking must focus on this widget!
    this->setFocus();
}

// Triggered when releasing any mouse button
void MainView::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug() << "Mouse button released" << ev->button();

    update();
}

// Triggered when clicking scrolling with the scroll wheel on the mouse
void MainView::wheelEvent(QWheelEvent *ev)
{
    Q_UNUSED(*ev);
}
