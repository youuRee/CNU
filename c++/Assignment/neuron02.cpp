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
    int num, cnt = 0;
    double lr, pred;
    vector < vector <double> > w_node; // 2차원 weight 벡터 (4x2)
    vector <double> pred_node;
    vector <double> w;
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
        if (cnt == 4) cnt = 0;
        double out = pred_node[cnt];
        cnt += 1;
        return out;
    }

    // pred_node(예측값) 반환 함수
    vector<double> &retPred() {
        return pred_node;
    }
    // random 숫자 생성 함수
    double randomFunc() {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<double> distr(MIN, MAX);

        double n = distr(eng);
        //cout << n << endl;

        return n;
    }
};

int main() {
   
    // step1. ~x1, ~x2 학습 (NOT 연산)
    Neuron* nx1 = new Neuron(1, 0.1);
    Neuron* nx2 = new Neuron(1, 0.1);

    double nx1_input[4][1] = { {0}, {0}, {1}, {1} };
    double nx1_output[4] = { 1, 1, 0, 0};

    double nx2_input[4][1] = { {0}, {1}, {0}, {1} };
    double nx2_output[4] = { 1, 0, 1, 0};

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 4; j++) {
            nx1->learn(nx1_input[j], nx1_output[j]);
            nx2->learn(nx2_input[j], nx2_output[j]); // 학습
        }
        nx1->fix();
        nx2->fix(); // 가중치 수정
        
        if ((i + 1) % 100 == 0) {
            cout << "------ Learn " << i + 1 << " times -----" << endl;
            cout << "nx1 nx2    nx1 pred nx2 pred " << endl;
            for (int j = 0; j < 4; j++) {
                cout << nx1_input[j][0] << "    " << nx2_input[j][0] << "  :  "
                    << nx1->work(nx1_input[j]) << ' ' << nx2->work(nx2_input[j]) << endl;
                    

            }
        }
    }
    
    // step2. x1 && ~x2 , x2 && ~x1 학습 (AND 연산)
    Neuron* ax1 = new Neuron(2, 0.1);
    Neuron* ax2 = new Neuron(2, 0.1);
    
    double ax1_input[4][2] = { {0,}, {0,}, {1,}, {1,} };
    double ax1_output[4] = { 0, 0, 1, 0};
    
    double ax2_input[4][2] = { {0,}, {1,}, {0,}, {1,} };
    double ax2_output[4] = { 0, 1, 0, 0};
    
    // neuron이 예측한 값 받아오기
    vector<double> p1, p2;
    p1 = nx1->retPred();
    p2 = nx2->retPred();
    
    // 출력값 가공 -> 0.5 기준으로 1, 0 구별
    for(int i = 0; i < 4; i++){
        if (p1[i] > 0.5) ax2_input[i][1] = 1;
        else ax2_input[i][1] = 0;
        if (p2[i] > 0.5) ax1_input[i][1] = 1;
        else ax1_input[i][1] = 0;
    }
    
    /* 
    -- 그냥 출력값 그대로 쓰고 싶다면 이 코드 이용 -- 
    for(int i = 0; i < 4; i++){
        ax1_input[i][1] = p1[i];
        ax2_input[i][1] = p2[i];
    }
    */
    
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 4; j++) {
            ax1->learn(ax1_input[j], ax1_output[j]);
            ax2->learn(ax2_input[j], ax2_output[j]); // 학습
        }
        ax1->fix();
        ax2->fix(); // 가중치 수정
        
        // Print result //
        if ((i + 1) % 100 == 0) {
            cout << "------ Learn " << i + 1 << " times -----" << endl;
            cout << "ax1             |  ax2 " << endl;
            for (int j = 0; j < 4; j++) {
                cout << ax1_input[j][0] << ' ' << ax1_input[j][1] << " : " << ax1->work(ax1_input[j]) << " | "
                    << ax2_input[j][0] << ' ' << ax2_input[j][1] << " : " << ax2->work(ax2_input[j]) << endl;
                    

            }
        }
    }
    
    // step3. (x1 && ~x2) || (x2 && ~x1) 학습 (OR 연산) -> 최종 XOR
    Neuron* ox = new Neuron(2, 0.1);
    
    double ox_input[4][2] = {};
    double ox_output[4] = { 0, 1, 1, 0};
    
    p1 = ax1->retPred();
    p2 = ax2->retPred();
    
    for(int i = 0; i < 4; i++){
        if (p1[i] > 0.5) ox_input[i][0] = 1;
        else ox_input[i][0] = 0;
        if (p2[i] > 0.5) ox_input[i][1] = 1;
        else ox_input[i][1] = 0;
    }

    /*for (int i = 0; i < 4; i++){
        cout << ox_input[i][0] << ' ' << ox_input[i][1] << endl;
    }*/
    
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 4; j++) {
            ox->learn(ax1_input[j], ox_output[j]);
        }
        ox->fix();
        
        if ((i + 1) % 100 == 0) {
            cout << "------ Learn " << i + 1 << " times -----" << endl;
            for (int j = 0; j < 4; j++) {
                cout << ox_input[j][0] << ' ' << ox_input[j][1] << " : " << ox->work(ox_input[j])<< endl;
            }
        }
    }
    return 0;
}