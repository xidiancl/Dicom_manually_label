#include "Dicom.h"

using namespace std;

Dicom::Dicom() {
}

Dicom::Dicom(std::string path) {
	dicom_folder = path;
}

Dicom::~Dicom() {
	DeleteDirectory("tmp");
}

void Dicom::show() {
	// Initialize renderer and interactor
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<MouseInteractorStyle> style = vtkSmartPointer<MouseInteractorStyle>::New();
	style->SetDefaultRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renderWindow);
	iren->SetInteractorStyle(style);

	// Read dicom data
	vector<string> filenames;
	vector<int> groupIds;
	vector<string> groupNames;
	vector<int> groupMemberNums;
	int max_group_id = 0;
	int max_group_size = 0;
	getFiles(dicom_folder, filenames);
	for (int i = 0; i < filenames.size(); ++i) {
		// Read tags
		OFCondition status;
		DcmFileFormat fileformat;
		status = fileformat.loadFile((dicom_folder + "/" + filenames[i]).c_str());
		DcmDataset *dataset = fileformat.getDataset();
		if (status.good()) {
			OFString series_instance_uid;
			dataset->findAndGetOFString(DCM_SeriesInstanceUID, series_instance_uid);
			int groupId = -1;
			for (int i = 0; i < groupNames.size(); ++i) {
				if (groupNames[i] == string(series_instance_uid.c_str())) {
					groupId = i;
					break;
				}
			}
			if (groupId == -1) {
				groupIds.push_back(groupNames.size());
				groupNames.push_back(string(series_instance_uid.c_str()));
				groupMemberNums.push_back(0);
			}
			else {
				groupIds.push_back(groupId);
				groupMemberNums[groupId]++;
			}
		}
		
	}
	for (int i = 0; i < groupNames.size(); ++i) {
		if (groupMemberNums[i] > max_group_size) {
			max_group_size = groupMemberNums[i];
			max_group_id = i;
		}
	}
	// Get correct dicoms
	DeleteDirectory("tmp");
	CreateDirectory("tmp", NULL);
	for (int i = 0; i < filenames.size(); ++i) {
		if (groupIds[i] == max_group_id) {
			CopyFile((dicom_folder + "/" + filenames[i]).c_str(), (string("tmp/") + filenames[i]).c_str(), TRUE);
		}
	}
	// Read Dicoms
	vtkSmartPointer<vtkDICOMImageReader> dicom_reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	dicom_reader->SetDirectoryName("tmp");
	dicom_reader->SetDataByteOrderToLittleEndian();
	dicom_reader->Update();
	
	// Reconstruct mesh model
	vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
	marchingCubes->SetInputConnection(dicom_reader->GetOutputPort());
	marchingCubes->SetValue(0, -150);
	vtkSmartPointer<vtkStripper> stripper = vtkSmartPointer<vtkStripper>::New();
	stripper->SetInputConnection(marchingCubes->GetOutputPort());

	// Render
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
}
