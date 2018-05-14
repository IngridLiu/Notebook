import torch
import torch.autograd as autograd
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim


training_data = [
    ("The dog ate the apple".split(), ["DET", "NN", "V", "DET", "NN"]),
    ("Everybody read that book".split(), ["NN", "V", "DET", "NN"])
]

# 构建单词的索引字典
word_to_idx = {}
tag_to_idx = {}
for sent, tags in training_data:
    for word in sent:
        if word not in word_to_idx:
            word_to_idx[word] = len(word_to_idx)
    for label in tags:
        if label not in tag_to_idx:
            tag_to_idx[label] = len(tag_to_idx)

alphabet = "abcdefghijklmnopqrstuvwxyz"
character_to_idx = {}
for i in range(len(alphabet)):
    character_to_idx[alphabet[i]] = i

# 定义字符水平的LSTM
class CharLSTM(nn.Module):
    def __init__(self, n_char, char_dim, char_hidden):
        super(CharLSTM, self).__init__()
        self.char_embedding = nn.Embedding(n_char, char_dim)
        self.char_lstm = nn.LSTM(char_dim, char_hidden, batch_first=True)

    def forward(self, x):
        x = self.char_embedding(x)
        _, h = self.char_lstm(x)
        return h[1]

#LSTM网络
class LSTMTagger(nn.Module):
    def __init__(self, n_word, n_char, char_dim, n_dim, char_hidden, n_hidden, n_tag):
        super(LSTMTagger, self).__init__()
        self.word_embedding = nn.Embedding(n_word, n_dim)
        self.char_lstm = CharLSTM(n_char, char_dim, char_hidden)
        self.lstm = nn.LSTM(n_dim, char_hidden, n_hidden, batch_first=True)
        self.linear1 = nn.Linear(n_hidden, n_tag)





