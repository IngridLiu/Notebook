# code source: https://blog.csdn.net/zzukun/article/details/49968129
# code explantation：https://cloud.tencent.com/developer/article/1113752

import copy
import numpy as np

np.random.seed(0)

# compute sigmoid nonlinearity，sigmoid是激活函数，常用激活函数sigmoid、tanh、relu，sigmoid取值范围0～1，tanh取值范围-1～1。
def sigmoid(x):
    output = 1/(1+np.exp(-x))
    return output

# convert output of sigmoid function to its derivative，声明sigmoid求导函数
def sigmoid_output_to_derivative(output):
    return output*(1-output)

# training dataset generation
int2binary = {} # 声明词典，由整型数字转成二进制，存起来不用随时计算，提前存好读取更快。
binary_dim = 8 # 声明二进制数字维度8

largest_number = pow(2, binary_dim) # 二进制能表达最大整数2^8=256，largest_number

# 预先把整数到二进制数转换词典存起来
binary = np.unpackbits(np.array([range(largest_number)], dtype=np.uint8).T, axis=1)
for i in range(largest_number):
    int2binary[i] = binary[i]


# 设置参数
alpha = 0.1 # 学习速度
input_dim = 2 # 输入层向量唯独
hidden_dim = 16 # 隐藏层向量维度，隐藏层神经元个数
output_dim = 1 # 输出层向量维度，输出一个c，是1维。

# 初始化权重
# 2x-1，np.random.random生成从0到1之间随机浮点数，2x-1使其取值范围在-1, 1。
synapse_0 = 2*np.random.random((input_dim, hidden_dim))-1
synapse_1 = 2*np.random.random((hidden_dim, output_dim))-1
synapse_h = 2*np.random.random((hidden_dim, hidden_dim))-1

# 声明三个矩阵更新
synapse_0_update = np.zeros_like(synapse_0)
synapse_1_update = np.zeros_like(synapse_1)
synapse_h_update = np.zeros_like(synapse_h)

# training logic
for j in range(10000):
    # generate a simple addition problem（a+b=c）
    a_int = np.random.randint(largest_number/2) # int version
    a = int2binary[a_int] # binary encoding

    b_int= np.random.randint(largest_number/2) # int version
    b = int2binary[a_int] # binary encoding

    # true answer
    c_int = a_int + b_int
    c = int2binary[c_int]

    # where we will store out best guess(binary encoded)
    d = np.zeros_like(c)

    # 全局误差
    overallError = 0

    # 存储第二层残差值
    layer_2_deltas = list()
    # 存储第一层（隐藏层）输出值
    layer_1_values = list()
    layer_1_values.append(np.zeros(hidden_dim))


    # 遍历二进制每一位
    # moving alone the positions in the binary encoding
    for position in range(binary_dim):
        # generate input and ouput
        X = np.array([[a[binary_dim - position - 1], b[binary_dim - position - 1]]])
        y = np.array([[c[binary_dim - position - 1]]]).T

        # hidden layer(input ~+ prev_hidden)
        layer_1 = sigmoid(np.dot(X, synapse_0)) + np.dot(layer_1_values[-1], synapse_h)

        # output layer (new binary representation
        layer_2 = sigmoid(np.dot(layer_1, synapse_1))

        # did we miss?... if so by how much?
        layer_2_error = y - layer_2
        layer_2_deltas.append((layer_2_error)*sigmoid_output_to_derivative(layer_2))
        overallError += np.abs(layer_2_error[0])

        # decode estimate so we can print it out
        d[binary_dim - position - 1] = np.round(layer_2[0][0])

        # store hidden layer so we can use it in the next timestep
        layer_1_values.append(copy.deepcopy(layer_1))

    future_layer_1_delta = np.zeros(hidden_dim)

    for position in range(binary_dim):
        X = np.array([[a[position], b[position]]])
        layer_1 = layer_1_values[-position-1]
        prev_layer_1 = layer_1_values[-position - 2]

        # error at output layer
        layer_2_delta = np.zeros(hidden_dim)

        # error at hidden layer
        layer_1_delta = (future_layer_1_delta.dot(synapse_h.T) + layer_2_delta.dot(synapse_1.T)) * sigmoid_output_to_derivative(layer_1)
        # let's update all our weights so we can try again
        synapse_1_update += np.atleast_2d(layer_1).T.dot(layer_2_delta)
        synapse_h_update += np.atleast_2d(prev_layer_1).T.dot(layer_1_delta)
        synapse_0_update += X.T.dot(layer_1_delta)

        future_layer_1_delta = layer_1_delta

    synapse_0 += synapse_0_update * alpha
    synapse_1 += synapse_1_update * alpha
    synapse_h += synapse_h_update * alpha

    synapse_0_update *= 0
    synapse_1_update *= 0
    synapse_h_update *= 0

    # print out progress
    if (j % 1000 == 0):
        print
        "Error:" + str(overallError)
        print
        "Pred:" + str(d)
        print
        "True:" + str(c)
        out = 0
        for index, x in enumerate(reversed(d)):
            out += x * pow(2, index)
        print
        str(a_int) + " + " + str(b_int) + " = " + str(out)
        print
        "------------"






