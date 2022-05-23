#include "hypro/neuralnets/parser/NNet.h"
#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"

#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>

// use rational arithmetic.
typedef double Number;	// -3090.30109487     <=>      -3090.3   (mpq_class vs double)


void test_simple_matrix_inversion() {
    hypro::vector_t<Number> initial_vect = hypro::vector_t<Number>(2);
    initial_vect << 1, 1;

    hypro::matrix_t<Number> rotation_matrix = hypro::matrix_t<Number>(2,2);
    rotation_matrix << 0.707106781,-0.707106781,0.707106781,0.707106781;
    std::cout << rotation_matrix << std::endl;
    hypro::matrix_t<Number> inverse_rotation = rotation_matrix.completeOrthogonalDecomposition().pseudoInverse();
    std::cout << inverse_rotation << std::endl;
    std::cout << rotation_matrix * inverse_rotation << std::endl;

    hypro::vector_t<Number> translation = hypro::vector_t<Number>(2);
    translation << 1, 1;

    std::cout << "Initial vector: " << std::endl << initial_vect << std::endl;
    hypro::vector_t<Number> transformed_vector = rotation_matrix * initial_vect + translation;
    std::cout << "Transformed vector:" << std::endl << transformed_vector << std::endl;
    std::cout << "Inverse transformed vector: " << std::endl << inverse_rotation * (transformed_vector - translation) << std::endl;
}

hypro::vector_t<Number> get_single_sample(const hypro::Starset<Number>& star, int max_trial = 1000) {
    hypro::vector_t<Number> sample = hypro::vector_t<Number>(star.dimension());

    hypro::vector_t<Number> center = star.center();
    hypro::matrix_t<Number> basis = star.generator();
    hypro::HPolytope<Number> polytope = star.constraintss();

    // std::cout << center << std::endl;
    // std::cout << basis << std::endl;
    // std::cout << polytope << std::endl;

    hypro::vector_t<Number> min_point = hypro::vector_t<Number>(polytope.dimension());
    hypro::vector_t<Number> max_point = hypro::vector_t<Number>(polytope.dimension());

    for(int i = 0; i < polytope.dimension(); i++) {
        hypro::vector_t<Number> dir_vect = hypro::vector_t<Number>::Zero(polytope.dimension());
        dir_vect[i] = 1;
		auto eval_low_result = polytope.evaluate( -1.0 * dir_vect );
		auto eval_high_result = polytope.evaluate( dir_vect );

        min_point[i] = -eval_low_result.supportValue;
        max_point[i] = eval_high_result.supportValue;
    }

    std::cout << "Min point: " << std::endl;
    std::cout << min_point << std::endl;
    std::cout << "Max point: " << std::endl;
    std::cout << max_point << std::endl;


    int k = 0;
    while(k < max_trial) {
        for(int i = 0; i < polytope.dimension(); i++) {
            sample[i] = min_point[i] + ((float) rand() / RAND_MAX) * (max_point[i] - min_point[i]);
            if(polytope.contains(sample)) {
                return basis * sample + center;
            }
        }

        k++;
    }    
    
    FATAL("examples.example_pseudoinv.get_single_sample", "Could not find a proper candidate in the sampling process")
    return basis * sample + center;
}

hypro::vector_t<Number> ReLU(const hypro::vector_t<Number>& x) {
    hypro::vector_t<Number> y(x);
    for(int i = 0; i < y.rows(); i++) {
        if(y[i] < 0)
            y[i] = Number(0);
    }
    return y;
}

hypro::vector_t<Number> sign(const hypro::vector_t<Number>& x) {
    hypro::vector_t<Number> y(x);
    for(int i = 0; i < y.rows(); i++) {
        if(y[i] < 0)
            y[i] = Number(-1);
        else
            y[i] = Number(+1);
    }
    return y;
}

Number l2_norm(const hypro::vector_t<Number>& x) {
    Number l2_norm = Number(0);
    for(int i = 0; i < x.rows(); i++) {
        l2_norm += x[i] * x[i];
    }
    return sqrt(l2_norm);
}

