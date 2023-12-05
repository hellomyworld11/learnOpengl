#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;
#define ATOR (MY_PI/180)

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0],
				 0, 1, 0, -eye_pos[1], 
				 0, 0, 1, -eye_pos[2], 
				 0, 0, 0,           1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
	//旋转矩阵
	double a = cos(rotation_angle * ATOR);
	double b = sin(rotation_angle * ATOR);

	model << a, -b, 0, 0,
			b, a, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1;
    return model;
}

//@eye_fov 视角
//@aspect_ratio   长宽比(r/t)
//@zNear      视锥近平面z
//@zFar		视锥远平面z
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // Students will implement this function

    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
	
	double r, l, t, b;
	double n = zNear;
	double f = zFar;
	
	t = tan((eye_fov * ATOR / 2)) * n ;
	b = -t;
	r = t * aspect_ratio;
	l = -r;
    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.
	
	Matrix4f oropro;
	//1. 正交投影的(-1 到 1 缩放)
	Matrix4f scaleMat;
	scaleMat << 2 / (r - l), 0, 0, 0,
				0, 2 / (t - b), 0, 0,
				0, 0, 2 / (n - f), 0,
				0, 0, 0, 1;
	//2. 正交投影的 移动坐标原点(0,0)位置
	Matrix4f moveMat;
	moveMat << 1, 0, 0, -(r + l) / 2,
			0, 1, 0, -(t + b) / 2,
			0, 0, 1, -(n + f) / 2,
			0, 0, 0, 1;
	//3. 透视到正交的变换矩阵
	Matrix4f pertoorMat;
	pertoorMat << n, 0, 0, 0,
				0, n, 0, 0,
				0, 0, (n + f), -n*f,
				0, 0, 1, 0;

	projection = scaleMat * moveMat * pertoorMat;
    return projection;
}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else
            return 0;
    }

    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
