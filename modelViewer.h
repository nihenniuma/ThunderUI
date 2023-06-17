#ifndef MODEL_VIEWER_H
#define MODEL_VIEWER_H

#include <QGLViewer/qglviewer.h>

class modelViewer : public QGLViewer {
public:
  modelViewer();
  ~modelViewer();
  virtual void draw();
  virtual QString helpString() const;
};


#endif
