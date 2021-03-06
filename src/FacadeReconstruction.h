#pragma once

#include "Classifier.h"
#include "Regression.h"
#include <boost/shared_ptr.hpp>
#include <opencv2/core.hpp>
#include <dlib/optimization.h>
#include <glm/glm.hpp>

namespace facarec {

	typedef dlib::matrix<double, 0, 1> column_vector;

	class obj_function {
	public:
		obj_function(int grammar_id, cv::Mat initial_facade_parsing, int num_floors, int num_columns, const std::vector<int>& selected_win_types);
		double operator() (const column_vector& arg) const;

	private:
		int grammar_id;
		cv::Mat initial_facade_parsing;
		int num_floors;
		int num_columns;
		std::vector<int> selected_win_types;
	};

	class Solver {
	public:
		Solver(int grammar_id, cv::Mat initial_facade_parsing, int num_floors, int num_columns, const std::vector<int>& selected_win_types);
		double operator() (const column_vector& arg) const;

	private:
		int grammar_id;
		cv::Mat initial_facade_parsing;
		int num_floors;
		int num_columns;
		std::vector<int> selected_win_types;
	};


	int recognition(boost::shared_ptr<Classifier> classifier, const cv::Mat& input_image, int mass_grammar_id, int num_floors);
	std::vector<float> parameterEstimation(int grammar_id, boost::shared_ptr<Regression> regression, const cv::Mat& input_image, float width, float height, int num_floors, int num_columns, const cv::Mat& initial_facade_parsing, const std::vector<int>& selected_win_types);

	void generateFacadeImage(int grammar_id, int width, int height, int num_floors, int num_columns, const std::vector<float>& params, const std::vector<int>& selected_win_types, int thickness, const cv::Scalar& bg_color, const cv::Scalar& fg_color, cv::Mat& image);
	std::vector<cv::Scalar> getFacadeColors(int grammar_id, const std::vector<float>& params, const cv::Mat& facade_img, float width, float height, int cluster_count);
}
