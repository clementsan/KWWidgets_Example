#include "vtkKWMyWindow.h"
#include "vtkKWApplication.h"
#include "vtkKWWindowBase.h"


#include "vtkObjectFactory.h"

#include <vtksys/SystemTools.hxx>

//----------------------------------------------------------------------------
vtkStandardNewMacro( vtkKWMyWindow );
vtkCxxRevisionMacro( vtkKWMyWindow, "$Revision: 1.3 $");

//----------------------------------------------------------------------------
vtkKWMyWindow::vtkKWMyWindow()
{

}

//----------------------------------------------------------------------------
vtkKWMyWindow::~vtkKWMyWindow()
{
 
}

void vtkKWMyWindow::CreateWidget()
{
  // Check if already created

  if (this->IsCreated())
    {
    vtkErrorMacro("class already created");
    return;
    }

  // Call the superclass to create the whole widget

  this->Superclass::CreateWidget();

  vtkKWApplication *app = this->GetApplication();
  
  vtkKWCheckButton *cb2b = vtkKWCheckButton::New();
  
  cb2b->SetParent(this->GetViewFrame());
  cb2b->Create();
  cb2b->SetText("Hello");
 
  app->Script(
    "pack %s -side top -anchor nw -expand n -padx 2 -pady 6", 
    cb2b->GetWidgetName());
    
  vtkKWCheckButton *cb1b = vtkKWCheckButton::New();
  
  cb1b->SetParent(this->GetViewFrame());
  cb1b->Create();
  cb1b->SetText("Hello2");
 
  app->Script(
    "pack %s -side bottom -anchor n -expand n -padx 2 -pady 6", 
    cb1b->GetWidgetName());
    
}
