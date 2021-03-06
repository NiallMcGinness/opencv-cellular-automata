#include <bitset>
#include <cxxopts.hpp>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace cv;

Mat cv_mat();
void cv_draw_point(Mat image, Point p);
void rule(int rule_number, Mat image);

void possible_states(bitset<8> rule_bits, int al, int a, int ar, Mat image, Point p);
void run_rule(int rule, Mat image, Point p);
void startCA(int rule_number);

int main(int argc, char* argv[])
{

    try {
        cxxopts::Options options("CA", "cellular automata cli flag parser");
        options.add_options()("rule", "rule number", cxxopts::value<int>())("all", "cycle through all 255 rules");

        const auto result = options.parse(argc, argv);

        int rule_selected = 126; // just picking this as a default because its an interesting pattern
        if (result.count("rule")) {
            int rule_flag = result["rule"].as<int>();

            if (rule_flag > 0 && rule_flag < 256) {
                rule_selected = rule_flag;
                cout << "building rule " << rule_selected << "\n";
            } else {
                cout << "rule must be between 0 and 255, picking rule 126 instead\n";
            }
        }

        if (result.count("all")) {

            cout << "building ca 0 - 255"
                 << "\n";

            for (int i = 0; i < 255; i++) {
                startCA(i);
            }

        }

        else {
            startCA(rule_selected);
        }

    } catch (exception& e) {
        cerr << e.what();
        return -1;
    }
}

void startCA(int rule_number)
{

    Mat image = cv_mat();

    int w = image.cols;

    Point seed = Point(0, w / 2);

    cv_draw_point(image, seed);

    rule(rule_number, image);

    string fig_title = "rule" + to_string(rule_number) + ".png";

    imwrite(fig_title, image);
}

Mat cv_mat()
{
    int cols = 800;
    int rows = 1000;
    Mat image = Mat::zeros(rows, cols, CV_8UC3);
    image.setTo(Scalar(255, 255, 255));

    return image;
}

void cv_draw_point(Mat image, Point p)
{

    int x = p.x;
    int y = p.y;
    //cout << " drawing point at col " << y << " row : " << x << endl;
    Vec3b color = image.at<Vec3b>(Point(y, x));

    color[0] = 0;
    color[1] = 0;
    color[2] = 0;

    image.at<Vec3b>(Point(y, x)) = color;
}

void rule(int rule_number, Mat image)
{

    int rows = image.rows;
    int cols = image.cols;

    // we treat each row as a new step in the computaion for our turing machine
    // each cell value is calculated by taking the values of the block of three cells in the row above it

    Point point_above_left, point_above, point_above_right;
    Point p;
    // used CV_8UC3 to create image which has three color channels for each pixel, just using white or black
    // to represent states so checking red channel is good enough ( can't be bothered to switch everything over to 1 channel at this point )
    Vec3b color, color_above_left, color_above, color_above_right;

    bitset<8> rule_bits(rule_number);
    int al, a, ar;
    for (int row = 1; row < rows; row++) {
        //cout << " row " << row << endl;
        // stating at col 1 not 0 to give some padding to avoid edge cases
        for (int col = 1; col < cols - 1; col++) {
            //cout << " col " << col << endl;
            p = Point(row, col);

            // <Vec3b> class takes coord of form (y,x) NOT (x,y)
            point_above_left = Point(row - 1, col - 1);
            color_above_left = image.at<Vec3b>(Point(point_above_left.y, point_above_left.x));
            al = color_above_left[0];

            point_above = Point(row - 1, col);
            color_above = image.at<Vec3b>(Point(point_above.y, point_above.x));
            a = color_above[0];

            point_above_right = Point(row - 1, col + 1);
            color_above_right = image.at<Vec3b>(Point(point_above_right.y, point_above_right.x));
            ar = color_above_right[0];

            possible_states(rule_bits, al, a, ar, image, p);
        }
    }
}

void possible_states(bitset<8> rule_bits, int al, int a, int ar, Mat image, Point p)
{

    // using a block of three cells in previous steps above left , above , above right
    // there are 2^3 or 8 possible states
    // each state can be assigned a rule, assign the correct cell a 1 or a 0 state
    // total of 2^8 or 256 possible rules

    if (al != 0 && a != 0 && ar != 0)
        run_rule(rule_bits[0], image, p);

    if (al != 0 && a != 0 && ar == 0)
        run_rule(rule_bits[1], image, p);

    if (al != 0 && a == 0 && ar != 0)
        run_rule(rule_bits[2], image, p);

    if (al != 0 && a == 0 && ar == 0)
        run_rule(rule_bits[3], image, p);

    if (al == 0 && a != 0 && ar != 0)
        run_rule(rule_bits[4], image, p);

    if (al == 0 && a != 0 && ar == 0)
        run_rule(rule_bits[5], image, p);

    if (al == 0 && a == 0 && ar != 0)
        run_rule(rule_bits[6], image, p);

    if (al == 0 && a == 0 && ar == 0)
        run_rule(rule_bits[7], image, p);
}

void run_rule(int rule, Mat image, Point p)
{

    if (rule == 1)
        cv_draw_point(image, p);
}
