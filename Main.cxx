#include "vtkKWApplication.h"
#include "vtkKWMyWindow.h"

#include <vtksys/SystemTools.hxx>
#include <vtksys/CommandLineArguments.hxx>

extern "C" int Kwwidgetstestlib_Init(Tcl_Interp *interp);

int my_main(int argc, char *argv[])
{

  Tcl_Interp *interp = vtkKWApplication::InitializeTcl(argc, argv, &cerr);
  
  int ret = 0; 
    
  if (!interp)
    {
    cerr << "Error: InitializeTcl failed" << endl ;
    return 1;
    }

  Kwwidgetstestlib_Init(interp);

  int option_test = 0;
  vtksys::CommandLineArguments args;
  args.Initialize(argc, argv);
  args.AddArgument(
    "--test", vtksys::CommandLineArguments::NO_ARGUMENT, &option_test, "");
  args.Parse();
  
  
  vtkKWApplication *app = vtkKWApplication::New();
  
  app->SetName("KWWidgetsTest");
  if (option_test)
    {
    app->SetRegistryLevel(0);
    app->PromptBeforeExitOff();
    }
  app->RestoreApplicationSettingsFromRegistry();

  app->SetHelpDialogStartingPage("http://www.kwwidgets.org");

  vtkKWMyWindow *win = vtkKWMyWindow::New();
  
  win->SupportHelpOn();
  app->AddWindow(win);
  win->Create();
  //win->MainPanelVisibilityOff();
  //win->SecondaryPanelVisibilityOff();
  win->SetSize(1100,690);

  
  win->Display();

  if (!option_test)
    {
    app->Start(argc, argv);
    ret = app->GetExitStatus();
    }
  win->Close();

  win->Delete();
  app->Delete();
 
  return ret;
}

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <windows.h>
int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int)
{
  int argc;
  char **argv;
  vtksys::SystemTools::ConvertWindowsCommandLineToUnixArguments(
    lpCmdLine, &argc, &argv);
  int ret = my_main(argc, argv);
  for (int i = 0; i < argc; i++) { delete [] argv[i]; }
  delete [] argv;
  return ret;
}
#else
int main(int argc, char *argv[])
{
  return my_main(argc, argv);
}
#endif
