#include <vtkAutoInit.h> 
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <iostream>

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkDICOMImageReader.h>
#include <vtkMarchingCubes.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkContourFilter.h>

#include "mouseInteractorStyle.h"

using namespace std;

vtkStandardNewMacro(MouseInteractorStyle);

int main() {
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<MouseInteractorStyle> style = vtkSmartPointer<MouseInteractorStyle>::New();
	style->SetDefaultRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renderWindow);
	iren->SetInteractorStyle(style);

	vtkSmartPointer<vtkDICOMImageReader> dicomReader = vtkSmartPointer<vtkDICOMImageReader>::New();
	dicomReader->SetDirectoryName("F:/Datasets/CT_face/16");
	dicomReader->SetDataByteOrderToLittleEndian();
	dicomReader->Update();

	//vtkSmartPointer<vtkContourFilter> filter = vtkSmartPointer<vtkContourFilter>::New();
	//filter->SetValue(1, -150);

	vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
	marchingCubes->SetInputConnection(dicomReader->GetOutputPort());
	marchingCubes->SetValue(1, -150);

	vtkSmartPointer<vtkStripper> stripper = vtkSmartPointer<vtkStripper>::New();
	stripper->SetInputConnection(marchingCubes->GetOutputPort());

	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(stripper->GetOutputPort());
	mapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetDiffuseColor(1, .49, .25);
	actor->GetProperty()->SetSpecular(0.3); 
	actor->GetProperty()->SetSpecularPower(20);
	actor->GetProperty()->SetOpacity(1.0);
	actor->GetProperty()->SetColor(1, 1, 1);
	actor->GetProperty()->SetRepresentationToWireframe();

	renderer->AddActor(actor);

	renderWindow->SetSize(800, 600);
	renderWindow->Render();
	iren->Initialize();
	iren->Start();
	return 0;
}
