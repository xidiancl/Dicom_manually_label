#pragma once

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCellPicker.h>
#include <iostream>

using namespace std;

class MouseInteractorStyle : public vtkInteractorStyleTrackballCamera {
public:
	static MouseInteractorStyle* New();
	vtkTypeMacro(MouseInteractorStyle, vtkInteractorStyleTrackballCamera);

	MouseInteractorStyle() {}
	~MouseInteractorStyle() {}

	virtual void OnLeftButtonDown() {
		down_pos[0] = this->GetInteractor()->GetEventPosition()[0];
		down_pos[1] = this->GetInteractor()->GetEventPosition()[1];
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	}
	virtual void OnLeftButtonUp() {
		up_pos[0] = this->GetInteractor()->GetEventPosition()[0];
		up_pos[1] = this->GetInteractor()->GetEventPosition()[1];
		if (up_pos[0] == down_pos[0] && up_pos[1] == down_pos[1]) {
			vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
			picker->SetTolerance(0.001);
			picker->Pick(down_pos[0], down_pos[1], 0, this->GetDefaultRenderer());
			int cell_id = picker->GetCellId();
			if (cell_id != -1) {
				cout << cell_id << endl;
			}
		}
		vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
	}

private:
	int down_pos[2];
	int up_pos[2];
};
