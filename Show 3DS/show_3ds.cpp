#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtk3DSImporter.h>
#include <vtkSmartPointer.h>
#include <vtkRenderLargeImage.h>
#include <vtkAutoInit.h>

#include <string>
#include <windows.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);

std::string file_path = "装配散件模型.3DS";
//std::string file_path = "汽缸盖.3DS";

int main()
{
	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();	// 创建窗口交互器
	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();			// 创建渲染窗口
	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();				// 创建渲染器

	iren->SetRenderWindow(renWin);		// 设置交互器控制的窗口为renWin
	renWin->AddRenderer(renderer);		// 将渲染器renderer添加到窗口renWin的渲染器列表中

	renderer->SetBackground(0.1, 0.2, 0.4);			// 设置背景色
	renWin->SetSize(600, 600);			// 设置窗口的默认大小

	vtkSmartPointer<vtk3DSImporter> importer =
		vtkSmartPointer<vtk3DSImporter>::New();		// 创建3DS加载器对象
	importer->SetFileName(file_path.c_str());		// 指定要读取的3DS文件的文件名或路径
	importer->ComputeNormalsOn();		// 开启法向量计算
	importer->Read();					// 加载3DS模型

	renderer->GetActiveCamera()->SetPosition(100, 200, 0);	// 设置相机的位置(世界坐标系中)
	renderer->GetActiveCamera()->SetFocalPoint(100, 0, 50);	// 设置相机的焦点(世界坐标系中)
	renderer->GetActiveCamera()->SetViewUp(0, 0, 1);		// 设置相机的观察试图

															// 获取加载的3DS模型中物体对象的个数
	int numOfActors = importer->GetRenderer()->GetActors()->GetNumberOfItems();

	// 从3ds图像中依次读取物体
	for (int i = 0; i < numOfActors; i++)
	{
		vtkActor *actor = (vtkActor *)importer->GetRenderer()->GetActors()->GetItemAsObject(i);
		renderer->AddActor(actor);		// 将上面获取的物体添加到渲染器中
	}

	renWin->Render();			// 令渲染窗口renWin中的所有渲染器开始渲染
	iren->Start();				// 开始事件循环

	return 0;
}