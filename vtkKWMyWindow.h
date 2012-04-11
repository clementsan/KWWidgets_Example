#ifndef VTKKWMYWINDOW_H
#define VTKKWMYWINDOW_H
#include "vtkKWWindow.h"

#include "vtkKWCheckButton.h"
#include "vtkKWFrame.h"

//class vtkKWCheckButton;
class vtkKWMyWindow: public vtkKWWindow
{
 public:
 
  vtkKWMyWindow();
  ~vtkKWMyWindow();
  
  
  static vtkKWMyWindow* New();
  vtkTypeRevisionMacro(vtkKWMyWindow,vtkKWWindow);
  
 protected:
 
 virtual void CreateWidget();
 
 private:
 
 vtkKWCheckButton *cb2b;
 vtkKWCheckButton *cb1b;
 
};

#endif
