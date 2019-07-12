#include <iostream>
#include <memory>
#include "pcv_window.h"
#include "Global_Variables.h"
#include "pcv_scene.h"
#include "pc.h"
#include "ppc.h"

int main(void){	
	auto gv = Global_Variables::Instance();

	pcv_window wnd;
	wnd.create_window(gv->width, gv->height, gv->title);

	// create scene
	std::shared_ptr<pcv_scene> cur_scene = std::make_shared<pcv_scene>();
	gv->_cur_scene = cur_scene;

	// create point cloud
	std::shared_ptr<pc> pc0 = std::make_shared<pc>(gv->vertex_shader, gv->fragment_shader);
	pc0->init_shader();
	pc0->load_pc("test.txt", 0.1f);

	// add clouds into current scene
	cur_scene->add_pc(pc0);

	// create camera
	gv->cur_ppc = std::make_shared<PPC>(80.0f, float(gv->width) / gv->height);
		
	cur_scene->setup_scene();
	wnd.draw_scene(cur_scene);
	wnd.show();

	system("pause");
	return 0;
}