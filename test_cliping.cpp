#include "clipping.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
	// ar_dirt_pose x
	Clipping dirt_clipping_x(-0.25, 0.55);
	std::cout << "dirt clipping x : a\t" << dirt_clipping_x.get_gradient() << "\tb\t" << dirt_clipping_x.get_intercepts() << std::endl;
	// ar_dirt_pose y
	Clipping dirt_clipping_y(0.2, 0.4);
	std::cout << "dirt clipping y : a\t" << dirt_clipping_y.get_gradient() << "\tb\t" << dirt_clipping_y.get_intercepts() << std::endl;
	// ar_dirt_pose z
	Clipping dirt_clipping_z(0.9, 1.2);
	std::cout << "dirt clipping z : a\t" << dirt_clipping_z.get_gradient() << "\tb\t" << dirt_clipping_z.get_intercepts() << std::endl;
	// ar_broom_pose x
	Clipping broom_clipping_x(-0.5,0.4);
	std::cout << "broom clipping x : a\t" << broom_clipping_x.get_gradient() << "\tb\t" << broom_clipping_x.get_intercepts() << std::endl;
	// ar_broom_pose y
	Clipping broom_clipping_y(-0.3,0.1);
	std::cout << "broom clipping y : a\t" << broom_clipping_y.get_gradient() << "\tb\t" << broom_clipping_y.get_intercepts() << std::endl;
	// ar_broom_pose z
	Clipping broom_clipping_z(0.7,1.1);
	std::cout << "broom clipping z : a\t" << broom_clipping_z.get_gradient() << "\tb\t" << broom_clipping_z.get_intercepts() << std::endl;
	// ar_broom_pose r
	Clipping broom_clipping_r(-3, -2);
	std::cout << "broom clipping r : a\t" << broom_clipping_r.get_gradient() << "\tb\t" << broom_clipping_r.get_intercepts() << std::endl;
	// ar_broom_pose p
	Clipping broom_clipping_p(-0.5,0.2);
	std::cout << "broom clipping p : a\t" << broom_clipping_p.get_gradient() << "\tb\t" << broom_clipping_p.get_intercepts() << std::endl;
	// ar_broom_pose w
	Clipping broom_clipping_w(-0.5,0.8);
	std::cout << "broom clipping w : a\t" << broom_clipping_w.get_gradient() << "\tb\t" << broom_clipping_w.get_intercepts() << std::endl;
	// pose_state_clipping x
	Clipping pose_state_0_x(0.4,0.9);
	std::cout << "pose state (0) x : a\t" << pose_state_0_x.get_gradient() << "\tb\t" << pose_state_0_x.get_intercepts() << std::endl;
	// pose_state_clipping y
	Clipping pose_state_0_y(-0.2,0.5);
	std::cout << "pose state (0) y : a\t" << pose_state_0_y.get_gradient() << "\tb\t" << pose_state_0_y.get_intercepts() << std::endl;
	// pose_state_clipping z
	Clipping pose_state_0_z(0.8,1.2);
	std::cout << "pose state (0) z : a\t" << pose_state_0_z.get_gradient() << "\tb\t" << pose_state_0_z.get_intercepts() << std::endl;
	// pose_state_clipping r
	Clipping pose_state_0_r(-3.0,1.0);
	std::cout << "pose state (0) r : a\t" << pose_state_0_r.get_gradient() << "\tb\t" << pose_state_0_r.get_intercepts() << std::endl;
	// pose_state_clipping p
	Clipping pose_state_0_p(-1.8,-0.5);
	std::cout << "pose state (0) p : a\t" << pose_state_0_p.get_gradient() << "\tb\t" << pose_state_0_p.get_intercepts() << std::endl;
	// pose_state_clipping w
	Clipping pose_state_0_w(-3.0,2.0);
	std::cout << "pose state (0) w : a\t" << pose_state_0_w.get_gradient() << "\tb\t" << pose_state_0_w.get_intercepts() << std::endl;

    return 0;
}
