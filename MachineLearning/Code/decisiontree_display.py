from sklearn.datasets import load_iris
from sklearn import tree
import sys
import os

# 载入sklearn的自带数据集，用决策树拟合，得到模型：
iris = load_iris()
clf = tree.DecisionTreeClassifier()
clf = clf.fit(iris.data, iris.target)

# method 1
# 将模型存入dot文件iris.dot
with open("iris.dot", 'w') as f:
    f = tree.export_graphviz(clf, out_file=f)
# 注意，这个命令在命令行执行
# dot -Tpdf iris.dot -o iris.pdf


# method 2
# 用pydotplus生成iris.pdf
import pydotplus
dot_data = tree.export_graphviz(clf, out_file=None)
graph = pydotplus.graph_from_dot_data(dot_data)
graph.write_pdf("iris.pdf")

# method 3
# 把图产生在ipython的notebook
from IPython.display import Image
dot_data = tree.export_graphviz(clf, out_file=None,
                         feature_names=iris.feature_names,
                         class_names=iris.target_names,
                         filled=True, rounded=True,
                         special_characters=True)
graph = pydotplus.graph_from_dot_data(dot_data)
Image(graph.create_png())