hypro::vector_t<Number> calculate_gradient(const hypro::NNet<Number>& nnet, const hypro::vector_t<Number>& y, const hypro::vector_t<Number>& x) {
    std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> l1 = nnet.layerParams(0);
    std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> l2 = nnet.layerParams(1);
    std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> l3 = nnet.layerParams(2);
    std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> l4 = nnet.layerParams(3);
    std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> l5 = nnet.layerParams(4);
    std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> l6 = nnet.layerParams(5);
    std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> l7 = nnet.layerParams(6);

    hypro::matrix_t<Number> W1 = l1.first;
    hypro::vector_t<Number> b1 = l1.second;
    hypro::matrix_t<Number> W2 = l2.first;
    hypro::vector_t<Number> b2 = l2.second;
    hypro::matrix_t<Number> W3 = l3.first;
    hypro::vector_t<Number> b3 = l3.second;
    hypro::matrix_t<Number> W4 = l4.first;
    hypro::vector_t<Number> b4 = l4.second;
    hypro::matrix_t<Number> W5 = l5.first;
    hypro::vector_t<Number> b5 = l5.second;
    hypro::matrix_t<Number> W6 = l6.first;
    hypro::vector_t<Number> b6 = l6.second;
    hypro::matrix_t<Number> W7 = l7.first;
    hypro::vector_t<Number> b7 = l7.second;

    hypro::vector_t<Number> t0 = b1 + W1 * x;
    hypro::vector_t<Number> t1 = b2 + W2 * ReLU(t0);
    hypro::vector_t<Number> t2 = b3 + W3 * ReLU(t1);
    hypro::vector_t<Number> t3 = b4 + W4 * ReLU(t2);
    hypro::vector_t<Number> t4 = b5 + W5 * ReLU(t3);
    hypro::vector_t<Number> t5 = b6 + W6 * ReLU(t4);
    hypro::vector_t<Number> t6 = b7 + W7 * ReLU(t5) - y;

    Number coeff = 1.0 / l2_norm(t6);


    // std::cout << W6.transpose().array().size() << std::endl;
    // auto temp = (W6.transpose() * (
    //     (W7.transpose() * t6).array() * (ReLU(sign(t5))).array()
    // ).matrix()).array() * (ReLU(sign(t4))).array();
    // std::cout << temp << std::endl;

    // my favourite piece of code
    return coeff * (
        W1.transpose() *
            ((W2.transpose() *
                ((W3.transpose() *
                    ((W4.transpose() *
                        ((W5.transpose() *
                            ((W6.transpose() *
                                    ((W7.transpose() * t6
                                ).array() * (ReLU(sign(t5))).array()).matrix()
                            ).array() * (ReLU(sign(t4))).array()).matrix()
                        ).array() * (ReLU(sign(t3))).array()).matrix()
                    ).array() * (ReLU(sign(t2))).array()).matrix()
                ).array() * (ReLU(sign(t1))).array()).matrix()
            ).array() * (ReLU(sign(t0))).array()).matrix()
    ).array();

    // return coeff * W1.transpose() * ((
    //         W2.transpose()  * ((
    //             W3.transpose() * ((
    //                 W4.transpose() * ((
    //                     W5.transpose() * ((
    //                         W6.transpose() * ((
    //                             W7.transpose() * t6
    //                         ).array() * (ReLU(sign(t5)).array()))
    //                     ).array() * (ReLU(sign(t4)).array()))
    //                 ).array() * (ReLU(sign(t3)).array()))
    //             ).array() * (ReLU(sign(t2)).array()))
    //         ).array() * (ReLU(sign(t1)).array()))
    //     ).array() * (ReLU(sign(t0)).array())).matrix();
}


//Complete one forward pass for a given set of inputs and return output values
hypro::vector_t<Number> forward_step( const hypro::NNet<Number> nnet, const hypro::vector_t<Number>& x ) {
	hypro::vector_t<Number> y = hypro::vector_t<Number>(x);
    for(int i = 0; i < nnet.numLayers(); i++) {
        std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> layerParams = nnet.layerParams(i);
        hypro::matrix_t<Number> weights = layerParams.first;
        hypro::vector_t<Number> biases = layerParams.second;

        y = weights * y + biases;

        if(i < nnet.numLayers() - 1) {
            for(int j = 0; j < y.rows(); j++) {
                if(y[i] < 0)
                    y[i] = 0;
            }
        }
    }
    return y;
}


