#include <iostream>
#include <ctime>
#include <random>
#include <iomanip>
#include <vector>

// Modify as needed
const int MIN = -1;
const int MAX = 1;

#define sigmoid(x) ( 1.0/(1.0+exp(-(x))) ) // sigmoid

using namespace std;

class Neuron {
private:
    int num, cnt = 0; // cnt : work() 호출 시 pred_node의 인덱스
    double lr, pred; 
    vector <double> w; 
    vector < vector <double> > w_node; // 2차원 weight 벡터 (4x2) 
    vector <double> pred_node; 
    vector<double> loss; 
public:
    Neuron(int num_of_input, double alpha) : num(num_of_input), lr(alpha) {}

    // learn overloading
    void learn(double(&x)[2], double(&label)) {
        for (int i = 0; i < num+1; i++)
            w.push_back(randomFunc());

        // 입력데이터(x)를 w 벡터에다가 push
        w.push_back(x[0]);
        w.push_back(x[1]);
        
        // 예측값 구하고
        pred = x[0] * w[0] + x[1] * w[1] + w[2];
        pred = sigmoid(pred);
        
        // pred_node 벡터에 담기
        pred_node.push_back(pred);
        loss.push_back(pred - label);
        
        // weight(w,b)들도 w_node 벡터에 담기 
        w_node.push_back(w);

    }

    void learn(double(&x)[1], double(&label)) {
        for (int i = 0; i < num+1; i++)
            w.push_back(randomFunc());

        w.push_back(x[0]);
        pred = x[0] * w[0] + w[1];
        
        pred = sigmoid(pred);
        pred_node.push_back(pred);
        loss.push_back(pred - label);
        w_node.push_back(w);

    }

    void fix() {

        int len = loss.size();
        // AND, OR
        if (num == 2) {
            for (int i = 0; i < len; i++) {
                // weight update
                w_node[i][0] = w_node[i][0] - lr * (loss[i] * w[3] * pred_node[i] * (1 - pred_node[i])); // w[3], w[4] = input
                w_node[i][1] = w_node[i][1] - lr * (loss[i] * w[4] * pred_node[i] * (1 - pred_node[i]));
                w_node[i][2] = w_node[i][2] - lr * (loss[i] * pred_node[i] * (1 - pred_node[i]));
                
                // update된 weight들로 다시 예측값 구하기
                pred = w[3] * w_node[i][0] + w[4] * w_node[i][1] + w_node[i][2];
                pred_node[i] = sigmoid(pred);
            }
        }
        // NOT
        else {
            for (int i = 0; i < len; i++) {
                w_node[i][0] = w_node[i][0] - lr * (loss[i] * w[2] * pred_node[i] * (1 - pred_node[i])); // w[2] = input
                w_node[i][1] = w_node[i][1] - lr * (loss[i] * pred_node[i] * (1 - pred_node[i]));

                pred = w[2] * w_node[i][0] + w_node[i][1];
                pred_node[i] = sigmoid(pred);

            }
        }

    }

    // work overloading
    double work(double(&x)[2]) {
        if (cnt == 4) cnt = 0;
        double out = pred_node[cnt];
        cnt += 1;
        return out;
    }

    double work(double(&x)[1]) {
        if (cnt == 2) cnt = 0;
        double out = pred_node[cnt];
        cnt += 1;
        return out;
    }

    // random 숫자 생성 함수
    double randomFunc() {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distr(MIN, MAX);

        double n = distr(eng);

        return n;
    }
};

int main() {

    // 뉴런 클래스 생성자. 
    // Neuron(int num_of_input, double alpha) 
                  //(입력의 수, learning rate)
    Neuron* neuron = new Neuron(2, 0.1);

    // AND 
    double sample_input[4][2] = { {0,0},{0,1},{1,0},{1,1} };
    double sample_output[4] = { 0, 0, 0, 1 };

    for (int i = 0; i < 5000; i++) {
        for (int j = 0; j < 4; j++) {
            neuron->learn(sample_input[j], sample_output[j]); // 학습
        }
        neuron->fix(); // 가중치 수정

        if ((i + 1) % 100 == 0) {
            cout << "------ Learn " << i + 1 << " times -----" << endl;
            for (int j = 0; j < 4; j++) {
                cout << sample_input[j][0] << ' ' << sample_input[j][1] << " : "
                    << neuron->work(sample_input[j]) << endl; // 결과값 
            }
        }
    }
    delete neuron;

    // NOT
    Neuron* neuron2 = new Neuron(1, 0.1);

    double sample_input2[2][1] = { {0}, {1} };
    double sample_output2[2] = { 1, 0 };

    for (int i = 0; i < 5000; i++) {
        for (int j = 0; j < 2; j++) {
            neuron2->learn(sample_input2[j], sample_output2[j]); // 학습
        }
        neuron2->fix(); // 가중치 수정

        if ((i + 1) % 100 == 0) {
            cout << "------ Learn " << i + 1 << " times -----" << endl;
            for (int j = 0; j < 2; j++) {
                cout << sample_input2[j][0] << " : "
                    << neuron2->work(sample_input2[j]) << endl; // 결과값 
            }
        }
    }
    delete neuron2;

    // OR
    Neuron* neuron3 = new Neuron(2, 0.1);

    double sample_input3[4][2] = { {0,0},{0,1},{1,0},{1,1} };
    double sample_output3[4] = { 0, 1, 1, 1 };

    for (int i = 0; i < 5000; i++) {
        for (int j = 0; j < 4; j++) {
            neuron3->learn(sample_input3[j], sample_output3[j]); // 학습
        }
        neuron3->fix(); // 가중치 수정
        
        if ((i + 1) % 100 == 0) {
            cout << "------ Learn " << i + 1 << " times -----" << endl;
            for (int j = 0; j < 4; j++) {
                cout << sample_input3[j][0] << ' ' << sample_input3[j][1] << " : "
                    << neuron3->work(sample_input3[j]) << endl; // 결과값 
            }
        }
    }
    delete neuron3;
    
    return 0;
}