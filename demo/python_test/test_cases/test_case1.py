import unittest

def add(a, b):
    return a + b


# 定义测试类
# class Test01(unittest.TestCase):
class Test01(unittest.TestCase):
    def setUp(self):
        self.a = 100
        print('setUp')
    
    def test_add(self):
        result = add(self.a, 1)
        print("结果为：", result, __name__)

    def test_add2(self):
        result = add(self.a, 2)
        print("结果为：", result, __name__)
        self.a = 200
        print('tearDown')

if __name__ == '__main__':  # 未执行的
    unittest.main()
    