hypro::vector_t<Number> find_input_given_output(const hypro::NNet<Number> nnet, const hypro::vector_t<Number>& y, int max_it = 1000, Number eps = 0.001, Number eta = 0.01) {
    hypro::vector_t<Number> x_n = hypro::vector_t<Number>::Random(y.rows());
    int it = 0;
    while(it < max_it) {
        if(it % 100 == 0)
            std::cout << "Iteration: " << it << " / " << max_it << std::endl;
        if(l2_norm(y - forward_step(nnet, x_n)) <= eps)
            return x_n;
        // std::cout << "calculating gradient..." << std::endl;
        // std::cout << calculate_gradient(nnet, y, x_n).array() << std::endl;
        if(l2_norm(calculate_gradient(nnet, y, x_n)) > 0)
            std::cout << it << " - " << l2_norm(calculate_gradient(nnet, y, x_n)) << std::endl;
        // std::cout << "stepping" << std::endl;
        x_n = x_n - (eta * calculate_gradient(nnet, y, x_n).array()).matrix();
        it++;
    }
    return x_n;
}

void test_network_weights_inversion(const char* nn_filename, const char* star_filename) {
    // read and build neural network + time measurement
	auto start = std::chrono::steady_clock::now();
	hypro::NNet<Number> input_nn = hypro::NNet<Number>( nn_filename );
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during building the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	// std::cout << input_nn << std::endl;

    hypro::Starset<Number> input_star = hypro::Starset<Number>::readFromFile(star_filename);
    std::cout << input_star << std::endl;


    hypro::vector_t<Number> sample = get_single_sample(input_star);
    std::cout << "Sample point: " << std::endl;
    std::cout << sample << std::endl;

    hypro::vector_t<Number> original_sample = hypro::vector_t<Number>(sample);

    // guide the sample through the network
    // then do it again backwards using the inverted weight matrices
    // see if the final result is the same as the original input

    for(int i = 0; i < input_nn.numLayers(); i++) {
        std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> layerParams = input_nn.layerParams(i);
        hypro::matrix_t<Number> weights = layerParams.first;
        hypro::vector_t<Number> biases = layerParams.second;

        sample = weights * sample + biases;

        std::cout << "Layer " << i << " result: " << std::endl;
        std::cout << sample << std::endl;   
    }

    hypro::vector_t<Number> output = hypro::vector_t<Number>(sample);

    for(int i = input_nn.numLayers() - 1; i >= 0; i--) {
        std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> layerParams = input_nn.layerParams(i);
        hypro::matrix_t<Number> weights = layerParams.first;
        hypro::vector_t<Number> biases = layerParams.second;

        std::cout << "Layer " << i << " result: " << std::endl;
        std::cout << sample << std::endl;

        // std::cout << "Finding inverse of weigth matrix " << i << "..." << std::endl;
        hypro::matrix_t<Number> weightsInverse = weights.completeOrthogonalDecomposition().pseudoInverse();
        sample = weightsInverse * (sample - biases);

        // std::cout << weightsInverse * weights << std::endl;
    }

    std::cout << "Sample point: " << std::endl;
    std::cout << sample << std::endl;

    hypro::vector_t<Number> predicted = find_input_given_output(input_nn, output);

    std::cout << "Original input: " << std::endl;
    std::cout << original_sample << std::endl;
    std::cout << "Predicted input: " << std::endl;
    std::cout << predicted << std::endl;

    std::cout << "Original output: " << std::endl;
    std::cout << output << std::endl;
    std::cout << "Predicted output:" << std::endl;
    std::cout << forward_step(input_nn, predicted);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // define NN input file name
	const char* nn_file = "../examples/nnet/fc_relu.nnet";
	if(argc > 1)
		nn_file = argv[1];
	std::cout << "NN input file is: " << nn_file << std::endl;

    // define star input file name
	const char* star_file = "../examples/star_inputs/star_prop3_5D_artificial_bounds.in";
	if(argc > 2)
		star_file = argv[2];
	std::cout << "Star input file is: " << star_file << std::endl;


    // test_simple_matrix_inversion();
    test_network_weights_inversion(nn_file, star_file);

    return 0;
}
