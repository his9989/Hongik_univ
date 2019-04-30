import numpy as np


class singleLayer :
    def __init__(self, W, Bias): # 제공. 호출 시 작동하는 생성자
        self.W = W
        self.B = Bias

    def SetParams(self, W_params, Bias_params): # 제공. W와 Bias를 바꾸고 싶을 때 쓰는 함수
        self.W = W_params
        self.B = Bias_params

    def ScoreFunction(self, X): # \Score값 계산 -> 직접작성
        #3.2
        ScoreMatrix = np.matmul(X, self.W) + self.B
        # Score Function 공식을 이용하였습니다.
        # 공식은 W * X 이지만, 그렇게 할 경우 하나의 case에 해당하는 Score가 열을 따라 저장되게 됩니다.
        # 그러한 경우, 공간적 비효율이 발생할 수 있어서 교과서의 공식과 살짝 다르게, 차원을 전환하였습니다.
        # 결과적으로 Y = X * W + B 공식을 구현한 것으로 볼 수 있습니다.
        return ScoreMatrix

    def Softmax(self, ScoreMatrix): # 제공.
        if ScoreMatrix.ndim == 2:
            temp = ScoreMatrix.T
            # 퀴즈1. 오버플로우 방지
            temp = temp - np.max(temp, axis=0)
            y_predict = np.exp(temp) / np.sum(np.exp(temp), axis=0)
            return y_predict.T
        temp = ScoreMatrix - np.max(ScoreMatrix, axis=0)
        expX = np.exp(temp)
        y_predict = expX / np.sum(expX)
        return y_predict

    def LossFunction(self, y_predict, Y): #  Loss Function을 구하십시오 -> 직접 작성
        # Softmax를 기반으로 loss 계산 Cross-Entropy 사용
        #3.3
        # y_predict는 Softmax function을 통해 얻은 probabilities입니다.
        # probabilities이므로 y_predict는 0에서 1 중 하나인 확률 값입니다.
        # 그러므로 y_predict는 0이거나 0에 극한값일 수 있습니다.
        # 그러나 log(0)인 경우 무한대 값으로 에러가 발생하므로, 작은 값을 넣어주어야합니다.
        # ...
        # H(p, q) = -시그마p(x)log q(x) # p : true distribution, q : estimated distribution
        # Cross-entropy 공식은 위와 같습니다. 즉, true distribution에 해당하는 Y를 곱해야합니다.
        # 공식에 대해 생각해보았습니다.
        # Y는 정답값으로 10개 클래스 중 하나를 표시하고, y_predict는 input case에 대해 10개 클래스의 Softmax의 결과 probabilities를 의미합니다.
        # 그리고 이에 대한 cross entropy 결과는 -np.log(y_predict)입니다. loss function의 목표는 cross entropy의 결과 중 실제 정답값에 해당하는 클래스의 loss값이 몇 인지를 파악하는 것입니다.
        # 즉, 모든 클래스에 대해 loss를 출력하는 y_predict.shape의 행렬에 Y를 곱함으로서, 실제 정답값에 해당하는 loss만 있는 L_i를 구할 수 있습니다.
        L_i = -np.log(y_predict+0.000000001) * Y
        # L_i는 모든 케이스에 대해 각각의 케이스의 정답 class의 cross entropy가 저장된 행렬입니다. 정답 class 외의 원소에는 0이 저장됩니다.
        # 즉, L_i는 W라는 image classifier로 모든 케이스를 분류했을 때, 각 케이스에 대해 정답 class의 loss값을 저장한 행렬이라고 할 수 있습니다.
        # LossFunction으로 구하고자 하는 값은 W라는 image classifier를 사용했을때, 평균적으로 loss가 몇이 나오는지를 의미합니다.
        # 그러므로, L_i의 모든 원소를 더한 뒤, 케이스의 갯수로 나누면 W라는 classifier를 사용했을 때, 평균적인 loss를 구할 수 있습니다.
        loss = np.sum(L_i)/np.count_nonzero(L_i)
        return loss

    def Forward(self, X, Y): # ScoreFunction과 Softmax, LossFunction를 적절히 활용해 y_predict 와 loss를 리턴시키는 함수. -> 직접 작성
        #3.4
        scoreMatrix = self.ScoreFunction(X)
        y_predict = self.Softmax(scoreMatrix)
        loss = self.LossFunction(y_predict, Y)
        # 위에 구현한 ScoreFunction은 X를 매개변수로 하며, scoreMatrix를 return합니다.
        # ScoreFunction은 각 케이스의 score를 구하는 function입니다.
        # 위에 구현한 Softmax는 scoreMatrix를 매개변수로 하며, y_predict를 return합니다.
        # Softmax는 각 케이스의 각 클래스의 softmax를 통해 얻은 probabilities를 구하는 function입니다.
        # 위에 구현한 LossFunction은 y_predict, Y를 매개변수로 하며, loss를 return합니다.
        # LossFunction은 각 케이스의 평균 loss를 구하는 function입니다.
        # Softmax를 이용해 구한 y_predict와 Lossfunction을 이용해 구한 loss를 return합니다.
        # ScoreFunction, LossFunction에 대한 설명은 위에서 했고, Softmax는 주어진 코드이므로 설명은 생략하였습니다.
        return y_predict, loss

    def delta_Loss_Scorefunction(self, y_predict, Y): # 제공.dL/dScoreFunction
        delta_Score = y_predict - Y
        return delta_Score

    def delta_Score_weight(self, delta_Score, X): # 제공. dScoreFunction / dw .
        delta_W = np.dot(X.T, delta_Score) / X[0].shape
        return delta_W

    def delta_Score_bias(self, delta_Score, X): # 제공. dScoreFunction / db .
        delta_B = np.sum(delta_Score) / X[0].shape
        return delta_B

    def numerical_gradient(self, X, Y, h=0.000001):
        # 결과를 저장할 변수입니다.
        delta_W = np.zeros(self.W.shape)
        # 변화값 측정을 위한 원본 값 계산입니다.
        # f(x)에 해당합니다.
        y_predict, loss = self.Forward(X, Y)
        # 각 원소에 대해 개별 연산을 하기 위해, 모든 원소를 탐색합니다.
        for i in range(10):
            for j in range(784):
                # h연산을 위한 임시 변수입니다.
                temp_W = self.W
                # 각 원소에 대해 +h 연산을 하여 loss를 측정합니다.
                temp_W[j][i] += h
                # 97~99줄이 f(x+h)에 해당합니다. 즉, +h 연산에 의한 변화값 계산입니다.
                temp_ScoreMatrix = np.matmul(X, temp_W) + self.B
                temp_y_predict = self.Softmax(temp_ScoreMatrix)
                temp_loss = self.LossFunction(temp_y_predict, Y)
                # numerical gradient를 이용해 구한 delta_W를 85줄에 선언한 변수에 저장합니다.
                delta_W[j][i] = (temp_loss - loss)/h
        # 각 원소에 대해 연산을 완료한 뒤, 이를 반환합니다.
        return delta_W

    # delta 함수를 적절히 써서 delta_w, delta_b 를 return 하십시오.
    def BackPropagation(self, X, y_predict, Y):
        #3.5
        delta_Score = self.delta_Loss_Scorefunction(y_predict, Y)
        delta_W = self.delta_Score_weight(delta_Score, X)
        delta_B = self.delta_Score_bias(delta_Score, X)
        # 위에 주어진 delta_Loss_Scorefunction은 y_predict, Y를 매개변수로 하여 delta_Score를 return합니다.
        # 위에 주어진 delta_Score_weight는 delta_Score, X를 매개변수로 하여 delta_W를 return합니다.
        # 위에 주어진 delta_Score_bias는 delta_Score, X를 매개변수로 하여 deltaB를 return합니다.
        # delta_Loss_Scorefunction, delta_Score_weight, delta_Score_bias는 주어진 함수이므로 설명은 생략하였습니다.
        # ...
        # BackPRopagation은 각 node의 gradient를 구하고, local gradient * upstream gradient를 구하면서 최종 노드에서 처음 노드로 역으로 계산하는 방식입니다.
        # numerical_gradient와 같은 목적이지만 훨씬 빠르고 안정적인 결과를 얻을 수 있습니다.
        # delta_W, delta_B를 return합니다.
        return delta_W, delta_B

    # 정확도를 체크하는 Accuracy 제공
    def Accuracy(self, X, Y):
        y_score = self.ScoreFunction(X)
        y_score_argmax = np.argmax(y_score, axis=1)
        if Y.ndim!=1 : Y = np.argmax(Y, axis=1)
        accuracy =100 * np.sum(y_score_argmax == Y) / X.shape[0]
        return accuracy

    # Forward와 BackPropagationAndTraining, Accuracy를 사용하여서 Training을 epoch만큼 시키고, 10번째 트레이닝마다
    # Training Set의 Accuracy 값과 Test Set의 Accuracy를 print 하십시오
    # learning_rate를 크게 잡으면, 평균에서 먼 경우에는 단번에 근접치에 다가갈 수 있지만, 근접치에 다가갈수록, 변동폭이 커져서 오히려 정확도가 낮아진다.
    def Optimization(self, X_train, Y_train, X_test, Y_test, learning_rate = 0.01, epoch=100):
        for i in range(epoch):
            #3.6
            y_predict, loss = self.Forward(X_train, Y_train)
            # BackPropagation의 매개변수로 필요한 y_predict 계산합니다.
            # loss는 현재 W의 loss값을 의미합니다.
            delta_W, delta_B = self.BackPropagation(X_train, y_predict, Y_train)
            # W와 B의 최적화를 위한 delta_W, delta_B를 BackPropagation을 이용하여 계산합니다.
            self.W = self.W - learning_rate*delta_W
            self.B = self.B - learning_rate*delta_B
            # delta_W, delta_B를 W, B에 반영합니다. 즉, W, B를 최적화합니다.
            # 이 때, 변경 폭이 너무 크지 않도록 learning_rate를 반영합니다.
            # learning_rate의 크기에 대한 이야기는 퀴즈3의 답안에서 다루도록 하겠습니다.
            #함수 작성
            if i % 10 == 0:
                Accuracy_Train = self.Accuracy(X_train, Y_train)
                Accuracy_Test = self.Accuracy(X_test, Y_test)
                # training, test data에 대한 Accuracy를 파악합니다.
                # W, B를 Optimizing함에따라 loss는 낮아지고, Accuracy는 상승합니다.
                print(i, "번째 트레이닝")
                print('현재 Loss(Cost)의 값 : ', loss)
                print("Train Set의 Accuracy의 값 : ", Accuracy_Train)
                print("Test Set의 Accuracy의 값 :", Accuracy_Test)
