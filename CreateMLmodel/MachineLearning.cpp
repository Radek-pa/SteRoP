#include <iostream>
#include "mlpack/core.hpp"
#include "mlpack/methods/random_forest/random_forest.hpp"
#include "mlpack/methods/decision_tree/random_dimension_select.hpp"
#include "mlpack/core/cv/k_fold_cv.hpp"
#include "mlpack/core/cv/metrics/accuracy.hpp"
#include "mlpack/core/cv/metrics/precision.hpp"
#include "mlpack/core/cv/metrics/recall.hpp"
#include "mlpack/core/cv/metrics/F1.hpp"

using namespace arma;
using namespace mlpack;
using namespace mlpack::tree;
using namespace mlpack::cv;


int main()
{
	mat dataset;
	bool loaded = mlpack::data::Load("database.csv", dataset);
	if (!loaded)
		return -1;

	Row<size_t> labels;
	labels = conv_to<Row<size_t>>::from(dataset.row(dataset.n_rows - 1));
	dataset.shed_row(dataset.n_rows - 1);

	/*
	data::ImageInfo info;
	arma::mat matrix;
	std::vector<std::string> files{ "sample1.jpg","sample2.jpg","sample3.jpg","sample4.jpg","sample5.jpg","sample6.jpg","sample7.jpg","sample8.jpg","sample9.jpg" };
	data::Load(files, matrix, info, false);

	//data::Load("sample1.jpg", matrix, info, false);
	
	Row<size_t> labels;
	labels = conv_to<Row<size_t>>::from(matrix.row(matrix.size()-1));
	matrix.shed_row(matrix.size() - 1);

	*/

	//training

	const size_t numClasses = 2;
	const size_t minimumLeafSize = 5;
	const size_t numTrees = 10;
	RandomForest<GiniGain, RandomDimensionSelect> rf;
	rf = RandomForest<GiniGain, RandomDimensionSelect>(dataset, labels,
		numClasses, numTrees, minimumLeafSize);

	Row<size_t> predictions;
	rf.Classify(dataset, predictions);
	const size_t correct = arma::accu(predictions == labels);
	cout << "\nTraining Accuracy: " << (double(correct) / double(labels.n_elem));


	//save model
	mlpack::data::Save("mymodel.xml", "model", rf, false);

	//lodad model
	mlpack::data::Load("mymodel.xml", "model", rf);

	//new sample
	mat sample;
	mlpack::data::Load("test.csv", sample);
	//mat sample("2 12 2 13 1 2 2 1 3 24 3 1 1 1 1 1 0 1 0 1 0 0 0"); 2,12,2,13,1,2,2,1,3,24,3,1,1,1,1,1,0,1,0,1,0,0,0
	mat probabilities;
	rf.Classify(sample, predictions, probabilities);
	u64 result = predictions.at(0);
	cout << "\nClassification result: " << result << " , Probabilities: " <<
		probabilities.at(0) << "/" << probabilities.at(1);

	return 0;
}
