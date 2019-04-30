import numpy as np

# 퀴즈2
def one_hot_label(i):
   one_hot_label = np.array([0,0,0,0])
   one_hot_label[i]=1
   return one_hot_label

for i in range(4):
   print('input parameter = ', i, ' -> ', one_hot_label(i))
print(type(one_hot_label(0)))
